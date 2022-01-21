/**
 * @file: Vector.h
 * @author: Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 2021-11-09
 * -----
 * Last Modified: 2021-11-17
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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstdint>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

typedef Vector4<int32_t> Vec4;
typedef Vector4<int16_t> Vec4h;
typedef Vector4<float> Vec4f;

typedef Vector3<int32_t> Vec3;
typedef Vector3<int16_t> Vec3h;
typedef Vector3<float> Vec3f;

typedef Vector2<int32_t> Vec2;
typedef Vector2<int16_t> Vec2h;
typedef Vector2<float> Vec2f;

#endif
