#include "MN_dtype.h"
#include "MN_macro.h"
#include "MN_math.h"
#include <arm_neon.h>
#include <assert.h>

mn_result_t mn_addc_float_neon (mn_float32_t * dst, mn_float32_t * src, const mn_float32_t cst, mn_uint32_t count)
{
    MN_ADDC_DstSrcCst_DO_COUNT_TIMES_FLOAT_NEON
    (
        n_dst = vaddq_f32 (n_src, n_cst);
        ,
        n_rest = vadd_f32 (n_rest, n_rest_cst);
    );
}

mn_result_t mn_addc_vec2f_neon (mn_vec2f_t * dst, mn_vec2f_t * src, const mn_vec2f_t * cst, mn_uint32_t count)
{
    MN_ADDC_DstSrc_DO_COUNT_TIMES_VEC2F_NEON
    (
        n_dst = vaddq_f32 (n_src , n_cst);
        ,
        n_rest = vadd_f32 (n_rest, n_rest_cst);
    );
}

mn_result_t mn_addc_vec3f_neon (mn_vec3f_t * dst, mn_vec3f_t * src, const mn_vec3f_t * cst, mn_uint32_t count)
{
    MN_ADDC_DstSrc_DO_COUNT_TIMES_VEC3F_NEON
    (
        n_dst1 = vaddq_f32 (n_src1 , n_cst1);
        n_dst2 = vaddq_f32 (n_src2 , n_cst2);
        n_dst3 = vaddq_f32 (n_src3 , n_cst3);
        ,
        n_rest.val[0] = vadd_f32 (n_rest.val[0], n_rest_cst.val[0]);   /* the X lane */
        n_rest.val[1] = vadd_f32 (n_rest.val[1], n_rest_cst.val[1]);   /* the Y lane */
        n_rest.val[2] = vadd_f32 (n_rest.val[2], n_rest_cst.val[2]);   /* the Z lane */
    );
}

mn_result_t mn_addc_vec4f_neon (mn_vec4f_t * dst, mn_vec4f_t * src, const mn_vec4f_t * cst, mn_uint32_t count)
{
    MN_ADDC_DstSrc_DO_COUNT_TIMES_VEC4F_NEON
    (
        n_dst = vaddq_f32 (n_src , n_cst);
    );
}

mn_result_t mn_addc_int32_neon (mn_int32_t * dst, mn_int32_t * src, const mn_int32_t cst, mn_uint32_t count)
{
    MN_ADDC_DstSrcCst_DO_COUNT_TIMES_INT32_NEON
    (
        n_dst = vaddq_s32 (n_src, n_cst);
        ,
        n_rest = vadd_s32 (n_rest, n_rest_cst);
    );
}

mn_result_t mn_addc_vec2i_neon (mn_vec2i_t * dst, mn_vec2i_t * src, const mn_vec2i_t * cst, mn_uint32_t count)
{
    MN_ADDC_DstSrc_DO_COUNT_TIMES_VEC2I_NEON
    (
        n_dst = vaddq_s32 (n_src , n_cst);
        ,
        n_rest = vadd_s32 (n_rest, n_rest_cst);
    );
}

mn_result_t mn_addc_vec3i_neon (mn_vec3i_t * dst, mn_vec3i_t * src, const mn_vec3i_t * cst, mn_uint32_t count)
{
    MN_ADDC_DstSrc_DO_COUNT_TIMES_VEC3I_NEON
    (
        n_dst1 = vaddq_s32 (n_src1 , n_cst1);
        n_dst2 = vaddq_s32 (n_src2 , n_cst2);
        n_dst3 = vaddq_s32 (n_src3 , n_cst3);
        ,
        n_rest.val[0] = vadd_s32 (n_rest.val[0], n_rest_cst.val[0]);   /* the X lane */
        n_rest.val[1] = vadd_s32 (n_rest.val[1], n_rest_cst.val[1]);   /* the Y lane */
        n_rest.val[2] = vadd_s32 (n_rest.val[2], n_rest_cst.val[2]);   /* the Z lane */
    );
}

mn_result_t mn_addc_vec4i_neon (mn_vec4i_t * dst, mn_vec4i_t * src, const mn_vec4i_t * cst, mn_uint32_t count)
{
    MN_ADDC_DstSrc_DO_COUNT_TIMES_VEC4I_NEON
    (
        n_dst = vaddq_s32 (n_src , n_cst);
    );
}
