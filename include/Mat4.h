/**
 * @file: Mat4.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-14
 * -----
 * Last Modified: 2021-11-20
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
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector4.h"

class Mat4
{
public:
    Mat4& operator=(const Mat4& m);

    Mat4& operator*=(float scalar);

    Mat4 operator*(float scalar) const;

    Mat4& operator*=(const Mat4& m);

    Mat4 operator*(const Mat4& m) const;

    Mat4 operator!() const;

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
     * @brief Rotation matrix arround Z axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat4 
     */
    static Mat4 RotationZ(float theta);

    /**
     * @brief Rotation matrix arround Y axis
     * 
     * @param theta Rotation angle in radians
     * @return Mat4 
     */
    static Mat4 RotationY(float theta);

    /**
     * @brief Rotation matrix arround X axis
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
    
public:
    // [ row ][ col ]
    float data[4][4];
};

template<typename T>
Vector4<T>& operator*=(Vector4<T>& v, const Mat4& m)
{
    return v = v * m;
}

template<typename T>
Vector4<T> operator*(const Vector4<T>& v, const Mat4& m)
{
    return{
        v.x * m.data[0][0] + v.y * m.data[1][0] + v.z * m.data[2][0] + v.w * m.data[3][0],
        v.x * m.data[0][1] + v.y * m.data[1][1] + v.z * m.data[2][1] + v.w * m.data[3][1],
        v.x * m.data[0][2] + v.y * m.data[1][2] + v.z * m.data[2][2] + v.w * m.data[3][2],
        v.x * m.data[0][3] + v.y * m.data[1][3] + v.z * m.data[2][3] + v.w * m.data[3][3]
    };
}

#endif // MATRIX4_H
