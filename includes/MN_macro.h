#ifndef MN_MACRO_H
#define MN_MACRO_H

#include <assert.h>
#include <stddef.h>
#include <math.h>

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

/*
===========================================================================
            MN-style Macros for Absolute Value (fabs) Operations
===========================================================================
These macros provide a convenient NEON-accelerated implementation for
computing the absolute value of float/int32 arrays. They handle both
SIMD vectorized processing for performance and leftover elements
when the number of floats/int32 is not a multiple of 4.
Notes:
- These macros are intended for single-precision floating point (float32) 
  and int32 arrays.
- They follow the MN style of separating SIMD main loop and scalar leftover loop.
- Using these macros ensures consistent SIMD processing while safely handling arrays
  whose length is not divisible by 4.
===========================================================================
*/

/*
    1. MN_DstSrc_DO_COUNT_TIMES_FLOAT/INT32_NEON(loopCode1, loopCode2)
       ---------------------------------------------------------------
       - Main macro that drives the loop over 'count' elements.
       - loopCode1: Code to process a block of 4 floats/int32 using NEON.
       - loopCode2: Code to process remaining floats/int32 (1-3) when count % 4 != 0.
       - Automatically handles pointer checking (MN_ASSERT_DS) and loop division.
       - Example usage for float:
            MN_ABS_DstSrc_DO_COUNT_TIMES_FLOAT_NEON(
                MN_MAINLOOP_FLOAT_NEON_ABS,   // SIMD block
                MN_SECONDLOOP_FLOAT_ABS       // leftover elements
            );
*/

#define MN_ABS_DstSrc_DO_COUNT_TIMES_FLOAT_NEON(loopCode1, loopCode2) { \
    MN_ASSERT_DS; /* check dst/src pointers does not overlap*/ \
    float32x4_t n_src; \
    float32x4_t n_dst; \
    int dif = count % 4; /* finds remaining elements if not multiple of 4 */ \
    for (; count > dif; count -= 4) { \
        loopCode1; \
    } \
    if (dif != 0) { \
        for (unsigned int idx = 0; idx < dif; idx++) { \
            loopCode2; \
        } \
    } \
}

#define MN_ABS_DstSrc_DO_COUNT_TIMES_INT32_NEON(loopCode1, loopCode2) { \
    MN_ASSERT_DS; /* check dst/src pointers does not overlap*/ \
    int32x4_t n_src; \
    int32x4_t n_dst; \
    int dif = count % 4; /* finds remaining elements if not multiple of 4 */ \
    for (; count > dif; count -= 4) { \
        loopCode1; \
    } \
    if (dif != 0) { \
        for (unsigned int idx = 0; idx < dif; idx++) { \
            loopCode2; \
        } \
    } \
}

#define MN_ABS_DstSrc_OPERATION_VEC2F_NEON(loopCode1, loopCode2) { \
   mn_result_t res = MN_OK; \
   float32x4_t n_src; \
   float32x4_t n_dst; \
   int dif = count % 2; \
   for (; count > dif; count -= 2) { \
    loopCode1; \
   } \
   if ( 0 != dif ) { \
    loopCode2; \
   } \
   return res; \
}

#define MN_ABS_DstSrc_OPERATION_VEC2I_NEON(loopCode1, loopCode2) { \
   mn_result_t res = MN_OK; \
   int32x4_t n_src; \
   int32x4_t n_dst; \
   int dif = count % 2; \
   for (; count > dif; count -= 2) { \
    loopCode1; \
   } \
   if ( 0 != dif ) { \
    loopCode2; \
   } \
   return res; \
}

#define MN_ABS_DstSrc_DO_COUNT_TIMES_VEC2F_NEON(loopCode1, loopCode2) { \
    MN_ASSERT_DS; /* check dst/src pointers does not overlap*/ \
    MN_ABS_DstSrc_OPERATION_VEC2F_NEON(  \
        MN_ABS_DstSrc_MAINLOOP_VEC2F_NEON(loopCode1); , \
        MN_ABS_DstSrc_SECONDLOOP_VEC2F_NEON(loopCode2); \
    ); \
}
/*
    2. MN_MAINLOOP_FLOAT/INT32_NEON_ABS
       -------------------------------
       - Loads 4 values from memory
       - Computes absolute values in parallel
       - Stores the results back 
       - Advances the source and destination pointers by 4.
*/
#define MN_MAINLOOP_FLOAT_NEON_ABS { \
    n_src = vld1q_f32((float32_t*)src); /* load 4 floats */ \
    n_dst = vabsq_f32(n_src);           /* compute abs */ \
    vst1q_f32((float32_t*)dst, n_dst); /* store back */ \
    src += 4; \
    dst += 4; \
}

#define MN_MAINLOOP_INT32_NEON_ABS { \
    n_src = vld1q_s32((float32_t*)src); /* load 4 int 32-bit elements */ \
    n_dst = vabsq_s32(n_src);           /* compute abs */ \
    vst1q_s32((float32_t*)dst, n_dst); /* store back */ \
    src += 4; \
    dst += 4; \
}

#define MN_ABS_DstSrc_MAINLOOP_VEC2F_NEON(loopCode) { \
     n_src = vld1q_f32( (float32_t*)src ); /* load two vectors */ \
     src += 2; /* move to the next two vectors */ \
     loopCode; /* actual operation */ /* The main loop iterates through two 2D vectors each time */ \
     vst1q_f32 ( (float32_t*)dst , n_dst ); /* store back */ \
     dst += 2; /* move to the next 2 vectors */ \
}

#define MN_ABS_DstSrc_MAINLOOP_VEC2I_NEON(loopCode) { \
     n_src = vld1q_s32( (int32_t*)src ); /* load two vectors */ \
     src += 2; /* move to the next two vectors */ \
     loopCode; /* actual operation */ /* The main loop iterates through two 2D vectors each time */ \
     vst1q_s32 ( (int32_t*)dst , n_dst ); /* store back */ \
     dst += 2; /* move to the next 2 vectors */ \
}
/*
    3. MN_SECONDLOOP_FLOAT/INT32_ABS
       ----------------------------
       - Handles leftover scalar elements (1-3 floats/int32) when count % 4 != 0.
       - Computes absolute value using the standard C function fabsf.
       - Advances source and destination pointers by 1 float/int32 per iteration.
*/
#define MN_SECONDLOOP_FLOAT_ABS { \
    *dst++ = fabsf(*src++); \
}

#define MN_SECONDLOOP_INT32_ABS { \
    *dst++ = abs(*src++); \
}

#define MN_ABS_DstSrc_SECONDLOOP_VEC2F_NEON(loopCode) { \
     float32x2_t n_rest; \
     n_rest = vld1_f32( (float32_t*)src  ); \
     loopCode; /* exceptional cases where the count isn't a multiple of 2 */ \
     vst1_f32( (float32_t*)dst, n_rest); \
}

#define MN_ABS_DstSrc_SECONDLOOP_VEC2I_NEON(loopCode) { \
     int32x2_t n_rest; \
     n_rest = vld1_s32( (int32_t*)src  ); \
     loopCode; /* exceptional cases where the count isn't a multiple of 2 */ \
     vst1_s32( (int32_t*)dst, n_rest); \
}

#define MN_ABS_DstSrc_DO_COUNT_TIMES_VEC2I_NEON(loopCode1, loopCode2) { \
    MN_ASSERT_DS; /* check dst/src pointers does not overlap*/ \
    MN_ABS_DstSrc_OPERATION_VEC2I_NEON(  \
        MN_ABS_DstSrc_MAINLOOP_VEC2I_NEON(loopCode1); , \
        MN_ABS_DstSrc_SECONDLOOP_VEC2I_NEON(loopCode2); \
    ); \
}
// -----------------------------------------------------------------------------
// End of header guards
// -----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MN_MACRO_H
