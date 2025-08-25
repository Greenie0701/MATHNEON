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
        vabs_f32 - NEON intrinsic to compute absolute value of 2 float32 values in parallel
        vst1q_f32 - NEON intrinsic to store 4 float32 values back to memory
        fabsf - Standard C library function that calculates the absolute value of a single float.
                Used here for leftover elements when count is not a multiple of 4.
    int32 routines:
        vld1q_s32 - NEON intrinsic to load 4 int32 values from memory
        vabsq_s32 - NEON intrinsic to compute absolute value of 4 int32 values in parallel
        vabs_s32  - NEON intrinsic to compute absolute value of 2 int32 values in parallel
        vst1q_s32 - NEON intrinsic to store 4 int32 values back to memory
        fabs - Standard C library function that calculates the absolute value of a single integer.
                Used here for leftover elements when count is not a multiple of 4.

Supported routines: Int and Float 32-bit data types [1 to 4 Dimensional arrays]
*/

mn_result_t mn_abs_float_neon(mn_float32_t * dst, mn_float32_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_FLOAT_NEON( /*TO DO - Remove macro logic and replace it by actual neon abs*/
        MN_MAINLOOP_FLOAT_NEON_ABS,  /* SIMD main loop */ 
        MN_SECONDLOOP_FLOAT_ABS      /* leftover elements */
    );

    return MN_SUCCESS;
}

mn_result_t mn_abs_int32_neon(mn_int32_t * dst, mn_int32_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_INT32_NEON( /*TO DO - Remove macro logic and replace it by actual neon abs*/
        MN_MAINLOOP_INT32_NEON_ABS,  /* SIMD main loop */ 
        MN_SECONDLOOP_INT32_ABS      /* leftover elements */
    );

    return MN_SUCCESS;
}

mn_result_t mn_abs_vec2f_neon(mn_vec2f_t * dst, mn_vec2f_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_VEC2F_NEON(
        n_dst  =  vabsq_f32(n_src); /* notice the q → quad = 128 bits (Main loop handles 4 x 32 bits) */
        ,
        n_rest =  vabs_f32(n_rest); /* 64 bits (Odd loop handles 2 x 32 bits) */
    );
}

mn_result_t mn_abs_vec2i_neon(mn_vec2i_t * dst, mn_vec2i_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_VEC2I_NEON(
        n_dst  =  vabsq_s32(n_src);
        ,
        n_rest =  vabs_s32(n_rest);
    );
}

mn_result_t mn_abs_vec3f_neon (mn_vec3f_t * dst, mn_vec3f_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_VEC3F_NEON
    (
        n_dst1 = vabsq_f32 (n_src1);
        n_dst2 = vabsq_f32 (n_src2);
        n_dst3 = vabsq_f32 (n_src3);
        ,
        n_rest.val[0] = vabs_f32 (n_rest.val[0]);   /* the X lane */
        n_rest.val[1] = vabs_f32 (n_rest.val[1]);   /* the Y lane */
        n_rest.val[2] = vabs_f32 (n_rest.val[2]);   /* the Z lane */
    );
}

mn_result_t mn_abs_vec3i_neon (mn_vec3i_t * dst, mn_vec3i_t * src, uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_VEC3I_NEON
    (
        n_dst1 = vabsq_s32 (n_src1);
        n_dst2 = vabsq_s32 (n_src2);
        n_dst3 = vabsq_s32 (n_src3);
        ,
        n_rest.val[0] = vabs_s32 (n_rest.val[0]);   /* the X lane */
        n_rest.val[1] = vabs_s32 (n_rest.val[1]);   /* the Y lane */
        n_rest.val[2] = vabs_s32 (n_rest.val[2]);   /* the Z lane */
    );
}
