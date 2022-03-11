/**
 * @file: Mat4.cpp
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-15
 * -----
 * Last Modified: 11-03-2022
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

#include "Mat4.h"
#include <cmath>
#include <cstring>

Mat4& Mat4::operator=(const Mat4& m)
{
    memcpy(data, m.data, sizeof(data));
    return *this;
}

Mat4& Mat4::operator*=(float scalar)
{
    for(auto& row : data)
    {
        for(float& e : row)
        {
            e *= scalar;
        }
    }
    return *this;
}

Mat4 Mat4::operator*(float scalar) const
{
    Mat4 result = *this;
    return result *= scalar;
}

Mat4& Mat4::operator*=(const Mat4& m)
{
    return *this = *this * m;
}

Mat4 Mat4::operator*(const Mat4& m) const
{
    Mat4 result;
    result.data[0][0] = data[0][0]*m.data[0][0] + data[0][1]*m.data[1][0] + data[0][2]*m.data[2][0] + data[0][3]*m.data[3][0];
    result.data[0][1] = data[0][0]*m.data[0][1] + data[0][1]*m.data[1][1] + data[0][2]*m.data[2][1] + data[0][3]*m.data[3][1];
    result.data[0][2] = data[0][0]*m.data[0][2] + data[0][1]*m.data[1][2] + data[0][2]*m.data[2][2] + data[0][3]*m.data[3][2];
    result.data[0][3] = data[0][0]*m.data[0][3] + data[0][1]*m.data[1][3] + data[0][2]*m.data[2][3] + data[0][3]*m.data[3][3];
    result.data[1][0] = data[1][0]*m.data[0][0] + data[1][1]*m.data[1][0] + data[1][2]*m.data[2][0] + data[1][3]*m.data[3][0];
    result.data[1][1] = data[1][0]*m.data[0][1] + data[1][1]*m.data[1][1] + data[1][2]*m.data[2][1] + data[1][3]*m.data[3][1];
    result.data[1][2] = data[1][0]*m.data[0][2] + data[1][1]*m.data[1][2] + data[1][2]*m.data[2][2] + data[1][3]*m.data[3][2];
    result.data[1][3] = data[1][0]*m.data[0][3] + data[1][1]*m.data[1][3] + data[1][2]*m.data[2][3] + data[1][3]*m.data[3][3];
    result.data[2][0] = data[2][0]*m.data[0][0] + data[2][1]*m.data[1][0] + data[2][2]*m.data[2][0] + data[2][3]*m.data[3][0];
    result.data[2][1] = data[2][0]*m.data[0][1] + data[2][1]*m.data[1][1] + data[2][2]*m.data[2][1] + data[2][3]*m.data[3][1];
    result.data[2][2] = data[2][0]*m.data[0][2] + data[2][1]*m.data[1][2] + data[2][2]*m.data[2][2] + data[2][3]*m.data[3][2];
    result.data[2][3] = data[2][0]*m.data[0][3] + data[2][1]*m.data[1][3] + data[2][2]*m.data[2][3] + data[2][3]*m.data[3][3];
    result.data[3][0] = data[3][0]*m.data[0][0] + data[3][1]*m.data[1][0] + data[3][2]*m.data[2][0] + data[3][3]*m.data[3][0];
    result.data[3][1] = data[3][0]*m.data[0][1] + data[3][1]*m.data[1][1] + data[3][2]*m.data[2][1] + data[3][3]*m.data[3][1];
    result.data[3][2] = data[3][0]*m.data[0][2] + data[3][1]*m.data[1][2] + data[3][2]*m.data[2][2] + data[3][3]*m.data[3][2];
    result.data[3][3] = data[3][0]*m.data[0][3] + data[3][1]*m.data[1][3] + data[3][2]*m.data[2][3] + data[3][3]*m.data[3][3];
    return result;
}

Mat4 Mat4::operator!() const
{
    Mat4 m;
    m.data[0][0] = data[0][0];
    m.data[0][1] = data[1][0];
    m.data[0][2] = data[2][0];
    m.data[0][3] = data[3][0];
    m.data[1][0] = data[0][1];
    m.data[1][1] = data[1][1];
    m.data[1][2] = data[2][1];
    m.data[1][3] = data[3][1];
    m.data[2][0] = data[0][2];
    m.data[2][1] = data[1][2];
    m.data[2][2] = data[2][2];
    m.data[2][3] = data[3][2];
    m.data[3][0] = data[0][3];
    m.data[3][1] = data[1][3];
    m.data[3][2] = data[2][3];
    m.data[3][3] = data[3][3];
    return m;
}

Mat4 Mat4::RotationZ(float theta)
{
    const float sinTheta = sinf(theta);
    const float cosTheta = cosf(theta);
    return {
        cosTheta,  sinTheta, 0.0f, 0.0f,
        -sinTheta, cosTheta, 0.0f, 0.0f,
        0.0f,      0.0f,     1.0f, 0.0f,
        0.0f,      0.0f,     0.0f, 1.0f,
    };
}

Mat4 Mat4::RotationY(float theta)
{
    const float sinTheta = sinf(theta);
    const float cosTheta = cosf(theta);

    return {
        cosTheta, 0.0f, -sinTheta, 0.0f,
        0.0f,     1.0f, 0.0f,      0.0f,
        sinTheta, 0.0f, cosTheta,  0.0f,
        0.0f,     0.0f, 0.0f,      1.0f,
    };
}

Mat4 Mat4::RotationX(float theta)
{
    const float sinTheta = sinf(theta);
    const float cosTheta = cosf(theta);

    return {
        1.0f, 0.0f,     0.0f,     0.0f,
        0.0f, cosTheta, sinTheta, 0.0f,
        0.0f,-sinTheta, cosTheta, 0.0f,
        0.0f, 0.0f,     0.0f,     1.0f,
    };
}
