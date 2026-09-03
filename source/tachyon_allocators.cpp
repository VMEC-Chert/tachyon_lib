
namespace tyon
{


CONSTRUCTOR memory_heap_allocator::memory_heap_allocator()
{
    PROFILE_SCOPE_FUNCTION();
    TYON_LOG( "New heap block" );
    buffer* block = &blocks.push_tail( {} );
    block->data = malloc( 400_MiB );
    block->size = 400_MiB;

    used.resize( max_tracked_allocations + 16 );
    free.resize( max_tracked_allocations + 16 );
}

PROC memory_heap_allocator::allocate_raw( isize bytes, isize alignment ) -> raw_pointer
{
    PROFILE_SCOPE_FUNCTION();
    std::scoped_lock _lock( this->lock );
    bool exceeded_trackable_allocations = (used.list_size >= max_tracked_allocations);
    if (exceeded_trackable_allocations)
    {
        TYON_ERRORF( "Exceeded trackable allocations {}", used.list_size );
        return {};
    };

    buffer* block = blocks.tail_address();
    bool add_block = (block->head_size + bytes + alignment > block->size);
    if (add_block)
    {
        TYON_LOG( "New heap block" );
        buffer new_block {};
        new_block.data = malloc( 400_MiB );
        new_block.size = std::max( 400_MiB, bytes + 100_MiB );

        if (new_block.data == nullptr)
        {   return nullptr; }
         &blocks.push_tail( new_block );
         free.push_tail( heap_entry {
                 .data = new_block.data,
                 .position = 0,
                 .size = new_block.size,
                 .alignment = 0,
                 .id = 0
             });
    }
    block = blocks.tail_address();

    // node_link<heap_entry>* new_node = used.push_tail( {} );
    i64 i_limit = free.size();
    node_link<heap_entry>* x_node = free.head();
    node_link<heap_entry>* found_node = nullptr;
    i64 next_i = linked_list_sentinel;
    i64 aligned_size = 0;
    i64 padding = 0;
    bool enough_bytes = false;

    // Try to find an entry that has enoguh space
    for (i32 i=0; i < i_limit; ++i)
    {
        padding = memory_padding( aligned_size, x_node->value.data );
        aligned_sized = (bytes + padding);
        enough_bytes = (x_node->size >aligned_sized);
        if (enough_bytes)
        {   found_node = x_node;
            break;
        }
        next_i = x_node->next;
        x_node = free_nodes.nodes[ i_next ].value;
    }
    if (found_node == false)
    {
        TYON_ERRORF( "Failed to find free node of aligned size {}", aligned_size );
        return nullptr;
    }

    /** Okay we have enough space now we need to fill out allocation information
        and calculate a usable address */
    new_node = used.push_tail( x_node );
    new_node->active_size = aligned_size;
    new_node->address = (block->data + padding);
    node_node->alignment = alignment;

    heap_entry* entry = &new_node->value;
    isize alignment_bytes = memory_padding( alignment, block->data + block->head_size );
    const i64 redzone_min_size = 64;
    isize redzone_size = redzone_min_size + memory_padding(
        alignment,
        (block->data + block->head_size + alignment + redzone_min_size)
    );
    isize used_bytes = (alignment_bytes + bytes + redzone_min_size);
    raw_pointer result = (block->data + block->head_size + alignment_bytes);

    *entry = heap_entry {
        .data = result,
        .position = block->head_size,
        .size = used_bytes,
        .active_size = bytes,
        .alignment = alignment,
        .id = 0
    };

    // Just unpoison the part after alignment.
    // Leave the redzone poisioned
    memory_unpoison( result, bytes );
    block->head_size += used_bytes + 100;
    // Debug tracing
    TYON_LOGF( "address {} bytes {} alignment {} block_size {} head_size {}",
               (void*)entry->data, entry->size, entry->alignment, block->size, block->head_size );

    return result;
}

    PROC memory_heap_allocator::allocate_raw_fast( i64 bytes, isize alignment ) -> raw_pointer
    {
        PROFILE_SCOPE_FUNCTION();
        std::scoped_lock _lock( this->lock );
        return nullptr;
    }

    PROC memory_heap_allocator::allocate_relocate( void* reference, i64 bytes ) -> raw_pointer
    {
        PROFILE_SCOPE_FUNCTION();
        std::scoped_lock _lock( this->lock );

        heap_entry x_entry {};
        node_link<heap_entry>* x_node = used.head();
        bool match = false;
        const i32 node_limit = 100'000;
        i32 i = 0;
        for (; i < node_limit; ++i)
        {
            x_entry = x_node->value;
            if (x_entry.data == reference)
            { match = true; break; }

            // DEBUG: Really really slow
            // TYON_LOGF( "Checking entry with address {} bytes {}",
                       // (void*)(x_entry.data), x_entry.size );
            if (x_node->next == linked_list_sentinel)
            {   break; }
            x_node = &used.nodes[ x_node->next ];
        }
        if (match == false)
        {
            TYON_ERROR( "Serious allocation failiure reallocating memory" );
            TYON_ERRORF( "Could not find entry associated with addres: {}\n"
                         "bytes: {}\n"
                         "iterations: {}",
                         reference, bytes, i );
            TYON_BREAK();
            return nullptr;
        }

        // Move entry to free list
        // NOTE: Do this before allocating to prevent pointer invalidation
        // free.push_tail( x_entry );
        used.remove_node( x_node );

        // Allocate new storage
        raw_pointer result = this->allocate_raw( bytes );
        /* Move data to new memory
           Normal reallocation APIs specifies the size may be smalelr than normal.
           So we have to copy only everything up to that point. */
        i64 copy_bytes = std::min( x_entry.active_size, bytes );
        memory_copy_raw( result, x_entry.data, copy_bytes );
        // Debug tracing
        /* TYON_LOGF( "Copying bytes for reallocation: {:<10}", x_entry.active_size ); */

        return result;
    }

    PROC memory_heap_allocator::deallocate( void* address ) -> void
    {
        PROFILE_SCOPE_FUNCTION();
        // NOTE: Passing nullptr is a valid operation, simplifies error handlig.
        if (address == nullptr) { return; }

        std::scoped_lock _lock( this->lock );
        // Debug tracing
        TYON_LOGF( "Deleted heap pointer {}", (void*)address );

        heap_entry x_entry {};
        node_link<heap_entry>* x_node = used.tail();
        bool match = false;
        i64 index = 0;
        i64 size = used.nodes.size();
        for (i64 i=0; i < size; ++i)
        {
            // Reverse walk to take advantage of allocation recency
            index = (size - 1 - i);
            x_node = &used.nodes[ index ];
            x_entry = x_node->value;
            if (x_entry.data == address)
            { match = true; break; }
        }
        if (match == false)
        {   TYON_ERRORF( "Could not find entry associated with addres: {}", address );
            return;
        }

        // Move entry to free list
        free.push_tail( x_entry );
        used.remove_node( x_node );
    }

    PROC memory_heap_allocator::blank_all() -> void
    {
        PROFILE_SCOPE_FUNCTION();
        std::scoped_lock _lock( this->lock );
    }
    allocator_info memory_heap_allocator::get_memory_statistics()
    {
        std::scoped_lock _lock( this->lock );
        return {};
    }

    CONSTRUCTOR memory_system_allocator::memory_system_allocator()
    {
        PROFILE_SCOPE_FUNCTION();
    }

    PROC memory_system_allocator::allocate_raw( isize bytes, isize alignment ) -> raw_pointer
    {
        PROFILE_SCOPE_FUNCTION();
        stats.churn++;
        stats.churn_bytes += bytes;
        stats.user_allocated += bytes;
        return malloc( bytes );
    }

    PROC memory_system_allocator::allocate_raw_fast( i64 bytes, isize alignment ) -> raw_pointer
    {
        PROFILE_SCOPE_FUNCTION();
        stats.churn++;
        stats.churn_bytes += bytes;
        stats.user_allocated += bytes;
        return malloc( bytes );
    }

    // realloc compat function
    PROC memory_system_allocator::allocate_relocate( void* reference, i64 bytes ) -> raw_pointer
    {
        PROFILE_SCOPE_FUNCTION();
        TYON_BREAK();
        return nullptr;
    }

    PROC memory_system_allocator::deallocate( void* address ) -> void
    {
        PROFILE_SCOPE_FUNCTION();
        free( address );
    }

    /** Clear all stored allocations and zero memory */
    PROC memory_system_allocator::blank_all() -> void
    {
        PROFILE_SCOPE_FUNCTION();
        TYON_BREAK();
    }

    PROC memory_system_allocator::get_memory_statistics() -> allocator_info
    {   return stats; }

}
