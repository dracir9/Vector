/**
 * @file   mat_mult.S
 * @author Ricard Bitriá Ribes (https://github.com/dracir9)
 * Created Date: 23-05-2023
 * -----
 * Last Modified: 29-05-2023
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



// Matrix multipliction functions for ESP32-S3 processor.
	.text
	.align  4
	.global mult_4x4x4_asm
	.type   mult_4x4x4_asm,@function

// esp_err_t dspm_mult_f32_ansi(const float* A, const float* B, float* C, int m, int n, int k)
mult_4x4x4_asm: 
	entry	a1, 16
// A - a2
// B - a3
// C - a4
// m - a5
// n - a6
// k - a7

//	// Ccheck if we can use S3 memory model:
//	or a12, a5, a6
//	or a12, a7, a12
//	movi.n	a11, 3
//	and a12, a12, a11
//	movi.n   a11, 15
//	or       a10, a3, a2
//	or       a10, a10, a4
//	and		 a10, a10, a11
//	or		 a12, a12, a10
//	beqz  a12, .s3_mmult
//	// Call Esp32 function
//	J 	.dspm_mult_f32_ae32_body

.s3_mmult:
// f0, f1, f2, f3 - multiplication result
// f4, f5, f6, f7 - input for matrix B
// f8, f9, f10,f11- input far matrix A
	movi.n	a14, 0

	slli     	a12, a7, 2		// a12 = K*4 - step for rows
	slli     	a10, a7, 2		// a10 = K*4 - step for rows
	srli	    a11, a6, 2		// N count
	addi.n		a11, a11, -1

	movi.n		a15, 0
	mov	 a13, a3
	mov  a7, a4

    movi.n	a2, 0 // return status ESP_OK
	retw.n

.loop_x_aes3:
	movi.n		a9, 0
	mov      	a8,  a2		// A matirx
	.loop_y_aes3:
		add	 a13, a3, a14		// Reload Y pointer to Y11 + A14
		EE.LDF.128.IP f11, f10, f9, f8, a8, 16  // Load A values: X11, X12, X13, X14
		EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y11, Y12, Y13, Y14
		mul.s	f0, f4, f8		// f0 = X11*Y11
		mul.s	f1, f5, f8		// f1 = X12*Y11
		mul.s	f2, f6, f8		// f2 = X13*Y11
		mul.s	f3, f7, f8		// f3 = X14*Y11

		EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y21, Y22, Y23, Y24
		madd.s	f0, f4, f9		// f0 = X11*Y11 + X12*Y21
		madd.s	f1, f5, f9		// f1 = X11*Y12 + X12*Y22
		madd.s	f2, f6, f9		// f2 = X11*Y13 + X12*Y23
		madd.s	f3, f7, f9		// f3 = X11*Y14 + X12*Y24

		EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y31, Y32, Y33, Y34
		madd.s	f0, f4, f10		// f0 = X11*Y11 + X12*Y21 + X13*Y31
		madd.s	f1, f5, f10		// f1 = X11*Y12 + X12*Y22 + X13*Y32
		madd.s	f2, f6, f10		// f2 = X11*Y13 + X12*Y23 + X13*Y33
		madd.s	f3, f7, f10		// f3 = X11*Y14 + X12*Y24 + X13*Y34

		EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y41, Y42, Y43, Y44
		madd.s	f0, f4, f11		// f0 = X11*Y11 + X12*Y21 + X13*Y31 + X14*Y41
		madd.s	f1, f5, f11		// f1 = X11*Y12 + X12*Y22 + X13*Y32 + X14*Y42
		madd.s	f2, f6, f11		// f2 = X11*Y13 + X12*Y23 + X13*Y33 + X14*Y43
		madd.s	f3, f7, f11		// f3 = X11*Y14 + X12*Y24 + X13*Y34 + X14*Y44
		
		loopnez a11, .loop_end_m_aes3
			EE.LDF.128.IP f11, f10, f9, f8, a8, 16  // Load A values: X15, X16, X17, X18

			EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y51, Y52, Y53, Y54
			madd.s	f0, f4, f8		// f0 += X15*Y51
			madd.s	f1, f5, f8		// f1 += X15*Y52
			madd.s	f2, f6, f8		// f2 += X15*Y53
			madd.s	f3, f7, f8		// f3 += X15*Y54

			EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y61, Y62, Y63, Y64
			madd.s	f0, f4, f9		// f0 += X16*Y61
			madd.s	f1, f5, f9		// f1 += X16*Y62 
			madd.s	f2, f6, f9		// f2 += X16*Y63 
			madd.s	f3, f7, f9		// f3 += X16*Y64 

			EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y71, Y72, Y73, Y74
			madd.s	f0, f4, f10		// f0 = 
			madd.s	f1, f5, f10		// f1 = 
			madd.s	f2, f6, f10		// f2 = 
			madd.s	f3, f7, f10		// f3 = 

			EE.LDF.128.XP f7, f6, f5, f4, a13, a12 // Load B value: Y81, Y82, Y83, Y84
			madd.s	f0, f4, f11		// f0 = 
			madd.s	f1, f5, f11		// f1 = 
			madd.s	f2, f6, f11		// f2 = 
			madd.s	f3, f7, f11		// f3 = 
		.loop_end_m_aes3:
		EE.STF.128.XP f3, f2, f1, f0, a4, a10 // Store result 

		addi  a9, a9, 1 // Increment loop1 counter
	blt   a9, a5, .loop_y_aes3
	addi.n  a7, a7, 16
	mov		a4, a7
	addi.n  a14, a14, 16			// B shift for 4
	addi  a15, a15, 16 // Increment loop1 counter
blt   a15, a12, .loop_x_aes3
	movi.n	a2, 0 // return status ESP_OK
	retw.n
