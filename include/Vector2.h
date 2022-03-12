/**
 * @file: Vector2.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-13
 * -----
 * Last Modified: 12-03-2022
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

#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <cassert>

//**********************************************************************
//* 2 dimensional vector (X,Y)
//**********************************************************************
template <class T>
class Vector2
{
public:
    //******************************************************************
    //* Constructors
    //******************************************************************
    Vector2() = default;
    constexpr Vector2(T x, T y) : x(x), y(y) {}

    template <class U>
    Vector2(const Vector2<U> &v) : x(v.x), y(v.y) {}
    //******************************************************************

    //******************************************************************
    //* Operators
    //******************************************************************
    template <class U>
    Vector2<T> &operator = (const Vector2<U> &v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }

    template <class U>
    Vector2<T> &operator += (const Vector2<U> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    template <class U>
    Vector2<T> &operator -= (const Vector2<U> &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    template <class U>  
    Vector2<T> &operator *= (const U scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <class U>
    Vector2<T> &operator /= (const U scalar)
    {
        assert(scalar != 0);
        scalar = 1.0f / scalar;
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2<T> &operator - ()
    {
        x = -x;
        y = -y;
        return *this;
    }

    T &operator [] (const int i)
    {
        if (i == 0) {
            return x;
        } else if (i == 1) {
            return y;
        } else {
            assert("[] Access error!");
        }
    }
    //******************************************************************

    //******************************************************************
    //* Methods
    //******************************************************************
    bool IsZero()
    {
        return !(x || y);
    }

    T LengthSquared()
    {
        return x*x + y*y;
    }

    float Length()
    {
        return sqrtf((float)LengthSquared());
    }

    void Normalize()
    {
        float len = Length();
        assert(len != 0);

        len = 1.0f / len;

        x *= len;
        y *= len;
    }

    bool IsNormalized()
    {
        return Length() == 1.0f;
    }
    //******************************************************************

    T x = 0;
    T y = 0;
};

//**********************************************************************
//* Vector2
//**********************************************************************
template <class T>
inline bool operator==(const Vector2<T> &v, const Vector2<T> &u)
{
    return (v.x == u.x &&
            v.y == u.y);
}

template <class T>
inline bool operator!=(const Vector2<T> &v, const Vector2<T> &u)
{
    return (v.x != u.x ||
            v.y != u.y);
}

template <class T, class U>
inline Vector2<T> operator+(const Vector2<T> &v, const Vector2<U> &u)
{
    return Vector2<T>(v.x+u.x, v.y+u.y);
}

template <class T, class U>
inline Vector2<T> operator-(const Vector2<T> &v,const Vector2<U> &u)
{
    return Vector2<T>(v.x-u.x, v.y-u.y);
}

template <class T, class U>
inline Vector2<T> operator*(const Vector2<T> &v, const U scalar)
{
    return Vector2<T>(v.x*scalar, v.y*scalar);
}

template <class T, class U>
inline Vector2<T> operator*(const U scalar, const Vector2<T> &v)
{
    return Vector2<T>(v.x*scalar, v.y*scalar);
}

template <class T, class U>
inline float operator*(const Vector2<T> &v, const Vector2<U> &u)
{
    return v.x*u.x + v.y*u.y + v.z*u.z;
}

template <class T, class U>
inline Vector2<T> operator/(const Vector2<T> &v, const U scalar)
{
    assert(scalar != 0);
    scalar = 1.0f / scalar;
    return Vector2<T>(v.x*scalar, v.y*scalar);
}

template <class T, class U>
inline Vector2<T> CrossProduct(const Vector2<T> &v, const Vector2<U> &u)
{
    return Vector2<T>(v.y*u.z - v.z*u.y,
                      v.z*u.x - v.x*u.z);
}

template <class T>
inline Vector2<T> Lerp(const Vector2<T> &v, const Vector2<T> &u, const float t)
{
    return Vec2f(v.x + (u.x - v.x) * t,
                   v.y + (u.y - v.y) * t);
}

template <class T>
inline Vector2<T> Clamp(const Vector2<T> &v, const T min, const T max)
{
    return Vector2<T>(v.x < min ? min : (v.x > max ? max : v.x),
                      v.y < min ? min : (v.y > max ? max : v.y));
}

template <class T>
inline Vector2<T> min(const Vector2<T> &v, const Vector2<T> &u)
{
    return Vector2<T>(v.x < u.x ? v.x : u.x,
                      v.y < u.y ? v.z : u.y);
}

template <class T>
inline Vector2<T> max(const Vector2<T> &v, const Vector2<T> &u)
{
    return Vector2<T>(v.x > u.x ? v.x : u.x,
                      v.y > u.y ? v.z : u.y,
                      v.z > u.z ? v.z : u.z);
}

template <class T>
inline float DistanceBetween(const Vector2<T> &v, const Vector2<T> &u)
{
    Vector2<T> distance = v - u;
    return distance.Length();
}

template <class T>
inline float DistanceBetweenSquared (const Vector2<T> &v, const Vector2<T> &u)
{
    Vector2<T> distance = v - u;
    return distance.LengthSquared();
}

#endif // VECTOR2_H
