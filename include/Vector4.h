/**
 * @file: Vector4.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-14
 * -----
 * Last Modified: 03-06-2023
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

#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector3.h"
#include <cmath>
#include <cassert>

//**********************************************************************
//* 4 dimensional vector (X,Y,Z,W)
//**********************************************************************
template <class T>
class alignas(sizeof(T)*4) Vector4 : public Vector3<T>
{
public:
    using Vector3<T>::x;
    using Vector3<T>::y;
    using Vector3<T>::z;
    //******************************************************************
    //* Constructors
    //******************************************************************
    // Default sets all components to zero.
    //------------------------------------------------------------------
    Vector4() = default;
    constexpr Vector4(T x, T y, T z, T w) : Vector3<T>::Vector3(x, y, z), w(w) {}

    template <class U>
    constexpr Vector4(const Vector4<U> &v) : Vector3<T>::Vector3(v.x, v.y, v.z), w(v.w) {}

    template <class U>
    constexpr Vector4(const Vector3<U> &v, T w = 1) : Vector3<T>::Vector3(v), w(w) {}
    //******************************************************************

    //******************************************************************
    //* Operators
    //******************************************************************
    template <class U>
    Vector4<T> &operator = (const Vector4<U> &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    template <class U>
    Vector4<T> &operator += (const Vector4<U> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    template <class U>
    Vector4<T> &operator -= (const Vector4<U> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    template <class U>
    Vector4<T> &operator *= (U scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    template <class U>
    Vector4<T> &operator /= (U scalar)
    {
        assert(scalar != 0);
        scalar = 1.0f / scalar;
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    Vector4<T> &operator - ()
    {
        x = -x;
        y = -y;
        z = -z;
        w = -w;
        return *this;
    }

    float &operator [] (int i)
    {
        if (i == 0) {
            return x;
        } else if (i == 1) {
            return y;
        } else if (i == 2) {
            return z;
        } else if (i == 3) {
            return w;
        } else {
            assert("[] Access error!");
        }
        return x;
    }
    //******************************************************************

    //******************************************************************
    //* Methods
    //******************************************************************
    bool IsZero()
    {
        return !(x || y || z || w);
    }

    float LengthSquared()
    {
        return x*x + y*y + z*z + w*w;
    }

    float Length()
    {
        return sqrtf(LengthSquared());
    }
    
    void Normalize()
    {
        float magnitude = Length();
        assert(magnitude != 0);

        magnitude = 1.0f / magnitude;

        x *= magnitude;
        y *= magnitude;
        z *= magnitude;
        w *= magnitude;
    }

    bool IsNormalized()
    {
        return Length() == 1.0f;
    }

    void Homogenize()
    {
        float wInv = 1.0f / w;

        x *= wInv;
        y *= wInv;
        //z *= wInv;
    }
    //******************************************************************

    T w = 0;
};

//**********************************************************************
//* Vector4
//**********************************************************************
template <class T>
inline bool operator==(const Vector4<T> &v, const Vector4<T> &u)
{
    return (v.x == u.x &&
            v.y == u.y &&
            v.z == u.z &&
            v.w == u.w);
}

template <class T>
inline bool operator!=(const Vector4<T> &v, const Vector4<T> &u)
{
    return (v.x != u.x ||
            v.y != u.y ||
            v.z != u.z ||
            v.w != u.w);
}

template <class T, class U>
inline Vector4<T> operator+(const Vector4<T> &v, const Vector4<U> &u)
{
    return Vector4<T>(v.x+u.x, v.y+u.y, v.z+u.z, v.w+u.w);
}

template <class T, class U>
inline Vector4<T> operator-(const Vector4<T> &v,const Vector4<U> &u)
{
    return Vector4<T>(v.x-u.x, v.y-u.y, v.z-u.z, v.w-u.w);
}

template <class T, class U>
inline Vector4<T> operator*(const Vector4<T> &v, const U scalar)
{
    return Vector4<T>(v.x*scalar, v.y*scalar, v.z*scalar, v.w*scalar);
}

template <class T, class U>
inline Vector4<T> operator*(const U scalar, const Vector4<T> &v)
{
    return Vector4<T>(v.x*scalar, v.y*scalar, v.z*scalar, v.w*scalar);
}

template <class T, class U>
inline float operator*(const Vector4<T> &v, const Vector4<U> &u)
{
    return v.x*u.x + v.y*u.y + v.z*u.z + v.w*u.w;
}

template <class T, class U>
inline Vector4<T> operator/(const Vector4<T> &v, const U scalar)
{
    assert(scalar != 0);
    scalar = 1.0f / scalar;
    return Vector4<T>(v.x*scalar, v.y*scalar, v.z*scalar, v.w*scalar);
}

template <class T>
inline Vector4<T> Lerp(const Vector4<T> &v, const Vector4<T> &u, const float t)
{
    return Vector4<float>(v.x + (u.x - v.x) * t,
                          v.y + (u.y - v.y) * t,
                          v.z + (u.z - v.z) * t,
                          v.w + (u.w - v.w) * t);
}

template <class T>
inline Vector4<T> Clamp(const Vector4<T> &v, const T min, const T max)
{
    return Vector4<T>(v.x < min ? min : (v.x > max ? max : v.x),
                      v.y < min ? min : (v.y > max ? max : v.y),
                      v.z < min ? min : (v.z > max ? max : v.z),
                      v.w < min ? min : (v.w > max ? max : v.w));
}

template <class T>
inline Vector4<T> min(const Vector4<T> &v, const Vector4<T> &u)
{
    return Vector4<T>(v.x < u.x ? v.x : u.x,
                      v.y < u.y ? v.y : u.y,
                      v.z < u.z ? v.z : u.z,
                      v.w < u.w ? v.w : u.w);
}

template <class T>
inline Vector4<T> max(const Vector4<T> &v, const Vector4<T> &u)
{
    return Vector4<T>(v.x > u.x ? v.x : u.x,
                      v.y > u.y ? v.y : u.y,
                      v.z > u.z ? v.z : u.z,
                      v.w > u.w ? v.w : u.w);
}

template <class T>
inline float DistanceBetween(const Vector4<T> &v, const Vector4<T> &u)
{
    Vector4<T> distance = v - u;
    return distance.Length();
}

template <class T>
inline float DistanceBetweenSquared (const Vector4<T> &v, const Vector4<T> &u)
{
    Vector4<T> distance = v - u;
    return distance.LengthSquared();
}

#endif // VECTOR4_H
