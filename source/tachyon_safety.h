
#pragma once

namespace tyon
{

/** Like clamp_u32 but signals an error if something goes wrong

 Borked. Not actually safe. */
template <typename t_return, typename T>
PROC limit( T arg )
{   T low_clamp = (arg > 0 ? arg : 0 );
    T type_max = std::numeric_limits<t_return>::max();
    T high_low_clamp = (low_clamp < type_max ? low_clamp : type_max);
    if (arg < 0 || arg > type_max)
    {   TYON_ERRORF( "Arg {} exceeds range of return type", arg ); }
    return static_cast<t_return>( high_low_clamp );

}

}
