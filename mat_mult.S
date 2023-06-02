/**
 * @file   mat_mult.S
 * @author Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 23-05-2023
 * -----
 * Last Modified: 02-06-2023
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

#include "sdkconfig.h"

#ifdef CONFIG_IDF_TARGET_ESP32S3

// Matrix multipliction functions for ESP32-S3 processor.
    .text
    .align  4
    .global mult_4x4x4_asm
    .type   mult_4x4x4_asm,@function

// esp_err_t mult_4x4x4_asm(const float* A, const float* B, const float* C);
mult_4x4x4_asm: 
    entry	a1, 16
// A - a2
// B - a3
// C - a4

// Start matrix multiplication
    // First row
    EE.LDF.128.IP f11, f10, f9, f8, a2, 16  // Load A values: X11, X12, X13, X14
    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y11, Y12, Y13, Y14
    mul.s	f0, f4, f8		// f0 = X11*Y11
    mul.s	f1, f5, f8		// f1 = X11*Y12
    mul.s	f2, f6, f8		// f2 = X11*Y13
    mul.s	f3, f7, f8		// f3 = X11*Y14

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y21, Y22, Y23, Y24
    madd.s	f0, f4, f9		// f0 = X11*Y11 + X12*Y21
    madd.s	f1, f5, f9		// f1 = X11*Y12 + X12*Y22
    madd.s	f2, f6, f9		// f2 = X11*Y13 + X12*Y23
    madd.s	f3, f7, f9		// f3 = X11*Y14 + X12*Y24

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y31, Y32, Y33, Y34
    madd.s	f0, f4, f10		// f0 = X11*Y11 + X12*Y21 + X13*Y31
    madd.s	f1, f5, f10		// f1 = X11*Y12 + X12*Y22 + X13*Y32
    madd.s	f2, f6, f10		// f2 = X11*Y13 + X12*Y23 + X13*Y33
    madd.s	f3, f7, f10		// f3 = X11*Y14 + X12*Y24 + X13*Y34

    EE.LDF.128.IP f7, f6, f5, f4, a3, -16 // Load B value: Y41, Y42, Y43, Y44
    madd.s	f0, f4, f11		// f0 = X11*Y11 + X12*Y21 + X13*Y31 + X14*Y41
    madd.s	f1, f5, f11		// f1 = X11*Y12 + X12*Y22 + X13*Y32 + X14*Y42
    madd.s	f2, f6, f11		// f2 = X11*Y13 + X12*Y23 + X13*Y33 + X14*Y43
    madd.s	f3, f7, f11		// f3 = X11*Y14 + X12*Y24 + X13*Y34 + X14*Y44

    EE.STF.128.IP f3, f2, f1, f0, a4, 16 // Store result

    // Second row - Now moving backwards through matrix B to reduce memory loads
    EE.LDF.128.IP f11, f10, f9, f8, a2, 16  // Load A values: X21, X22, X23, X24
    mul.s	f0, f4, f11		// f0 = X24*Y41
    mul.s	f1, f5, f11		// f1 = X24*Y42
    mul.s	f2, f6, f11		// f2 = X24*Y43
    mul.s	f3, f7, f11		// f3 = X24*Y44

    EE.LDF.128.IP f7, f6, f5, f4, a3, -16 // Load B value: Y31, Y32, Y33, Y34
    madd.s	f0, f4, f10		// f0 = X23*Y31 + X24*Y41
    madd.s	f1, f5, f10		// f1 = X23*Y32 + X24*Y42
    madd.s	f2, f6, f10		// f2 = X23*Y33 + X24*Y43
    madd.s	f3, f7, f10		// f3 = X23*Y34 + X24*Y44

    EE.LDF.128.IP f7, f6, f5, f4, a3, -16 // Load B value: Y21, Y22, Y23, Y24
    madd.s	f0, f4, f9		// f0 = X22*Y21 + X23*Y31 + X24*Y41
    madd.s	f1, f5, f9		// f1 = X22*Y22 + X23*Y32 + X24*Y42
    madd.s	f2, f6, f9		// f2 = X22*Y23 + X23*Y33 + X24*Y43
    madd.s	f3, f7, f9		// f3 = X22*Y24 + X23*Y34 + X24*Y44

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y11, Y12, Y13, Y14
    madd.s	f0, f4, f8		// f0 = X21*Y11 + X22*Y21 + X23*Y31 + X24*Y41
    madd.s	f1, f5, f8		// f1 = X21*Y12 + X22*Y22 + X23*Y32 + X24*Y42
    madd.s	f2, f6, f8		// f2 = X21*Y13 + X22*Y23 + X23*Y33 + X24*Y43
    madd.s	f3, f7, f8		// f3 = X21*Y14 + X22*Y24 + X23*Y34 + X24*Y44

    EE.STF.128.IP f3, f2, f1, f0, a4, 16 // Store result

    // Third row - Now moving forward
    EE.LDF.128.IP f11, f10, f9, f8, a2, 16  // Load A values: X31, X32, X33, X34
    mul.s	f0, f4, f8		// f0 = X31*Y11
    mul.s	f1, f5, f8		// f1 = X31*Y12
    mul.s	f2, f6, f8		// f2 = X31*Y13
    mul.s	f3, f7, f8		// f3 = X31*Y14

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y21, Y22, Y23, Y24
    madd.s	f0, f4, f9		// f0 = X31*Y11 + X32*Y21
    madd.s	f1, f5, f9		// f1 = X31*Y12 + X32*Y22
    madd.s	f2, f6, f9		// f2 = X31*Y13 + X32*Y23
    madd.s	f3, f7, f9		// f3 = X31*Y14 + X32*Y24

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y31, Y32, Y33, Y34
    madd.s	f0, f4, f10		// f0 = X31*Y11 + X32*Y21 + X33*Y31
    madd.s	f1, f5, f10		// f1 = X31*Y12 + X32*Y22 + X33*Y32
    madd.s	f2, f6, f10		// f2 = X31*Y13 + X32*Y23 + X33*Y33
    madd.s	f3, f7, f10		// f3 = X31*Y14 + X32*Y24 + X33*Y34

    EE.LDF.128.IP f7, f6, f5, f4, a3, -16 // Load B value: Y41, Y42, Y43, Y44
    madd.s	f0, f4, f11		// f0 = X31*Y11 + X32*Y21 + X33*Y31 + X34*Y41
    madd.s	f1, f5, f11		// f1 = X31*Y12 + X32*Y22 + X33*Y32 + X34*Y42
    madd.s	f2, f6, f11		// f2 = X31*Y13 + X32*Y23 + X33*Y33 + X34*Y43
    madd.s	f3, f7, f11		// f3 = X31*Y14 + X32*Y24 + X33*Y34 + X34*Y44

    EE.STF.128.IP f3, f2, f1, f0, a4, 16 // Store result

    // Forth row - Now moving backwards
    EE.LDF.128.IP f11, f10, f9, f8, a2, 16  // Load A values: X41, X42, X43, X44
    mul.s	f0, f4, f11		// f0 = X44*Y41
    mul.s	f1, f5, f11		// f1 = X44*Y42
    mul.s	f2, f6, f11		// f2 = X44*Y43
    mul.s	f3, f7, f11		// f3 = X44*Y44

    EE.LDF.128.IP f7, f6, f5, f4, a3, -16 // Load B value: Y31, Y32, Y33, Y34
    madd.s	f0, f4, f10		// f0 = X43*Y31 + X44*Y41
    madd.s	f1, f5, f10		// f1 = X43*Y32 + X44*Y42
    madd.s	f2, f6, f10		// f2 = X43*Y33 + X44*Y43
    madd.s	f3, f7, f10		// f3 = X43*Y34 + X44*Y44

    EE.LDF.128.IP f7, f6, f5, f4, a3, -16 // Load B value: Y21, Y22, Y23, Y24
    madd.s	f0, f4, f9		// f0 = X42*Y21 + X43*Y31 + X44*Y41
    madd.s	f1, f5, f9		// f1 = X42*Y22 + X43*Y32 + X44*Y42
    madd.s	f2, f6, f9		// f2 = X42*Y23 + X43*Y33 + X44*Y43
    madd.s	f3, f7, f9		// f3 = X42*Y24 + X43*Y34 + X44*Y44

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y11, Y12, Y13, Y14
    madd.s	f0, f4, f8		// f0 = X41*Y11 + X42*Y21 + X43*Y31 + X44*Y41
    madd.s	f1, f5, f8		// f1 = X41*Y12 + X42*Y22 + X43*Y32 + X44*Y42
    madd.s	f2, f6, f8		// f2 = X41*Y13 + X42*Y23 + X43*Y33 + X44*Y43
    madd.s	f3, f7, f8		// f3 = X41*Y14 + X42*Y24 + X43*Y34 + X44*Y44

    EE.STF.128.IP f3, f2, f1, f0, a4, 0 // Store result

    movi.n	a2, 0 // return status ESP_OK
    retw.n

// END


// Vector * Matrix
    .align 4
    .global mult_1x4x4_asm
    .type   mult_1x4x4_asm,@function

// mult_1x4x4_asm(const float* v, const float* m, const float* C);
mult_1x4x4_asm: 
    entry	a1, 16
// v - a2
// m - a3
// C - a4

    EE.LDF.128.IP f11, f10, f9, f8, a2, 16  // Load A values: X11, X12, X13, X14
    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y11, Y12, Y13, Y14
    mul.s	f0, f4, f8		// f0 = X11*Y11
    mul.s	f1, f5, f8		// f1 = X11*Y12
    mul.s	f2, f6, f8		// f2 = X11*Y13
    mul.s	f3, f7, f8		// f3 = X11*Y14

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y21, Y22, Y23, Y24
    madd.s	f0, f4, f9		// f0 = X11*Y11 + X12*Y21
    madd.s	f1, f5, f9		// f1 = X11*Y12 + X12*Y22
    madd.s	f2, f6, f9		// f2 = X11*Y13 + X12*Y23
    madd.s	f3, f7, f9		// f3 = X11*Y14 + X12*Y24

    EE.LDF.128.IP f7, f6, f5, f4, a3, 16 // Load B value: Y31, Y32, Y33, Y34
    madd.s	f0, f4, f10		// f0 = X11*Y11 + X12*Y21 + X13*Y31
    madd.s	f1, f5, f10		// f1 = X11*Y12 + X12*Y22 + X13*Y32
    madd.s	f2, f6, f10		// f2 = X11*Y13 + X12*Y23 + X13*Y33
    madd.s	f3, f7, f10		// f3 = X11*Y14 + X12*Y24 + X13*Y34

    EE.LDF.128.IP f7, f6, f5, f4, a3, 0 // Load B value: Y41, Y42, Y43, Y44
    madd.s	f0, f4, f11		// f0 = X11*Y11 + X12*Y21 + X13*Y31 + X14*Y41
    madd.s	f1, f5, f11		// f1 = X11*Y12 + X12*Y22 + X13*Y32 + X14*Y42
    madd.s	f2, f6, f11		// f2 = X11*Y13 + X12*Y23 + X13*Y33 + X14*Y43
    madd.s	f3, f7, f11		// f3 = X11*Y14 + X12*Y24 + X13*Y34 + X14*Y44

    EE.STF.128.IP f3, f2, f1, f0, a4, 16 // Store result

    movi.n	a2, 0 // return status ESP_OK
    retw.n
// END

#endif
