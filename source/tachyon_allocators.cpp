
namespace tyon
{


CONSTRUCTOR memory_heap_allocator::memory_heap_allocator()
{
    PROFILE_SCOPE_FUNCTION();
    TYON_LOG( "New heap block" );
}

PROC memory_heap_allocator::allocate_raw( isize bytes, isize alignment ) -> raw_pointer
{
    PROFILE_SCOPE_FUNCTION();
    std::scoped_lock _lock( this->lock );
    raw_pointer result;

    // Just unpoison the part after alignment.
    // Leave the redzone poisioned
    // TODO: Allocate storage
    // TODO: Add metadata
    // TODO: Redzone
    // TODO: Trace logging

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
        raw_pointer result;
        if (bytes == 0 || reference == nullptr)
        {   TYON_ERROR( "Tried to relocate memory from nullptr or 0 width bytes" );
            return nullptr;
        }
        // TODO: Find allocated node
        // TODO: Allocate new storage
        // TODO: memcopy to new storage
        // TODO: deallocate old storage, remember redzones
        // TODO: Update metadata
        // TODO: Trace logging

        return result;
    }

    PROC memory_heap_allocator::deallocate( void* address ) -> void
    {
        PROFILE_SCOPE_FUNCTION();
        // NOTE: Passing nullptr is a valid operation, simplifies error handlig.
        if (address == nullptr) { return; }
        // TODO
       
    }

    PROC memory_heap_allocator::blank_all() -> void
    {
        PROFILE_SCOPE_FUNCTION();
        std::scoped_lock _lock( this->lock );
        // TODO
    }
    allocator_info memory_heap_allocator::get_memory_statistics()
    {
        std::scoped_lock _lock( this->lock );
        // TODO
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
