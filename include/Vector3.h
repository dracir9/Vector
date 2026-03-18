/**
 * @file: Vector3.h
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

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector2.h"
#include <cmath>
#include <cassert>
#include <cstddef>

//**********************************************************************
//* 3 dimensional vector (X,Y,Z)
//**********************************************************************
/**
 * @brief 3D vector with public x/y/z components.
 * @tparam T component type.
 */
template <class T>
class Vector3 : public Vector2<T>
{
public:
    using Vector2<T>::x;
    using Vector2<T>::y;
    //******************************************************************
    //* Constructors
    //******************************************************************
    /** @brief Default constructor. Components are left uninitialized. */
    Vector3() = default;

    /** @brief Construct from explicit x/y/z values. */
    constexpr Vector3(T x, T y, T z) : Vector2<T>::Vector2(x, y), z(z) {}

    /** @brief Construct with all components set to the same scalar. */
    constexpr Vector3(const T &s) : Vector2<T>::Vector2(s), z(s) {}

    template <class U>
    /** @brief Converting copy constructor. */
    constexpr Vector3(const Vector3<U> &v) : Vector2<T>::Vector2(v.x, v.y), z(v.z) {}

    template <class U>
    /** @brief Build from a 2D vector plus z component. */
    constexpr Vector3(const Vector2<U> &v, T z) : Vector2<T>::Vector2(v), z(z) {}
    //******************************************************************

    //******************************************************************
    //* Operators
    //******************************************************************
    template <class U>
    /** @brief Assign from vector with possibly different component type. */
    Vector3<T> &operator = (const Vector3<U> &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    template <class U>
    /** @brief Component-wise addition assignment. */
    Vector3<T> &operator += (const Vector3<U> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    template <class U>
    /** @brief Component-wise subtraction assignment. */
    Vector3<T> &operator -= (const Vector3<U> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <class U>
    /** @brief Scalar multiplication assignment. */
    Vector3<T> &operator *= (U scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    template <class U>
    /** @brief Scalar division assignment. */
    Vector3<T> &operator /= (U scalar)
    {
        assert(scalar != 0);
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    /** @brief Unary minus in-place. */
    Vector3<T> &operator - ()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    /** @brief Indexed component access (0 -> x, 1 -> y, 2 -> z). */
    constexpr T &operator [] (const size_t i)
    {
        assert(i < 3 && "[] Access error!");
        return (i == 0) ? x : ((i == 1) ? y : z);
    }

    /** @brief Indexed component access for const vectors. */
    constexpr const T &operator [] (const size_t i) const
    {
        assert(i < 3 && "[] Access error!");
        return (i == 0) ? x : ((i == 1) ? y : z);
    }
    //******************************************************************

    //******************************************************************
    //* Methods
    //******************************************************************
    /** @brief True if all components are numerically zero. */
    bool IsZero() const
    {
        return !(x || y || z);
    }

    /** @brief Squared Euclidean length. */
    float LengthSquared() const
    {
        return x*x + y*y + z*z;
    }

    /** @brief Euclidean length. */
    float Length() const
    {
        return std::sqrt(LengthSquared());
    }
    
    /** @brief Normalize vector in place. */
    void Normalize()
    {
        float magnitude = Length();
        assert(magnitude != 0);

        magnitude = 1.0f / magnitude;

        x *= magnitude;
        y *= magnitude;
        z *= magnitude;
    }

    /** @brief True if vector length is approximately one. */
    bool IsNormalized() const
    {
        const float epsilon = 1e-5f;
        return std::fabs(Length() - 1.0f) <= epsilon;
    }
    //******************************************************************

    T z;
};

//**********************************************************************
//* Vector3
//**********************************************************************
template <class T>
/** @brief Exact equality comparison (component-wise). */
inline bool operator==(const Vector3<T> &v, const Vector3<T> &u)
{
    return (v.x == u.x &&
            v.y == u.y &&
            v.z == u.z);
}

template <class T>
/** @brief Exact inequality comparison (component-wise). */
inline bool operator!=(const Vector3<T> &v, const Vector3<T> &u)
{
    return (v.x != u.x ||
            v.y != u.y ||
            v.z != u.z);
}

template <class T, class U>
/** @brief Component-wise vector addition. */
inline Vector3<T> operator+(const Vector3<T> &v, const Vector3<U> &u)
{
    return Vector3<T>(v.x+u.x, v.y+u.y, v.z+u.z);
}

template <class T, class U>
/** @brief Component-wise vector subtraction. */
inline Vector3<T> operator-(const Vector3<T> &v,const Vector3<U> &u)
{
    return Vector3<T>(v.x-u.x, v.y-u.y, v.z-u.z);
}

template <class T, class U>
/** @brief Vector multiplied by scalar. */
inline Vector3<T> operator*(const Vector3<T> &v, const U scalar)
{
    return Vector3<T>(v.x*scalar, v.y*scalar, v.z*scalar);
}

template <class T, class U>
/** @brief Scalar multiplied by vector. */
inline Vector3<T> operator*(const U scalar, const Vector3<T> &v)
{
    return Vector3<T>(v.x*scalar, v.y*scalar, v.z*scalar);
}

template <class T, class U>
/** @brief Dot product. */
inline float operator*(const Vector3<T> &v, const Vector3<U> &u)
{
    return v.x*u.x + v.y*u.y + v.z*u.z;
}

template <class T, class U>
/** @brief Vector divided by scalar. */
inline Vector3<T> operator/(const Vector3<T> &v, const U scalar)
{
    assert(scalar != 0);
    return Vector3<T>(v.x/scalar, v.y/scalar, v.z/scalar);
}

template <class T, class U>
/** @brief 3D cross product. */
inline Vector3<T> CrossProduct(const Vector3<T> &v, const Vector3<U> &u)
{
    return Vector3<T>(v.y*u.z - v.z*u.y,
                      v.z*u.x - v.x*u.z,
                      v.x*u.y - v.y*u.x);
}

template <class T>
/** @brief Linear interpolation from v to u. */
inline Vector3<T> Lerp(const Vector3<T> &v, const Vector3<T> &u, const float t)
{
    return Vector3<T>(v.x + (u.x - v.x) * t,
                      v.y + (u.y - v.y) * t,
                      v.z + (u.z - v.z) * t);
}

template <class T>
/** @brief Clamp each component to [min, max]. */
inline Vector3<T> Clamp(const Vector3<T> &v, const T min, const T max)
{
    return Vector3<T>(v.x < min ? min : (v.x > max ? max : v.x),
                      v.y < min ? min : (v.y > max ? max : v.y),
                      v.z < min ? min : (v.z > max ? max : v.z));
}

template <class T>
/** @brief Component-wise minimum. */
inline Vector3<T> min(const Vector3<T> &v, const Vector3<T> &u)
{
    return Vector3<T>(v.x < u.x ? v.x : u.x,
                      v.y < u.y ? v.y : u.y,
                      v.z < u.z ? v.z : u.z);
}

template <class T>
/** @brief Component-wise maximum. */
inline Vector3<T> max(const Vector3<T> &v, const Vector3<T> &u)
{
    return Vector3<T>(v.x > u.x ? v.x : u.x,
                      v.y > u.y ? v.y : u.y,
                      v.z > u.z ? v.z : u.z);
}

template <class T>
/** @brief Euclidean distance between two vectors. */
inline float DistanceBetween(const Vector3<T> &v, const Vector3<T> &u)
{
    Vector3<T> distance = v - u;
    return distance.Length();
}

template <class T>
/** @brief Squared Euclidean distance between two vectors. */
inline float DistanceBetweenSquared(const Vector3<T> &v, const Vector3<T> &u)
{
    Vector3<T> distance = v - u;
    return distance.LengthSquared();
}

#endif // VECTOR3_H
