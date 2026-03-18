/**
 * @file: Vector4.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-14
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

#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector3.h"
#include <cmath>
#include <cassert>
#include <cstddef>

//**********************************************************************
//* 4 dimensional vector (X,Y,Z,W)
//**********************************************************************
/**
 * @brief 4D vector with public x/y/z/w components.
 * @tparam T component type.
 */
template <class T>
class alignas((sizeof(T)*4) > 16 ? 16 : (sizeof(T)*4)) Vector4 : public Vector3<T>
{
public:
    using Vector3<T>::x;
    using Vector3<T>::y;
    using Vector3<T>::z;
    //******************************************************************
    //* Constructors
    //******************************************************************
    /** @brief Default constructor. Components are left uninitialized. */
    Vector4() = default;

    /** @brief Construct from explicit x/y/z/w values. */
    constexpr Vector4(T x, T y, T z, T w) : Vector3<T>::Vector3(x, y, z), w(w) {}

    /** @brief Construct with all components set to the same scalar. */
    constexpr Vector4(const T &s) : Vector3<T>::Vector3(s), w(s) {}

    template <class U>
    /** @brief Converting copy constructor. */
    constexpr Vector4(const Vector4<U> &v) : Vector3<T>::Vector3(v.x, v.y, v.z), w(v.w) {}

    template <class U>
    /** @brief Build from a 3D vector plus homogeneous component w. */
    constexpr Vector4(const Vector3<U> &v, T w = 1) : Vector3<T>::Vector3(v), w(w) {}
    //******************************************************************

    //******************************************************************
    //* Operators
    //******************************************************************
    template <class U>
    /** @brief Assign from vector with possibly different component type. */
    Vector4<T> &operator = (const Vector4<U> &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    template <class U>
    /** @brief Component-wise addition assignment. */
    Vector4<T> &operator += (const Vector4<U> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    template <class U>
    /** @brief Component-wise subtraction assignment. */
    Vector4<T> &operator -= (const Vector4<U> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    template <class U>
    /** @brief Scalar multiplication assignment. */
    Vector4<T> &operator *= (U scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    template <class U>
    /** @brief Scalar division assignment. */
    Vector4<T> &operator /= (U scalar)
    {
        assert(scalar != 0);
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    /** @brief Unary minus in-place. */
    Vector4<T> &operator - ()
    {
        x = -x;
        y = -y;
        z = -z;
        w = -w;
        return *this;
    }

    /** @brief Indexed component access (0 -> x, 1 -> y, 2 -> z, 3 -> w). */
    constexpr T &operator [] (const size_t i)
    {
        assert(i < 4 && "[] Access error!");
        return (i == 0) ? x : ((i == 1) ? y : ((i == 2) ? z : w));
    }

    /** @brief Indexed component access for const vectors. */
    constexpr const T &operator [] (const size_t i) const
    {
        assert(i < 4 && "[] Access error!");
        return (i == 0) ? x : ((i == 1) ? y : ((i == 2) ? z : w));
    }
    //******************************************************************

    //******************************************************************
    //* Methods
    //******************************************************************
    /** @brief True if all components are numerically zero. */
    bool IsZero() const
    {
        return !(x || y || z || w);
    }

    /** @brief Squared Euclidean length. */
    float LengthSquared() const
    {
        return x*x + y*y + z*z + w*w;
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
        w *= magnitude;
    }

    /** @brief True if vector length is approximately one. */
    bool IsNormalized() const
    {
        const float epsilon = 1e-5f;
        return std::fabs(Length() - 1.0f) <= epsilon;
    }

    /** @brief Divide x/y/z by w (homogeneous to Cartesian projection). */
    void Homogenize()
    {
        assert(w != 0);
        float wInv = 1.0f / w;

        x *= wInv;
        y *= wInv;
        z *= wInv;
    }
    //******************************************************************

    T w;
};

//**********************************************************************
//* Vector4
//**********************************************************************
template <class T>
/** @brief Exact equality comparison (component-wise). */
inline bool operator==(const Vector4<T> &v, const Vector4<T> &u)
{
    return (v.x == u.x &&
            v.y == u.y &&
            v.z == u.z &&
            v.w == u.w);
}

template <class T>
/** @brief Exact inequality comparison (component-wise). */
inline bool operator!=(const Vector4<T> &v, const Vector4<T> &u)
{
    return (v.x != u.x ||
            v.y != u.y ||
            v.z != u.z ||
            v.w != u.w);
}

template <class T, class U>
/** @brief Component-wise vector addition. */
inline Vector4<T> operator+(const Vector4<T> &v, const Vector4<U> &u)
{
    return Vector4<T>(v.x+u.x, v.y+u.y, v.z+u.z, v.w+u.w);
}

template <class T, class U>
/** @brief Component-wise vector subtraction. */
inline Vector4<T> operator-(const Vector4<T> &v,const Vector4<U> &u)
{
    return Vector4<T>(v.x-u.x, v.y-u.y, v.z-u.z, v.w-u.w);
}

template <class T, class U>
/** @brief Vector multiplied by scalar. */
inline Vector4<T> operator*(const Vector4<T> &v, const U scalar)
{
    return Vector4<T>(v.x*scalar, v.y*scalar, v.z*scalar, v.w*scalar);
}

template <class T, class U>
/** @brief Scalar multiplied by vector. */
inline Vector4<T> operator*(const U scalar, const Vector4<T> &v)
{
    return Vector4<T>(v.x*scalar, v.y*scalar, v.z*scalar, v.w*scalar);
}

template <class T, class U>
/** @brief Dot product. */
inline float operator*(const Vector4<T> &v, const Vector4<U> &u)
{
    return v.x*u.x + v.y*u.y + v.z*u.z + v.w*u.w;
}

template <class T, class U>
/** @brief Vector divided by scalar. */
inline Vector4<T> operator/(const Vector4<T> &v, const U scalar)
{
    assert(scalar != 0);
    return Vector4<T>(v.x/scalar, v.y/scalar, v.z/scalar, v.w/scalar);
}

template <class T>
/** @brief Linear interpolation from v to u. */
inline Vector4<T> Lerp(const Vector4<T> &v, const Vector4<T> &u, const float t)
{
    return Vector4<T>(v.x + (u.x - v.x) * t,
                      v.y + (u.y - v.y) * t,
                      v.z + (u.z - v.z) * t,
                      v.w + (u.w - v.w) * t);
}

template <class T>
/** @brief Clamp each component to [min, max]. */
inline Vector4<T> Clamp(const Vector4<T> &v, const T min, const T max)
{
    return Vector4<T>(v.x < min ? min : (v.x > max ? max : v.x),
                      v.y < min ? min : (v.y > max ? max : v.y),
                      v.z < min ? min : (v.z > max ? max : v.z),
                      v.w < min ? min : (v.w > max ? max : v.w));
}

template <class T>
/** @brief Component-wise minimum. */
inline Vector4<T> min(const Vector4<T> &v, const Vector4<T> &u)
{
    return Vector4<T>(v.x < u.x ? v.x : u.x,
                      v.y < u.y ? v.y : u.y,
                      v.z < u.z ? v.z : u.z,
                      v.w < u.w ? v.w : u.w);
}

template <class T>
/** @brief Component-wise maximum. */
inline Vector4<T> max(const Vector4<T> &v, const Vector4<T> &u)
{
    return Vector4<T>(v.x > u.x ? v.x : u.x,
                      v.y > u.y ? v.y : u.y,
                      v.z > u.z ? v.z : u.z,
                      v.w > u.w ? v.w : u.w);
}

template <class T>
/** @brief Euclidean distance between two vectors. */
inline float DistanceBetween(const Vector4<T> &v, const Vector4<T> &u)
{
    Vector4<T> distance = v - u;
    return distance.Length();
}

template <class T>
/** @brief Squared Euclidean distance between two vectors. */
inline float DistanceBetweenSquared (const Vector4<T> &v, const Vector4<T> &u)
{
    Vector4<T> distance = v - u;
    return distance.LengthSquared();
}

#endif // VECTOR4_H
