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

mn_result_t mn_div_vec2f_neon(mn_vec2f_t * dst, mn_vec2f_t * src1, mn_vec2f_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC2F_NEON(
        /* Use reciprocal approximation for float division */
        float32x4_t rec = vrecpeq_f32(n_src2); \
        rec = vmulq_f32(vrecpsq_f32(n_src2, rec), rec); \
        rec = vmulq_f32(vrecpsq_f32(n_src2, rec), rec); \
        n_dst = vmulq_f32(n_src1, rec);,
        /* Handle leftover elements with scalar division */
        float32x2_t rec_rest = vrecpe_f32(n_rest2); \
        rec_rest = vmul_f32(vrecps_f32(n_rest2, rec_rest), rec_rest); \
        rec_rest = vmul_f32(vrecps_f32(n_rest2, rec_rest), rec_rest); \
        n_rest = vmul_f32(n_rest1, rec_rest);
    );
}

mn_result_t mn_div_vec2i_neon(mn_vec2i_t * dst, mn_vec2i_t * src1, mn_vec2i_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC2I_NEON(
        /* Convert to float, divide, then convert back to int */
        float32x4_t f_src1 = vcvtq_f32_s32(n_src1); \
        float32x4_t f_src2 = vcvtq_f32_s32(n_src2); \
        float32x4_t rec = vrecpeq_f32(f_src2); \
        rec = vmulq_f32(vrecpsq_f32(f_src2, rec), rec); \
        rec = vmulq_f32(vrecpsq_f32(f_src2, rec), rec); \
        float32x4_t f_result = vmulq_f32(f_src1, rec); \
        n_dst = vcvtq_s32_f32(f_result);,
        /* Handle leftover elements with scalar division */
        float32x2_t f_rest1 = vcvt_f32_s32(n_rest1); \
        float32x2_t f_rest2 = vcvt_f32_s32(n_rest2); \
        float32x2_t rec_rest = vrecpe_f32(f_rest2); \
        rec_rest = vmul_f32(vrecps_f32(f_rest2, rec_rest), rec_rest); \
        rec_rest = vmul_f32(vrecps_f32(f_rest2, rec_rest), rec_rest); \
        float32x2_t f_result_rest = vmul_f32(f_rest1, rec_rest); \
        n_rest = vcvt_s32_f32(f_result_rest);
    );
}

mn_result_t mn_div_vec3f_neon(mn_vec3f_t * dst, mn_vec3f_t * src1, mn_vec3f_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC3F_NEON(
        /* X components */
        float32x4_t rec1 = vrecpeq_f32(n_src21); \
        rec1 = vmulq_f32(vrecpsq_f32(n_src21, rec1), rec1); \
        rec1 = vmulq_f32(vrecpsq_f32(n_src21, rec1), rec1); \
        n_dst1 = vmulq_f32(n_src11, rec1); \
        /* Y components */ \
        float32x4_t rec2 = vrecpeq_f32(n_src22); \
        rec2 = vmulq_f32(vrecpsq_f32(n_src22, rec2), rec2); \
        rec2 = vmulq_f32(vrecpsq_f32(n_src22, rec2), rec2); \
        n_dst2 = vmulq_f32(n_src12, rec2); \
        /* Z components */ \
        float32x4_t rec3 = vrecpeq_f32(n_src23); \
        rec3 = vmulq_f32(vrecpsq_f32(n_src23, rec3), rec3); \
        rec3 = vmulq_f32(vrecpsq_f32(n_src23, rec3), rec3); \
        n_dst3 = vmulq_f32(n_src13, rec3);,
        /* Handle leftover elements */
        float32x2_t rec_x = vrecpe_f32(vget_low_f32(vcombine_f32(n_rest2.val[0], n_rest2.val[0]))); \
        rec_x = vmul_f32(vrecps_f32(vget_low_f32(vcombine_f32(n_rest2.val[0], n_rest2.val[0])), rec_x), rec_x); \
        n_rest1.val[0] = vmul_f32(n_rest1.val[0], rec_x); \
        float32x2_t rec_y = vrecpe_f32(vget_low_f32(vcombine_f32(n_rest2.val[1], n_rest2.val[1]))); \
        rec_y = vmul_f32(vrecps_f32(vget_low_f32(vcombine_f32(n_rest2.val[1], n_rest2.val[1])), rec_y), rec_y); \
        n_rest1.val[1] = vmul_f32(n_rest1.val[1], rec_y); \
        float32x2_t rec_z = vrecpe_f32(vget_low_f32(vcombine_f32(n_rest2.val[2], n_rest2.val[2]))); \
        rec_z = vmul_f32(vrecps_f32(vget_low_f32(vcombine_f32(n_rest2.val[2], n_rest2.val[2])), rec_z), rec_z); \
        n_rest1.val[2] = vmul_f32(n_rest1.val[2], rec_z);
    );
}

mn_result_t mn_div_vec3i_neon(mn_vec3i_t * dst, mn_vec3i_t * src1, mn_vec3i_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC3I_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        /* X components */
        float32x4_t f_src11 = vcvtq_f32_s32(n_src11); \
        float32x4_t f_src21 = vcvtq_f32_s32(n_src21); \
        float32x4_t rec1 = vrecpeq_f32(f_src21); \
        rec1 = vmulq_f32(vrecpsq_f32(f_src21, rec1), rec1); \
        rec1 = vmulq_f32(vrecpsq_f32(f_src21, rec1), rec1); \
        n_dst1 = vcvtq_s32_f32(vmulq_f32(f_src11, rec1)); \
        /* Y components */ \
        float32x4_t f_src12 = vcvtq_f32_s32(n_src12); \
        float32x4_t f_src22 = vcvtq_f32_s32(n_src22); \
        float32x4_t rec2 = vrecpeq_f32(f_src22); \
        rec2 = vmulq_f32(vrecpsq_f32(f_src22, rec2), rec2); \
        rec2 = vmulq_f32(vrecpsq_f32(f_src22, rec2), rec2); \
        n_dst2 = vcvtq_s32_f32(vmulq_f32(f_src12, rec2)); \
        /* Z components */ \
        float32x4_t f_src13 = vcvtq_f32_s32(n_src13); \
        float32x4_t f_src23 = vcvtq_f32_s32(n_src23); \
        float32x4_t rec3 = vrecpeq_f32(f_src23); \
        rec3 = vmulq_f32(vrecpsq_f32(f_src23, rec3), rec3); \
        rec3 = vmulq_f32(vrecpsq_f32(f_src23, rec3), rec3); \
        n_dst3 = vcvtq_s32_f32(vmulq_f32(f_src13, rec3));,
        /* Handle leftover elements - convert to scalar operations */
        float f_x1 = (float)vget_lane_s32(n_rest1.val[0], 0); \
        float f_x2 = (float)vget_lane_s32(n_rest2.val[0], 0); \
        int32_t result_x = (int32_t)(f_x1 / f_x2); \
        n_rest1.val[0] = vset_lane_s32(result_x, n_rest1.val[0], 0); \
        float f_y1 = (float)vget_lane_s32(n_rest1.val[1], 0); \
        float f_y2 = (float)vget_lane_s32(n_rest2.val[1], 0); \
        int32_t result_y = (int32_t)(f_y1 / f_y2); \
        n_rest1.val[1] = vset_lane_s32(result_y, n_rest1.val[1], 0); \
        float f_z1 = (float)vget_lane_s32(n_rest1.val[2], 0); \
        float f_z2 = (float)vget_lane_s32(n_rest2.val[2], 0); \
        int32_t result_z = (int32_t)(f_z1 / f_z2); \
        n_rest1.val[2] = vset_lane_s32(result_z, n_rest1.val[2], 0);
    );
}

mn_result_t mn_div_vec4f_neon(mn_vec4f_t * dst, mn_vec4f_t * src1, mn_vec4f_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC4F_NEON(
        /* Use reciprocal approximation for better performance */
        float32x4_t rec = vrecpeq_f32(n_src2); \
        rec = vmulq_f32(vrecpsq_f32(n_src2, rec), rec); \
        rec = vmulq_f32(vrecpsq_f32(n_src2, rec), rec); \
        n_dst = vmulq_f32(n_src1, rec);
    );
}

mn_result_t mn_div_vec4i_neon(mn_vec4i_t * dst, mn_vec4i_t * src1, mn_vec4i_t * src2, uint32_t count)
{
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC4I_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        float32x4_t f_src1 = vcvtq_f32_s32(n_src1); \
        float32x4_t f_src2 = vcvtq_f32_s32(n_src2); \
        float32x4_t rec = vrecpeq_f32(f_src2); \
        rec = vmulq_f32(vrecpsq_f32(f_src2, rec), rec); \
        rec = vmulq_f32(vrecpsq_f32(f_src2, rec), rec); \
        float32x4_t f_result = vmulq_f32(f_src1, rec); \
        n_dst = vcvtq_s32_f32(f_result);
    );
}
