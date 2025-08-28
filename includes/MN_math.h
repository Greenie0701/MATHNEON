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

#ifdef __cplusplus
}
#endif
#endif // MN_MATH_H
