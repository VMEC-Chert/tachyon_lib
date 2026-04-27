
#pragma once

namespace tyon
{

template <typename T>
struct search_result
{
    T* match = nullptr;
    i64 index = -1;
    bool match_found = false;

    /** Returns a copy of the the only match OR the specified default value */
    PROC copy_default( T default_value ) -> T
    {   return (match_found ? *match : default_value);
    }

    /** Returns a pointer to only match OR the specified default value */
    PROC allocate_default( T default_value ) -> T*
    {   if (this->match)
        {   return this->match;
        }
        T* result = memory_allocate<T>( 1 );
        *result = default_value;
        return result;
    }
};

template <typename t_key, typename t_value>
struct generic_search_result
{
    t_value* match = nullptr;
    array<t_value*> matches = nullptr;
    t_key key = {};
    bool match_found = false;
};

#if (REFLECTION_LITTLE_ENDIAN)
/** A standard rgba color container.
*/
struct rgba
{
    union {
        struct { u8 a; u8 b; u8 g; u8 r; };
        u32 hex;
    };
};
#else
struct rgba
{
    union {
        struct { u8 r; u8 g; u8 b; u8 a };
        u32 hex = 0;
    };
};
#endif // REFLECTION_LITTLE_ENDIAN
static_assert( sizeof(rgba) == 4, "Can't do packed operations if size is off" );

struct rgba_byte_ordered
{
    u8 r=0, g=0, b=0, a=0;
};
static_assert( sizeof(rgba_byte_ordered) == 4, "Can't do packed operations if size is off" );

/** Common format used internally by graphics cards / mmonitors */
struct bgra
{
    u8 b=0, g=0, r=0, a=0;
};
/** Common format used internally by graphics cards / mmonitors */
struct argb
{
    u8 b=0, g=0, r=0, a=0;
};
static_assert( sizeof(bgra) == 4, "Can't do packed operations if size is off" );

template <typename t_color_out, typename t_color_in>
PROC image_color_reorder_inplace( image<t_color_in> arg ) -> image<t_color_out>
{
    PROFILE_SCOPE_FUNCTION();
    static_assert( sizeof(t_color_in) == sizeof(t_color_in),
                   "Input and output color must bother have the same size and RGBA components" );
    static_assert( std::is_same_v<t_color_out, t_color_in> == false,
                   "Having the same input and output type both is likely a bug" );
    t_color_in temp = {};
    t_color_in* read = arg.data;
    t_color_out* write = raw_pointer( arg.data );
    i64 i_limit = arg.size_pixels();
    for (i64 i_pixel=0; i_pixel < i_limit; ++i_pixel)
    {
        temp = read[ i_pixel ];
        write[ i_pixel ].r = temp.r;
        write[ i_pixel ].g = temp.g;
        write[ i_pixel ].b = temp.b;
        write[ i_pixel ].a = temp.a;
    };
    image<t_color_out> result;
    result.data = raw_pointer(arg.data);
    result.size = arg.size;
    return result;
}

template <typename t_pixel>
PROC image_packed_from_simd( image<t_pixel> arg ) -> image<t_pixel>
{
    PROFILE_SCOPE_FUNCTION();
    image<t_pixel> result;
    if (arg.alignment == 0 && arg.stride_bytes_ == 0) { return arg; }
    i64 simd_stride = arg.stride_bytes();
    i64 width = arg.size.x;
    i64 width_bytes = width * sizeof(t_pixel);
    i64 height = arg.size.y;

    result.data = memory_allocate<t_pixel>( arg.size_pixels() );
    result.size = arg.size;

    raw_pointer read_start = arg.data;
    raw_pointer readhead = arg.data;
    t_pixel* writehead = result.data;
    for (i64 i_y=0; i_y < height; ++i_y)
    {
        // Copy a row at a time to the new buffer
        readhead = read_start + (i_y * simd_stride);
        writehead = result.data + (i_y * width);
        memory_copy_raw( writehead, readhead, width_bytes );
    }
    return result;
}

PROC image_color_reorder_inplace_u8_bgra_rgba( image<rgba> arg ) -> image<bgra>;

template <typename T>
struct array
{
    using t_self = array<T>;
    pointer<T> data = nullptr;
    isize size_ = 0;
    isize head = 0;
    isize head_size = 0;
    bool bounded = true;
    // Enforce RAII
    bool autofree = true;

    /** Default Constructor */
    CONSTRUCTOR array() {}

    CONSTRUCTOR array( std::initializer_list<T> arg )
    {
        this->change_allocation( arg.size() );
        head_size = arg.size();
        isize i = 0;
        for (auto x : arg ) { data[i] = x; ++i; }
        ERROR_GUARD( i <= this->size_,
                     "Index overran initializer list, memory is likely corrupted" );
    }

    CONSTRUCTOR array( std::vector<T>& arg )
    {
        this->change_allocation( arg.size() );
        head_size = arg.size();
        isize i = 0;
        for (auto x : arg )
        {   data[i] = x; ++i;
        }
        ERROR_GUARD( i <= this->size_,
                     "Index overran initializer list, memory is likely corrupted" );
    }

    bool
    change_allocation( i_memory_allocator* allocator, isize count )
    {
        data.allocator_set( allocator );
        return change_allocation( count );
    }

    /** Reallocates data into new storage and default constructs objects

        it uses the storage allocator, or 'g_allocator' if none is provided
    */
    bool
    change_allocation( isize count )
    {
        i_memory_allocator* allocator = (data.allocator() ? data.allocator() : g_allocator);
        T* new_storage = allocator->allocate_raw( count * sizeof(T), alignof(T) );
        ERROR_GUARD( new_storage != nullptr, "Allocation failed" );
        // TODO: Does this really make sense to placement new the full range?
        // This could just be the active range
        new(new_storage) T[count] {};
        if (data)
        {
            for (i32 i=0; i < std::min( size(), count ); ++i )
            {
                new_storage[i] = std::move( data[i] );
                std::destroy_at( &this->data[i] );
            }
            allocator->deallocate( (void*)(data) );
        }
        if (new_storage)
        {
            data.data = new_storage;
            data.size_ = count;
            size_ = count;
            head = std::min( head, count );
            head_size = std::min( head_size, count );
        }
        else
        { return false; }
        // ERROR_GUARD( size_ > 100'000'000'000 || size_ < 0, "Bogus data" );
        // ERROR_GUARD( head_size > 100'000'000'000 || head_size < 0, "Bogus data" );
        // ERROR_GUARD( head > 100'000'000'000 || head < 0, "Bogus data" );
        return true;
    }

    bool
    change_allocation_raw( isize count )
    {
        i_memory_allocator* allocator = (data.allocator ? data.allocator : g_allocator);
        T* new_storage = allocator->allocate_raw( count * sizeof(T), alignof(T) );
        ERROR_GUARD( new_storage != nullptr, "Allocation failed" );
        if (data)
        {
            memory_copy( new_storage, data.data, std::min( size_, count ) );
            allocator->deallocate( data );
        }
        if (new_storage)
        {
            data = new_storage;
            size_ = count;
            head = std::min( head, count );
            head_size = std::min( head_size, count );
        }
        else
        { return false; }
        return true;
    }

    bool
    FUNCTION allocate( i_memory_allocator* allocator, isize count )
    {
        // TODO: BROKEN
        data = allocator->allocate_raw( count * sizeof(T) );
        size_ = count;
        head_size = std::min( head_size, count );
        return (data != nullptr);
    }

    template<typename t_allocator>
    bool
    FUNCTION deallocate( t_allocator* allocator )
    {
        allocator->deallocate( data );
        size_ = 0;
        head_size = 0;
        head = 0;

        return true;
    }

    /// Pushes an new before the 'head' index and decrements the 'head'
    bool
    FUNCTION push_head( T item )
    {
        if (bounded && (head <= 0)) { return false; }
        data[ --head ] = item;
        ++head_size;
        return true;
    }

    /// Pushes a new item at off the tail (head + head_size) and increments 'head_size'
    T&
    FUNCTION push_tail( T& item )
    {
        if (bounded && (head + head_size >= size_))
        {
            // Greedy, 2x allocation
            bool resize_ok = change_allocation( std::max<isize>(size_, 1) * 2 );
            ERROR_GUARD( resize_ok, "Serious error has occured if a resize failed" );
        }
        i64 index = head + (head_size++);
        data[ index ] = item;
        return data[ index ];
    }

    T&
    FUNCTION push_tail( T&& item )
    {
        if (bounded && (head + head_size >= size_))
        {
            // Greedy, 2x allocation
            bool resize_ok = change_allocation( std::max<isize>(size_, 1) * 2 );
            ERROR_GUARD( resize_ok, "Serious error has occured if a resize failed" );
        }
        i64 index = head + (head_size++);
        data[ index ] = item;
        return data[ index ];
    }

    /// Pushes a new item at off the tail (head + head_size) and increments 'head_size'
    bool
    FUNCTION push_tail_unbounded( T item )
    {
        ERROR_GUARD(head + head_size < size_, "Tried to push outside of allocated capacity" );
        if (bounded && (head + head_size >= size_))
        { return false; }
        data[ head + (head_size++) ] = item;
        return true;
    }

    T
    FUNCTION pop_head()
    {
        if (bounded && (head_size == 0)) { return false; }
        T result = data[ head++ ];
        --head_size;
        return result;
    }

    T
    FUNCTION pop_tail()
    {
        if (bounded && (head_size == 0)) { return {}; }
        T result = data[ head + head_size - 1 ];
        --head_size;
        return result;
    }

    T&
    FUNCTION tail()
    { return data[ head+head_size -1 ]; }

    T*
    tail_address()
    { return (data.get() + (head+head_size -1)); }

    PROC tail_index() -> i64
    { return (head+head_size -1); }

    T&
    operator []( isize i )
    {
        ERROR_GUARD( (i >= 0) || (i < size_), "Tried to access index ouside of bounds" );
        return data[std::clamp<i64>( i, 0, size_ )];
    }

    T&
    operator []( isize i ) const
    {
        ERROR_GUARD( (i >= 0) || (i < size_), "Tried to access index ouside of bounds" );
        return data[std::clamp<i64>( i, 0, size_ )];
    }

    PROC address( isize i ) -> T*
    {
        ERROR_GUARD( (i >= 0) || (i < size_), "Tried to access index ouside of bounds" );
        return (T*)(data + std::clamp<i64>( i, 0, size_ ));
    }

    t_self&
    COPY_ASSIGNMENT operator= ( const t_self& rhs )
    {
        // Make sure we leave good data for before trying to use copy operators...
        // This flagged up as a major issue with std::string usage
        // I tried to call reset() here but its redundant as change_allocation() will init anew.
        this->cleanup();
        this->head_size = rhs.head_size;
        this->change_allocation( rhs.size_ );
        for (i64 i=0; i < rhs.head_size; ++i )
        {
            data[i] = rhs.data[i];
        }
        return *this;
    }

    /// Set memory of array to read only and employ data integrity checks
    void
    FUNCTION protect()
    {
        // Crash
        TYON_BREAK();
    }

    /** Zero from 0 to 'head_size' memory and set head and tail to zero. */
    void
    reset()
    {
        // Default init old
        new(data) T[head_size]{};
        head_size = 0;
    }

    void
    clear()
    {
        // Default init old
        new(data) T[size_]{};
    }

    // std::vector compat
    void
    FUNCTION push_back( T& item )
    {
        push_tail( item );
    }

    void
    FUNCTION push_back( T&& item )
    {
        push_tail( std::move( item ) );
    }

    PROC resize( usize count )
    {
        change_allocation( isize(count) );
        head_size = count;
    }

    void
    FUNCTION reserve( usize count )
    {
        change_allocation( isize(count) );
    }

    /* NOTE: I tried to make this compatible with vector containers using
       usize. But now I realize I actually just don't want to have compat with
       that stuff. And it complicates my code by having signed compare warnings.
       Which I don't care for. */
    isize
    FUNCTION size()
    {   return head_size; }

    PROC back() -> T&
    {
        this->tail();
    }
    // -- End of std::vector compat

    template <typename t_proc>
    PROC map_procedure( t_proc&& arg ) -> void
    {
        for (i64 i=0; i < size(); ++i)
        {   arg( data[i] );
        }
    }

    /** Same as map_procedure by provides the index argument */
    template <typename t_proc>
    PROC map_procedure_indexed( t_proc&& arg  ) -> void
    {
        for (i64 i=0; i < size(); ++i)
        {   arg( data[i], i );
        }
    }

    // Search from 0 to 'size'
    template <typename t_single_comparison>
    search_result<T>
    FUNCTION linear_search( t_single_comparison comparator )
    {
        search_result<T> result;
        for (i64 i=0; i < size(); ++i)
        {
            if (comparator( data[i] ))
            {
                result.match = &(data[i]);
                result.index = i;
                result.match_found = true;
                break;
            }
        }
        if (result.match_found == false)
        {   result.index = -1; }
        return result;
    }

    // Search from 0 to 'size'
    search_result<T>
    FUNCTION linear_search_value( T comparison )
    {
        search_result<T> result;
        for (i64 i=0; i < size(); ++i)
        {
            if (comparison ==data[i])
            {
                result.value = &(data[i]);
                result.index = i;
                result.match_found = true;
                break;
            }
        }
        return result;
    }

    // Search from head to tail
    search_result<T>
    FUNCTION linear_search_head( generic_procedure<bool(T&)> comparator )
    {
        search_result<T> result;
        for (i64 i=head; i < head_size; ++i)
        {
            if (comparator( data[i] ))
            {
                result.value = &(data[i]);
                result.index = i;
                result.match_found = true;
                break;
            }
        }
        return result;
    }

    // Search from head to tail
    search_result<T>
    FUNCTION linear_search_head_value( T comparison )
    {
        search_result<T> result;
        for (i64 i=head; i < head_size; ++i)
        {
            if (comparison == data[i])
            {
                result.value = &(data[i]);
                result.index = i;
                result.match_found = true;
                break;
            }
        }
        return result;
    }

    void
    cleanup()
    {
        i64 array_limit = (1ll << 50);
        i64 start_i = this->head;
        i64 end_i = ((head + head_size < array_limit) ? (head + head_size) : array_limit );
        if (head + head_size > array_limit) [[unlikely]]
        {   TYON_ERRORF( "Tried to traverse unrealistically large {} entries, leaking resources. {}",
                         head_size, uid("199f1e05-1b40-4896-8a30-07de6534309f"_uuid) );
            return;
        }

        for (i64 i=start_i; i < end_i; ++i )
        {   this->data[i].~T(); }
        // C++17 alternative
        // std::destroy_n( this->data, this->head_size );
    }

    DESTRUCTOR ~array()
    {
        if (this->autofree) { this->cleanup(); }
    }

    struct stl_iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = i64;
        using value_type        = T;
        using pointer           = T*;  // or also value_type*
        using reference         = T&;  // or also value_type&
        using t_self = stl_iterator;
        using t_context = array<value_type>*;

        t_context context = nullptr;
        pointer data = nullptr;
        difference_type offset = 0;

        CONSTRUCTOR stl_iterator() = default;
        CONSTRUCTOR stl_iterator( t_context arg1, pointer arg2, difference_type arg3 ) :
            context(arg1), data(arg2), offset(arg3) {}
        CONSTRUCTOR stl_iterator( const t_self& arg )
        {
            context = arg.context;
            data = arg.data;
            offset = arg.offset;
        }

        reference operator *() { return *(data +offset); }
        pointer operator->() { return (data +offset); }

        // PROC operator= ( t_self rhs ) -> t_self&
        // {
        //     context = rhs.context;
        //     data = rhs.data;
        //     offset = rhs.offset;
        //     return (*this);
        // }

        COPY_CONSTRUCTOR PROC operator= ( const t_self& rhs ) -> t_self&
        {
            context = rhs.context;
            data = rhs.data;
            offset = rhs.offset;
            return (*this);
        }

        friend
        PROC operator+ ( t_self& lhs, difference_type& rhs ) -> t_self
        {
            t_self result = (lhs);
            result.offset += rhs;
            return result;
        }

        friend
        PROC operator+ ( difference_type& lhs, t_self& rhs ) -> t_self
        {   t_self result = rhs;
            rhs.offset += lhs;
            return result;
        }

        PROC operator+= ( difference_type arg_offset ) -> t_self&
        {   offset += arg_offset;
            return *this;
        }

        PROC operator- ( difference_type arg_offset ) -> t_self
        {
            t_self result = (*this);
            result.offset -= arg_offset;
            return result;
        }

        PROC operator- ( t_self rhs ) -> t_self
        {
            t_self result = (*this);
            result.offset -= rhs.offset;
            return result;
        }

        friend
        PROC operator- ( difference_type& lhs, t_self& rhs ) -> difference_type
        {   return (lhs - rhs.offset);
        }

        PROC operator-= ( difference_type arg_offset ) -> t_self&
        {   return (*this) += (-arg_offset); }

        PROC operator[]( difference_type arg_offset ) -> t_self&
        {   offset += arg_offset;
            return *this;
        }

        stl_iterator& operator++() { ++offset; return *this; }
        stl_iterator operator++(int)
        {
            stl_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        stl_iterator& operator--() { --offset; return *this; }
        stl_iterator operator--(int)
        {
            stl_iterator tmp = *this;
            --(*this);
            return tmp;
        }
        friend bool operator==( stl_iterator& rhs, stl_iterator& lhs )
        { return rhs.offset == lhs.offset; }

        friend bool operator!=( stl_iterator& rhs, stl_iterator& lhs )
        { return rhs.offset != lhs.offset; }

        /** True iterator if has not reached passed tail index. End iterators
         * are invalid to dereference */
        operator bool() { return (offset < context->head_size); }
    };

    using iterator = stl_iterator;
    stl_iterator begin() { return stl_iterator{ this, data.data, 0 }; }
    stl_iterator end() { return stl_iterator{ this, data.data, head_size }; }
};


template <typename T>
struct node_link
{
    i64 index = -1;
    i64 prev = -1;
    i64 next = -1;
    T value {};
};

template <typename T>
struct linked_list
{
    using t_self = linked_list<T>;
    using t_node = node_link<T>;
    array< t_node > nodes;
    // The index of the first node in the list
    i64 head_ = -1;
    // The index of the last node in the list
    i64 tail_ = -1;
    // The length of the list from head to tail
    isize list_size = 0;

    PROC resize( isize count )
    {   nodes.resize( count ); }

    PROC size_grow( isize count )
    {
        nodes.resize( nodes.size() + count );
    }

    PROC push_tail( T arg ) -> t_node*
    {
        t_node* new_node = &nodes.push_tail( {} );
        new_node->index = nodes.size() - 1;
        new_node->value = arg;

        bool no_tail = (this->tail_ < 0);
        bool no_head = (this->head_ < 0);
        if (no_tail)
        {   head_ = new_node->index;
            tail_ = head_;
        }
        new_node->prev = tail_;
        tail_ = new_node->index;

        // Make sure 'prev' of first node doesn't point to anything
        if (no_head)
        {   new_node->prev = -1;
        }
        bool prev_exists = (new_node->prev >= 0);
        if (prev_exists)
        {   nodes[ new_node->prev ].next = new_node->index;
        }

        ++list_size;
        return new_node;
    }

    PROC pop_tail( T arg )
    {
        monad<t_node> result;
        // return error on bad invalid tail but let the last value pop off
        if (tail_ < 0)
        { result.error = true; return result; }

        result.index = -1;
        result.value = nodes[ tail_ ];
        // nullify tail so it can be detected as an unused node
        tail() = {};
        nodes.head_size--;

        ERROR_GUARD( (head_ == -1 && tail_ == -1) || (head_ = -1 && tail_ == -1) ||
                     (head_ >= 0 && tail_ >= 0),
                     "Probably a bug if these tests fail" );
        return result;
    }

    PROC
    insert_after( t_node* target_node, T value ) -> t_node*
    {
        ERROR_GUARD( (target_node >= nodes.address(0)) && (target_node <= nodes.address( nodes.size_ )),
                     "A node from outside this container has been used as an argument" );
        t_node* new_node = &nodes.push_tail( {} );
        // Set index before proceeding
        new_node->index = list_size;
        if (target_node->next >= 0)
        {   t_node& next_node = nodes[ target_node->next ];
            next_node.prev = new_node->index;
        }
        new_node->next = target_node->next;
        new_node->prev = target_node->index;
        target_node->next = new_node->index;
        new_node->value = value;
        ++list_size;
        if (target_node->index == tail_)
        {   tail_ = new_node->index;
        }

        return new_node;
    }
    PROC
    insert_before( t_node* target_node, T value ) -> t_node*
    {
        ERROR_GUARD( (target_node >= nodes.address(0)) && (target_node <= nodes.address( nodes.size_ )),
                     "A node from outside this container has been used as an argument" );
        t_node* new_node = &nodes.push_tail( {} );
        // Set index before proceeding
        new_node->index = list_size;

        if (target_node->prev >= 0)
        {   t_node& prev_node = nodes[ target_node->prev ];
            prev_node.next = new_node->index;
        }
        new_node->prev = target_node->prev;
        new_node->next = target_node->index;
        target_node->prev = new_node->index;
        new_node->value = value;
        ++list_size;
        if (target_node->index == head_)
        {   head_ = new_node->index;
        }
        return new_node;
    }


    PROC remove_node( t_node* arg ) -> void
    {
        ERROR_GUARD( (arg >= nodes.address(0)) && (arg <= nodes.address( nodes.size_ )),
                     "A node from outside this container has been used as an argument" );
        bool prev_valid = (arg->prev >= 0);
        bool next_valid = (arg->next >= 0);
        i64 next_of = arg->next;
        i64 prev_of = arg->prev;
        if (prev_valid && next_valid)
        {   // pass old references to prev and next
            // 1 - 2 - 3
            // 1 next   <-prev 3
            // 1 next->   prev 3
            nodes[ arg->prev ].next = next_of;
            nodes[ arg->next ].prev = prev_of;
        }
        else if (prev_valid)
        {   // Only prev, no next node, nullify that reference and make it the tail
            tail_ = arg->prev;
            nodes[ arg->prev ].next = -1;
        }
        else if (next_valid)
        {   // Only next, no prev node, nullify that reference and make it the head
            head_ = next_of;
            nodes[ next_of ].prev = -1;
        }

        // Clear node to made node detected as empty
        *arg = {};
        arg->prev = -1;
        arg->next = -1;

        // ai marked as bad
        // nodes.head_size--;
        list_size--;
        ERROR_GUARD( (head_ == -1 && tail_ == -1) || (head_ == -1 && tail_ == -1) ||
                     (head_ >= 0 && tail_ >= 0),
                     "Wut" );
    }

    /** LOOKING links in node order from head to tail */
    PROC operator [] ( isize arg ) -> monad<t_node*>
    {
        monad<t_node*> result;
        t_node* x_node = &nodes[ head_ ];
        if ( head_ < 0 || arg > list_size)
        {   result.error = true;  return result; }

        for (isize i=0; i < arg; ++i)
        {
            ERROR_GUARD( x_node->next >= 0, "Broken link is indicative of a logic issue" );
            x_node = &nodes[ x_node->next ];
        }
        result.value = x_node;
        return result;
    }

    PROC head() -> t_node*
    {   return &nodes[ head_ ]; }

    PROC tail() -> t_node*
    {   return &nodes[ tail_ ]; }

    // TODO: Indexer is bugged, I cant' for the life of me figured out why, some kind off by one error
    struct indexer
    {
        /** What index in the container the current value is */
        isize index = 0;
        isize iteration = 0;
        t_self* context;
        t_node* value = nullptr;
        isize range_min = 0;
        isize range_max = 0;
        bool do_iteration = false;

        /** Returns true if this iteration should be used */
        PROC forward() -> fresult
        {
            bool next_invalid = (value->next < 0);
            do_iteration = (index < range_max);
            if (do_iteration && next_invalid)
            {   TYON_ERROR( "Container must be broken if the current node is negative" );
                TYON_BREAK();
            }
            if (next_invalid == false)
            {   value = &context->nodes[ value->next ];
            }
            index += 1;
            iteration += 1;
            return do_iteration;
        }

        /** Returns true if this iteration should be used */
        PROC backward() -> fresult
        {
            bool prev_invalid = (value->prev < 0);
            do_iteration = (index > range_min);
            if (do_iteration && prev_invalid)
            {   TYON_ERROR( "Container must be broken if the prev node is negative" );
                TYON_BREAK();
            }
            if (do_iteration)
            {   value = &context->nodes[ value->prev ];
            }
            index -= 1;
            iteration += 1;
            return do_iteration;
        }

        PROC operator == ( indexer& rhs ) -> bool
        {   return this->value->value == rhs.value; }

    };

    /** Uses exact inclusive range

        returns an invalid iterator on invalid range */
    PROC indexer_ranged( isize min = 0, isize max = 0 ) -> indexer
    {
        indexer result;
        // Flag an error is max is outsize of 'list_size' or 'head' is nullptr
        // Uses inclusive max
        if (min < 0 || max < 0 || max > list_size || min > max || head_ < 0) { return result; }

        result = indexer {
            .index = min,
            .context = this,
            .value = (*this)[min].copy_default({}),
            .range_min = min,
            .range_max = max,
            .do_iteration = true
        };
        return result;
    }

    /** index the full range of the container from head to tail

        returns an invalid iterator on invalid range */
    PROC indexer_full() -> indexer
    {
        return indexer_ranged( 0, list_size -1 );
    }

};

template <typename T>
struct dynamic_span
{
    T* data;
    i64 size;
};

struct string
{
    using t_self = string;
    using t_char = char;

    i64 size_ = 0;
    array< dynamic_span<t_char> > parts;

    // TODO: We will have to do hashing for each individual at some point (performance optimization).
    // minihash hash;

    COPY_CONSTRUCTOR string() = default;
    COPY_CONSTRUCTOR string( const t_self& arg );
    COPY_CONSTRUCTOR string( fstring& arg );
    /** Measures the size of a cstring and creates a sized string minus the null terminator
     The string is null terminated by it is not included in the size. */
    COPY_CONSTRUCTOR string( cstring arg );

    inline
    PROC size() const -> i64
    {   return size_; }

    /** Should really be count but whatever */
    inline
    PROC parts_size() const -> i64
    { return parts.head_size; }

    PROC append( fstring arg ) -> string&;
    PROC operator += ( fstring rhs ) -> string&;
    operator fstring();

    // SECTION: Immutable functions
    PROC split_whitespace() const -> string;
    PROC join_parts( fstring_view connector ) const -> string;

};

template <typename T>
struct ntree_node
{
    // uid id;
    ntree_node* parent;
    array< ntree_node<T>*> children;
    T value;

};

template <typename T>
struct n_tree
{
    using node = ntree_node<T>;
    node* data;
    isize size;
    // The absolute parent of all, might be imaginary
    node* root_node;
    // Where this particular tree starts from, doesn't change anything, just convenience
    node* start_node;
    i32 max_depth;
    i32 max_breadth;

    DESTRUCTOR ~n_tree()
    {
        for (i32 i=0; i < this->size; ++i)
        {
            // this->data[i].children.deallocate();
        }
    }
};


}
