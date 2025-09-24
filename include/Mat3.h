/**
 * @file: Mat3.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-14
 * -----
 * Last Modified: 24-09-2025
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

#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vector3.h"

class Mat3
{
public:
    constexpr Mat3() = default;
    constexpr Mat3(const Mat3&) = default;

    constexpr Mat3(const float a11, const float a12, const float a13
                 , const float a21, const float a22, const float a23
                 , const float a31, const float a32, const float a33) :
        data { a11, a12, a13,
               a21, a22, a23,
               a31, a32, a33 }
    {}

    Mat3& operator=(const Mat3& m);

    Mat3& operator*=(float scalar);

    Mat3 operator*(float scalar) const;

    Mat3& operator*=(const Mat3& m);

    Mat3 operator*(const Mat3& m) const;

    Mat3 operator!() const;

    constexpr static Mat3 Identity()
    {
        return {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
        };
    }

    constexpr static Mat3 Scaling(float factor)
    {
        return {
            factor, 0.0f, 0.0f,
            0.0f, factor, 0.0f,
            0.0f, 0.0f, factor,
        };
    }

    static Mat3 RotationZ(float theta);

    static Mat3 RotationY(float theta);

    static Mat3 RotationX(float theta);

public:
	// [ row ][ col ]
	float data[3][3] = {0};
};

// ASM functions
#if defined(STM32F407xx)
extern "C" void mult_3x3x3_asm(const float* A, const float* B, float* C);
extern "C" void mult_1x3x3_asm(const float* v, const float* M, float* u);
extern "C" void mult_3x3xS_asm(const float* A, const float* s, float* C);
#endif

template<typename T>
Vector3<T>& operator*=(Vector3<T>& v, const Mat3& m)
{
	return v = v * m;
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Mat3& m)
{
	return {
		v.x * m.data[0][0] + v.y * m.data[1][0] + v.z * m.data[2][0],
		v.x * m.data[0][1] + v.y * m.data[1][1] + v.z * m.data[2][1],
		v.x * m.data[0][2] + v.y * m.data[1][2] + v.z * m.data[2][2]
	};
}

#if defined(STM32F407xx)
template<>
inline Vector3<float> operator*(const Vector3<float>& v, const Mat3& m)
{
    static Vector3<float> u;
    mult_1x3x3_asm((float*)&v, &m.data[0][0], (float*)&u);
    return u;
}

template<>
inline Vector3<float>& operator*=(Vector3<float>& v, const Mat3& m)
{
    mult_1x3x3_asm((float*)&v, &m.data[0][0], (float*)&v);
    return v;
}
#endif

#endif // MATRIX3_H
