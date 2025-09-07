#ifndef MN_MATH_H
#define MN_MATH_H
#include "MN_dtype.h"
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * ================================
 * MN ABSOLUTE OPERATOR USING C & NEON
 * ================================
 */

/**
 * @brief Computes absolute value of float array using C.
 */
mn_result_t mn_abs_float_c(mn_float32_t *dst, mn_float32_t *src, size_t count);
mn_result_t mn_abs_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src, size_t count);
mn_result_t mn_abs_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src, size_t count);
mn_result_t mn_abs_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src, size_t count);

/**
 * @brief Computes absolute value of float array using NEON.
 */
mn_result_t mn_abs_float_neon(mn_float32_t *dst, mn_float32_t *src, size_t count);
mn_result_t mn_abs_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src, size_t count);
mn_result_t mn_abs_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src, size_t count);
mn_result_t mn_abs_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src, size_t count);

/**
 * @brief Computes absolute value of int array using C.
 */
mn_result_t mn_abs_int32_c(mn_int32_t *dst, mn_int32_t *src, size_t count);
mn_result_t mn_abs_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src, size_t count);
mn_result_t mn_abs_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src, size_t count);
mn_result_t mn_abs_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src, size_t count);

/**
 * @brief Computes absolute value of int array using NEON.
 */
mn_result_t mn_abs_int32_neon(mn_int32_t *dst, mn_int32_t *src, size_t count);
mn_result_t mn_abs_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src, size_t count);
mn_result_t mn_abs_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src, size_t count);
mn_result_t mn_abs_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src, size_t count);

/**
 * ================================
 * MN ADD OPERATOR USING C
 * ================================
 */

/**
 * @brief Adds two int arrays.
 */
mn_result_t mn_add_int32_c(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

/**
 * @brief Adds two float arrays.
 */
mn_result_t mn_add_float_c(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * ================================
 * MN ADD OPERATOR USING NEON
 * ================================
 */

/**
 * @brief Adds two float arrays using NEON.
 */
mn_result_t mn_add_float_neon(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * @brief Adds two int arrays using NEON.
 */
mn_result_t mn_add_int32_neon(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_add_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

/**
 * ================================
 * MN SUB OPERATOR USING C
 * ================================
 */

/**
 * @brief subs two int arrays.
 */
mn_result_t mn_sub_int32_c(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

/**
 * @brief subs two float arrays.
 */
mn_result_t mn_sub_float_c(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * ================================
 * MN SUB OPERATOR USING NEON
 * ================================
 */

/**
 * @brief subs two float arrays using NEON.
 */
mn_result_t mn_sub_float_neon(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * @brief subs two int arrays using NEON.
 */
mn_result_t mn_sub_int32_neon(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_sub_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

/**
 * ================================
 * MN ADD-CONSTANT (ADDC) USING C
 * ================================
 */

mn_result_t mn_addc_float_c(mn_float32_t *dst, mn_float32_t *src, mn_float32_t cst, size_t count);
mn_result_t mn_addc_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src, const mn_vec2f_t *cst, size_t count);
mn_result_t mn_addc_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src, const mn_vec3f_t *cst, size_t count);
mn_result_t mn_addc_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src, const mn_vec4f_t *cst, size_t count);

mn_result_t mn_addc_int32_c(mn_int32_t *dst, mn_int32_t *src, mn_int32_t cst, size_t count);
mn_result_t mn_addc_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src, const mn_vec2i_t *cst, size_t count);
mn_result_t mn_addc_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src, const mn_vec3i_t *cst, size_t count);
mn_result_t mn_addc_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src, const mn_vec4i_t *cst, size_t count);

/**
 * ================================
 * MN ADD-CONSTANT (ADDC) USING NEON
 * ================================
 */

mn_result_t mn_addc_float_neon(mn_float32_t *dst, mn_float32_t *src, mn_float32_t cst, size_t count);
mn_result_t mn_addc_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src, const mn_vec2f_t *cst, size_t count);
mn_result_t mn_addc_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src, const mn_vec3f_t *cst, size_t count);
mn_result_t mn_addc_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src, const mn_vec4f_t *cst, size_t count);

mn_result_t mn_addc_int32_neon(mn_int32_t *dst, mn_int32_t *src, mn_int32_t cst, size_t count);
mn_result_t mn_addc_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src, const mn_vec2i_t *cst, size_t count);
mn_result_t mn_addc_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src, const mn_vec3i_t *cst, size_t count);
mn_result_t mn_addc_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src, const mn_vec4i_t *cst, size_t count);


/**
 * ================================
 * MN SUB CONSTANT (SUBC) USING C
 * ================================
 */

mn_result_t mn_subc_float_c(mn_float32_t *dst, mn_float32_t *src, mn_float32_t cst, size_t count);
mn_result_t mn_subc_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src, const mn_vec2f_t *cst, size_t count);
mn_result_t mn_subc_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src, const mn_vec3f_t *cst, size_t count);
mn_result_t mn_subc_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src, const mn_vec4f_t *cst, size_t count);

mn_result_t mn_subc_int32_c(mn_int32_t *dst, mn_int32_t *src, mn_int32_t cst, size_t count);
mn_result_t mn_subc_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src, const mn_vec2i_t *cst, size_t count);
mn_result_t mn_subc_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src, const mn_vec3i_t *cst, size_t count);
mn_result_t mn_subc_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src, const mn_vec4i_t *cst, size_t count);

/**
 * =================================
 * MN SUB CONSTANT (SUBC) USING NEON
 * =================================
 */

mn_result_t mn_subc_float_neon(mn_float32_t *dst, mn_float32_t *src, mn_float32_t cst, size_t count);
mn_result_t mn_subc_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src, const mn_vec2f_t *cst, size_t count);
mn_result_t mn_subc_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src, const mn_vec3f_t *cst, size_t count);
mn_result_t mn_subc_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src, const mn_vec4f_t *cst, size_t count);

mn_result_t mn_subc_int32_neon(mn_int32_t *dst, mn_int32_t *src, mn_int32_t cst, size_t count);
mn_result_t mn_subc_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src, const mn_vec2i_t *cst, size_t count);
mn_result_t mn_subc_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src, const mn_vec3i_t *cst, size_t count);
mn_result_t mn_subc_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src, const mn_vec4i_t *cst, size_t count);

/**
 * ================================
 * MN MUL OPERATOR USING C
 * ================================
 */

/**
 * @brief multiply two int arrays.
 */
mn_result_t mn_mul_int32_c(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

/**
 * @brief multiply two float arrays.
 */
mn_result_t mn_mul_float_c(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * ================================
 * MN MUL OPERATOR USING NEON
 * ================================
 */

/**
 * @brief multiply two float arrays using NEON.
 */
mn_result_t mn_mul_float_neon(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * @brief multiply two int arrays using NEON.
 */
mn_result_t mn_mul_int32_neon(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_mul_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

/**
 * ===================================
 * MN MULTIPLY CONSTANT (MULC) USING C
 * ===================================
 */

mn_result_t mn_mulc_float_c(mn_float32_t *dst, mn_float32_t *src, mn_float32_t cst, size_t count);
mn_result_t mn_mulc_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src, const mn_vec2f_t *cst, size_t count);
mn_result_t mn_mulc_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src, const mn_vec3f_t *cst, size_t count);
mn_result_t mn_mulc_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src, const mn_vec4f_t *cst, size_t count);

mn_result_t mn_mulc_int32_c(mn_int32_t *dst, mn_int32_t *src, mn_int32_t cst, size_t count);
mn_result_t mn_mulc_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src, const mn_vec2i_t *cst, size_t count);
mn_result_t mn_mulc_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src, const mn_vec3i_t *cst, size_t count);
mn_result_t mn_mulc_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src, const mn_vec4i_t *cst, size_t count);

/**
 * ======================================
 * MN MULTIPLY CONSTANT (MULC) USING NEON
 * ======================================
 */

mn_result_t mn_mulc_float_neon(mn_float32_t *dst, mn_float32_t *src, mn_float32_t cst, size_t count);
mn_result_t mn_mulc_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src, const mn_vec2f_t *cst, size_t count);
mn_result_t mn_mulc_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src, const mn_vec3f_t *cst, size_t count);
mn_result_t mn_mulc_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src, const mn_vec4f_t *cst, size_t count);

mn_result_t mn_mulc_int32_neon(mn_int32_t *dst, mn_int32_t *src, mn_int32_t cst, size_t count);
mn_result_t mn_mulc_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src, const mn_vec2i_t *cst, size_t count);
mn_result_t mn_mulc_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src, const mn_vec3i_t *cst, size_t count);
mn_result_t mn_mulc_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src, const mn_vec4i_t *cst, size_t count);


/**
 * ================================
 * MN Division OPERATOR USING C
 * ================================
 */

/**
 * @brief division two int arrays.
 */
mn_result_t mn_div_int32_c(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec2i_c(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec3i_c(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec4i_c(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

/**
 * @brief division two float arrays.
 */
mn_result_t mn_div_float_c(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec2f_c(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec3f_c(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec4f_c(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * ================================
 * MN Division OPERATOR USING NEON
 * ================================
 */

/**
 * @brief division two float arrays using NEON.
 */
mn_result_t mn_div_float_neon(mn_float32_t *dst, mn_float32_t *src1, mn_float32_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec2f_neon(mn_vec2f_t *dst, mn_vec2f_t *src1, mn_vec2f_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec3f_neon(mn_vec3f_t *dst, mn_vec3f_t *src1, mn_vec3f_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec4f_neon(mn_vec4f_t *dst, mn_vec4f_t *src1, mn_vec4f_t *src2, mn_uint32_t count);

/**
 * @brief division two int arrays using NEON.
 */
mn_result_t mn_div_int32_neon(mn_int32_t *dst, mn_int32_t *src1, mn_int32_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec2i_neon(mn_vec2i_t *dst, mn_vec2i_t *src1, mn_vec2i_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec3i_neon(mn_vec3i_t *dst, mn_vec3i_t *src1, mn_vec3i_t *src2, mn_uint32_t count);
mn_result_t mn_div_vec4i_neon(mn_vec4i_t *dst, mn_vec4i_t *src1, mn_vec4i_t *src2, mn_uint32_t count);

#ifdef __cplusplus
}
#endif
#endif // MN_MATH_H
