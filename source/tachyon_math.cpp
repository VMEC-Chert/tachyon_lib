
namespace tyon
{
    /** Types */
        // Matrices
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f32::matrix2_f32() : m11(0.0f), m12(0.0f), m21(0.0f), m22(0.0f) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f32::matrix2_f32( f32 arg ) : m11(arg), m12(arg), m21(arg), m22(arg) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f32::matrix2_f32( f32 m11, f32 m12, f32 m21, f32 m22) : m11(m11), m12(m12), m21(m21), m22(m22) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f32::matrix2_f32( f64 arg ) {}

        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f64::matrix2_f64() : m11(0.0), m12(0.0), m21(0.0), m22(0.0) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f64::matrix2_f64( f64 arg ) : m11(arg), m12(arg), m21(arg), m22(arg) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f64::matrix2_f64( f64 m11, f64 m12, f64 m21, f64 m22) : m11(m11), m12(m12), m21(m21), m22(m22) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix2_f64::matrix2_f64( f32 arg ) {}

        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f32::matrix3_f32() : m11(0.0f), m12(0.0f), m13(0.0f), m21(0.0f), m22(0.0f), m23(0.0f), m31(0.0f), m32(0.0f), m33(0.0f) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f32::matrix3_f32( f32 arg ) : m11(arg), m12(arg), m13(arg), m21(arg), m22(arg), m23(arg), m31(arg), m32(arg), m33(arg) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f32::matrix3_f32( f32 m11, f32 m12, f32 m13, f32 m21, f32 m22, f32 m23, f32 m31, f32 m32, f32 m33) : m11(m11), m12(m12), m13(m13), m21(m21), m22(m22), m23(m23), m31(m31), m32(m32), m33(m33) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f32::matrix3_f32( f64 arg ) {}

        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f64::matrix3_f64() : m11(0.0), m12(0.0), m13(0.0), m21(0.0), m22(0.0), m23(0.0), m31(0.0), m32(0.0), m33(0.0) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f64::matrix3_f64( f32 arg ) : m11(arg), m12(arg), m13(arg), m21(arg), m22(arg), m23(arg), m31(arg), m32(arg), m33(arg) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f64::matrix3_f64( f32 m11, f32 m12, f32 m13, f32 m21, f32 m22, f32 m23, f32 m31, f32 m32, f32 m33) : m11(m11), m12(m12), m13(m13), m21(m21), m22(m22), m23(m23), m31(m31), m32(m32), m33(m33) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix3_f64::matrix3_f64( f64 arg ) {}

        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f32::matrix4_f32() : m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f), m21(0.0f), m22(0.0f), m23(0.0f), m24(0.0f), m31(0.0f), m32(0.0f), m33(0.0f), m34(0.0f), m41(0.0f), m42(0.0f), m43(0.0f), m44(0.0f) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f32::matrix4_f32( f32 arg ) : m11(arg), m12(arg), m13(arg), m14(arg), m21(arg), m22(arg), m23(arg), m24(arg), m31(arg), m32(arg), m33(arg), m34(arg), m41(arg), m42(arg), m43(arg), m44(arg) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f32::matrix4_f32( f32 m11, f32 m12, f32 m13, f32 m14, f32 m21, f32 m22, f32 m23, f32 m24, f32 m31, f32 m32, f32 m33, f32 m34, f32 m41, f32 m42, f32 m43, f32 m44) : m11(m11), m12(m12), m13(m13), m14(m14), m21(m21), m22(m22), m23(m23), m24(m24), m31(m31), m32(m32), m33(m33), m34(m34), m41(m41), m42(m42), m43(m43), m44(m44) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f32::matrix4_f32( f64 arg ) {}

        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f64::matrix4_f64() : m11(0.0), m12(0.0), m13(0.0), m14(0.0), m21(0.0), m22(0.0), m23(0.0), m24(0.0), m31(0.0), m32(0.0), m33(0.0), m34(0.0), m41(0.0), m42(0.0), m43(0.0), m44(0.0) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f64::matrix4_f64( f64 arg ) : m11(arg), m12(arg), m13(arg), m14(arg), m21(arg), m22(arg), m23(arg), m24(arg), m31(arg), m32(arg), m33(arg), m34(arg), m41(arg), m42(arg), m43(arg), m44(arg) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f64::matrix4_f64( f64 m11, f64 m12, f64 m13, f64 m14, f64 m21, f64 m22, f64 m23, f64 m24, f64 m31, f64 m32, f64 m33, f64 m34, f64 m41, f64 m42, f64 m43, f64 m44) : m11(m11), m12(m12), m13(m13), m14(m14), m21(m21), m22(m22), m23(m23), m24(m24), m31(m31), m32(m32), m33(m33), m34(m34), m41(m41), m42(m42), m43(m43), m44(m44) {}
        TYON_CUDA_SHARED
        CONSTRUCTOR matrix4_f64::matrix4_f64( f32 arg ) {}



    /** Operators */
        // Vector-Matrix
            TYON_CUDA_SHARED
            PROC operator*(const v2_f32 v0, const matrix2_f32 m0) -> v2_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f32 m0, const v2_f32 v0) -> v2_f32
            {
                v2_f32 result;
                result.x = m0.m11 * v0.x + m0.m12 * v0.y;
                result.y = m0.m21 * v0.x + m0.m22 * v0.y;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const v3_f32 v0, const matrix3_f32 m0) -> v3_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f32 m0, const v3_f32 v0) -> v3_f32
            {
                v3_f32 result;
                result.x = m0.m11 * v0.x + m0.m12 * v0.y + m0.m13 * v0.z;
                result.y = m0.m21 * v0.x + m0.m22 * v0.y + m0.m23 * v0.z;
                result.z = m0.m31 * v0.x + m0.m32 * v0.y + m0.m33 * v0.z;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const v4_f32 v0, const matrix4_f32 m0) -> v4_f32;

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f32 m0, const v4_f32 v0) -> v4_f32
            {
                v4_f32 result;
                result.x = m0.m11 * v0.x + m0.m12 * v0.y + m0.m13 * v0.z + m0.m14 * v0.w;
                result.y = m0.m21 * v0.x + m0.m22 * v0.y + m0.m23 * v0.z + m0.m24 * v0.w;
                result.z = m0.m31 * v0.x + m0.m32 * v0.y + m0.m33 * v0.z + m0.m34 * v0.w;
                result.w = m0.m41 * v0.x + m0.m42 * v0.y + m0.m43 * v0.z + m0.m44 * v0.w;
                return result;
            }



        // Matrices
            // Matrix Addition
            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f32 m0, const matrix2_f32 m1) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = m0.m11 + m1.m11;
                result.m12 = m0.m12 + m1.m12;

                result.m21 = m0.m21 + m1.m21;
                result.m22 = m0.m22 + m1.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f64 m0, const matrix2_f64 m1) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = m0.m11 + m1.m11;
                result.m12 = m0.m12 + m1.m12;

                result.m21 = m0.m21 + m1.m21;
                result.m22 = m0.m22 + m1.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f32 m0, const matrix3_f32 m1) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = m0.m11 + m1.m11;
                result.m12 = m0.m12 + m1.m12;
                result.m13 = m0.m13 + m1.m13;

                result.m21 = m0.m21 + m1.m21;
                result.m22 = m0.m22 + m1.m22;
                result.m23 = m0.m23 + m1.m23;

                result.m31 = m0.m31 + m1.m31;
                result.m32 = m0.m32 + m1.m32;
                result.m33 = m0.m33 + m1.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f64 m0, const matrix3_f64 m1) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = m0.m11 + m1.m11;
                result.m12 = m0.m12 + m1.m12;
                result.m13 = m0.m13 + m1.m13;

                result.m21 = m0.m21 + m1.m21;
                result.m22 = m0.m22 + m1.m22;
                result.m23 = m0.m23 + m1.m23;

                result.m31 = m0.m31 + m1.m31;
                result.m32 = m0.m32 + m1.m32;
                result.m33 = m0.m33 + m1.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f32 m0, const matrix4_f32 m1) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = m0.m11 + m1.m11;
                result.m12 = m0.m12 + m1.m12;
                result.m13 = m0.m13 + m1.m13;
                result.m14 = m0.m14 + m1.m14;

                result.m21 = m0.m21 + m1.m21;
                result.m22 = m0.m22 + m1.m22;
                result.m23 = m0.m23 + m1.m23;
                result.m24 = m0.m24 + m1.m24;

                result.m31 = m0.m31 + m1.m31;
                result.m32 = m0.m32 + m1.m32;
                result.m33 = m0.m33 + m1.m33;
                result.m34 = m0.m34 + m1.m34;

                result.m41 = m0.m41 + m1.m41;
                result.m42 = m0.m42 + m1.m42;
                result.m43 = m0.m43 + m1.m43;
                result.m44 = m0.m44 + m1.m44;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f64 m0, const matrix4_f64 m1) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = m0.m11 + m1.m11;
                result.m12 = m0.m12 + m1.m12;
                result.m13 = m0.m13 + m1.m13;
                result.m14 = m0.m14 + m1.m14;

                result.m21 = m0.m21 + m1.m21;
                result.m22 = m0.m22 + m1.m22;
                result.m23 = m0.m23 + m1.m23;
                result.m24 = m0.m24 + m1.m24;

                result.m31 = m0.m31 + m1.m31;
                result.m32 = m0.m32 + m1.m32;
                result.m33 = m0.m33 + m1.m33;
                result.m34 = m0.m34 + m1.m34;

                result.m41 = m0.m41 + m1.m41;
                result.m42 = m0.m42 + m1.m42;
                result.m43 = m0.m43 + m1.m43;
                result.m44 = m0.m44 + m1.m44;
                return result;
            }

            // Scalar Addition
            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f32 m0, const f32 s0) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = m0.m11 + s0;
                result.m12 = m0.m12 + s0;
                result.m21 = m0.m21 + s0;
                result.m22 = m0.m22 + s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix2_f32 m0) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = s0 + m0.m11;
                result.m12 = s0 + m0.m12;
                result.m21 = s0 + m0.m21;
                result.m22 = s0 + m0.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix2_f64 m0, const f64 s0) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = m0.m11 + s0;
                result.m12 = m0.m12 + s0;
                result.m21 = m0.m21 + s0;
                result.m22 = m0.m22 + s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const f64 s0, const matrix2_f64 m0) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = s0 + m0.m11;
                result.m12 = s0 + m0.m12;
                result.m21 = s0 + m0.m21;
                result.m22 = s0 + m0.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f32 m0, const f32 s0) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = m0.m11 + s0;
                result.m12 = m0.m12 + s0;
                result.m13 = m0.m13 + s0;

                result.m21 = m0.m21 + s0;
                result.m22 = m0.m22 + s0;
                result.m23 = m0.m23 + s0;

                result.m31 = m0.m31 + s0;
                result.m32 = m0.m32 + s0;
                result.m33 = m0.m33 + s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix3_f32 m0) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = s0 + m0.m11;
                result.m12 = s0 + m0.m12;
                result.m13 = s0 + m0.m13;

                result.m21 = s0 + m0.m21;
                result.m22 = s0 + m0.m22;
                result.m23 = s0 + m0.m23;

                result.m31 = s0 + m0.m31;
                result.m32 = s0 + m0.m32;
                result.m33 = s0 + m0.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix3_f64 m0, const f64 s0) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = m0.m11 + s0;
                result.m12 = m0.m12 + s0;
                result.m13 = m0.m13 + s0;

                result.m21 = m0.m21 + s0;
                result.m22 = m0.m22 + s0;
                result.m23 = m0.m23 + s0;

                result.m31 = m0.m31 + s0;
                result.m32 = m0.m32 + s0;
                result.m33 = m0.m33 + s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix3_f64 m0) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = s0 + m0.m11;
                result.m12 = s0 + m0.m12;
                result.m13 = s0 + m0.m13;

                result.m21 = s0 + m0.m21;
                result.m22 = s0 + m0.m22;
                result.m23 = s0 + m0.m23;

                result.m31 = s0 + m0.m31;
                result.m32 = s0 + m0.m32;
                result.m33 = s0 + m0.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f32 m0, const f32 s0) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = m0.m11 + s0;
                result.m12 = m0.m12 + s0;
                result.m13 = m0.m13 + s0;
                result.m14 = m0.m14 + s0;

                result.m21 = m0.m21 + s0;
                result.m22 = m0.m22 + s0;
                result.m23 = m0.m23 + s0;
                result.m24 = m0.m24 + s0;

                result.m31 = m0.m31 + s0;
                result.m32 = m0.m32 + s0;
                result.m33 = m0.m33 + s0;
                result.m34 = m0.m34 + s0;

                result.m41 = m0.m41 + s0;
                result.m42 = m0.m42 + s0;
                result.m43 = m0.m43 + s0;
                result.m44 = m0.m44 + s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix4_f32 m0) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = s0 + m0.m11;
                result.m12 = s0 + m0.m12;
                result.m13 = s0 + m0.m13;
                result.m14 = s0 + m0.m14;

                result.m21 = s0 + m0.m21;
                result.m22 = s0 + m0.m22;
                result.m23 = s0 + m0.m23;
                result.m24 = s0 + m0.m24;

                result.m31 = s0 + m0.m31;
                result.m32 = s0 + m0.m32;
                result.m33 = s0 + m0.m33;
                result.m34 = s0 + m0.m34;

                result.m41 = s0 + m0.m41;
                result.m42 = s0 + m0.m42;
                result.m43 = s0 + m0.m43;
                result.m44 = s0 + m0.m44;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const matrix4_f64 m0, const f64 s0) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = m0.m11 + s0;
                result.m12 = m0.m12 + s0;
                result.m13 = m0.m13 + s0;
                result.m14 = m0.m14 + s0;

                result.m21 = m0.m21 + s0;
                result.m22 = m0.m22 + s0;
                result.m23 = m0.m23 + s0;
                result.m24 = m0.m24 + s0;

                result.m31 = m0.m31 + s0;
                result.m32 = m0.m32 + s0;
                result.m33 = m0.m33 + s0;
                result.m34 = m0.m34 + s0;

                result.m41 = m0.m41 + s0;
                result.m42 = m0.m42 + s0;
                result.m43 = m0.m43 + s0;
                result.m44 = m0.m44 + s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator+(const f32 s0, const matrix4_f64 m0) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = s0 + m0.m11;
                result.m12 = s0 + m0.m12;
                result.m13 = s0 + m0.m13;
                result.m14 = s0 + m0.m14;

                result.m21 = s0 + m0.m21;
                result.m22 = s0 + m0.m22;
                result.m23 = s0 + m0.m23;
                result.m24 = s0 + m0.m24;

                result.m31 = s0 + m0.m31;
                result.m32 = s0 + m0.m32;
                result.m33 = s0 + m0.m33;
                result.m34 = s0 + m0.m34;

                result.m41 = s0 + m0.m41;
                result.m42 = s0 + m0.m42;
                result.m43 = s0 + m0.m43;
                result.m44 = s0 + m0.m44;
                return result;
            }

            // Matrix Subtraction
            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f32 m0, const matrix2_f32 m1) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = m0.m11 - m1.m11;
                result.m12 = m0.m12 - m1.m12;

                result.m21 = m0.m21 - m1.m21;
                result.m22 = m0.m22 - m1.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f64 m0, const matrix2_f64 m1) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = m0.m11 - m1.m11;
                result.m12 = m0.m12 - m1.m12;

                result.m21 = m0.m21 - m1.m21;
                result.m22 = m0.m22 - m1.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f32 m0, const matrix3_f32 m1) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = m0.m11 - m1.m11;
                result.m12 = m0.m12 - m1.m12;
                result.m13 = m0.m13 - m1.m13;

                result.m21 = m0.m21 - m1.m21;
                result.m22 = m0.m22 - m1.m22;
                result.m23 = m0.m23 - m1.m23;

                result.m31 = m0.m31 - m1.m31;
                result.m32 = m0.m32 - m1.m32;
                result.m33 = m0.m33 - m1.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f64 m0, const matrix3_f64 m1) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = m0.m11 - m1.m11;
                result.m12 = m0.m12 - m1.m12;
                result.m13 = m0.m13 - m1.m13;

                result.m21 = m0.m21 - m1.m21;
                result.m22 = m0.m22 - m1.m22;
                result.m23 = m0.m23 - m1.m23;

                result.m31 = m0.m31 - m1.m31;
                result.m32 = m0.m32 - m1.m32;
                result.m33 = m0.m33 - m1.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f32 m0, const matrix4_f32 m1) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = m0.m11 - m1.m11;
                result.m12 = m0.m12 - m1.m12;
                result.m13 = m0.m13 - m1.m13;
                result.m14 = m0.m14 - m1.m14;

                result.m21 = m0.m21 - m1.m21;
                result.m22 = m0.m22 - m1.m22;
                result.m23 = m0.m23 - m1.m23;
                result.m24 = m0.m24 - m1.m24;

                result.m31 = m0.m31 - m1.m31;
                result.m32 = m0.m32 - m1.m32;
                result.m33 = m0.m33 - m1.m33;
                result.m34 = m0.m34 - m1.m34;

                result.m41 = m0.m41 - m1.m41;
                result.m42 = m0.m42 - m1.m42;
                result.m43 = m0.m43 - m1.m43;
                result.m44 = m0.m44 - m1.m44;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f64 m0, const matrix4_f64 m1) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = m0.m11 - m1.m11;
                result.m12 = m0.m12 - m1.m12;
                result.m13 = m0.m13 - m1.m13;
                result.m14 = m0.m14 - m1.m14;

                result.m21 = m0.m21 - m1.m21;
                result.m22 = m0.m22 - m1.m22;
                result.m23 = m0.m23 - m1.m23;
                result.m24 = m0.m24 - m1.m24;

                result.m31 = m0.m31 - m1.m31;
                result.m32 = m0.m32 - m1.m32;
                result.m33 = m0.m33 - m1.m33;
                result.m34 = m0.m34 - m1.m34;

                result.m41 = m0.m41 - m1.m41;
                result.m42 = m0.m42 - m1.m42;
                result.m43 = m0.m43 - m1.m43;
                result.m44 = m0.m44 - m1.m44;
                return result;
            }

            // Scalar Subtraction 
            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f32 m0, const f32 s0) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = m0.m11 - s0;
                result.m12 = m0.m12 - s0;
                result.m21 = m0.m21 - s0;
                result.m22 = m0.m22 - s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix2_f32 m0) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = s0 - m0.m11;
                result.m12 = s0 - m0.m12;
                result.m21 = s0 - m0.m21;
                result.m22 = s0 - m0.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix2_f64 m0, const f64 s0) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = m0.m11 - s0;
                result.m12 = m0.m12 - s0;
                result.m21 = m0.m21 - s0;
                result.m22 = m0.m22 - s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const f64 s0, const matrix2_f64 m0) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = s0 - m0.m11;
                result.m12 = s0 - m0.m12;
                result.m21 = s0 - m0.m21;
                result.m22 = s0 - m0.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f32 m0, const f32 s0) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = m0.m11 - s0;
                result.m12 = m0.m12 - s0;
                result.m13 = m0.m13 - s0;

                result.m21 = m0.m21 - s0;
                result.m22 = m0.m22 - s0;
                result.m23 = m0.m23 - s0;

                result.m31 = m0.m31 - s0;
                result.m32 = m0.m32 - s0;
                result.m33 = m0.m33 - s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix3_f32 m0) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = s0 - m0.m11;
                result.m12 = s0 - m0.m12;
                result.m13 = s0 - m0.m13;

                result.m21 = s0 - m0.m21;
                result.m22 = s0 - m0.m22;
                result.m23 = s0 - m0.m23;

                result.m31 = s0 - m0.m31;
                result.m32 = s0 - m0.m32;
                result.m33 = s0 - m0.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix3_f64 m0, const f64 s0) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = m0.m11 - s0;
                result.m12 = m0.m12 - s0;
                result.m13 = m0.m13 - s0;

                result.m21 = m0.m21 - s0;
                result.m22 = m0.m22 - s0;
                result.m23 = m0.m23 - s0;

                result.m31 = m0.m31 - s0;
                result.m32 = m0.m32 - s0;
                result.m33 = m0.m33 - s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix3_f64 m0) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = s0 - m0.m11;
                result.m12 = s0 - m0.m12;
                result.m13 = s0 - m0.m13;

                result.m21 = s0 - m0.m21;
                result.m22 = s0 - m0.m22;
                result.m23 = s0 - m0.m23;

                result.m31 = s0 - m0.m31;
                result.m32 = s0 - m0.m32;
                result.m33 = s0 - m0.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f32 m0, const f32 s0) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = m0.m11 - s0;
                result.m12 = m0.m12 - s0;
                result.m13 = m0.m13 - s0;
                result.m14 = m0.m14 - s0;

                result.m21 = m0.m21 - s0;
                result.m22 = m0.m22 - s0;
                result.m23 = m0.m23 - s0;
                result.m24 = m0.m24 - s0;

                result.m31 = m0.m31 - s0;
                result.m32 = m0.m32 - s0;
                result.m33 = m0.m33 - s0;
                result.m34 = m0.m34 - s0;

                result.m41 = m0.m41 - s0;
                result.m42 = m0.m42 - s0;
                result.m43 = m0.m43 - s0;
                result.m44 = m0.m44 - s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix4_f32 m0) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = s0 - m0.m11;
                result.m12 = s0 - m0.m12;
                result.m13 = s0 - m0.m13;
                result.m14 = s0 - m0.m14;

                result.m21 = s0 - m0.m21;
                result.m22 = s0 - m0.m22;
                result.m23 = s0 - m0.m23;
                result.m24 = s0 - m0.m24;

                result.m31 = s0 - m0.m31;
                result.m32 = s0 - m0.m32;
                result.m33 = s0 - m0.m33;
                result.m34 = s0 - m0.m34;

                result.m41 = s0 - m0.m41;
                result.m42 = s0 - m0.m42;
                result.m43 = s0 - m0.m43;
                result.m44 = s0 - m0.m44;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const matrix4_f64 m0, const f64 s0) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = m0.m11 - s0;
                result.m12 = m0.m12 - s0;
                result.m13 = m0.m13 - s0;
                result.m14 = m0.m14 - s0;

                result.m21 = m0.m21 - s0;
                result.m22 = m0.m22 - s0;
                result.m23 = m0.m23 - s0;
                result.m24 = m0.m24 - s0;

                result.m31 = m0.m31 - s0;
                result.m32 = m0.m32 - s0;
                result.m33 = m0.m33 - s0;
                result.m34 = m0.m34 - s0;

                result.m41 = m0.m41 - s0;
                result.m42 = m0.m42 - s0;
                result.m43 = m0.m43 - s0;
                result.m44 = m0.m44 - s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator-(const f32 s0, const matrix4_f64 m0) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = s0 - m0.m11;
                result.m12 = s0 - m0.m12;
                result.m13 = s0 - m0.m13;
                result.m14 = s0 - m0.m14;

                result.m21 = s0 - m0.m21;
                result.m22 = s0 - m0.m22;
                result.m23 = s0 - m0.m23;
                result.m24 = s0 - m0.m24;

                result.m31 = s0 - m0.m31;
                result.m32 = s0 - m0.m32;
                result.m33 = s0 - m0.m33;
                result.m34 = s0 - m0.m34;

                result.m41 = s0 - m0.m41;
                result.m42 = s0 - m0.m42;
                result.m43 = s0 - m0.m43;
                result.m44 = s0 - m0.m44;
                return result;
            }

            // Matrix Multiplication
            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f32 m0, const matrix2_f32 m1) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21;
                result.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22;
                result.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21;
                result.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f64 m0, const matrix2_f64 m1) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21;
                result.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22;
                result.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21;
                result.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f32 m0, const matrix3_f32 m1) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21 + m0.m13 * m1.m31;
                result.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22 + m0.m13 * m1.m32;
                result.m13 = m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13 * m1.m33;
                result.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21 + m0.m23 * m1.m31;
                result.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22 + m0.m23 * m1.m32;
                result.m23 = m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23 * m1.m33;
                result.m31 = m0.m31 * m1.m11 + m0.m32 * m1.m21 + m0.m33 * m1.m31;
                result.m32 = m0.m31 * m1.m12 + m0.m32 * m1.m22 + m0.m33 * m1.m32;
                result.m33 = m0.m31 * m1.m13 + m0.m32 * m1.m23 + m0.m33 * m1.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f64 m0, const matrix3_f64 m1) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21 + m0.m13 * m1.m31;
                result.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22 + m0.m13 * m1.m32;
                result.m13 = m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13 * m1.m33;
                result.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21 + m0.m23 * m1.m31;
                result.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22 + m0.m23 * m1.m32;
                result.m23 = m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23 * m1.m33;
                result.m31 = m0.m31 * m1.m11 + m0.m32 * m1.m21 + m0.m33 * m1.m31;
                result.m32 = m0.m31 * m1.m12 + m0.m32 * m1.m22 + m0.m33 * m1.m32;
                result.m33 = m0.m31 * m1.m13 + m0.m32 * m1.m23 + m0.m33 * m1.m33;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f32 m0, const matrix4_f32 m1) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21 + m0.m13 * m1.m31 + m0.m14 * m1.m41;
                result.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22 + m0.m13 * m1.m32 + m0.m14 * m1.m42;
                result.m13 = m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13 * m1.m33 + m0.m14 * m1.m43;
                result.m14 = m0.m11 * m1.m14 + m0.m12 * m1.m24 + m0.m13 * m1.m34 + m0.m14 * m1.m44;
                result.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21 + m0.m23 * m1.m31 + m0.m24 * m1.m41;
                result.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22 + m0.m23 * m1.m32 + m0.m24 * m1.m42;
                result.m23 = m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23 * m1.m33 + m0.m24 * m1.m43;
                result.m24 = m0.m21 * m1.m14 + m0.m22 * m1.m24 + m0.m23 * m1.m34 + m0.m24 * m1.m44;
                result.m31 = m0.m31 * m1.m11 + m0.m32 * m1.m21 + m0.m33 * m1.m31 + m0.m34 * m1.m41;
                result.m32 = m0.m31 * m1.m12 + m0.m32 * m1.m22 + m0.m33 * m1.m32 + m0.m34 * m1.m42;
                result.m33 = m0.m31 * m1.m13 + m0.m32 * m1.m23 + m0.m33 * m1.m33 + m0.m34 * m1.m43;
                result.m34 = m0.m31 * m1.m14 + m0.m32 * m1.m24 + m0.m33 * m1.m34 + m0.m34 * m1.m44;
                result.m41 = m0.m41 * m1.m11 + m0.m42 * m1.m21 + m0.m43 * m1.m31 + m0.m44 * m1.m41;
                result.m42 = m0.m41 * m1.m12 + m0.m42 * m1.m22 + m0.m43 * m1.m32 + m0.m44 * m1.m42;
                result.m43 = m0.m41 * m1.m13 + m0.m42 * m1.m23 + m0.m43 * m1.m33 + m0.m44 * m1.m43;
                result.m44 = m0.m41 * m1.m14 + m0.m42 * m1.m24 + m0.m43 * m1.m34 + m0.m44 * m1.m44;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f64 m0, const matrix4_f64 m1) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = m0.m11 * m1.m11 + m0.m12 * m1.m21 + m0.m13 * m1.m31 + m0.m14 * m1.m41;
                result.m12 = m0.m11 * m1.m12 + m0.m12 * m1.m22 + m0.m13 * m1.m32 + m0.m14 * m1.m42;
                result.m13 = m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13 * m1.m33 + m0.m14 * m1.m43;
                result.m14 = m0.m11 * m1.m14 + m0.m12 * m1.m24 + m0.m13 * m1.m34 + m0.m14 * m1.m44;
                result.m21 = m0.m21 * m1.m11 + m0.m22 * m1.m21 + m0.m23 * m1.m31 + m0.m24 * m1.m41;
                result.m22 = m0.m21 * m1.m12 + m0.m22 * m1.m22 + m0.m23 * m1.m32 + m0.m24 * m1.m42;
                result.m23 = m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23 * m1.m33 + m0.m24 * m1.m43;
                result.m24 = m0.m21 * m1.m14 + m0.m22 * m1.m24 + m0.m23 * m1.m34 + m0.m24 * m1.m44;
                result.m31 = m0.m31 * m1.m11 + m0.m32 * m1.m21 + m0.m33 * m1.m31 + m0.m34 * m1.m41;
                result.m32 = m0.m31 * m1.m12 + m0.m32 * m1.m22 + m0.m33 * m1.m32 + m0.m34 * m1.m42;
                result.m33 = m0.m31 * m1.m13 + m0.m32 * m1.m23 + m0.m33 * m1.m33 + m0.m34 * m1.m43;
                result.m34 = m0.m31 * m1.m14 + m0.m32 * m1.m24 + m0.m33 * m1.m34 + m0.m34 * m1.m44;
                result.m41 = m0.m41 * m1.m11 + m0.m42 * m1.m21 + m0.m43 * m1.m31 + m0.m44 * m1.m41;
                result.m42 = m0.m41 * m1.m12 + m0.m42 * m1.m22 + m0.m43 * m1.m32 + m0.m44 * m1.m42;
                result.m43 = m0.m41 * m1.m13 + m0.m42 * m1.m23 + m0.m43 * m1.m33 + m0.m44 * m1.m43;
                result.m44 = m0.m41 * m1.m14 + m0.m42 * m1.m24 + m0.m43 * m1.m34 + m0.m44 * m1.m44;
                return result;
            }

            // Scalar Multiplication
            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f32 m0, const f32 s0) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix2_f32 m0) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix2_f64 m0, const f64 s0) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const f64 s0, const matrix2_f64 m0) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f32 m0, const f32 s0) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix3_f32 m0) -> matrix3_f32
            {
                matrix3_f32 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix3_f64 m0, const f64 s0) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix3_f64 m0) -> matrix3_f64
            {
                matrix3_f64 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f32 m0, const f32 s0) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;
                result.m14 = m0.m14 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;
                result.m24 = m0.m24 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                result.m34 = m0.m34 * s0;

                result.m41 = m0.m41 * s0;
                result.m42 = m0.m42 * s0;
                result.m43 = m0.m43 * s0;
                result.m44 = m0.m44 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix4_f32 m0) -> matrix4_f32
            {
                matrix4_f32 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;
                result.m14 = m0.m14 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;
                result.m24 = m0.m24 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                result.m34 = m0.m34 * s0;

                result.m41 = m0.m41 * s0;
                result.m42 = m0.m42 * s0;
                result.m43 = m0.m43 * s0;
                result.m44 = m0.m44 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const matrix4_f64 m0, const f64 s0) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;
                result.m14 = m0.m14 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;
                result.m24 = m0.m24 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                result.m34 = m0.m34 * s0;

                result.m41 = m0.m41 * s0;
                result.m42 = m0.m42 * s0;
                result.m43 = m0.m43 * s0;
                result.m44 = m0.m44 * s0;
                return result;
            }

            TYON_CUDA_SHARED
            PROC operator*(const f32 s0, const matrix4_f64 m0) -> matrix4_f64
            {
                matrix4_f64 result;
                result.m11 = m0.m11 * s0;
                result.m12 = m0.m12 * s0;
                result.m13 = m0.m13 * s0;
                result.m14 = m0.m14 * s0;

                result.m21 = m0.m21 * s0;
                result.m22 = m0.m22 * s0;
                result.m23 = m0.m23 * s0;
                result.m24 = m0.m24 * s0;

                result.m31 = m0.m31 * s0;
                result.m32 = m0.m32 * s0;
                result.m33 = m0.m33 * s0;
                result.m34 = m0.m34 * s0;

                result.m41 = m0.m41 * s0;
                result.m42 = m0.m42 * s0;
                result.m43 = m0.m43 * s0;
                result.m44 = m0.m44 * s0;
                return result;
            }



    /** Functions */
 


        // Trigonometry
        TYON_CUDA_SHARED
        PROC sinus(const f32 a) -> f32
        {
            return std::sinf(a);
        }

        TYON_CUDA_SHARED
        PROC sinus(const f64 a) -> f64
        {
            return std::sin(a);
        }

        TYON_CUDA_SHARED
        PROC cosinus(const f32 a) -> f32
        {
            return std::cosf(a);
        }

        TYON_CUDA_SHARED
        PROC cosinus(const f64 a) -> f64
        {
            return std::cos(a);
        }

        TYON_CUDA_SHARED
        PROC tangent(const f32 a) -> f32
        {
            return std::tanf(a);
        }

        TYON_CUDA_SHARED
        PROC tangent(const f64 a) -> f64
        {
            return std::tan(a);
        }

        TYON_CUDA_SHARED
        PROC arcsin(const f32 a) -> f32
        {
            return std::asinf(a);
        }

        TYON_CUDA_SHARED
        PROC arcsin(const f64 a) -> f64
        {
            return std::asin(a);
        }

        TYON_CUDA_SHARED
        PROC arccos(const f32 a) -> f32
        {
            return std::acosf(a);
        }

        TYON_CUDA_SHARED
        PROC arccos(const f64 a) -> f64
        {
            return std::acos(a);
        }

        TYON_CUDA_SHARED
        PROC arctan(const f32 a) -> f32
        {
            return atanf(a);
        }

        TYON_CUDA_SHARED
        PROC arctan(const f64 a) -> f64
        {
            return atan(a);
        }

        TYON_CUDA_SHARED
        PROC arctan2(const f32 x, const f32 y) -> f32
        {
            return std::atan2f(x,y);
        }

        TYON_CUDA_SHARED
        PROC arctan2(const f64 x, const f64 y) -> f64
        {
            return std::atan2(x,y);
        }



        // Matrix
            // Rotation
            TYON_CUDA_SHARED
            PROC general_2d_rotation_matrix(const f32 theta) -> matrix2_f32
            {
                matrix2_f32 result;
                result.m11 = cosinus(theta);
                result.m12 = -sinus(theta);
                result.m21 = sinus(theta);
                result.m22 = cosinus(theta);
                return result;
            }

            TYON_CUDA_SHARED
            PROC general_2d_rotation_matrix(const f64 theta) -> matrix2_f64
            {
                matrix2_f64 result;
                result.m11 = cosinus(theta);
                result.m12 = -sinus(theta);
                result.m21 = sinus(theta);
                result.m22 = cosinus(theta);
                return result;
            }

            TYON_CUDA_SHARED
            PROC general_3d_rotation_matrix(const f32 r_x, const f32 r_y, const f32 r_z) -> matrix3_f32
            {
                matrix3_f32 m_x, m_y, m_z;

                // X Rotation
                m_x.m11 = 1.0f;
                m_x.m12 = 0.0f;
                m_x.m13 = 0.0f;

                m_x.m21 = 0.0f;
                m_x.m22 = cosinus(r_x);
                m_x.m23 = -sinus(r_x);

                m_x.m31 = 0.0f;
                m_x.m32 = sinus(r_x);
                m_x.m33 = cosinus(r_x);
            
                // Y Rotation
                m_y.m11 = cosinus(r_y);
                m_y.m12 = 0.0f;
                m_y.m13 = sinus(r_y);

                m_y.m21 = 0.0f;
                m_y.m22 = 1.0f;
                m_y.m23 = 0.0f;

                m_y.m31 = -sinus(r_y);
                m_y.m32 = 0.0f;
                m_y.m33 = cosinus(r_y);

                // Z Rotation
                m_z.m11 = cosinus(r_z);
                m_z.m12= -sinus(r_z);
                m_z.m13 = 0.0f;

                m_z.m21 = sinus(r_z);
                m_z.m22 = cosinus(r_z);
                m_z.m23 = 0.0f;

                m_z.m31 = 0.0f;
                m_z.m32 = 0.0f;
                m_z.m33 = 1.0f;

                return m_x * m_y * m_z;
            }

            TYON_CUDA_SHARED
            PROC general_3d_rotation_matrix(const f64 r_x, const f64 r_y, const f64 r_z) -> matrix3_f64
            {
            {
                matrix3_f64 m_x, m_y, m_z;

                // X Rotation
                m_x.m11 = 1.0;
                m_x.m12 = 0.0;
                m_x.m13 = 0.0;

                m_x.m21 = 0.0;
                m_x.m22 = cosinus(r_x);
                m_x.m23 = -sinus(r_x);

                m_x.m31 = 0.0;
                m_x.m32 = sinus(r_x);
                m_x.m33 = cosinus(r_x);
            
                // Y Rotation
                m_y.m11 = cosinus(r_y);
                m_y.m12 = 0.0;
                m_y.m13 = sinus(r_y);

                m_y.m21 = 0.0;
                m_y.m22 = 1.0;
                m_y.m23 = 0.0;

                m_y.m31 = -sinus(r_y);
                m_y.m32 = 0.0;
                m_y.m33 = cosinus(r_y);

                // Z Rotation
                m_z.m11 = cosinus(r_z);
                m_z.m12= -sinus(r_z);
                m_z.m13 = 0.0;

                m_z.m21 = sinus(r_z);
                m_z.m22 = cosinus(r_z);
                m_z.m23 = 0.0;

                m_z.m31 = 0.0;
                m_z.m32 = 0.0;
                m_z.m33 = 1.0;

                return m_x * m_y * m_z;
            }
            }

            TYON_CUDA_SHARED
            PROC euler_rotation_matrix(const f32 theta, const v3_f32 u) -> matrix3_f32
            {
                matrix3_f32 R;

                R.m11 = cosinus(theta) + u.x * u.x * (1.0f - cosinus(theta));
                R.m12 = u.x * u.y * ( 1.0f - cosinus(theta)) - u.z * sinus(theta);
                R.m13 = u.x * u.z * ( 1.0f - cosinus(theta)) + u.y * sinus(theta);

                R.m21 = u.y * u.x * (1.0f - cosinus(theta)) + u.z * sinus(theta);
                R.m22 = cosinus(theta) + u.y * u.y * (1.0f - cosinus(theta));
                R.m23 = u.y * u.z * (1.0f - cosinus(theta)) - u.x * sinus(theta);

                R.m31 = u.z * u.x * (1.0f - cosinus(theta)) - u.y * sinus(theta);
                R.m32 = u.z * u.y * (1.0f - cosinus(theta)) + u.x * sinus(theta);
                R.m33 = cosinus(theta) + u.z * u.z * (1.0f - cosinus(theta));

                return R;
            }



            // Transpose
            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix2_f32 m) -> matrix2_f32
            {
                matrix2_f32 transpose;
                transpose.m11 = m.m11;
                transpose.m12 = m.m21;
                transpose.m21 = m.m12;
                transpose.m22 = m.m22;

                return transpose;
            }

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix2_f64 m) -> matrix2_f64
            {
                matrix2_f64 transpose;
                transpose.m11 = m.m11;
                transpose.m12 = m.m21;
                transpose.m21 = m.m12;
                transpose.m22 = m.m22;

                return transpose;
            }

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix3_f32 m) -> matrix3_f32
            {
                matrix3_f32 transpose;
                transpose.m11 = m.m11;
                transpose.m12 = m.m21;
                transpose.m13 = m.m31;
                transpose.m21 = m.m12;
                transpose.m22 = m.m22;
                transpose.m23 = m.m32;
                transpose.m31 = m.m13;
                transpose.m32 = m.m23;
                transpose.m33 = m.m33;

                return transpose;
            }

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix3_f64 m) -> matrix3_f64
            {
                matrix3_f64 transpose;
                transpose.m11 = m.m11;
                transpose.m12 = m.m21;
                transpose.m13 = m.m31;
                transpose.m21 = m.m12;
                transpose.m22 = m.m22;
                transpose.m23 = m.m32;
                transpose.m31 = m.m13;
                transpose.m32 = m.m23;
                transpose.m33 = m.m33;

                return transpose;
            }

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix4_f32 m) -> matrix4_f32
            {
                matrix4_f32 transpose;
                transpose.m11 = m.m11;
                transpose.m12 = m.m21;
                transpose.m13 = m.m31;
                transpose.m14 = m.m41;
                transpose.m21 = m.m12;
                transpose.m22 = m.m22;
                transpose.m23 = m.m32;
                transpose.m24 = m.m42;
                transpose.m31 = m.m13;
                transpose.m32 = m.m23;
                transpose.m33 = m.m33;
                transpose.m34 = m.m43;
                transpose.m41 = m.m14;
                transpose.m42 = m.m24;
                transpose.m43 = m.m34;
                transpose.m44 = m.m44;

                return transpose;
            }

            TYON_CUDA_SHARED
            PROC transpose_matrix(const matrix4_f64 m) -> matrix4_f64
            {
                matrix4_f64 transpose;
                transpose.m11 = m.m11;
                transpose.m12 = m.m21;
                transpose.m13 = m.m31;
                transpose.m14 = m.m41;
                transpose.m21 = m.m12;
                transpose.m22 = m.m22;
                transpose.m23 = m.m32;
                transpose.m24 = m.m42;
                transpose.m31 = m.m13;
                transpose.m32 = m.m23;
                transpose.m33 = m.m33;
                transpose.m34 = m.m43;
                transpose.m41 = m.m14;
                transpose.m42 = m.m24;
                transpose.m43 = m.m34;
                transpose.m44 = m.m44;

                return transpose;
            }



        // Conversion
            // Spherical coordinates
            TYON_CUDA_SHARED
            PROC cartesian_to_spherical(const v3_f32 cartesian) -> v3_f32
            {
                f32 r = vector_length(cartesian);
                f32 theta = arccos(cartesian.y / r);
                f32 phi = arctan2(cartesian.z, cartesian.x);

                return v3_f32(r, theta, phi);
            }

            TYON_CUDA_SHARED
            PROC spherical_to_cartesian(const v3_f32 spherical) -> v3_f32
            {
                f32 x = spherical.x * sinus(spherical.y) * cosinus(spherical.z);
                f32 y = spherical.x * cosinus(spherical.y);
                f32 z = spherical.x * sinus(spherical.y) * sinus(spherical.z);

                return v3_f32(x, y, z);
            }
}
