
#pragma once

namespace tyon
{

/** Temporary change the thread local allocator and restore it at end of scope.

    Can be chained within the same scopeo. */
struct push_allocator
{
    i_allocator* previous_allocator = nullptr;

    /** Only set it if passed a valid allocator */
    inline CONSTRUCTOR push_allocator( i_allocator* arg )
    {
        previous_allocator = g_allocator;
        if (arg != nullptr)
        {   g_allocator = arg; }
    }

    /** Restore the allocator */
    inline DESTRUCTOR ~push_allocator()
    {   g_allocator = previous_allocator; }
};

struct heap_entry
{
    raw_pointer data;
    i64 position;
    i64 size;
    i64 active_size;
    i64 alignment;
    // User specified ID to disambiguate between different entries
    i32 id;
};

struct memory_heap_allocator final : i_allocator
{
    // using entry
    linked_list<heap_entry> used;
    linked_list<heap_entry> free;
    array<buffer> blocks;
    // Required for self-calls
    std::recursive_mutex lock;

    CONSTRUCTOR memory_heap_allocator();

    PROC allocate_raw( isize bytes, isize alignment = 1 ) -> raw_pointer override;
    PROC allocate_raw_fast( i64 bytes, isize alignment = 1 ) -> raw_pointer override;
    // realloc compat function
    PROC allocate_relocate( void* reference, i64 bytes ) -> raw_pointer override;
    PROC deallocate( void* address ) -> void override;
    /** Clear all stored allocations and zero memory */
    PROC blank_all() -> void override;
    PROC get_memory_statistics() -> allocator_info override;
};

/** Special global thread-shared allocator */
struct memory_root_allocator
{
};

struct memory_system_allocator : i_allocator
{
    allocator_info stats;

    CONSTRUCTOR memory_system_allocator();

    PROC allocate_raw( isize bytes, isize alignment = 1 ) -> raw_pointer override;
    PROC allocate_raw_fast( i64 bytes, isize alignment = 1 ) -> raw_pointer override;
    // realloc compat function
    PROC allocate_relocate( void* reference, i64 bytes ) -> raw_pointer override;
    PROC deallocate( void* address ) -> void override;
    /** Clear all stored allocations and zero memory */
    PROC blank_all() -> void override;
    PROC get_memory_statistics() -> allocator_info override;
};

};
