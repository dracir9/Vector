/**
 * @file: Mat3.cpp
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

#include "Mat3.h"
#include <cmath>
#include <cassert>
#include <cstring>

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

__attribute__((optimize("O3"))) Mat3 Mat3::Inverse() const
{
    Mat3 mIn = *this;
    Mat3 mOut = Mat3::Identity();

    // Compute the inverse using Gaussian elimination

    for (int i = 0; i < 3; i++) {
        // Find pivot
        float pivot = mIn.data[i][i];
        if (pivot == 0.0f) {
            // Check rows below for a non-zero pivot
            bool found = false;

            for (int j = i + 1; j < 3; j++) {
                if (mIn.data[j][i] != 0.0f) {
                    // Swap rows in both matrices
                    for (int k = 0; k < 3; k++) {
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
                return Mat3(); // Singular matrix, return zero matrix
        }
        
        // Scale pivot row
        for (int j = 0; j < 3; j++) {
            mIn.data[i][j] /= pivot;
            mOut.data[i][j] /= pivot;
        }
        // Eliminate column
        for (int j = 0; j < 3; j++) {
            if (j != i) {
                float factor = mIn.data[j][i];
                for (int k = 0; k < 3; k++) {
                    mIn.data[j][k] -= factor * mIn.data[i][k];
                    mOut.data[j][k] -= factor * mOut.data[i][k];
                }
            }
        }
    }
    return mOut;
}

float Mat3::Determinant() const
{
    return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
           data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
           data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
}
