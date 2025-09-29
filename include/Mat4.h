/**
 * @file: Mat4.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-14
 * -----
 * Last Modified: 29-09-2025
 * Modified By: Ricard Bitriá Ribes
 * -----
 * @copyright (c) 2021 Ricard Bitriá Ribes
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MATRIX4_H
#define MATRIX4_H

#include <stdint.h>
#include "Vector4.h"
#include "Mat3.h"

class alignas(16) Mat4
{
public:
    Mat4() = default;
    constexpr Mat4(const Mat4&) = default;
    
    constexpr Mat4(const float s) :
        data { s, s, s, s,
               s, s, s, s,
               s, s, s, s,
               s, s, s, s }
    {}

    constexpr Mat4(const float a11, const float a12, const float a13, const float a14
                 , const float a21, const float a22, const float a23, const float a24
                 , const float a31, const float a32, const float a33, const float a34
                 , const float a41, const float a42, const float a43, const float a44) :
        data { a11, a12, a13, a14,
               a21, a22, a23, a24,
               a31, a32, a33, a34,
               a41, a42, a43, a44 }
    {}

    constexpr Mat4(const Mat3& m) :
        data { m.data[0][0], m.data[0][1], m.data[0][2], 0.0f,
               m.data[1][0], m.data[1][1], m.data[1][2], 0.0f,
               m.data[2][0], m.data[2][1], m.data[2][2], 0.0f,
                       0.0f,         0.0f,         0.0f, 1.0f }
    {}

#ifdef CONFIG_IDF_TARGET_ESP32S3
    Mat4& operator=(const Mat4& m)
        {
        asm(R"(
            EE.VLD.128.IP q0, a3, 16
            EE.VST.128.IP q0, a2, 16

            EE.VLD.128.IP q0, a3, 16
            EE.VST.128.IP q0, a2, 16

            EE.VLD.128.IP q0, a3, 16
            EE.VST.128.IP q0, a2, 16

            EE.VLD.128.IP q0, a3, -48
            EE.VST.128.IP q0, a2, -48
        )");
        return *this;
    }
#endif

    /**
     * @brief  Scalar multiplication assignment
     * 
     * @param  scalar Scalar to multiply
     * @return Mat4& Reference to this matrix
     */
    Mat4& operator*=(float scalar)
    {
    #ifdef CONFIG_IDF_TARGET_ESP32S3
        mult_4x4xS_asm(&data[0][0], &scalar, &data[0][0]);
    #else
        data[0][0] *= scalar;
        data[0][1] *= scalar;
        data[0][2] *= scalar;
        data[0][3] *= scalar;
        data[1][0] *= scalar;
        data[1][1] *= scalar;
        data[1][2] *= scalar;
        data[1][3] *= scalar;
        data[2][0] *= scalar;
        data[2][1] *= scalar;
        data[2][2] *= scalar;
        data[2][3] *= scalar;
        data[3][0] *= scalar;
        data[3][1] *= scalar;
        data[3][2] *= scalar;
        data[3][3] *= scalar;
    #endif
        return *this;
    }

    /**
     * @brief Scalar multiplication
     * 
     * @param scalar Scalar to multiply
     * @return Mat4 Result of the multiplication
     */
    Mat4 operator*(float scalar) const
    {
    #ifdef CONFIG_IDF_TARGET_ESP32S3
        Mat4 result;
        mult_4x4xS_asm(&data[0][0], &scalar, &result.data[0][0]);
        return result;
    #else
        return {
            data[0][0] * scalar, data[0][1] * scalar, data[0][2] * scalar, data[0][3] * scalar,
            data[1][0] * scalar, data[1][1] * scalar, data[1][2] * scalar, data[1][3] * scalar,
            data[2][0] * scalar, data[2][1] * scalar, data[2][2] * scalar, data[2][3] * scalar,
            data[3][0] * scalar, data[3][1] * scalar, data[3][2] * scalar, data[3][3] * scalar,
        };
    #endif
    }

    /**
     * @brief Matrix multiplication
     * 
     * @param m Matrix to multiply
     * @return Mat4 Result of the multiplication
     */
    Mat4& operator*=(const Mat4& m);

    /**
     * @brief Matrix multiplication
     * 
     * @param m Matrix to multiply
     * @return Mat4 Result of the multiplication
     */
    Mat4 operator*(const Mat4& m) const;

    /**
     * @brief Matrix addition
     * 
     * @param m Matrix to add
     * @return Mat4 Result of the addition
     */
    Mat4 operator+(const Mat4& m) const
    {
        return {
            data[0][0] + m.data[0][0], data[0][1] + m.data[0][1], data[0][2] + m.data[0][2], data[0][3] + m.data[0][3],
            data[1][0] + m.data[1][0], data[1][1] + m.data[1][1], data[1][2] + m.data[1][2], data[1][3] + m.data[1][3],
            data[2][0] + m.data[2][0], data[2][1] + m.data[2][1], data[2][2] + m.data[2][2], data[2][3] + m.data[2][3],
            data[3][0] + m.data[3][0], data[3][1] + m.data[3][1], data[3][2] + m.data[3][2], data[3][3] + m.data[3][3],
        };
    }

    /**
     * @brief  Matrix addition assignment
     * 
     * @param m Matrix to add
     * @return Mat4& Reference to this matrix
     */
    Mat4& operator+=(const Mat4& m)
    {
        data[0][0] += m.data[0][0];
        data[0][1] += m.data[0][1];
        data[0][2] += m.data[0][2];
        data[0][3] += m.data[0][3];
        data[1][0] += m.data[1][0];
        data[1][1] += m.data[1][1];
        data[1][2] += m.data[1][2];
        data[1][3] += m.data[1][3];
        data[2][0] += m.data[2][0];
        data[2][1] += m.data[2][1];
        data[2][2] += m.data[2][2];
        data[2][3] += m.data[2][3];
        data[3][0] += m.data[3][0];
        data[3][1] += m.data[3][1];
        data[3][2] += m.data[3][2];
        data[3][3] += m.data[3][3];
        return *this;
    }

    /**
     * @brief Matrix subtraction
     * 
     * @param m Matrix to subtract
     * @return Mat4 Result of the subtraction
     */
    Mat4 operator-(const Mat4& m) const
    {
        return {
            data[0][0] - m.data[0][0], data[0][1] - m.data[0][1], data[0][2] - m.data[0][2], data[0][3] - m.data[0][3],
            data[1][0] - m.data[1][0], data[1][1] - m.data[1][1], data[1][2] - m.data[1][2], data[1][3] - m.data[1][3],
            data[2][0] - m.data[2][0], data[2][1] - m.data[2][1], data[2][2] - m.data[2][2], data[2][3] - m.data[2][3],
            data[3][0] - m.data[3][0], data[3][1] - m.data[3][1], data[3][2] - m.data[3][2], data[3][3] - m.data[3][3],
        };
    }

    /**
     * @brief  Matrix subtraction assignment
     * 
     * @param m Matrix to subtract
     * @return Mat4& Reference to this matrix
     */
    Mat4& operator-=(const Mat4& m)
    {
        data[0][0] -= m.data[0][0];
        data[0][1] -= m.data[0][1];
        data[0][2] -= m.data[0][2];
        data[0][3] -= m.data[0][3];
        data[1][0] -= m.data[1][0];
        data[1][1] -= m.data[1][1];
        data[1][2] -= m.data[1][2];
        data[1][3] -= m.data[1][3];
        data[2][0] -= m.data[2][0];
        data[2][1] -= m.data[2][1];
        data[2][2] -= m.data[2][2];
        data[2][3] -= m.data[2][3];
        data[3][0] -= m.data[3][0];
        data[3][1] -= m.data[3][1];
        data[3][2] -= m.data[3][2];
        data[3][3] -= m.data[3][3];
        return *this;
    }

    /**
     * @brief Transpose matrix
     * 
     * @return Mat4 
     */
    __attribute__((always_inline)) inline Mat4 operator!() const
    {
        return {
            data[0][0], data[1][0], data[2][0], data[3][0],
            data[0][1], data[1][1], data[2][1], data[3][1],
            data[0][2], data[1][2], data[2][2], data[3][2],
            data[0][3], data[1][3], data[2][3], data[3][3],
        };
    }

    __attribute__((always_inline)) inline float& operator()(int row, int col)
    {
        assert(row >= 0 && row < 4 && col >= 0 && col < 4 && "Mat4: row and col indices must be in [0,3]");
        return data[row][col];
    }

    /**
     * @brief  Identity matrix
     * 
     * @return constexpr Mat4   Return identity matrix
     */
    constexpr static Mat4 Identity()
    {
        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
    }

    /**
     * @brief Scaling matrix
     * 
     * @param factor Scale factor
     * @return constexpr Mat4 
     */
    constexpr static Mat4 Scaling(float factor)
    {
        return Scaling(factor, factor, factor);
    }

    /**
     * @brief Scaling matrix
     * 
     * @param x Scale factor in X axis
     * @param y Scale factor in Y axis
     * @param z Scale factor in Z axis
     * @return constexpr Mat4 
     */
    constexpr static Mat4 Scaling(float x, float y, float z)
    {
        return {
            x,    0.0f, 0.0f, 0.0f,
            0.0f, y,    0.0f, 0.0f,
            0.0f, 0.0f, z,    0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
    }

    /**
     * @brief Rotation matrix around Z axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat4 
     */
    static Mat4 RotationZ(float theta);

    /**
     * @brief Rotation matrix around Y axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat4 
     */
    static Mat4 RotationY(float theta);

    /**
     * @brief Rotation matrix around X axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat4 
     */
    static Mat4 RotationX(float theta);

    template<class V>
    constexpr static Mat4 Translation(const V& tl)
    {
        return Translation( tl.x,tl.y,tl.z );
    }

    constexpr static Mat4 Translation(float x, float y, float z)
    {
        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            x,    y,    z,    1.0f,
        };
    }

    /**
     * @brief Generate projection matrix
     * 
     * @param w  Screen width in pixels
     * @param h  Screen height in pixels
     * @param n  Distance between the near plane and the focal point
     * @return constexpr Mat4 
     */
    constexpr static Mat4 Projection(float w, float h, float n)
    {
        return {
            2.0f * n / w, 0.0f,         0.0f, 0.0f,
            0.0f,         2.0f * n / h, 0.0f, 0.0f,
            0.0f,         0.0f,         1.0f, 1.0f,
            0.0f,         0.0f,         0.0f, 0.0f,
        };
    }

    /**
     * @brief Inverse matrix
     * 
     * @return Mat4 Inverted matrix. If the matrix is not invertible, returns zero matrix.
     */
    Mat4 Inverse() const;

    float Determinant() const;

public:
    // [ row ][ col ]
    float data[4][4];
};

// ASM functions
#if defined(CONFIG_IDF_TARGET_ESP32S3)
extern "C" void mult_4x4x4_asm(const float* A, const float* B, float* C);
extern "C" void mult_1x4x4_asm(const float* v, const float* M, float* u);
extern "C" void mult_4x4xS_asm(const float* A, const float* s, float* C);
#endif

template<typename T>
__attribute__((always_inline, hot, optimize("O3"))) inline Vector4<T>& operator*=(Vector4<T>& v, const Mat4& m)
{
    return v = v * m;
}

template<typename T>
__attribute__((always_inline, hot, optimize("O3"))) inline Vector4<T> operator*(const Vector4<T>& v, const Mat4& m)
{
    return{
        v.x * m.data[0][0] + v.y * m.data[1][0] + v.z * m.data[2][0] + v.w * m.data[3][0],
        v.x * m.data[0][1] + v.y * m.data[1][1] + v.z * m.data[2][1] + v.w * m.data[3][1],
        v.x * m.data[0][2] + v.y * m.data[1][2] + v.z * m.data[2][2] + v.w * m.data[3][2],
        v.x * m.data[0][3] + v.y * m.data[1][3] + v.z * m.data[2][3] + v.w * m.data[3][3]
    };
}

#if defined(CONFIG_IDF_TARGET_ESP32S3)
template<>
inline Vector4<float> operator*(const Vector4<float>& v, const Mat4& m)
{
    static Vector4<float> u;
    mult_1x4x4_asm((float*)&v, &m.data[0][0], (float*)&u);
    return u;
}

template<>
inline Vector4<float>& operator*=(Vector4<float>& v, const Mat4& m)
{
    mult_1x4x4_asm((float*)&v, &m.data[0][0], (float*)&v);
    return v;
}
#endif

#endif // MATRIX4_H
