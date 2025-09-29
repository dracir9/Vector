/**
 * @file: Mat3.h
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

    /**
     * @brief  Scalar multiplication assignment
     * 
     * @param  scalar Scalar to multiply
     * @return Mat3& Reference to this matrix
     */
    __attribute__((always_inline)) inline Mat3& operator*=(float scalar)
    {
        data[0][0] *= scalar;
        data[0][1] *= scalar;
        data[0][2] *= scalar;
        data[1][0] *= scalar;
        data[1][1] *= scalar;
        data[1][2] *= scalar;
        data[2][0] *= scalar;
        data[2][1] *= scalar;
        data[2][2] *= scalar;
        return *this;
    }

    /**
     * @brief Scalar multiplication
     * 
     * @param scalar Scalar to multiply
     * @return Mat3 Result of the multiplication
     */
    __attribute__((always_inline)) inline Mat3 operator*(float scalar) const
    {
        return {
            data[0][0] * scalar, data[0][1] * scalar, data[0][2] * scalar,
            data[1][0] * scalar, data[1][1] * scalar, data[1][2] * scalar,
            data[2][0] * scalar, data[2][1] * scalar, data[2][2] * scalar,
        };
    }

    /**
     * @brief Matrix multiplication
     * 
     * @param m Matrix to multiply
     * @return Mat3 Result of the multiplication
     */
    Mat3& operator*=(const Mat3& m);

    /**
     * @brief Matrix multiplication
     * 
     * @param m Matrix to multiply
     * @return Mat3 Result of the multiplication
     */
    Mat3 operator*(const Mat3& m) const;

    /**
     * @brief Matrix addition
     * 
     * @param m Matrix to add
     * @return Mat3 Result of the addition
     */
    __attribute__((always_inline)) inline Mat3 operator+(const Mat3& m) const
    {
        return {
            data[0][0] + m.data[0][0], data[0][1] + m.data[0][1], data[0][2] + m.data[0][2],
            data[1][0] + m.data[1][0], data[1][1] + m.data[1][1], data[1][2] + m.data[1][2],
            data[2][0] + m.data[2][0], data[2][1] + m.data[2][1], data[2][2] + m.data[2][2],
        };
    }

    /**
     * @brief  Matrix addition assignment
     * 
     * @param m Matrix to add
     * @return Mat3& Reference to this matrix
     */
    __attribute__((always_inline)) inline Mat3& operator+=(const Mat3& m)
    {
        data[0][0] += m.data[0][0];
        data[0][1] += m.data[0][1];
        data[0][2] += m.data[0][2];
        data[1][0] += m.data[1][0];
        data[1][1] += m.data[1][1];
        data[1][2] += m.data[1][2];
        data[2][0] += m.data[2][0];
        data[2][1] += m.data[2][1];
        data[2][2] += m.data[2][2];
        return *this;
    }

    /**
     * @brief Matrix subtraction
     * 
     * @param m Matrix to subtract
     * @return Mat3 Result of the subtraction
     */
    __attribute__((always_inline)) inline Mat3 operator-(const Mat3& m) const
    {
        return {
            data[0][0] - m.data[0][0], data[0][1] - m.data[0][1], data[0][2] - m.data[0][2],
            data[1][0] - m.data[1][0], data[1][1] - m.data[1][1], data[1][2] - m.data[1][2],
            data[2][0] - m.data[2][0], data[2][1] - m.data[2][1], data[2][2] - m.data[2][2],
        };
    }

    /**
     * @brief  Matrix subtraction assignment
     * 
     * @param m Matrix to subtract
     * @return Mat3& Reference to this matrix
     */
    __attribute__((always_inline)) inline Mat3& operator-=(const Mat3& m)
    {
        data[0][0] -= m.data[0][0];
        data[0][1] -= m.data[0][1];
        data[0][2] -= m.data[0][2];
        data[1][0] -= m.data[1][0];
        data[1][1] -= m.data[1][1];
        data[1][2] -= m.data[1][2];
        data[2][0] -= m.data[2][0];
        data[2][1] -= m.data[2][1];
        data[2][2] -= m.data[2][2];
        return *this;
    }

    /**
     * @brief Transpose matrix
     * 
     * @return Mat3 
     */
    __attribute__((always_inline)) inline Mat3 operator!() const
    {
        return {
            data[0][0], data[1][0], data[2][0],
            data[0][1], data[1][1], data[2][1],
            data[0][2], data[1][2], data[2][2],
        };
    }

    __attribute__((always_inline)) inline float& operator()(int row, int col)
    {
        assert(row >= 0 && row < 3 && col >= 0 && col < 3 && "Mat3: row and col indices must be in [0,2]");
        return data[row][col];
    }

    /**
     * @brief  Identity matrix
     * 
     * @return constexpr Mat3   Return identity matrix
     */
    constexpr static Mat3 Identity()
    {
        return {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
        };
    }

    /**
     * @brief Scaling matrix
     * 
     * @param factor Scale factor
     * @return constexpr Mat3 
     */
    constexpr static Mat3 Scaling(float factor)
    {
        return {
            factor, 0.0f, 0.0f,
            0.0f, factor, 0.0f,
            0.0f, 0.0f, factor,
        };
    }

    /**
     * @brief Scaling matrix
     * 
     * @param x Scale factor in X axis
     * @param y Scale factor in Y axis
     * @param z Scale factor in Z axis
     * @return constexpr Mat3 
     */
    constexpr static Mat3 Scaling(float x, float y, float z)
    {
        return {
            x,    0.0f, 0.0f,
            0.0f, y,    0.0f,
            0.0f, 0.0f, z,
        };
    }

    /**
     * @brief Rotation matrix around Z axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat3
     */
    static Mat3 RotationZ(float theta);

    /**
     * @brief Rotation matrix around Y axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat3
     */
    static Mat3 RotationY(float theta);

    /**
     * @brief Rotation matrix around X axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat3
     */
    static Mat3 RotationX(float theta);

    /**
     * @brief Inverse matrix
     * 
     * @return Mat3 Inverted matrix. If the matrix is not invertible, returns zero matrix.
     */
    Mat3 Inverse() const;

    /**
     * @brief Determinant of the matrix
     * 
     * @return float Determinant value
     */
    float Determinant() const;

public:
	// [ row ][ col ]
	float data[3][3] = {0};
};

template<typename T>
__attribute__((hot, optimize("O3"), always_inline)) inline Vector3<T>& operator*=(Vector3<T>& v, const Mat3& m)
{
	return v = v * m;
}

template<typename T>
__attribute__((hot, optimize("O3"), always_inline)) inline Vector3<T> operator*(const Vector3<T>& v, const Mat3& m)
{
	return {
		v.x * m.data[0][0] + v.y * m.data[1][0] + v.z * m.data[2][0],
		v.x * m.data[0][1] + v.y * m.data[1][1] + v.z * m.data[2][1],
		v.x * m.data[0][2] + v.y * m.data[1][2] + v.z * m.data[2][2]
	};
}

#endif // MATRIX3_H
