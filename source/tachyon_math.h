
#pragma once

namespace tyon
{
    /** Types & Templates */
        // #######################
        // ### Complex Numbers ###
        // #######################
        template<typename T_real, typename T_imag> struct complex_type
        {
            T_real real;
            T_imag imag;
        };

        // Addition
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC operator+(complex_type<T_real, T_imag> a, complex_type<T_real, T_imag> b)
        {
            return complex_type{ a.real + b.real, a.imag + b.imag };
        }

        // Subtraction
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC operator-(complex_type<T_real, T_imag> a, complex_type<T_real, T_imag> b)
        {
            return complex_type{ a.real - b.real, a.imag - b.imag };
        }

        // Multiplication
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC operator*(complex_type<T_real, T_imag> a, complex_type<T_real, T_imag> b)
        {
            return complex_type{ (a.real * b.real) - (a.imag * b.imag), (a.real * b.imag) + (a.imag * b.real) };
        }

        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC operator*(complex_type<T_real, T_imag> a, T_real b)
        {
            return complex_type{ a.real * b, a.real * b };
        }

        // Division
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC operator/(complex_type<T_real, T_imag> a, complex_type<T_real, T_imag> b)
        {
            return complex_type{ ((a.real * b.real) + (a.imag * b.imag)) / ((b.real * b.real) + (b.imag * b.imag)), ((a.imag * b.real) - (a.real * b.imag)) / ((b.real * b.real) + (b.imag * b.imag)) };
        }

        // Inverse
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC operator-(complex_type<T_real, T_imag> a)
        {
            return complex_type{ -a.real, a.imag };
        }

        // Conjugate
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC complex_conjugate(complex_type<T_real, T_imag> a)
        {
            return complex_type{ a.real, -a.imag };
        }

        // Modulus
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC complex_modulus(complex_type<T_real, T_imag> a)
        {
            using std::sqrt;
            return sqrt(a.real * a.real + a.imag * a.imag);
        }

        // Argument
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC complex_arg(complex_type<T_real, T_imag> a)
        {
            return atan2(a.imag, a.real);
        }

        // Sqrt
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC square_root(complex_type<T_real, T_imag> a)
        {
            // Branch cut along negative real axis to follow std::sqrt(std::complex) standard

            T_real x = a.real;
            T_real y = a.imag;

            if(x == static_cast<T_real>(0.0) && y == static_cast<T_real>(0.0))
            {
                return complex_type{ static_cast<T_real>(0.0), static_cast<T_imag>(0.0) };
            }

            T_real mag = hypot(x, y);
            T_real w = std::sqrt((mag + std::abs(x)) / static_cast<T_real>(2.0));

            T_real x2, y2;

            if (x >= static_cast<T_real>(0.0))
            {
                x2 = w;
                y2 = y / (static_cast<T_real>(2.0) * w);
            }
            else
            {
                x2 = std::abs(y) / (static_cast<T_real>(2.0) * w);
                y2 = (y >= static_cast<T_real>(0.0)) ? w : -w;
            }

            return complex_type{ x2, y2 };
        }

        // Nth Power
        template<typename T_real, typename T_imag> TYON_CUDA_SHARED inline PROC power(complex_type<T_real, T_imag> z, T_real n)
        {
            T_real x = z.real;
            T_real y = z.imag;

            if (x == static_cast<T_real>(0.0) && y == static_cast<T_real>(0.0))
            {
                if (n == static_cast<T_real>(0.0))
                {
                    return complex_type<T_real, T_imag>{ static_cast<T_real>(1.0), static_cast<T_imag>(0.0) };
                }
                else if (n > static_cast<T_real>(0.0))
                {
                    return complex_type<T_real, T_imag>{ static_cast<T_real>(0.0), static_cast<T_imag>(0.0) };
                }
            }

            T_real abs_r = tyon::complex_modulus(z);
            T_real arg = tyon::complex_arg(z);

            T_real r_n = pow(abs_r, n);
            T_real theta_n = n * arg;

            T_real cos_theta, sin_theta;

            #ifdef __CUDA_ARCH__
                sincos(theta_n, &sin_theta, &cos_theta);
            #else
                cos_theta = cos(theta_n);
                sin_theta = sin(theta_n);
            #endif

            return complex_type<T_real, T_imag>{ r_n * cos_theta, static_cast<T_imag>(r_n * sin_theta)};
        }



        // ####################
        // ### Dual Numbers ###
        // ####################
        template<typename T_real, typename T_dual> struct dual_type
        {
            T_real real;
            T_dual dual;
        };

        // Addition
        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator+(dual_type<T_real, T_dual> a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a.real + b.real, a.dual + b.dual };
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator+(dual_type<T_real, T_dual> a, T_real b)
        {
            return dual_type{ a.real + b, a.dual };
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator+(T_real a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a + b.real, b.dual };
        }

        // Subtraction
        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator-(dual_type<T_real, T_dual> a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a.real - b.real, a.dual - b.dual };
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator-(dual_type<T_real, T_dual> a, T_real b)
        {
            return dual_type{ a.real - b, a.dual };
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator-(T_real a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a - b.real, -b.dual };
        }

        // Multiplication
        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator*(dual_type<T_real, T_dual> a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a.real * b.real, b.real * a.dual + a.real * b.dual };
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator*(dual_type<T_real, T_dual> a, T_real b)
        {
            return dual_type{ a.real * b, a.dual * b };
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator*(T_real a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a * b.real, a * b.dual };
        }

        // Division
        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator/(dual_type<T_real, T_dual> a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a.real / b.real, (a.dual / b.real) - (a.real * b.dual) / (b.real * b.real) };
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator/(dual_type<T_real, T_dual> a, T_real b)
        {
            return dual_type{ a.real / b, a.dual / b};
        }

        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator/(T_real a, dual_type<T_real, T_dual> b)
        {
            return dual_type{ a / b.real, -(a / (b.real * b.real)) * b.dual };
        }

        // Inversion
        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC operator-(dual_type<T_real, T_dual> a)
        {
            return dual_type{ -a.real, -a.dual };
        }

        // Compound assigments

        // Square root
        template<typename T_real, typename T_dual> TYON_CUDA_SHARED inline PROC square_root(dual_type<T_real, T_dual> a)
        {
            using std::sqrt;
            return dual_type{ sqrt(a.real), a.dual / (static_cast<T_real>(2.0) * sqrt(a.real)) };
        }



        // #########################
        // ### General functions ###
        // #########################
        // Square root
        template<typename T> TYON_CUDA_SHARED inline PROC square_root(const T x) -> T
        {
            return std::sqrt(x);
        }

        // Exponential
        template<typename T> TYON_CUDA_SHARED inline PROC power(const T base, const T exponent) -> T
        {
            return std::pow(base, exponent);
        }

        template<typename T> TYON_CUDA_SHARED inline PROC exponential(const T exponent) -> T
        {
            return std::exp(exponent);
        }

        // Logarithms
        template<typename T> TYON_CUDA_SHARED inline PROC natural_logarithm(const T x) -> T
        {
            return std::log(x);
        }

        // Probability
        template<typename T> TYON_CUDA_SHARED inline PROC error_function(const T a) -> T
        {
            return std::erf(a);
        }

        template<typename T> TYON_CUDA_SHARED inline PROC norm_gaussian_cdf(const T mean, const T x, const T standard_deviation) -> T
        {
            return static_cast<T>(0.5) * (static_cast<T>(1.0) + std::erf((x - mean) / (standard_deviation * std::sqrt(static_cast<T>(2.0)))));
        }



        // ################
        // ### Vector-2 ###
        // ################
        // Structs
        struct v2_f32
        {
            f32 x;
            f32 y;

            TYON_CUDA_SHARED constexpr CONSTRUCTOR v2_f32();
            TYON_CUDA_SHARED constexpr CONSTRUCTOR v2_f32( f32 arg );
            TYON_CUDA_SHARED constexpr CONSTRUCTOR v2_f32( f32 x, f32 y);
        };

        // Constructors
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v2_f32::v2_f32() : x(0.0f), y(0.0f) {}
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v2_f32::v2_f32( f32 arg) : x(arg), y(arg) {}
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v2_f32::v2_f32( f32 x, f32 y) : x(x), y(y) {}

        // Operators
        // Addition
        TYON_CUDA_SHARED inline PROC operator+(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x + v1.x, v0.y + v1.y );
        }

        // Subtraction
        TYON_CUDA_SHARED inline PROC operator-(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x - v1.x, v0.y - v1.y );
        }

        // Multiplication
        TYON_CUDA_SHARED inline PROC operator*(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x * v1.x, v0.y * v1.y );
        }

        TYON_CUDA_SHARED inline PROC operator*(const v2_f32 v, const f32 s)
        {
            return v2_f32( v.x * s, v.y * s );
        }

        TYON_CUDA_SHARED inline PROC operator*(const f32 s, const v2_f32 v)
        {
            return v2_f32( v.x * s, v.y * s );
        }

        // Division
        TYON_CUDA_SHARED inline PROC operator/(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x / v1.x, v0.y / v1.y );
        }

        TYON_CUDA_SHARED inline PROC operator/(const v2_f32 v, const f32 s)
        {
            return v2_f32( v.x / s, v.y / s );
        }

        TYON_CUDA_SHARED inline PROC operator/(const f32 s, const v2_f32 v)
        {
            return v2_f32( s / v.x, s / v.y );
        }

        // Compound
        TYON_CUDA_SHARED inline PROC operator+=(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x + v1.x, v0.y + v1.y );
        }

        TYON_CUDA_SHARED inline PROC operator-=(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x - v1.x, v0.y - v1.y );
        }

        TYON_CUDA_SHARED inline PROC operator*=(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x * v1.x, v0.y * v1.y );
        }

        TYON_CUDA_SHARED inline PROC operator/=(const v2_f32 v0, const v2_f32 v1)
        {
            return v2_f32( v0.x / v1.x, v0.y / v1.y );
        }

        // Inversion
        TYON_CUDA_SHARED inline PROC operator-(const v2_f32 v)
        {
            return v2_f32( -v.x, -v.y );
        }

        // Functions
        TYON_CUDA_SHARED inline PROC vector_dot_product(const v2_f32 v0, const v2_f32 v1)
        {
            return (v0.x * v1.x) + (v0.y * v1.y);
        }

        TYON_CUDA_SHARED inline PROC angle_radians(const v2_f32 v0, const v2_f32 v1)
        {
            return std::acosf(vector_dot_product(v0, v1));
        }

        TYON_CUDA_SHARED inline PROC vector_normalize(const v2_f32 v)
        {
            return v / std::sqrtf( v.x*v.x + v.y*v.y );
        }

        TYON_CUDA_SHARED inline PROC vector_reflect(const v2_f32 d, const v2_f32 n)
        {
            return (d - (2.0f * n * vector_dot_product(d, n)));
        }

        TYON_CUDA_SHARED inline PROC vector_refract(const v2_f32 d, const v2_f32 n, const f32 eta_0, const f32 eta_1)
        {
                f32 cos_theta_i = vector_dot_product(d, n);
                f32 eta_relative = eta_0 / eta_1;
                f32 sin2_theta_t = eta_relative * eta_relative * (1.0f - cos_theta_i * cos_theta_i);
                return (eta_relative * cos_theta_i - std::sqrtf(1.0f - sin2_theta_t)) * n - eta_relative * d;
        }

        TYON_CUDA_SHARED inline PROC vector_project(const v2_f32 v0, const v2_f32 v1)
        {
            return (vector_dot_product(v0, v1) * v1) / vector_dot_product(v1, v1);
        }

        TYON_CUDA_SHARED inline PROC v_barycentric(const v2_f32 p0, const v2_f32 p1, const v2_f32 p2, const v2_f32 barycentric_coordinates)
        {
            return p0 * barycentric_coordinates.x + p1 * barycentric_coordinates.y + p2 * (1.0f - barycentric_coordinates.x - barycentric_coordinates.y);
        }

        TYON_CUDA_SHARED inline PROC vector_length(const v2_f32 v)
        {
            return std::sqrtf( v.x*v.x + v.y*v.y );
        }

        TYON_CUDA_SHARED inline PROC vector_length2(const v2_f32 v)
        {
            return ( v.x*v.x + v.y*v.y );
        }

        TYON_CUDA_SHARED inline PROC vector_distance(const v2_f32 v0, const v2_f32 v1)
        {
            return vector_length(v0 - v1);
        }

        TYON_CUDA_SHARED inline PROC vector_distance2(const v2_f32 v0, const v2_f32 v1)
        {
            return vector_length2(v0 - v1);
        }



        // ################
        // ### Vector-3 ###
        // ################
        // Structs
        struct v3_f32
        {
            f32 x;
            f32 y;
            f32 z;

            TYON_CUDA_SHARED constexpr CONSTRUCTOR v3_f32();
            TYON_CUDA_SHARED constexpr CONSTRUCTOR v3_f32( f32 arg );
            TYON_CUDA_SHARED constexpr CONSTRUCTOR v3_f32( f32 x, f32 y, f32 z );
        };

        // Constructors
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v3_f32::v3_f32() : x(0.0f), y(0.0f), z(0.0f) {}
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v3_f32::v3_f32( f32 arg) : x(arg), y(arg), z(arg) {}
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v3_f32::v3_f32( f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

    // Forward Right-Up (FRU) xyz Unreal Engine
    constexpr PROC world_up() -> v3_f32 {      return { 0.0, 0.0, 1.0 }; }
    constexpr PROC world_forward() -> v3_f32 {  return { 1.0, 0.0, 0.0 }; }
    constexpr PROC world_right() -> v3_f32 {    return { 0.0, 1.0, 0.0 }; }
    constexpr PROC world_down() -> v3_f32 {     return { 0.0, 0.0,-1.0 }; }
    constexpr PROC world_backward() -> v3_f32 { return {-1.0, 0.0, 0.0 }; }
    constexpr PROC world_left() -> v3_f32 {     return { 0.0,-1.0, 0.0 }; }

    constexpr PROC screen_up() -> v3_f32 {       return world_up(); }
    constexpr PROC screen_forward() -> v3_f32 {  return world_forward(); }
    constexpr PROC screen_right() -> v3_f32 {    return world_right(); }
    constexpr PROC screen_down() -> v3_f32 {     return world_down(); }
    constexpr PROC screen_backward() -> v3_f32 { return world_backward(); }
    constexpr PROC screen_left() -> v3_f32 {     return world_left(); }

        // Operators
        // Addition
        TYON_CUDA_SHARED inline PROC operator+(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x + v1.x, v0.y + v1.y, v0.z + v1.z );
        }

        // Subtraction
        TYON_CUDA_SHARED inline PROC operator-(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x - v1.x, v0.y - v1.y, v0.z - v1.z );
        }

        // Multiplication
        TYON_CUDA_SHARED inline PROC operator*(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x * v1.x, v0.y * v1.y, v0.z * v1.z );
        }

        TYON_CUDA_SHARED inline PROC operator*(const v3_f32 v, const f32 s)
        {
            return v3_f32( v.x * s, v.y * s, v.z * s );
        }

        TYON_CUDA_SHARED inline PROC operator*(const f32 s, const v3_f32 v)
        {
            return v3_f32( v.x * s, v.y * s, v.z * s );
        }

        // Division
        TYON_CUDA_SHARED inline PROC operator/(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x / v1.x, v0.y / v1.y, v0.z / v1.z );
        }

        TYON_CUDA_SHARED inline PROC operator/(const v3_f32 v, const f32 s)
        {
            return v3_f32( v.x / s, v.y / s, v.z / s );
        }

        TYON_CUDA_SHARED inline PROC operator/(const f32 s, const v3_f32 v)
        {
            return v3_f32( s / v.x, s / v.y, s / v.z );
        }

        // Compound
        TYON_CUDA_SHARED inline PROC operator+=(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x + v1.x, v0.y + v1.y, v0.z + v1.z );
        }

        TYON_CUDA_SHARED inline PROC operator-=(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x - v1.x, v0.y - v1.y, v0.z - v1.z );
        }

        TYON_CUDA_SHARED inline PROC operator*=(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x * v1.x, v0.y * v1.y, v0.z * v1.z );
        }

        TYON_CUDA_SHARED inline PROC operator/=(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.x / v1.x, v0.y / v1.y, v0.z / v1.z );
        }

        // Inversion
        TYON_CUDA_SHARED inline PROC operator-(const v3_f32 v)
        {
            return v3_f32( -v.x, -v.y, -v.z );
        }

        // Functions
        TYON_CUDA_SHARED inline PROC vector_dot_product(const v3_f32 v0, const v3_f32 v1)
        {
            return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
        }

        TYON_CUDA_SHARED inline PROC vector_cross_product(const v3_f32 v0, const v3_f32 v1)
        {
            return v3_f32( v0.y*v1.z - v0.z*v1.y , v0.z*v1.x - v0.x*v1.z , v0.x*v1.y - v0.y*v1.x );
        }

        TYON_CUDA_SHARED inline PROC angle_radians(const v3_f32 v0, const v3_f32 v1)
        {
            return std::acosf(vector_dot_product(v0, v1));
        }

        TYON_CUDA_SHARED inline PROC vector_normalize(const v3_f32 v)
        {
            return v / std::sqrtf( v.x*v.x + v.y*v.y + v.z*v.z );
        }

        TYON_CUDA_SHARED inline PROC vector_reflect(const v3_f32 d, const v3_f32 n)
        {
            return (d - (2.0f * n * vector_dot_product(d, n)));
        }

        TYON_CUDA_SHARED inline PROC vector_refract(const v3_f32 d, const v3_f32 n, const f32 eta_0, const f32 eta_1)
        {
                f32 cos_theta_i = vector_dot_product(d, n);
                f32 eta_relative = eta_0 / eta_1;
                f32 sin2_theta_t = eta_relative * eta_relative * (1.0f - cos_theta_i * cos_theta_i);
                return (eta_relative * cos_theta_i - std::sqrtf(1.0f - sin2_theta_t)) * n - eta_relative * d;
        }

        TYON_CUDA_SHARED inline PROC vector_project(const v3_f32 v0, const v3_f32 v1)
        {
            return (vector_dot_product(v0, v1) * v1) / vector_dot_product(v1, v1);
        }

        TYON_CUDA_SHARED inline PROC v_barycentric(const v3_f32 p0, const v3_f32 p1, const v3_f32 p2, const v2_f32 barycentric_coordinates)
        {
            return p0 * barycentric_coordinates.x + p1 * barycentric_coordinates.y + p2 * (1.0f - barycentric_coordinates.x - barycentric_coordinates.y);
        }

        TYON_CUDA_SHARED inline PROC vector_length(const v3_f32 v)
        {
            return std::sqrtf( v.x*v.x + v.y*v.y + v.z*v.z );
        }

        TYON_CUDA_SHARED inline PROC vector_length2(const v3_f32 v)
        {
            return ( v.x*v.x + v.y*v.y + v.z*v.z);
        }

        TYON_CUDA_SHARED inline PROC vector_distance(const v3_f32 v0, const v3_f32 v1)
        {
            return vector_length(v0 - v1);
        }

        TYON_CUDA_SHARED inline PROC vector_distance2(const v3_f32 v0, const v3_f32 v1)
        {
            return vector_length2(v0 - v1);
        }



        // ################
        // ### Vector-4 ###
        // ################
        // Structs
        struct v4_f32
        {
            f32 x;
            f32 y;
            f32 z;
            f32 w;

            TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32();
            TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32( f32 arg );
            TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32( f32 x, f32 y, f32 z, f32 w);
            TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32( v3_f32 a, f32 w_ );
            TYON_CUDA_SHARED constexpr PROC xyz() -> v3_f32 { return { x, y, z }; }
            TYON_CUDA_SHARED constexpr PROC xy() -> v2_f32 { return { x, y }; }
            TYON_CUDA_SHARED constexpr PROC yz() -> v2_f32 { return { y, z }; }
            TYON_CUDA_SHARED constexpr PROC zw() -> v2_f32 { return { z, w }; }
        };

        // Constructors
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32::v4_f32()
            : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32::v4_f32( f32 arg )
            : x(arg), y(arg), z(arg) {}
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32::v4_f32( f32 x, f32 y, f32 z, f32 w)
            : x(x), y(y), z(z), w(w) {}
        TYON_CUDA_SHARED constexpr CONSTRUCTOR v4_f32::v4_f32( v3_f32 a, f32 w_ )
            : x(a.x), y(a.y), z(a.z), w(w_) {}

        // Operators
        // Addition
        TYON_CUDA_SHARED inline PROC operator+(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w );
        }

        // Subtraction
        TYON_CUDA_SHARED inline PROC operator-(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w );
        }

        // Multiplication
        TYON_CUDA_SHARED inline PROC operator*(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w );
        }

        TYON_CUDA_SHARED inline PROC operator*(const v4_f32 v, const f32 s)
        {
            return v4_f32( v.x * s, v.y * s, v.z * s, v.w * s );
        }

        TYON_CUDA_SHARED inline PROC operator*(const f32 s, const v4_f32 v)
        {
            return v4_f32( v.x * s, v.y * s, v.z * s, v.w * s );
        }

        // Division
        TYON_CUDA_SHARED inline PROC operator/(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w );
        }

        TYON_CUDA_SHARED inline PROC operator/(const v4_f32 v, const f32 s)
        {
            return v4_f32( v.x / s, v.y / s, v.z / s, v.w / s );
        }

        TYON_CUDA_SHARED inline PROC operator/(const f32 s, const v4_f32 v)
        {
            return v4_f32( s / v.x, s / v.y, s / v.z, s / v.w );
        }

        // Compound
        TYON_CUDA_SHARED inline PROC operator+=(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w );
        }

        TYON_CUDA_SHARED inline PROC operator-=(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w );
        }

        TYON_CUDA_SHARED inline PROC operator*=(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w );
        }

        TYON_CUDA_SHARED inline PROC operator/=(const v4_f32 v0, const v4_f32 v1)
        {
            return v4_f32( v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w );
        }

        // Inversion
        TYON_CUDA_SHARED inline PROC operator-(const v4_f32 v)
        {
            return v4_f32( -v.x, -v.y, -v.z, -v.w );
        }

        // Functions
        TYON_CUDA_SHARED inline PROC vector_dot_product(const v4_f32 v0, const v4_f32 v1)
        {
            return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z) + (v0.w * v1.w);
        }

        TYON_CUDA_SHARED inline PROC angle_radians(const v4_f32 v0, const v4_f32 v1)
        {
            return std::acosf(vector_dot_product(v0, v1));
        }

        TYON_CUDA_SHARED inline PROC vector_normalize(const v4_f32 v)
        {
            return v / std::sqrtf( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w );
        }

        TYON_CUDA_SHARED inline PROC vector_reflect(const v4_f32 d, const v4_f32 n)
        {
            return (d - (2.0f * n * vector_dot_product(d, n)));
        }

        TYON_CUDA_SHARED inline PROC vector_refract(const v4_f32 d, const v4_f32 n, const f32 eta_0, const f32 eta_1)
        {
                f32 cos_theta_i = vector_dot_product(d, n);
                f32 eta_relative = eta_0 / eta_1;
                f32 sin2_theta_t = eta_relative * eta_relative * (1.0f - cos_theta_i * cos_theta_i);
                return (eta_relative * cos_theta_i - std::sqrtf(1.0f - sin2_theta_t)) * n - eta_relative * d;
        }

        TYON_CUDA_SHARED inline PROC vector_project(const v4_f32 v0, const v4_f32 v1)
        {
            return (vector_dot_product(v0, v1) * v1) / vector_dot_product(v1, v1);
        }

        TYON_CUDA_SHARED inline PROC v_barycentric(const v4_f32 p0, const v4_f32 p1, const v4_f32 p2, const v2_f32 barycentric_coordinates)
        {
            return p0 * barycentric_coordinates.x + p1 * barycentric_coordinates.y + p2 * (1.0f - barycentric_coordinates.x - barycentric_coordinates.y);
        }

        TYON_CUDA_SHARED inline PROC vector_length(const v4_f32 v)
        {
            return std::sqrtf( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w );
        }

        TYON_CUDA_SHARED inline PROC vector_length2(const v4_f32 v)
        {
            return ( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
        }

        TYON_CUDA_SHARED inline PROC vector_distance(const v4_f32 v0, const v4_f32 v1)
        {
            return vector_length(v0 - v1);
        }

        TYON_CUDA_SHARED inline PROC vector_distance2(const v4_f32 v0, const v4_f32 v1)
        {
            return vector_length2(v0 - v1);
        }



        // #########################
        // ### Utility functions ###
        // #########################
        // Angle conversion
        TYON_CUDA_SHARED inline PROC to_radians(const f32 degrees)
        {
            return (degrees * M_PI) / 180.0f;
        }

        TYON_CUDA_SHARED inline PROC to_degrees(const f32 radians)
        {
            return radians * (180.0f / M_PI);
        }

        // Lerp
        template<typename T> TYON_CUDA_SHARED inline T lerp(const T a, const T b, const f32 t)
        {
            return a + t * (b - a);
        }

        // Clamp
        TYON_CUDA_SHARED inline PROC clamp_range(const f32 edge0, const f32 edge1, const f32 a)
        {
            if(a < edge0) return edge0;
            if(a > edge1) return edge1;
            return a;
        }

        // Smooth step
        TYON_CUDA_SHARED inline PROC smooth_step(const f32 edge0, const f32 edge1, const f32 t)
        {
            f32 x = clamp_range(0.0f, 1.0f, ((t - edge0) / (edge1 * edge0)));
            return x * x * (3.0f - 2.0f * x);
        }

        // Rounding
        TYON_CUDA_SHARED inline PROC round_down(const f32 a)
        {
            return std::floorf(a);
        }

        TYON_CUDA_SHARED inline PROC round_up(const f32 a)
        {
            return std::ceilf(a);
        }

        TYON_CUDA_SHARED inline PROC round_normal(const f32 a)
        {
            return std::roundf(a);
        }

        // Fraction
        TYON_CUDA_SHARED inline PROC fraction(const f32 a)
        {
            f32 _fraction;
            return std::modff(a, &_fraction);
        }

        // Remap
        TYON_CUDA_SHARED inline PROC remap(const f32 start0, const f32 end0, const f32 start1, const f32 end1, const f32 value)
        {
            return start1 + ((end1 - start1) / (end0 - start0)) * (value - start0);
        }

        // Smooth ramp
        TYON_CUDA_SHARED inline PROC smooth_ramp(const f32 amplitude, const f32 exponent, const f32 x, const f32 x0, const f32 range)
        {
            f32 sign_range = 1.0f;

            if(range < 0.0f)
            {
                sign_range = -1.0f;
            }

            if((sign_range*x) > (sign_range*(range + x0)))
            {
                return amplitude;
            }
            else if((sign_range*x) < (sign_range*x0))
            {
                return 0.0f;
            }
            else
            {
                return amplitude / ( 1.0f + tyon::power( (x - x0) / (range - (x - x0)) , -exponent ) );
            }
        }

        // Swap
        template<typename T> TYON_CUDA_SHARED inline void swap_pair(T& a, T& b)
        {
            T T_temp = b;
            b = a;
            a = T_temp;
        }



        // Matrices
        struct matrix2_f32
        {
            f32 m11; f32 m12;
            f32 m21; f32 m22;

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix2_f32();
            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix2_f32( f32 arg );
            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix2_f32( f32 m11, f32 m12, f32 m21, f32 m22);
            TYON_CUDA_SHARED explicit constexpr
            CONSTRUCTOR matrix2_f32( f64 arg );
        };

        struct matrix2_f64
        {
            f64 m11; f64 m12;
            f64 m21; f64 m22;

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix2_f64();
            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix2_f64( f64 arg );
            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix2_f64( f64 m11, f64 m12, f64 m21, f64 m22);
            TYON_CUDA_SHARED explicit constexpr
            CONSTRUCTOR matrix2_f64( f32 arg );
        };

        struct matrix3_f32
        {
            f32 m11; f32 m12; f32 m13;
            f32 m21; f32 m22; f32 m23;
            f32 m31; f32 m32; f32 m33;

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix3_f32();

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix3_f32( f32 arg );

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix3_f32(
                f32 m11, f32 m12, f32 m13,
                f32 m21, f32 m22, f32 m23,
                f32 m31, f32 m32, f32 m33
            );
            TYON_CUDA_SHARED
            explicit constexpr CONSTRUCTOR matrix3_f32( f64 arg );
        };

        struct matrix3_f64
        {
            f64 m11; f64 m12; f64 m13;
            f64 m21; f64 m22; f64 m23;
            f64 m31; f64 m32; f64 m33;

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix3_f64();

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix3_f64( f32 arg );

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix3_f64(
                f32 m11, f32 m12, f32 m13,
                f32 m21, f32 m22, f32 m23,
                f32 m31, f32 m32, f32 m33
            );

            TYON_CUDA_SHARED constexpr explicit
            CONSTRUCTOR matrix3_f64( f64 arg );
        };

        struct matrix4_f32
        {
            f32 m11; f32 m12; f32 m13; f32 m14;
            f32 m21; f32 m22; f32 m23; f32 m24;
            f32 m31; f32 m32; f32 m33; f32 m34;
            f32 m41; f32 m42; f32 m43; f32 m44;

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix4_f32();

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix4_f32( f32 arg );

            TYON_CUDA_SHARED constexpr
            CONSTRUCTOR matrix4_f32(
                f32 m11, f32 m12, f32 m13, f32 m14,
                f32 m21, f32 m22, f32 m23, f32 m24,
                f32 m31, f32 m32, f32 m33, f32 m34,
                f32 m41, f32 m42, f32 m43, f32 m44
            );
            TYON_CUDA_SHARED constexpr
            explicit CONSTRUCTOR matrix4_f32( f64 arg );
        };

        struct matrix4_f64
        {
            f64 m11; f64 m12; f64 m13; f64 m14;
            f64 m21; f64 m22; f64 m23; f64 m24;
            f64 m31; f64 m32; f64 m33; f64 m34;
            f64 m41; f64 m42; f64 m43; f64 m44;

            TYON_CUDA_SHARED
            constexpr CONSTRUCTOR matrix4_f64();
            TYON_CUDA_SHARED
            constexpr CONSTRUCTOR matrix4_f64( f64 arg );
            TYON_CUDA_SHARED
            constexpr CONSTRUCTOR matrix4_f64( f64 m11, f64 m12, f64 m13, f64 m14, f64 m21, f64 m22, f64 m23, f64 m24, f64 m31, f64 m32, f64 m33, f64 m34, f64 m41, f64 m42, f64 m43, f64 m44);
            TYON_CUDA_SHARED
            explicit constexpr CONSTRUCTOR matrix4_f64( f32 arg );
        };

    // // Inline to reduce duplicates across a program
    // template <typename T> constexpr inline T identity_define;
    // template <> constexpr inline matrix4_f32 identity_define<matrix4_f32> = { 1.0, 0.0, 0.0, 0.0,
    //                                                               0.0, 1.0, 0.0, 0.0,
    //                                                               0.0, 0.0, 1.0, 0.0,
    //                                                               0.0, 0.0, 0.0, 1.0 };
    // struct identity_t
    // {
    //     template <typename T>
    //     constexpr operator T() const { return identity_define<T>; }
    // };
    // constexpr inline identity_t identity;

    constexpr
    PROC matrix4_f32_identity() -> matrix4_f32
    {   return { 1.0, 0.0, 0.0, 0.0,
                 0.0, 1.0, 0.0, 0.0,
                 0.0, 0.0, 1.0, 0.0,
                 0.0, 0.0, 0.0, 1.0 };
    }

        struct transform_2d
        {
          v2_f32 translation;
          v2_f32 rotation;
          v2_f32 scale = { 1.0, 1.0 };
        };

        struct transform_3d
        {
          v3_f32 translation = { 0.0, 0.0, 0.0 };
          v3_f32 rotation = { 0.0, 0.0, 0.0 };
          v3_f32 scale =  { 1.0, 1.0, 1.0 };
        };

        struct box_2d
        {
            v2_f32 position;
            v2_f32 size;
        };

        struct box_3d
        {
            v3_f32 position;
            v3_f32 size;
        };

    /** Operators */
        // Vector-Matrix
            TYON_CUDA_SHARED
            PROC operator*(const v2_f32 v0, const matrix2_f32 m0) -> v2_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f32 m0, const v2_f32 v0) -> v2_f32;

            TYON_CUDA_SHARED
            PROC operator*(const v3_f32 v0, const matrix3_f32 m0) -> v3_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f32 m0, const v3_f32 v0) -> v3_f32;

            TYON_CUDA_SHARED
            PROC operator*(const v4_f32 v0, const matrix4_f32 m0) -> v4_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f32 m0, const v4_f32 v0) -> v4_f32;



        // Matrices
            // Matrix Addition
            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f32 m0, const matrix2_f32 m1) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f64 m0, const matrix2_f64 m1) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f32 m0, const matrix3_f32 m1) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f64 m0, const matrix3_f64 m1) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f32 m0, const matrix4_f32 m1) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f64 m0, const matrix4_f64 m1) -> matrix4_f64;

            // Scalar Addition
            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f32 m0, const f32 s0) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix2_f32 m0) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f64 m0, const f64 s0) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator+(const f64 s0, const matrix2_f64 m0) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f32 m0, const f32 s0) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix3_f32 m0) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f64 m0, const f64 s0) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix3_f64 m0) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f32 m0, const f32 s0) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix4_f32 m0) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f64 m0, const f64 s0) -> matrix4_f64;

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix4_f64 m0) -> matrix4_f64;

            // Matrix Subtraction
            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f32 m0, const matrix2_f32 m1) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f64 m0, const matrix2_f64 m1) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f32 m0, const matrix3_f32 m1) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f64 m0, const matrix3_f64 m1) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f32 m0, const matrix4_f32 m1) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f64 m0, const matrix4_f64 m1) -> matrix4_f64;

            // Scalar Subtraction
            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f32 m0, const f32 s0) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix2_f32 m0) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f64 m0, const f64 s0) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator-(const f64 s0, const matrix2_f64 m0) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f32 m0, const f32 s0) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix3_f32 m0) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f64 m0, const f64 s0) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix3_f64 m0) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f32 m0, const f32 s0) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix4_f32 m0) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f64 m0, const f64 s0) -> matrix4_f64;

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix4_f64 m0) -> matrix4_f64;

            // Matrix Multiplication
            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f32 m0, const matrix2_f32 m1) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f64 m0, const matrix2_f64 m1) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f32 m0, const matrix3_f32 m1) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f64 m0, const matrix3_f64 m1) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f32 m0, const matrix4_f32 m1) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f64 m0, const matrix4_f64 m1) -> matrix4_f64;

            // Scalar Multiplication
            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f32 m0, const f32 s0) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix2_f32 m0) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f64 m0, const f64 s0) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator*(const f64 s0, const matrix2_f64 m0) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f32 m0, const f32 s0) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix3_f32 m0) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f64 m0, const f64 s0) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix3_f64 m0) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f32 m0, const f32 s0) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix4_f32 m0) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f64 m0, const f64 s0) -> matrix4_f64;

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix4_f64 m0) -> matrix4_f64;



    /** Functions */
        // Trigonometry
        TYON_CUDA_SHARED
        PROC sinus(const f32 a) -> f32;

        TYON_CUDA_SHARED
        PROC sinus(const f64 a) -> f64;

        TYON_CUDA_SHARED
        PROC cosinus(const f32 a) -> f32;

        TYON_CUDA_SHARED
        PROC cosinus(const f64 a) -> f64;

        TYON_CUDA_SHARED
        PROC tangent(const f32 a) -> f32;

        TYON_CUDA_SHARED
        PROC tangent(const f64 a) -> f64;

        TYON_CUDA_SHARED
        PROC arcsin(const f32 a) -> f32;

        TYON_CUDA_SHARED
        PROC arcsin(const f64 a) -> f64;

        TYON_CUDA_SHARED
        PROC arccos(const f32 a) -> f32;

        TYON_CUDA_SHARED
        PROC arccos(const f64 a) -> f64;

        TYON_CUDA_SHARED
        PROC arctan(const f32 a) -> f32;

        TYON_CUDA_SHARED
        PROC arctan(const f64 a) -> f64;

        TYON_CUDA_SHARED
        PROC arctan2(const f32 x, const f32 y) -> f32;

        TYON_CUDA_SHARED
        PROC arctan2(const f64 x, const f64 y) -> f64;



        // Matrix
            // Rotation
            TYON_CUDA_SHARED
            PROC general_2d_rotation_matrix(const f32 theta) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC general_2d_rotation_matrix(const f64 theta) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC general_3d_rotation_matrix(const f32 r_x, const f32 r_y, const f32 r_z) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC general_3d_rotation_matrix(const f64 r_x, const f64 r_y, const f64 r_z) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC euler_rotation_matrix(const f32 theta, const v3_f32 u) -> matrix3_f32;



            // Transpose
            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix2_f32 m) -> matrix2_f32;

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix2_f64 m) -> matrix2_f64;

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix3_f32 m) -> matrix3_f32;

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix3_f64 m) -> matrix3_f64;

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix4_f32 m) -> matrix4_f32;

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix4_f64 m) -> matrix4_f64;

    constexpr
    PROC matrix_transform( transform_3d arg) -> matrix4_f32
    {
        auto t = arg.translation;
        auto r = arg.rotation;
        auto s = arg.scale;
        // // Euler Combined 3 Axis Translation Rotation Scale Matrix
        return matrix4_f32 {
            // Row 1
            s.x * cosf(r.y)*cosf(r.z),
            s.y * cosf(r.x)*sinf(r.z) + cosf(r.z)*sinf(r.x)*sinf(r.y),
            s.z * sinf(r.x)*sinf(r.z) - cosf(r.x)*cosf(r.z)*sinf(r.y),
            t.x,
            // Row 2
            s.x -cosf(r.y)*sinf(r.z),
            s.y * cosf(r.x)*cosf(r.z) - sinf(r.x)*sinf(r.y)*sinf(r.z),
            s.z * cosf(r.x)*sinf(r.y)*sinf(r.z) + cosf(r.z)*sinf(r.x),
            t.y,
            // Row 3
            s.x * sinf(r.y),
            s.y * -cosf(r.y)*sinf(r.x),
            s.z * cosf(r.x)*cosf(r.y),
            t.z,
            // Row 4
            0, 0, 0, 1
        };
    }

//     PROC matrix_rotation_arbitrary( vf3) -> matrix4_f32
// {
//     matrix{ cosf(ar) + (a.x*a.x) * (1 - cosf(ar)),
//         a.x*a.y * (1 - cosf(ar)) - a.z*sinf(ar),
//         a.x*a.z * (1 - cosf(ar)) + a.y*sinf(ar),
//         0,

//         a.y*a.x * (1 - cosf(ar)) + a.z*sinf(ar),
//         cosf(ar) + (a.y*a.y) * (1 - cosf(ar)),
//         a.y*a.z * (1 - cosf(ar)) - a.x*sinf(ar),
//         0,

//         a.z*a.x * (1 - cosf(ar)) - a.y*sinf(ar),
//         a.z*a.y * (1 - cosf(ar)) + a.z*sinf(ar), // <-- see note below
//         cosf(ar) + (a.z*a.z) * (1 - cosf(ar)),
//         0,

//         0, 0, 0, 1 };
// }

    constexpr
    PROC matrix_translation( v3_f32 arg) -> matrix4_f32
    {   auto t = arg;
        return matrix4_f32 { 1.0, 0.0, 0.0, t.x,
                             0.0, 1.0, 0.0, t.y,
                             0.0, 0.0, 1.0, t.z,
                             0.0, 0.0, 0.0, 1.0 };
    }

    // NOTE: Needs custom function to be constexpr
    constexpr
    PROC matrix_rotation( v3_f32 arg ) -> matrix4_f32
    {
        v3_f32 r = arg;
        // // Euler Combined 3 Axis Rotation Matrix (Row-Major)
        return matrix4_f32 {
            // Row 1
            cosf(r.y)*cosf(r.z),
            cosf(r.x)*sinf(r.z) + cosf(r.z)*sinf(r.x)*sinf(r.y),
            sinf(r.x)*sinf(r.z) - cosf(r.x)*cosf(r.z)*sinf(r.y),
            0,
            // Row 2
            -cosf(r.y)*sinf(r.z),
            cosf(r.x)*cosf(r.z) - sinf(r.x)*sinf(r.y)*sinf(r.z),
            cosf(r.x)*sinf(r.y)*sinf(r.z) + cosf(r.z)*sinf(r.x),
            0,
            // Row 3
            sinf(r.y),
            -cosf(r.y)*sinf(r.x),
            cosf(r.x)*cosf(r.y),
            0,
            // Row 4
            0, 0, 0, 1 };
    }

    constexpr
    PROC matrix_scale( v3_f32 arg ) -> matrix4_f32
    {   auto s = arg;
        return matrix4_f32 { s.x, 0.0, 0.0, 0.0,
                             0.0, s.y, 0.0, 0.0,
                             0.0, 0.0, s.z, 0.0,
                             0.0, 0.0, 0.0, 1.0 };
    }

    // constexpr
    // PROC matrix_shear( v3_f32 arg ) -> matrix4_f32
    // {
    //     return matrix4_f32 { 1.0, 0.0, 0.0, 0.0,
    //                          0.0, 1.0, 0.0, 0.0,
    //                          0.0, 0.0, 1.0, 0.0,
    //                          0.0, 0.0, 0.0, 1.0 };
    // }

    constexpr
    PROC matrix_transform_v3( matrix4_f32 transform, v3_f32 point ) -> v3_f32
    {   return (transform * v4_f32 { point, 1.0f }).xyz(); }

    /** Ignores translation since its a direction vector */
    constexpr
    PROC matrix_transform_direction_v3( matrix4_f32 transform, v3_f32 direction ) ->v3_f32
    {   return (transform * v4_f32 { direction, 1.0f }).xyz(); }

    constexpr
    PROC matrix_rotate_v3( v3_f32 rotation, v3_f32 target ) -> v3_f32
    {   return matrix_transform_v3( matrix_rotation( rotation ), target ); }

    // constexpr
    // PROC matrix_project_v3( )

    struct scene_camera
    {
        transform_3d transform;
        v2_f32 sensor_size;
        f32 near_clip;
        f32 far_clip;

        /** NOTE: Direction vector functions incoherent for objects that aren't
         * in the local space of the camera, which is to say parented to the
         * camera. Transform it into world space if you want real usage */
        /** Create local normalized foward vector */

        constexpr PROC forward() -> v3_f32
        {   return matrix_rotate_v3( transform.rotation , world_forward() ); }
        // Create local normalized up vector
        // constexpr PROC up() -> v3_f32
        // {   return matrix_transform_v3( matrix_rotation( transform.rotation ), world_up() ); }
        // // Create local normalized right vector
        // constexpr PROC right() -> v3_f32
        // {   return matrix_transform_v3( matrix_rotation( transform.rotation ) * world_right() ); }
        // constexpr PROC backward() -> v3_f32
        // {   return matrix_transform_v3( matrix_rotation( transform.rotation ) * world_backward() ); }
        // // Create local normalized up vector
        // constexpr PROC down() -> v3_f32
        // {   return matrix_transform_vv3( matrix_rotation( transform.rotation ) * world_down() ); }
        // // Create local normalized right vector
        // constexpr PROC left() -> v3_f32
        // {   return matrix_rotation( transform.rotation ) * world_left(); }
    };

    /** (Inverse Translation * Inverse Rotation) */
    constexpr
    PROC matrix_view( transform_3d arg ) -> matrix4_f32
    {   return matrix_translation( arg.translation ) * matrix_rotation( arg.rotation); }

    constexpr
    PROC matrix_projection_orthographic( scene_camera arg ) -> matrix4_f32
    {
        // Clip Plane Dimensions
        /* Near */  f32 n = arg.near_clip;
        /* Far */   f32 f = arg.far_clip;
        // NOTE: aspect divide doesn't seem to be nessesary
        /* Right */ f32 r = (arg.sensor_size.x / 2.0f);
        /* Left */  f32 l = -r;
        /* Top */   f32 t = (arg.sensor_size.y / 2.0f);
        /* Bottom */f32 b = -t;

        /* This is rearranged for z up, x forward, y right, Unreal/Tachyon coordinates

           NOTE: This used to be X right to make it a bit like screen coordinates,
           but I think that's a bit stupid and using forward-up-right declerations
           is much more user friendly. Additionally it means coordinate versions are
           done in one time constants, not constantly throughout the code.

           NOTE: This is also a Vulkan specific function. It generates a Vulkan
           compatible projection but the coordinate rearrangement to NDC is performed
           later. This does format depth in 0-1.0 however.*/
        return matrix4_f32 {
            1/(f-n),    0.0f,       0.0f,       -n/(f-n),
            0.0f,       2/(r-l),    0.0f,       -(r+l) / (r-l),
            0.0f,       0.0f,       2/(t-b),    -(t+b)/(t-b),
            0.0f,       0.0f,       0.0f,       1.0f
        };
    }

    constexpr
    PROC matrix_projection_perspective( scene_camera arg ) -> matrix4_f32
    {
        f32 camera_width = std::round( arg.sensor_size.x );
        f32 aspect_ratio_vh = arg.sensor_size.y / arg.sensor_size.x;
        // Clip Plane Dimensions
        /* Near */  f32 n = arg.near_clip;
        /* Far */   f32 f = arg.far_clip;
        /* Right */ f32 r = -(camera_width / 2.0f) / aspect_ratio_vh;
        /* Left */  f32 l = -r;
        /* Top */   f32 t = (camera_width / 2.0f);
        /* Bottom */f32 b = -t;

        // TODO: Temporary fix cuz too lazy to transpose algorithm.
        // TODO:. Well... This is for NDC coordinates...
        return matrix4_f32 {
            (2.f*n) / (r-l),       0.f,               0.0f,         0,
            0.f,                   (2.f*n) / (t-b),   0.0f,         0,
            (r+l) / (r-l),         (t+b)/(t-b),    -(f+n)/(f-n),    -1,
            0.f,                   0.f,        -(2.f*f*n)/(f-n),    0
        };
    }

    constexpr
    PROC v3_f32_fru( f32 forward, f32 right, f32 up ) -> v3_f32
    {   return v3_f32{ forward, right, up };
    }

    constexpr
    PROC v3_f32_luf( f32 left, f32 up, f32 forward ) -> v3_f32
    {
        return v3_f32 { forward, -left, up };
    }

    // TODO: Add front face???
    inline
    PROC geometry_rectangle( v3_f32 size ) -> array<v3_f32>
    {
        f32 w = size.x/2;
        f32 h = size.y/2;
        // Counter clockwise
        array<v3_f32> result = {
            { 0.0, -w,  h },
            { 0.0,  w, -h },
            { 0.0,  w,  h },

            { 0.0, -w,  h },
            { 0.0, -w, -h },
            { 0.0,  w, -h },
        };
        return result;
    }

    enum class e_triangulation : i32
    {
        grid,
        fan,
        strip,
        ear_clipping
    };

    inline
    PROC geometry_circle(
        f32 radius, f32 segments, e_triangulation triangulation = e_triangulation::fan )
    -> array<v3_f32>
    {
        ERROR_GUARD( triangulation == e_triangulation::fan, "" );
        array<v3_f32> result;
        f32 angle = 0;
        f32 next_angle = 0;
        f32 segment_arc = (6.283185307 / segments);
        v3_f32 point;
        v3_f32 point2;
        for (i32 i_segment=0; i_segment < segments; ++i_segment)
        {
            // We make points clockwise but wind the triangles anti-clockwise (front-face)
            next_angle += segment_arc;

            point = {
                0.0,                  // Forward axis not used, 2D
                sinf(angle) * radius, // opposite is Up/Down axis
                cosf(angle) * radius // adjacent is Right/Left axis
            };
            point2 = {
                0.0,
                sinf(next_angle) * radius, // opposite is Up/Down axis
                cosf(next_angle) * radius // adjacent is Right/Left axis
            };
            /* We make the first vertex on the outside the first vertex of each
               triangle don't overlap in the middle for debugging convenience */
            result.push_back( point );
            result.push_back( v3_f32{0.0} );
            result.push_back( point2 );

            angle += segment_arc;
        }
        return result;
    }

    inline
    PROC geometry_elipse( f32 major_radius, f32 minor_radius, f32 segments ) -> array<v3_f32>
    {
        return {};
    }

    inline
    PROC geometry_cube( f32 width, f32 height = 0, f32 depth = 0 ) -> array<v3_f32>
    {
        // Half width
        f32 w = width/2;
        f32 h = (height ? height/2 : w);
        f32 d = (depth ? depth/2 : h);
        // Counter-Clickwise faces
        array<v3_f32> result = {
            // front top-right tri
            v3_f32_fru( -d, -w, h ),           // 1
            v3_f32_fru( -d,  w, -h ),          // 2
            v3_f32_fru( -d,  w, h ),           // 3
            // front bottom-left tri
            v3_f32_fru( -d,  -w, h ),          // 4
            v3_f32_fru( -d,  -w, -h ),         // 5
            v3_f32_fru( -d,  w, -h ),          // 6
            // left bottom-right
            v3_f32_fru( -d,  -w, h ),          // 7
            v3_f32_fru( d,  -w, -h ),          // 8
            v3_f32_fru( -d,  -w, -h ),         // 9
            // left top-right
            v3_f32_fru( -d,  -w, h ),          // 10
            v3_f32_fru( d,  -w, h ),            // 11
            v3_f32_fru( d,  -w, -h ),           // 12
            // top left-forward
            v3_f32_fru( -d, -w, h ),            // 13
            v3_f32_fru( d, w, h ),              // 14
            v3_f32_fru( d, -w, h ),             // 15
            // top right-backward
            v3_f32_fru( -d,  -w, h ),           // 16
            v3_f32_fru( -d,  w, h ),            // 17
            v3_f32_fru( d,  w, h ),             // 18
            // right top-left
            v3_f32_fru( d,  w, h ),             // 19
            v3_f32_fru( -d,  w, h ),            // 20
            v3_f32_fru( -d,  w, -h ),           // 21
            // right bottom-right
            v3_f32_fru( d,  w, h ),             // 22
            v3_f32_fru( -d,  w, -h ),           // 23
            v3_f32_fru( d,  w, -h ),            // 24
            // back bottom-left
            v3_f32_fru( d,  w, h ),             // 25
            v3_f32_fru( d,  w, -h ),            // 26
            v3_f32_fru( d,  -w, -h ),           // 27
            // back top-right
            v3_f32_fru( d,  w, h ),             // 28
            v3_f32_fru( d, -w, -h ),            // 29
            v3_f32_fru( d, -w, h ),             // 30
            // bottom right-back
            v3_f32_fru( d, -w, -h ),            // 31
            v3_f32_fru( d, w, -h ),             // 32
            v3_f32_fru( -d, w, -h ),            // 33
            // bottom left-forward
            v3_f32_fru( d, -w, -h ),            // 34
            v3_f32_fru( -d, w, -h ),            // 35
            v3_f32_fru( -d, -w, -h ),           // 36
        };
        return result;
    }

    inline
    PROC geometry_sphere( f32 radius ) -> array<v3_f32>
    {
        return {};
    }

    inline
    PROC geometry_torus( f32 radius_ring, f32 radius_cross, f32 segments ) -> array<v3_f32>
    {
        return {};
    }


    struct geometry_torus_args
    {
        array<v3_f32> ring_shape;
        f32 radius_ring = 0;
        f32 ring_segments = 0;
        f32 twist = 0 ;
        f32 twist_phase = 0;
    };
    inline
    PROC geometry_torus_generic( geometry_torus_args args ) -> array<v3_f32>
    {
        return {};
    }

    inline
    PROC geometry_spine() -> array<v3_f32>
    {
        return {};
    }

    inline
    PROC geometry_pipe() -> array<v3_f32>
    {
        return {};
    }

    inline
    PROC geometry_extrude_2d( array<v3_f32> geometry ) -> array<v3_f32>
    {
        return {};
    }

    inline
    PROC geometry_extrude_faces( array<v3_f32> geometry, array<i32> target_faces ) -> array<v3_f32>
    {
        return {};
    }

    // TODO: Sphere
    // TODO: Torus
    // TODO: Cylinder
    // TODO: Cone
    // TODO: Cuboid
    // TODO: N Base Pyramid
    // TODO: Triangular Prism
    // TODO: N Prism

        // Conversion
            // Spherical coordinates
            TYON_CUDA_SHARED
            PROC cartesian_to_spherical(const v3_f32 cartesian) -> v3_f32;

            TYON_CUDA_SHARED
            PROC spherical_to_cartesian(const v3_f32 spherical) -> v3_f32;



        // Utility
            /** Absolute() or abs() value.

                Has the effect or removing the the negative part of the number.

                NOTE: This is  a type safe version because the  built in cstdlib
                version  are  quite  error  prone and  have  lots  of  undefined
                behaviour.   With   the   help   of   some   template   function
                ovelroads/template  specialization  we  can  gurantee  only  the
                correct version can ever be called.

                This  is  because  template  specializations  have  the  special
                property that they do not do automatic type casting.

                According to some sources non std::abs is very dangerous and can
                truncate numbers randomally on top of normal casting issues.

                This is the generic version using long double. Other other
                primitive will get it's own overload.

                NOTE: CUDA templates get stamped out into the header when device
                code so need to be inline
            */
            template <typename t_numberic> TYON_CUDA_SHARED inline
            PROC absolute( const t_numberic arg ) -> t_numberic
            {   return fabsl( arg ); }


            template <> TYON_CUDA_SHARED inline
            PROC absolute<f32>( const f32 arg ) -> f32
            {   return fabsf( arg ); }

            /* NOTE: CUDA does not support fabsl, long doubles are rarely used anyway */
            template <> TYON_CUDA_SHARED inline
            PROC absolute<f64>( const f64 arg ) -> f64
            {   return fabs( arg ); }

            //* NOTE: Don't be an idiot like I did and try to define absolute for an unsigned integer */

            template <> TYON_CUDA_SHARED inline
            PROC absolute<i8>( const i8 arg ) -> i8
            {   return static_cast<i8>( abs( arg ) ); }

            template <> TYON_CUDA_SHARED inline
            PROC absolute<i16>( const i16 arg ) -> i16
            {   return static_cast<i16>( abs( arg ) ); }

            template <> TYON_CUDA_SHARED inline
            PROC absolute<i32>( const i32 arg ) -> i32
            {   return abs( arg ); }

            template <> TYON_CUDA_SHARED inline
            PROC absolute<i64>( const i64 arg ) -> i64
            {   return llabs( arg ); }

            /** Clamp i64 to stay inside range of a u32, used for deterministic casting.

                NOTE:  This  is  not  guranteed to  give  your  algorithms  correct
                behaviour,  it  is  just  *deterministic* behaviour.  It  is  never
                undefined behaviour to use this function and all values will map to
                a consistent value. */
            constexpr TYON_CUDA_SHARED
            PROC clamp_u32( i64 arg )
            {   using T = i64;
                T low_clamp = (arg > 0 ? arg : 0 );
                T type_max = UINT32_MAX;
                T high_low_clamp = (low_clamp < type_max ? low_clamp : type_max);
                return static_cast<u32>( high_low_clamp );
            }

            /** Clamp i64 to stay inside range of a u32, used for deterministic casting.

                NOTE:  This  is  not  guranteed to  give  your  algorithms  correct
                behaviour,  it  is  just  *deterministic* behaviour.  It  is  never
                undefined behaviour to use this function and all values will map to
                a consistent value. */
            constexpr TYON_CUDA_SHARED
            PROC clamp_u32( u64 arg )
            {   using T = u64;
                T low_clamp = (arg > 0 ? arg : 0 );
                T type_max = UINT32_MAX;
                T high_low_clamp = (low_clamp < type_max ? low_clamp : type_max);
                return static_cast<u32>( high_low_clamp );
            }

            constexpr TYON_CUDA_SHARED
            PROC clamp_u64( i64 arg )
            {   using T = i64;
                T low_clamp = (arg > 0 ? arg : 0 );
                T type_max = INT64_MAX;
                T high_low_clamp = (low_clamp < type_max ? low_clamp : type_max);
                return static_cast<u64>( high_low_clamp );
            }

            /** Clamp u32 to stay inside range of a u32, used for deterministic casting.

                NOTE:  This  is  not  guranteed to  give  your  algorithms  correct
                behaviour,  it  is  just  *deterministic* behaviour.  It  is  never
                undefined behaviour to use this function and all values will map to
                a consistent value. */
            constexpr TYON_CUDA_SHARED
            PROC clamp_i32( u32 arg )
            {   using T = decltype(arg);
                // Unsigned can never be negative, don't need a low clamp
                T type_max = INT32_MAX;
                T high_low_clamp = (arg < type_max ? arg : type_max);
                return static_cast<i32>( high_low_clamp );
            }

            constexpr TYON_CUDA_SHARED
            PROC clamp_i32( i64 arg )
            {   using T = decltype(arg);
                // Unsigned can never be negative, don't need a low clamp
                T type_max = INT32_MAX;
                T high_low_clamp = (arg < type_max ? arg : type_max);
                return static_cast<i32>( high_low_clamp );
            }

            /** Clamp u64 to stay inside range of a i64, used for deterministic casting.

                NOTE:  This  is  not  guranteed to  give  your  algorithms  correct
                behaviour,  it  is  just  *deterministic* behaviour.  It  is  never
                undefined behaviour to use this function and all values will map to
                a consistent value. */
            constexpr TYON_CUDA_SHARED
            PROC clamp_i64( u64 arg )
            {   using T = decltype(arg);
                // Unsigned can never be negative, don't need a low clamp
                T type_max = INT64_MAX;
                T high_low_clamp = (arg < type_max ? arg : type_max);
                return static_cast<i64>( high_low_clamp );
            }

            // NOTE: This template replaces multiple minimum functions
            template <typename T> TYON_CUDA_SHARED constexpr inline
            PROC minimum(const T a, const T b) -> T
            {   if(a < b)
                { return a; }
                return b;
            }

            /* DOCS NOTE: I don't use const for 4 main reasons,
               1 - it's noisy and makes small amounts of code harder to read

               2 - constness is mostly about  the programmer being stupid in C++
               "you  are  likely  to  make  a mistake  so  you  should  babygate
               yourself", I think outside of specific contexts this is minimally
               helpful and you can't really  patch over bad and bad programmers-
               either the  programmer should  improve or  be told  to work  on a
               different project.

               3 - This is more complicated. const is... Viral...  When you use
               it a lot it leaks down into other code, and causes incompatible
               type errors.  This is not only error prone and tricky to use, but
               it wastes a huge amount of mental overhead trying to make it fit
               const in.

               4 -  const is  a lie. I  said earlier const  is mostly  about the
               programmer being stupid. I really  meant that. You see, const has
               no physical  meaning in  the hardware, there's  no such  thing as
               "const" memory", there's READ_ONLY  memory, but that usually goes
               in pages, >4 KiB.

               This is important when reasoning about performance and aliasing
               rules.  Because as far as the compiler is concerned- many times,
               it can't assume that 'const T x' is safe to optimize out, or
               cache. This is one of the rationale behind using references (T)
               in the first place. Yet it is sometimes wrong, because it is
               still a mutable pointer, and still often had indirection and
               uncachable access. On the other hand pass-by-value you can safely
               assume you are the sole owner. The trade off being, you spend
               some memory for this.

               But in my view, always expensive is a better tradeoff than
               "sometimes" faster.
            */

            template <typename T> TYON_CUDA_SHARED constexpr inline
            PROC maximum(const T a, const T b) -> T
            {   if(a > b)
                { return a; }
                return b;
            }

            TYON_CUDA_SHARED constexpr
            PROC array_2d_index( vec2_i64 position, vec2_i64 size ) -> i64
            {
                i64 index = position.x + (position.y * size.x);
                i64 index_max = (size.x * size.y);
                // TODO: Check sign
                bool out_of_bounds = (index >= index_max);
                if (out_of_bounds) { return -1; }

                return index;
            }

        TYON_CUDA_SHARED constexpr
        PROC array_2d_index( vec2_i64 position, vec2_i64 size, i64 stride ) -> i64
        {
            i64 index = position.x + (position.y * stride);
            i64 index_max = (size.x * size.y);
            // TODO: Check sign
            bool out_of_bounds = (index >= index_max);

            return (out_of_bounds ? -1 : index);
        }

        TYON_CUDA_SHARED constexpr
        PROC array_2d_inverse_index( i64 position, vec2_i64 size ) -> vec2_i64
        {
            vec2_i64 result {};
            i64 size_x_remainder = (position % size.x);
            result.x = size_x_remainder;
            result.y = (position - size_x_remainder) / size.y;
            return result;
        }

        TYON_CUDA_SHARED constexpr
        PROC array_2d_inverse_index( i64 position, vec2_i64 size, i64 stride ) -> vec2_i64
        {
            vec2_i64 result {};
            i64 size_x_remainder = (position % size.x);
            result.x = size_x_remainder;
            result.y = (position - size_x_remainder) / size.y;
            return result;
        }


    template <typename T>
    TYON_CUDA_SHARED constexpr
    PROC transfer_quantity( T* sender, T* receiver, T quantity ) -> fresult
    {
        ERROR_GUARD( *sender >= 0, "Negative sender quantities are impossible" );
        bool quantity_exceeds_sender = (quantity > *sender);
        if (quantity_exceeds_sender) { return false; }
        *sender -= quantity;
        *receiver += quantity;
        return true;
    }

    template <typename T>
    TYON_CUDA_SHARED constexpr
    PROC transfer_quantity_all( T* sender, T* receiver ) -> fresult
    {
        ERROR_GUARD( *sender >= 0, "Negative sender quantities are impossible" );
        T quantity = *sender;
        *sender = 0;
        *receiver += quantity;
        return true;
    }

    // usng fstring = std::string;;
    constexpr fstring
    format_as( v3_f32 arg )
    { return fmt::format( "[{:.5} {:.5} {:.5}]", arg.x, arg.y, arg.z ); }

    inline fstring
    format_as( v2_f32 arg )
    { return fmt::format( "[{:.5} {:.5}]", arg.x, arg.y ); }

}
