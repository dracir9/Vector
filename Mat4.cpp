/**
 * @file: Mat4.cpp
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-15
 * -----
 * Last Modified: 16-08-2023
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

#include "Mat4.h"
#include <cmath>
#include <cstring>

Mat4& Mat4::operator=(const Mat4& m)
{
#ifdef CONFIG_IDF_TARGET_ESP32S3
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
#else
    data[0][0] = m.data[0][0];
    data[0][1] = m.data[0][1];
    data[0][2] = m.data[0][2];
    data[0][3] = m.data[0][3];
    data[1][0] = m.data[1][0];
    data[1][1] = m.data[1][1];
    data[1][2] = m.data[1][2];
    data[1][3] = m.data[1][3];
    data[2][0] = m.data[2][0];
    data[2][1] = m.data[2][1];
    data[2][2] = m.data[2][2];
    data[2][3] = m.data[2][3];
    data[3][0] = m.data[3][0];
    data[3][1] = m.data[3][1];
    data[3][2] = m.data[3][2];
    data[3][3] = m.data[3][3];
#endif
    return *this;
}

Mat4& Mat4::operator*=(float scalar)
{
#ifdef CONFIG_IDF_TARGET_ESP32S3
    mult_4x4xS_asm(&data[0][0], &scalar, &data[0][0]);
#else
    for(auto& row : data)
    {
        for(float& e : row)
        {
            e *= scalar;
        }
    }
#endif
    return *this;
}

Mat4 Mat4::operator*(float scalar) const
{
    Mat4 result;
#ifdef CONFIG_IDF_TARGET_ESP32S3
    mult_4x4xS_asm(&data[0][0], &scalar, &result.data[0][0]);
    
#else
    result = *this;
    result *= scalar;
#endif
    return result;
}

Mat4& Mat4::operator*=(const Mat4& m)
{
#ifdef CONFIG_IDF_TARGET_ESP32S3
    mult_4x4x4_asm(&data[0][0], &m.data[0][0], &data[0][0]);
    return *this;
#else
    return *this = *this * m;
#endif
}

Mat4 Mat4::operator*(const Mat4& m) const
{
    Mat4 result;

#ifdef CONFIG_IDF_TARGET_ESP32S3
    mult_4x4x4_asm(&data[0][0], &m.data[0][0], &result.data[0][0]);
#else
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
#endif
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
