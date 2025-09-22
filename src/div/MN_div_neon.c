// MSVC-Compatible MN_div_neon.c
#include "MN_dtype.h"
#include "MN_macro.h"
#include "MN_math.h"
#include <arm_neon.h>
#include <assert.h>

/*
Input Arguments:
    dst    - Destination pointer that stores the results
    src1   - Source pointer to array 1 (dividend)
    src2   - Source pointer to array 2 (divisor)
    count  - Number of elements to process
    
Note: For integer division, we use floating point conversion since NEON
      doesn't have native integer division intrinsics.
      For float division, we use reciprocal approximation for better performance.
Please refer to: https://stackoverflow.com/questions/6759897/divide-by-floating-point-number-using-neon-intrinsics [Current implementation]

Intrinsics used:
    float32 routines:
        vld1q_f32 - NEON intrinsic to load 4 float32 values from memory
        vst1q_f32 - NEON intrinsic to store 4 float32 values back to memory
        vrecpeq_f32 - NEON reciprocal approximation
        vrecpsq_f32 - NEON reciprocal step for Newton-Raphson refinement
    int32 routines:
        vld1q_s32 - NEON intrinsic to load 4 int32 values from memory
        vst1q_s32 - NEON intrinsic to store 4 int32 values back to memory
        vcvtq_f32_s32 - Convert int32 to float32
        vcvtq_s32_f32 - Convert float32 to int32
        
Supported routines: Int and Float 32-bit data types [1 to 4 Dimensional arrays]
*/

mn_result_t mn_div_float_neon(mn_float32_t * dst, mn_float32_t * src1, mn_float32_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_FLOAT_NEON(
        MN_MAINLOOP_FLOAT_NEON_DIV,      /* SIMD block for 4 elements */
        MN_SECONDLOOP_FLOAT_DIV          /* scalar leftover elements */
    );
}

mn_result_t mn_div_int32_neon(mn_int32_t * dst, mn_int32_t * src1, mn_int32_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_INT32_NEON(
        MN_MAINLOOP_INT32_NEON_DIV,      /* SIMD block for 4 elements */
        MN_SECONDLOOP_INT32_DIV          /* scalar leftover elements */
    );
}

