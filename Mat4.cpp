/**
 * @file: Mat4.cpp
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-15
 * -----
 * Last Modified: 30-09-2025
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

__attribute__((optimize("O3"))) Mat4 Mat4::Inverse() const
{
    Mat4 mIn = *this;
    Mat4 mOut = Mat4::Identity();

    // Compute the inverse using Gaussian elimination

    for (int i = 0; i < 4; i++) {
        // Find pivot
        float pivot = mIn.data[i][i];
        if (pivot == 0.0f) {
            // Check rows below for a non-zero pivot
            bool found = false;

            for (int j = i + 1; j < 4; j++) {
                if (mIn.data[j][i] != 0.0f) {
                    // Swap rows in both matrices
                    for (int k = 0; k < 4; k++) {
                        float tmp = mIn.data[i][k];
                        mIn.data[i][k] = mIn.data[j][k];
                        mIn.data[j][k] = tmp;

                        tmp = mOut.data[i][k];
                        mOut.data[i][k] = mOut.data[j][k];
                        mOut.data[j][k] = tmp;
                    }
                    pivot = mIn.data[i][i];
                    found = true;
                    break;
                }
            }

            if (!found)
                return Mat4(); // Singular matrix, return zero matrix
        }
        
        // Scale pivot row
        for (int j = 0; j < 4; j++) {
            mIn.data[i][j] /= pivot;
            mOut.data[i][j] /= pivot;
        }
        // Eliminate column
        for (int j = 0; j < 4; j++) {
            if (j != i) {
                float factor = mIn.data[j][i];
                for (int k = 0; k < 4; k++) {
                    mIn.data[j][k] -= factor * mIn.data[i][k];
                    mOut.data[j][k] -= factor * mOut.data[i][k];
                }
            }
        }
    }
    return mOut;
}

float Mat4::Determinant() const
{
    float det;
    det  = data[0][3] * data[1][2] * data[2][1] * data[3][0] - data[0][2] * data[1][3] * data[2][1] * data[3][0]
         - data[0][3] * data[1][1] * data[2][2] * data[3][0] + data[0][1] * data[1][3] * data[2][2] * data[3][0]
         + data[0][2] * data[1][1] * data[2][3] * data[3][0] - data[0][1] * data[1][2] * data[2][3] * data[3][0]
         - data[0][3] * data[1][2] * data[2][0] * data[3][1] + data[0][2] * data[1][3] * data[2][0] * data[3][1]
         + data[0][3] * data[1][0] * data[2][2] * data[3][1] - data[0][0] * data[1][3] * data[2][2] * data[3][1]
         - data[0][2] * data[1][0] * data[2][3] * data[3][1] + data[0][0] * data[1][2] * data[2][3] * data[3][1]
         + data[0][3] * data[1][1] * data[2][0] * data[3][2] - data[0][1] * data[1][3] * data[2][0] * data[3][2]
         - data[0][3] * data[1][0] * data[2][1] * data[3][2] + data[0][0] * data[1][3] * data[2][1] * data[3][2]
         + data[0][1] * data[1][0] * data[2][3] * data[3][2] - data[0][0] * data[1][1] * data[2][3] * data[3][2]
         - data[0][2] * data[1][1] * data[2][0] * data[3][3] + data[0][1] * data[1][2] * data[2][0] * data[3][3]
         + data[0][2] * data[1][0] * data[2][1] * data[3][3] - data[0][0] * data[1][2] * data[2][1] * data[3][3]
         - data[0][1] * data[1][0] * data[2][2] * data[3][3] + data[0][0] * data[1][1] * data[2][2] * data[3][3];
    return det;
}
