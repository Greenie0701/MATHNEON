#ifndef MN_MACRO_H
#define MN_MACRO_H

#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Macros for pointer overlap safety checks
// -----------------------------------------------------------------------------
//
// These macros check whether two buffers (dst and src) overlap in memory.
// This prevents undefined behavior when functions read from src and write to dst.
// They assume that `count` is the number of elements (not bytes).
// -----------------------------------------------------------------------------

/**
 * @brief Ensures that dst and src do not overlap for `count` elements.
 *
 * Expands into a runtime assertion:
 *  - If dst < src, then the dst range must end before src begins.
 *  - If dst > src, then the src range must end before dst begins.
 *
 * Both dst and src are cast to (const char*) for byte-wise pointer arithmetic.
 * The overlap check accounts for the size of the pointed-to type.
 */
#define MN_CHECK_DstSRC \
    do { \
        const char* dst_bytes = (const char*)(dst); \
        const char* src_bytes = (const char*)(src); \
        if (dst_bytes < src_bytes) { \
            assert(dst_bytes + count * sizeof(*dst) <= src_bytes); \
        } else if (dst_bytes > src_bytes) { \
            assert(src_bytes + count * sizeof(*src) <= dst_bytes); \
        } \
    } while (0)

/**
 * @brief Shorthand for calling MN_CHECK_DstSRC.
 *
 * Used inside functions like:
 * @code
 * mn_result_t mn_abs_int_c(mn_int32_t* dst, mn_int32_t* src, mn_uint32_t count) {
 *     MN_ASSERT_DS;
 *     ...
 * }
 * @endcode
 */
#define MN_ASSERT_DS MN_CHECK_DstSRC

// -----------------------------------------------------------------------------
// End of header guards
// -----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MN_MACRO_H
