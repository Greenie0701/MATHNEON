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
        /* Use reciprocal approximation for better performance */
        float32x4_t reciprocal = vrecpeq_f32(n_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        n_dst = vmulq_f32(n_src1, reciprocal);,      /* SIMD block for 4 elements */
        *dst = *src1 / *src2;                        /* scalar leftover elements */
    );
}

mn_result_t mn_div_int32_neon(mn_int32_t * dst, mn_int32_t * src1, mn_int32_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_INT32_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        float32x4_t f_src1 = vcvtq_f32_s32(n_src1);
        float32x4_t f_src2 = vcvtq_f32_s32(n_src2);
        float32x4_t reciprocal = vrecpeq_f32(f_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        float32x4_t f_result = vmulq_f32(f_src1, reciprocal);
        n_dst = vcvtq_s32_f32(f_result);,      /* SIMD block for 4 elements */
        *dst = *src1 / *src2;                  /* scalar leftover elements */
    );
}

mn_result_t mn_div_vec2f_neon(mn_vec2f_t * dst, mn_vec2f_t * src1, mn_vec2f_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC2F_NEON(
        /* Use reciprocal approximation for 2-element vector division */
        float32x2_t reciprocal = vrecpe_f32(n_src2);
        reciprocal = vmul_f32(vrecps_f32(n_src2, reciprocal), reciprocal);
        reciprocal = vmul_f32(vrecps_f32(n_src2, reciprocal), reciprocal);
        n_dst = vmul_f32(n_src1, reciprocal);,     /* SIMD main loop */
        /* Scalar division for leftover elements */
        dst->x = src1->x / src2->x;
        dst->y = src1->y / src2->y;
    );
}

mn_result_t mn_div_vec2i_neon(mn_vec2i_t * dst, mn_vec2i_t * src1, mn_vec2i_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC2I_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        float32x2_t f_src1 = vcvt_f32_s32(n_src1);
        float32x2_t f_src2 = vcvt_f32_s32(n_src2);
        float32x2_t reciprocal = vrecpe_f32(f_src2);
        reciprocal = vmul_f32(vrecps_f32(f_src2, reciprocal), reciprocal);
        reciprocal = vmul_f32(vrecps_f32(f_src2, reciprocal), reciprocal);
        float32x2_t f_result = vmul_f32(f_src1, reciprocal);
        n_dst = vcvt_s32_f32(f_result);,     /* SIMD main loop */
        /* Scalar division for leftover elements */
        dst->x = src1->x / src2->x;
        dst->y = src1->y / src2->y;
    );
}

mn_result_t mn_div_vec3f_neon(mn_vec3f_t * dst, mn_vec3f_t * src1, mn_vec3f_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC3F_NEON(
        /* Reciprocal approximation for each component group */
        float32x4_t rec1 = vrecpeq_f32(n_src21);
        rec1 = vmulq_f32(vrecpsq_f32(n_src21, rec1), rec1);
        rec1 = vmulq_f32(vrecpsq_f32(n_src21, rec1), rec1);
        n_dst1 = vmulq_f32(n_src11, rec1);   /* X components */
        float32x4_t rec2 = vrecpeq_f32(n_src22);
        rec2 = vmulq_f32(vrecpsq_f32(n_src22, rec2), rec2);
        rec2 = vmulq_f32(vrecpsq_f32(n_src22, rec2), rec2);
        n_dst2 = vmulq_f32(n_src12, rec2);   /* Y components */
        float32x4_t rec3 = vrecpeq_f32(n_src23);
        rec3 = vmulq_f32(vrecpsq_f32(n_src23, rec3), rec3);
        rec3 = vmulq_f32(vrecpsq_f32(n_src23, rec3), rec3);
        n_dst3 = vmulq_f32(n_src13, rec3);,  /* Z components */
        /* Scalar division for leftover elements */
        dst->x = src1->x / src2->x;
        dst->y = src1->y / src2->y;
        dst->z = src1->z / src2->z;
    );
}

mn_result_t mn_div_vec3i_neon(mn_vec3i_t * dst, mn_vec3i_t * src1, mn_vec3i_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC3I_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        float32x4_t f_src11 = vcvtq_f32_s32(n_src11);
        float32x4_t f_src21 = vcvtq_f32_s32(n_src21);
        float32x4_t rec1 = vrecpeq_f32(f_src21);
        rec1 = vmulq_f32(vrecpsq_f32(f_src21, rec1), rec1);
        rec1 = vmulq_f32(vrecpsq_f32(f_src21, rec1), rec1);
        n_dst1 = vcvtq_s32_f32(vmulq_f32(f_src11, rec1));   /* X components */
        float32x4_t f_src12 = vcvtq_f32_s32(n_src12);
        float32x4_t f_src22 = vcvtq_f32_s32(n_src22);
        float32x4_t rec2 = vrecpeq_f32(f_src22);
        rec2 = vmulq_f32(vrecpsq_f32(f_src22, rec2), rec2);
        rec2 = vmulq_f32(vrecpsq_f32(f_src22, rec2), rec2);
        n_dst2 = vcvtq_s32_f32(vmulq_f32(f_src12, rec2));   /* Y components */
        float32x4_t f_src13 = vcvtq_f32_s32(n_src13);
        float32x4_t f_src23 = vcvtq_f32_s32(n_src23);
        float32x4_t rec3 = vrecpeq_f32(f_src23);
        rec3 = vmulq_f32(vrecpsq_f32(f_src23, rec3), rec3);
        rec3 = vmulq_f32(vrecpsq_f32(f_src23, rec3), rec3);
        n_dst3 = vcvtq_s32_f32(vmulq_f32(f_src13, rec3));,  /* Z components */
        /* Scalar division for leftover elements */
        dst->x = src1->x / src2->x;
        dst->y = src1->y / src2->y;
        dst->z = src1->z / src2->z;
    );
}

mn_result_t mn_div_vec4f_neon(mn_vec4f_t * dst, mn_vec4f_t * src1, mn_vec4f_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC4F_NEON(
        /* Use reciprocal approximation - Each vec4f fits exactly in 128-bit register */
        float32x4_t reciprocal = vrecpeq_f32(n_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        n_dst = vmulq_f32(n_src1, reciprocal);      
    );
}

mn_result_t mn_div_vec4i_neon(mn_vec4i_t * dst, mn_vec4i_t * src1, mn_vec4i_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC4I_NEON(
        /* Convert to float, divide using reciprocal, convert back - Each vec4i fits exactly in 128-bit register */
        float32x4_t f_src1 = vcvtq_f32_s32(n_src1);
        float32x4_t f_src2 = vcvtq_f32_s32(n_src2);
        float32x4_t reciprocal = vrecpeq_f32(f_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        float32x4_t f_result = vmulq_f32(f_src1, reciprocal);
        n_dst = vcvtq_s32_f32(f_result);      
    );
}
