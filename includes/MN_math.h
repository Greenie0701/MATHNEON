#ifndef MN_MATH_H
#define MN_MATH_H

#include "MN_dtype.h"
#include <stddef.h>   // for size_t

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Computes absolute value of float array using NEON.
 *
 * @param dst  Destination buffer (must not overlap with src).
 * @param src  Source buffer.
 * @param count Number of elements.
 */
mn_result_t mn_abs_float_neon(float *dst, const float *src, size_t count);

/**
 * @brief Computes absolute value of int array using NEON.
 *
 * @param dst  Destination buffer (must not overlap with src).
 * @param src  Source buffer.
 * @param count Number of elements.
 */
mn_result_t mn_abs_int32_neon(int *dst, const int *src, size_t count);

#ifdef __cplusplus
}
#endif

#endif // MN_MATH_H
