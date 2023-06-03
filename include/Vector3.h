/**
 * @file: Vector3.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-13
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

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector2.h"
#include <cmath>
#include <cassert>

//**********************************************************************
//* 3 dimensional vector (X,Y,Z)
//**********************************************************************
template <class T>
class Vector3 : public Vector2<T>
{
public:
    using Vector2<T>::x;
    using Vector2<T>::y;
    //******************************************************************
    //* Constructors
    //******************************************************************
    Vector3() = default;
    constexpr Vector3(T x, T y, T z) : Vector2<T>::Vector2(x, y), z(z) {}

    constexpr Vector3(const T &s) : Vector2<T>::Vector2(s), z(s) {}

    template <class U>
    constexpr Vector3(const Vector3<U> &v) : Vector2<T>::Vector2(v.x, v.y), z(v.z) {}

    template <class U>
    constexpr Vector3(const Vector2<U> &v, T z) : Vector2<T>::Vector2(v), z(z) {}
    //******************************************************************

    //******************************************************************
    //* Operators
    //******************************************************************
    template <class U>
    Vector3<T> &operator = (const Vector3<U> &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    template <class U>
    Vector3<T> &operator += (const Vector3<U> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    template <class U>
    Vector3<T> &operator -= (const Vector3<U> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <class U>
    Vector3<T> &operator *= (U scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    template <class U>
    Vector3<T> &operator /= (U scalar)
    {
        assert(scalar != 0);
        scalar = 1.0f / scalar;
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3<T> &operator - ()
    {
        x = -x;
        y = -y;
        z = -z;
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
        return !(x || y || z);
    }

    float LengthSquared()
    {
        return x*x + y*y + z*z;
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
    }

    bool IsNormalized()
    {
        return Length() == 1.0f;
    }
    //******************************************************************

    T z;
};

//**********************************************************************
//* Vector3
//**********************************************************************
template <class T>
inline bool operator==(const Vector3<T> &v, const Vector3<T> &u)
{
    return (v.x == u.x &&
            v.y == u.y &&
            v.z == u.z);
}

template <class T>
inline bool operator!=(const Vector3<T> &v, const Vector3<T> &u)
{
    return (v.x != u.x ||
            v.y != u.y ||
            v.z != u.z);
}

template <class T, class U>
inline Vector3<T> operator+(const Vector3<T> &v, const Vector3<U> &u)
{
    return Vector3<T>(v.x+u.x, v.y+u.y, v.z+u.z);
}

template <class T, class U>
inline Vector3<T> operator-(const Vector3<T> &v,const Vector3<U> &u)
{
    return Vector3<T>(v.x-u.x, v.y-u.y, v.z-u.z);
}

template <class T, class U>
inline Vector3<T> operator*(const Vector3<T> &v, const U scalar)
{
    return Vector3<T>(v.x*scalar, v.y*scalar, v.z*scalar);
}

template <class T, class U>
inline Vector3<T> operator*(const U scalar, const Vector3<T> &v)
{
    return Vector3<T>(v.x*scalar, v.y*scalar, v.z*scalar);
}

template <class T, class U>
inline float operator*(const Vector3<T> &v, const Vector3<U> &u)
{
    return v.x*u.x + v.y*u.y + v.z*u.z;
}

template <class T, class U>
inline Vector3<T> operator/(const Vector3<T> &v, const U scalar)
{
    assert(scalar != 0);
    scalar = 1.0f / scalar;
    return Vector3<T>(v.x*scalar, v.y*scalar, v.z*scalar);
}

template <class T, class U>
inline Vector3<T> CrossProduct(const Vector3<T> &v, const Vector3<U> &u)
{
    return Vector3<T>(v.y*u.z - v.z*u.y,
                      v.z*u.x - v.x*u.z,
                      v.x*u.y - v.y*u.x);
}

template <class T>
inline Vector3<T> Lerp(const Vector3<T> &v, const Vector3<T> &u, const float t)
{
    return Vector3<float>(v.x + (u.x - v.x) * t,
                          v.y + (u.y - v.y) * t,
                          v.z + (u.z - v.z) * t);
}

template <class T>
inline Vector3<T> Clamp(const Vector3<T> &v, const T min, const T max)
{
    return Vector3<T>(v.x < min ? min : (v.x > max ? max : v.x),
                      v.y < min ? min : (v.y > max ? max : v.y),
                      v.z < min ? min : (v.z > max ? max : v.z));
}

template <class T>
inline Vector3<T> min(const Vector3<T> &v, const Vector3<T> &u)
{
    return Vector3<T>(v.x < u.x ? v.x : u.x,
                      v.y < u.y ? v.y : u.y,
                      v.z < u.z ? v.z : u.z);
}

template <class T>
inline Vector3<T> max(const Vector3<T> &v, const Vector3<T> &u)
{
    return Vector3<T>(v.x > u.x ? v.x : u.x,
                      v.y > u.y ? v.y : u.y,
                      v.z > u.z ? v.z : u.z);
}

template <class T>
inline float DistanceBetween(const Vector3<T> &v, const Vector3<T> &u)
{
    Vector3<T> distance = v - u;
    return distance.Length();
}

template <class T>
inline float DistanceBetweenSquared (const Vector3<T> &v, const Vector3<T> &u)
{
    Vector3<T> distance = v - u;
    return distance.LengthSquared();
}

#endif // VECTOR3_H
