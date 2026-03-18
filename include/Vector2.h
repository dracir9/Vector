/**
 * @file: Vector2.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-13
 * -----
 * Last Modified: 22-10-2025
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

#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <cassert>
#include <cstddef>

//**********************************************************************
//* 2 dimensional vector (X,Y)
//**********************************************************************
/**
 * @brief 2D vector with public x/y components.
 * @tparam T component type.
 */
template <class T>
class Vector2
{
public:
    //******************************************************************
    //* Constructors
    //******************************************************************
    /** @brief Default constructor. Components are left uninitialized. */
    Vector2() = default;

    /** @brief Construct from explicit x/y values. */
    constexpr Vector2(T x, T y) : x(x), y(y) {}

    /** @brief Construct with both components set to the same scalar. */
    constexpr Vector2(const T &s) : x(s), y(s) {}

    template <class U>
    /** @brief Converting copy constructor. */
    constexpr Vector2(const Vector2<U> &v) : x(v.x), y(v.y) {}
    //******************************************************************

    //******************************************************************
    //* Operators
    //******************************************************************
    template <class U>
    /** @brief Assign from vector with possibly different component type. */
    Vector2<T> &operator = (const Vector2<U> &v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }

    template <class U>
    /** @brief Component-wise addition assignment. */
    Vector2<T> &operator += (const Vector2<U> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    template <class U>
    /** @brief Component-wise subtraction assignment. */
    Vector2<T> &operator -= (const Vector2<U> &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    template <class U>  
    /** @brief Scalar multiplication assignment. */
    Vector2<T> &operator *= (const U scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <class U>
    /** @brief Scalar division assignment. */
    Vector2<T> &operator /= (const U scalar)
    {
        assert(scalar != 0);
        x /= scalar;
        y /= scalar;
        return *this;
    }

    /** @brief Unary minus in-place. */
    Vector2<T> &operator - ()
    {
        x = -x;
        y = -y;
        return *this;
    }

    /** @brief Indexed component access (0 -> x, 1 -> y). */
    constexpr T &operator [] (const size_t i)
    {
        assert(i < 2 && "[] Access error!");
        return (i == 0) ? x : y;
    }

    /** @brief Indexed component access for const vectors (0 -> x, 1 -> y). */
    constexpr const T &operator [] (const size_t i) const
    {
        assert(i < 2 && "[] Access error!");
        return (i == 0) ? x : y;
    }
    //******************************************************************

    //******************************************************************
    //* Methods
    //******************************************************************
    /** @brief True if both components are numerically zero. */
    bool IsZero() const
    {
        return !(x || y);
    }

    /** @brief Squared Euclidean length. */
    float LengthSquared() const
    {
        return static_cast<float>(x) * static_cast<float>(x) +
               static_cast<float>(y) * static_cast<float>(y);
    }

    /** @brief Euclidean length. */
    float Length() const
    {
        return std::sqrt(LengthSquared());
    }

    /** @brief Normalize vector in place. */
    void Normalize()
    {
        float len = Length();
        assert(len != 0);

        len = 1.0f / len;

        x *= len;
        y *= len;
    }

    /** @brief True if vector length is approximately one. */
    bool IsNormalized() const
    {
        const float epsilon = 1e-5f;
        return std::fabs(Length() - 1.0f) <= epsilon;
    }
    //******************************************************************

    T x;
    T y;
};

//**********************************************************************
//* Vector2
//**********************************************************************
template <class T>
/** @brief Exact equality comparison (component-wise). */
inline bool operator==(const Vector2<T> &v, const Vector2<T> &u)
{
    return (v.x == u.x &&
            v.y == u.y);
}

template <class T>
/** @brief Exact inequality comparison (component-wise). */
inline bool operator!=(const Vector2<T> &v, const Vector2<T> &u)
{
    return (v.x != u.x ||
            v.y != u.y);
}

template <class T, class U>
/** @brief Component-wise vector addition. */
inline Vector2<T> operator+(const Vector2<T> &v, const Vector2<U> &u)
{
    return Vector2<T>(v.x+u.x, v.y+u.y);
}

template <class T, class U>
/** @brief Component-wise vector subtraction. */
inline Vector2<T> operator-(const Vector2<T> &v,const Vector2<U> &u)
{
    return Vector2<T>(v.x-u.x, v.y-u.y);
}

template <class T, class U>
/** @brief Vector multiplied by scalar. */
inline Vector2<T> operator*(const Vector2<T> &v, const U scalar)
{
    return Vector2<T>(v.x*scalar, v.y*scalar);
}

template <class T, class U>
/** @brief Scalar multiplied by vector. */
inline Vector2<T> operator*(const U scalar, const Vector2<T> &v)
{
    return Vector2<T>(v.x*scalar, v.y*scalar);
}

template <class T, class U>
/** @brief Dot product. */
inline float operator*(const Vector2<T> &v, const Vector2<U> &u)
{
    return v.x*u.x + v.y*u.y;
}

template <class T, class U>
/** @brief Vector divided by scalar. */
inline Vector2<T> operator/(const Vector2<T> &v, const U scalar)
{
    assert(scalar != 0);
    return Vector2<T>(v.x/scalar, v.y/scalar);
}

template <class T, class U>
/** @brief 2D cross product (z-component of the 3D equivalent). */
inline auto CrossProduct(const Vector2<T> &v, const Vector2<U> &u) -> decltype(v.x*u.y - v.y*u.x)
{
    return v.x*u.y - v.y*u.x;
}

template <class T>
/** @brief Linear interpolation from v to u. */
inline Vector2<T> Lerp(const Vector2<T> &v, const Vector2<T> &u, const float t)
{
    return Vector2<T>(v.x + (u.x - v.x) * t,
                      v.y + (u.y - v.y) * t);
}

template <class T>
/** @brief Clamp each component to [min, max]. */
inline Vector2<T> Clamp(const Vector2<T> &v, const T min, const T max)
{
    return Vector2<T>(v.x < min ? min : (v.x > max ? max : v.x),
                      v.y < min ? min : (v.y > max ? max : v.y));
}

template <class T>
/** @brief Component-wise minimum. */
inline Vector2<T> min(const Vector2<T> &v, const Vector2<T> &u)
{
    return Vector2<T>(v.x < u.x ? v.x : u.x,
                      v.y < u.y ? v.y : u.y);
}

template <class T>
/** @brief Component-wise maximum. */
inline Vector2<T> max(const Vector2<T> &v, const Vector2<T> &u)
{
    return Vector2<T>(v.x > u.x ? v.x : u.x,
                      v.y > u.y ? v.y : u.y);
}

template <class T>
/** @brief Euclidean distance between two vectors. */
inline float DistanceBetween(const Vector2<T> &v, const Vector2<T> &u)
{
    Vector2<T> distance = v - u;
    return distance.Length();
}

template <class T>
/** @brief Squared Euclidean distance between two vectors. */
inline float DistanceBetweenSquared (const Vector2<T> &v, const Vector2<T> &u)
{
    Vector2<T> distance = v - u;
    return distance.LengthSquared();
}

#endif // VECTOR2_H
