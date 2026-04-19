
#include "include_tachyon_lib_core.h"

namespace tyon
{

    COPY_CONSTRUCTOR string::string( const t_self& arg )
    {
        parts = {};
        size_ = 0;
        i64 i_limit = arg.parts.head_size;
        parts.resize( i_limit );
        dynamic_span<char> x_part;
        dynamic_span<char>* x_new_part = nullptr;

        // Copy all parts across
        for (i64 i=0; i < i_limit; ++i)
        {
            x_new_part = this->parts.address(i);
            x_part = arg.parts[i];

            x_new_part->data = memory_allocate<t_char>( x_part.size );
            x_new_part->size = x_part.size;
            memory_copy<t_char>( x_new_part->data, x_part.data, x_part.size );
        }
    }

    COPY_CONSTRUCTOR string::string( fstring& arg )
    {
        parts = {};
        size_ = 0;
        parts.resize( 1 );

        dynamic_span<t_char>& new_part = parts[0];
        new_part.size = memory_align( arg.size(), 4 );
        new_part.data = memory_allocate<t_char>( parts[0].size );
        memory_copy<t_char>( new_part.data, arg.data(), arg.size() );
    }

    COPY_CONSTRUCTOR string::string( cstring arg )
    {
        parts = {};
        size_ = 0;
        parts.resize( 1 );

        i64 max_string_size = 1_GiB;
        i64 size = 0;
        // NOTE: Tried to use if (arg[size] == 0) { break; } in a normal for
        // loop but that lead to including the null terminator in the size
        bool null_terminator = false;
        for (;size < max_string_size; )
        {   null_terminator = (arg[size] == char(0));
            if (null_terminator) { break; }
            ++size;
        }

        dynamic_span<t_char>& new_part = parts[0];
        new_part.size = memory_align( size, 4 );
        // Add extra null termination
        new_part.data = memory_allocate<t_char>( parts[0].size + 4 );
        memory_copy<t_char>( new_part.data, arg, size );
    }

    PROC string::append( fstring arg ) -> string&
    {
        dynamic_span<char> message;
        message.size = arg.size();
        message.data = memory_allocate<char>( message.size + 1);
        parts.push_tail( message );
        memory_copy_raw( message.data, arg.data(), message.size );
        size_ += message.size;

        return *this;
    }

    PROC string::operator += ( fstring rhs ) -> string&
    {
        this->append( rhs );
        return *this;
    }

    string::operator fstring()
    {
        PROFILE_SCOPE_FUNCTION();
        fstring result;
        result.reserve( size_ );
        dynamic_span<char> x_part;
        for (i64 i=0; i < parts.head_size; ++i)
        {
            x_part = parts[i];
            result.append( x_part.data, x_part.size );
        }
        return result;
    }

    PROC string::split_whitespace() const -> string
    {
        // It's more code to work on a multi-part string so we'll join it first.
        string result = this->join_parts( "" );
        dynamic_span<char> str = result.parts[0];

        /** State Varients
            first char non-space - in_whitespace 0 | i_part_start 0
            first char space - in_whitespace 0 | i_part_start 0
         */
        // Loop state
        bool in_whitespace = false;
        // Have we started recording the size of a part
        bool start_recorded = false;
        // Start index of a new string
        i64 i_part_start = 0;
        i64 i_limit = str.size;
        i32 x_char = 0;
        dynamic_span<char> new_part;
        for (i64 i=0; i < i_limit; ++i)
        {
            x_char = str.data[i];
            bool end_string = (! std::isspace( x_char ) && start_recorded);
            if (end_string)
            {
                in_whitespace = true;
                // Create new string part
                new_part.size = (i - i_part_start + 1);
                new_part.data = memory_allocate<t_char>( new_part.size + 4);
                memory_copy<t_char>( new_part.data, str.data + i_part_start, new_part.size );
                // Reset part
                new_part = {};
            }
            else if (start_recorded == false)
            {

            }
        }

        return {};
    }

    PROC string::join_parts( fstring_view connector ) const -> string
    {
        string result;

        i64 connector_size = connector.size();
        // Size of all parts + connector + some arbitrary SIMD padding / null termination
        i64 allocation = (result.size_ + (connector_size * result.parts_size()) + 12);
        t_char* storage = memory_allocate<t_char>( allocation );

        if (storage == nullptr) { return string{}; }

        result.parts.resize( 1 );
        result.size_ = allocation;
        // Collapse on 0 size if something went wrong
        result.parts[0] = { storage, 0 };

        i64 parts_limit = parts_size();
        i64 writehead = 0;
        dynamic_span<t_char> x_part;

        // Combine each part of the string
        for (i64 i = 0; i < parts_limit; ++i)
        {
            x_part = parts[i];
            // Don't add connecting string to beginning of first part
            if (connector_size && i != 0)
            {
                memory_copy<t_char>( (storage + writehead), (t_char*)connector.data(), connector_size );
                writehead += connector_size;
            }
            memory_copy<t_char>( (storage + writehead), x_part.data, x_part.size );
            writehead += x_part.size;
        }
        // Save calculated size to result string
        result.size_ = writehead;
        result.parts[0].size = writehead;
        ERROR_GUARD( writehead > allocation - 1, "More chars were written than allocated" );
        return result;
    }

    PROC image_color_reorder_inplace_u8_bgra_rgba( image<rgba> arg ) -> image<bgra>
    {
        PROFILE_SCOPE_FUNCTION();
        using t_color_in = rgba;
        using t_color_out = bgra;
        static_assert( sizeof(t_color_in) == sizeof(t_color_in),
                       "Input and output color must bother have the same size and RGBA components" );
        static_assert( std::is_same_v<t_color_out, t_color_in> == false,
                       "Having the same input and output type both is likely a bug" );
        u32 temp_1 = 0;
        u32 temp_2 = 0;
        t_color_in* read = arg.data;
        t_color_out* write = raw_pointer( arg.data );
        i64 i_limit = arg.size_pixels();
        for (i64 i_pixel=0; i_pixel < i_limit; ++i_pixel)
        {
            /** Move RGB down 1 byte/8 bits and replace the A channel moving it up 3 bytes 24 bits
                RGBA    RRGGBB00    000000AA
                ARGB    00RRGGBB    AA000000
            */
            static_assert( REFLECTION_LITTLE_ENDIAN, "Size is fixed" );
            temp_1 = std::bit_cast<u32>( read[ i_pixel ]);
            temp_1 = (temp_1 >> 8) | ((temp_1 & 0xFF) << 24);
            write[ i_pixel ] = std::bit_cast<bgra>( temp_1 );
        };
        image<t_color_out> result;
        result.data = raw_pointer(arg.data);
        result.size = arg.size;
        return result;
    }
}
