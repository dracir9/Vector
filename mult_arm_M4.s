/**
 * @file   mult_arm_M4.s
 * @author Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 23-09-2025
 * -----
 * Last Modified: 24-09-2025
 * Modified By: Ricard Bitriá Ribes
 * -----
 * @copyright (c) 2023 Ricard Bitriá Ribes
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

#ifdef STM32F407xx

// uint32_t mult_1x4x4_asm(const float* v, const float* M, const float* u);
    .section  .text.mult_1x4x4_asm
  .align 4                            // Align to word boundary
  .global mult_1x4x4_asm              // This makes it a real symbol
  .type mult_1x4x4_asm, %function     // Declare mult_1x4x4_asm to be a function.
mult_1x4x4_asm:
// v - r0
// M - r1
// u - r2
//	mov		r0, sp
//	sub     r0, #16
//	str     r1, [r0, #4]
//	str     r2, [r0, #8]
//	str     r3, [r0, #12]

    vldm.32 r0, {s0-s3}   // Load v values: X11, X12, X13, X14
    vldm.32 r1!, {s4-s7}   // Load M value: Y11, Y12, Y13, Y14
    vmul.F32 s8, s0, s4   // s8 = X11*Y11
    vmul.F32 s9, s0, s5   // s9 = X11*Y12
    vmul.F32 s10, s0, s6  // s10 = X11*Y13
    vmul.F32 s11, s0, s7  // s11 = X11*Y14

    vldm.32 r1!, {s4-s7}   // Load M value: Y21, Y22, Y23, Y24
    vfma.F32 s8, s1, s4   // s8 = X11*Y11 + X12*Y21
    vfma.F32 s9, s1, s5   // s9 = X11*Y12 + X12*Y22
    vfma.F32 s10, s1, s6  // s10 = X11*Y13 + X12*Y23
    vfma.F32 s11, s1, s7  // s11 = X11*Y14 + X12*Y24

    vldm.32 r1!, {s4-s7}   // Load M value: Y31, Y32, Y33, Y34
    vfma.F32 s8, s2, s4   // s8 = X11*Y11 + X12*Y21 + X13*Y31
    vfma.F32 s9, s2, s5   // s9 = X11*Y12 + X12*Y22 + X13*Y32
    vfma.F32 s10, s2, s6  // s10 = X11*Y13 + X12*Y23 + X13*Y33
    vfma.F32 s11, s2, s7  // s11 = X11*Y14 + X12*Y24 + X13*Y34

    vldm.32 r1, {s4-s7}   // Load M value: Y41, Y42, Y43, Y44
    vfma.F32 s8, s3, s4   // s8 = X11*Y11 + X12*Y21 + X13*Y31 + X14*Y41
    vfma.F32 s9, s3, s5   // s9 = X11*Y12 + X12*Y22 + X13*Y32 + X14*Y42
    vfma.F32 s10, s3, s6  // s10 = X11*Y13 + X12*Y23 + X13*Y33 + X14*Y43
    vfma.F32 s11, s3, s7  // s11 = X11*Y14 + X12*Y24 + X13*Y34 + X14*Y44

    vstm.32 r2, {s8-s11}  // Store result

    bx      lr
// END

#endif
