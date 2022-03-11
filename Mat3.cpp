/**
 * @file: Mat3.cpp
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-14
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

#include "Mat3.h"
#include <cmath>
#include <cassert>
#include <cstring>

Mat3& Mat3::operator=(const Mat3& m)
{
    memcpy(data, m.data, sizeof(data));
    return *this;
}

Mat3& Mat3::operator*=(float scalar)
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

Mat3 Mat3::operator*(float scalar) const
{
    Mat3 result = *this;
    return result *= scalar;
}

Mat3& Mat3::operator*=(const Mat3& m)
{
    return *this = *this * m;
}

Mat3 Mat3::operator*(const Mat3& m) const
{
    Mat3 result;
    result.data[0][0] = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] + data[0][2] * m.data[2][0];
    result.data[0][1] = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] + data[0][2] * m.data[2][1];
    result.data[0][2] = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] + data[0][2] * m.data[2][2];
    result.data[1][0] = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] + data[1][2] * m.data[2][0];
    result.data[1][1] = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] + data[1][2] * m.data[2][1];
    result.data[1][2] = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] + data[1][2] * m.data[2][2];
    result.data[2][0] = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] + data[2][2] * m.data[2][0];
    result.data[2][1] = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] + data[2][2] * m.data[2][1];
    result.data[2][2] = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] + data[2][2] * m.data[2][2];
    return result;
}

Mat3 Mat3::operator!() const
{
    Mat3 m;
    m.data[0][0] = data[0][0];
    m.data[0][1] = data[1][0];
    m.data[0][2] = data[2][0];
    m.data[1][0] = data[0][1];
    m.data[1][1] = data[1][1];
    m.data[1][2] = data[2][1];
    m.data[2][0] = data[0][2];
    m.data[2][1] = data[1][2];
    m.data[2][2] = data[2][2];
    return m;
}

Mat3 Mat3::RotationZ(float theta)
{
    const float sinTheta = sinf(theta);
    const float cosTheta = cosf(theta);

    return {
        cosTheta,  sinTheta, 0.0f,
        -sinTheta, cosTheta, 0.0f,
        0.0f,      0.0f,     1.0f,
    };
}

Mat3 Mat3::RotationY(float theta)
{
    const float sinTheta = sinf(theta);
    const float cosTheta = cosf(theta);

    return {
        cosTheta, 0.0f, -sinTheta,
        0.0f,     1.0f, 0.0f,
        sinTheta, 0.0f, cosTheta
    };
}

Mat3 Mat3::RotationX(float theta)
{
    const float sinTheta = sinf(theta);
    const float cosTheta = cosf(theta);

    return {
        1.0f,  0.0f,     0.0f,
        0.0f,  cosTheta, sinTheta,
        0.0f, -sinTheta, cosTheta,
    };
}
