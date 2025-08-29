#include "MN_dtype.h"
#include "MN_macro.h"
#include "MN_math.h"
#include <arm_neon.h>
#include <assert.h>

/*
Input Arguments:
    dst    - Destination pointer that stores the results
    src1   - Source pointer to array 1
    src2   - Source pointer to array 2 
    count  - Number of elements to process

Intrinsics used: 
    float32 routines:
        vld1q_f32 - NEON intrinsic to load 4 float32 values from memory
        vst1q_f32 - NEON intrinsic to store 4 float32 values back to memory

    int32 routines:
        vld1q_s32 - NEON intrinsic to load 4 int32 values from memory
        vst1q_s32 - NEON intrinsic to store 4 int32 values back to memory

Supported routines: Int and Float 32-bit data types [1 to 4 Dimensional arrays]
*/

mn_result_t mn_add_float_neon(mn_float32_t * dst, mn_float32_t * src1, mn_float32_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_FLOAT_NEON(
        MN_MAINLOOP_FLOAT_NEON_ADD,  /* SIMD main loop */ 
        MN_SECONDLOOP_FLOAT_ADD      /* leftover elements */
    );

    return MN_SUCCESS;
}

mn_result_t mn_add_int32_neon(mn_int32_t * dst, mn_int32_t * src1, mn_int32_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_INT32_NEON(
        MN_MAINLOOP_INT32_NEON_ADD,  /* SIMD main loop */ 
        MN_SECONDLOOP_INT32_ADD      /* leftover elements */
    );

    return MN_SUCCESS;
}

mn_result_t mn_add_vec2f_neon(mn_vec2f_t * dst, mn_vec2f_t * src1, mn_vec2f_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC2F_NEON(
        n_dst  =  vaddq_f32(n_src); /* notice the q → quad = 128 bits (Main loop handles 4 x 32 bits) */
        ,
        n_rest =  vadd_f32(n_rest); /* 64 bits (Odd loop handles 2 x 32 bits) */
    );
}

mn_result_t mn_add_vec2i_neon(mn_vec2i_t * dst, mn_vec2i_t * src1, mn_vec2i_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC2I_NEON(
        n_dst  =  vaddq_s32(n_src);
        ,
        n_rest =  vadd_s32(n_rest);
    );
}

mn_result_t mn_add_vec3f_neon (mn_vec3f_t * dst, mn_vec3f_t * src1, mn_vec3f_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC3F_NEON
    (
        n_dst1 = vaddq_f32 (n_src1);
        n_dst2 = vaddq_f32 (n_src2);
        n_dst3 = vaddq_f32 (n_src3);
        ,
        n_rest.val[0] = vadd_f32 (n_rest.val[0]);   /* the X lane */
        n_rest.val[1] = vadd_f32 (n_rest.val[1]);   /* the Y lane */
        n_rest.val[2] = vadd_f32 (n_rest.val[2]);   /* the Z lane */
    );
}

mn_result_t mn_add_vec3i_neon (mn_vec3i_t * dst, mn_vec3i_t * src1, mn_vec3i_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC3I_NEON
    (
        n_dst1 = vaddq_s32 (n_src1);
        n_dst2 = vaddq_s32 (n_src2);
        n_dst3 = vaddq_s32 (n_src3);
        ,
        n_rest.val[0] = vadd_s32 (n_rest.val[0]);   /* the X lane */
        n_rest.val[1] = vadd_s32 (n_rest.val[1]);   /* the Y lane */
        n_rest.val[2] = vadd_s32 (n_rest.val[2]);   /* the Z lane */
    );
}

mn_result_t mn_add_vec4f_neon (mn_vec4f_t * dst, mn_vec4f_t * src1, mn_vec4f_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC4F_NEON
    (
        n_dst = vaddq_f32 (n_src);
    );
}

mn_result_t mn_add_vec4i_neon (mn_vec4i_t * dst, mn_vec4i_t * src1, mn_vec4i_t * src2,  uint32_t count)
{
    MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC4I_NEON
    (
        n_dst = vaddq_s32 (n_src);
    );
}

