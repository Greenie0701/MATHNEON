#include "MN_dtype.h"
#include "MN_macro.h"
#include "MN_math.h"
#include <arm_neon.h>
#include <assert.h>

/*
Input Arguments:
    dst    - Destination pointer that stores the results
    src    - Source pointer that contains user input values
    count  - Number of elements to process

Intrinsics used: 
    float32 routines:
        vld1q_f32 - NEON intrinsic to load 4 float32 values from memory
        vabsq_f32 - NEON intrinsic to compute absolute value of 4 float32 values in parallel
        vst1q_f32 - NEON intrinsic to store 4 float32 values back to memory
        fabsf - Standard C library function that calculates the absolute value of a single float.
                Used here for leftover elements when count is not a multiple of 4.
    int32 routines:
        vld1q_s32 - NEON intrinsic to load 4 int32 values from memory
        vabsq_s32 - NEON intrinsic to compute absolute value of 4 int32 values in parallel
        vst1q_s32 - NEON intrinsic to store 4 int32 values back to memory
        fabs - Standard C library function that calculates the absolute value of a single integer.
                Used here for leftover elements when count is not a multiple of 4.
*/

mn_result_t mn_abs_float_neon(mn_float32_t * dst, mn_float32_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_FLOAT_NEON( /*TO DO - Remove loop logic and replace it by actual neon abs*/
        MN_MAINLOOP_FLOAT_NEON_ABS,  /* SIMD main loop */ 
        MN_SECONDLOOP_FLOAT_ABS      /* leftover elements */
    );

    return MN_SUCCESS;
}

mn_result_t mn_abs_int32_neon(mn_int32_t * dst, mn_int32_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_INT32_NEON( /*TO DO - Remove loop logic and replace it by actual neon abs*/
        MN_MAINLOOP_INT32_NEON_ABS,  /* SIMD main loop */ 
        MN_SECONDLOOP_INT32_ABS      /* leftover elements */
    );

    return MN_SUCCESS;
}

mn_result_t mn_abs_vec2f_neon(mn_vec2f_t * dst, mn_vec2f_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_VEC2F_NEON(
        n_dst  =  vabsq_f32(n_src);
        ,
        n_rest =  vabsq_f32(n_rest);
    );
}

mn_result_t mn_abs_vec2i_neon(mn_vec2i_t * dst, mn_vec2i_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_VEC2I_NEON(
        n_dst  =  vabsq_i32(n_src);
        ,
        n_rest =  vabsq_i32(n_rest);
    );
}


