
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
    /** Actual address given out by the API, acts as an identifier */
    raw_pointer data;
    /** Offset in bytes from block start */
    i64 position;
    /** Absolute capaciy of this entry */
    i64 size;
    /** Actual size used by an allocated object, 0 if unallocated. */
    i64 active_size;
    /** If not 0 or 1 means the allocated object needs to be placed on a multiple address */
    i64 alignment;
    // User specified ID to disambiguate between different entries
    i32 id;
};

struct memory_heap_allocator final : i_allocator
{
    // Required for self-calls
    std::recursive_mutex lock;
    i64 max_tracked_allocations = 10000;
    allocator_info stats;

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
