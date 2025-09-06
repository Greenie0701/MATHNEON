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

mn_result_t mn_mul_float_neon(mn_float32_t * dst, mn_float32_t * src1, mn_float32_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_FLOAT_NEON(
        MN_MAINLOOP_FLOAT_NEON_MUL,      /* SIMD block for 4 elements */
        MN_SECONDLOOP_FLOAT_MUL          /* scalar leftover elements */
    );
}

mn_result_t mn_mul_int32_neon(mn_int32_t * dst, mn_int32_t * src1, mn_int32_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_INT32_NEON(
        MN_MAINLOOP_INT32_NEON_MUL,      /* SIMD block for 4 elements */
        MN_SECONDLOOP_INT32_MUL          /* scalar leftover elements */
    );
}

mn_result_t mn_mul_vec2f_neon(mn_vec2f_t * dst, mn_vec2f_t * src1, mn_vec2f_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_VEC2F_NEON(
        n_dst = vmulq_f32(n_src1, n_src2);,     /* SIMD main loop */
        n_rest = vmul_f32(n_rest1, n_rest2);    /* leftover elements */
    );
}

mn_result_t mn_mul_vec2i_neon(mn_vec2i_t * dst, mn_vec2i_t * src1, mn_vec2i_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_VEC2I_NEON(
        n_dst = vmulq_s32(n_src1, n_src2);,     /* SIMD main loop */
        n_rest = vmul_s32(n_rest1, n_rest2);    /* leftover elements */
    );
}

mn_result_t mn_mul_vec3f_neon(mn_vec3f_t * dst, mn_vec3f_t * src1, mn_vec3f_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_VEC3F_NEON(
        n_dst1 = vmulq_f32(n_src11, n_src21);   /* X components */
        n_dst2 = vmulq_f32(n_src12, n_src22);   /* Y components */  
        n_dst3 = vmulq_f32(n_src13, n_src23);,  /* Z components */
        n_rest1.val[0] = vmul_f32(n_rest1.val[0], n_rest2.val[0]); /* X */
        n_rest1.val[1] = vmul_f32(n_rest1.val[1], n_rest2.val[1]); /* Y */
        n_rest1.val[2] = vmul_f32(n_rest1.val[2], n_rest2.val[2]); /* Z */
    );
}

mn_result_t mn_mul_vec3i_neon(mn_vec3i_t * dst, mn_vec3i_t * src1, mn_vec3i_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_VEC3I_NEON(
        n_dst1 = vmulq_s32(n_src11, n_src21);   /* X components */
        n_dst2 = vmulq_s32(n_src12, n_src22);   /* Y components */
        n_dst3 = vmulq_s32(n_src13, n_src23);,  /* Z components */
        n_rest1.val[0] = vmul_s32(n_rest1.val[0], n_rest2.val[0]); /* X */
        n_rest1.val[1] = vmul_s32(n_rest1.val[1], n_rest2.val[1]); /* Y */
        n_rest1.val[2] = vmul_s32(n_rest1.val[2], n_rest2.val[2]); /* Z */
    );
}

mn_result_t mn_mul_vec4f_neon(mn_vec4f_t * dst, mn_vec4f_t * src1, mn_vec4f_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_VEC4F_NEON(
        n_dst = vmulq_f32(n_src1, n_src2);      /* Each vec4f fits exactly in 128-bit register */
    );
}

mn_result_t mn_mul_vec4i_neon(mn_vec4i_t * dst, mn_vec4i_t * src1, mn_vec4i_t * src2, uint32_t count)
{
    MN_MUL_DstSrc1Src2_DO_COUNT_TIMES_VEC4I_NEON(
        n_dst = vmulq_s32(n_src1, n_src2);      /* Each vec4i fits exactly in 128-bit register */
    );
}
