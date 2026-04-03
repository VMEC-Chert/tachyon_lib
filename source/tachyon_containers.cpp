
#include "include_tachyon_lib_core.h"

namespace tyon
{
    __attribute__((optimize("O2")))
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
            temp_2 = (temp_1 >> 8) | ((temp_1 & 0xFF) << 24);
            write[ i_pixel ] = std::bit_cast<bgra>( temp_2 );
        };
        image<t_color_out> result;
        result.data = raw_pointer(arg.data);
        result.size = arg.size;
        return result;
    }
}
