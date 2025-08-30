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

#define MN_CHECK_Dst1SRC1SRC2(arg1, arg2, arg3) \
   if ( (void *)arg1 < (void *)arg2 ) \
    { assert ( (void *)arg1 + count <= (void *)arg2 ); } \
   else if ( (void *)arg1 > (void *)arg2 ) \
    { assert ( (void *)arg2 + count <= (void *)arg1 ); } \
   if ( (void *)arg1 < (void *)arg3 ) \
    { assert ( (void *)arg1 + count <= (void *)arg3 ); } \
   else if ( (void *)arg1 > (void *)arg3 ) \
    { assert ( (void *)arg3 + count <= (void *)arg1 ); } \
   if ( (void *)arg3 < (void *)arg2 ) \
    { assert ( (void *)arg3 + count <= (void *)arg2 ); } \
   else if ( (void *)arg3 > (void *)arg2 ) \
    { assert ( (void *)arg2 + count <= (void *)arg3 ); }

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
#define MN_ASSERT_DS1S2 MN_CHECK_Dst1SRC1SRC2

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

#define MN_ABS_DstSrc_OPERATION_VEC3F_NEON(loopCode1, loopCode2) { \
  mn_result_t res = MN_OK; \
  float32x4_t n_src1, n_src2, n_src3; \
  float32x4_t n_dst1, n_dst2, n_dst3; \
  int dif = count % 4;  \
  for (; count > dif; count -= 4) { \
   loopCode1; \
  } \
  if ( 0 != dif ) { \
    unsigned int idx; \
    for ( idx = 0 ; idx < dif; idx++ ) { \
      loopCode2; \
    } \
  } \
  return res; \
 }

#define MN_ABS_DstSrc_OPERATION_VEC3I_NEON(loopCode1, loopCode2) { \
  mn_result_t res = MN_OK; \
  int32x4_t n_src1, n_src2, n_src3; \
  int32x4_t n_dst1, n_dst2, n_dst3; \
  int dif = count % 4;  \
  for (; count > dif; count -= 4) { \
   loopCode1; \
  } \
  if ( 0 != dif ) { \
    unsigned int idx; \
    for ( idx = 0 ; idx < dif; idx++ ) { \
      loopCode2; \
    } \
  } \
  return res; \
 }

#define MN_ABS_DstSrc_OPERATION_VEC4F_NEON(loopCode) { \
   mn_result_t res = MN_OK; \
   float32x4_t n_src; \
   float32x4_t n_dst; \
   for (; count != 0; count --) { \
     loopCode; \
    } \
   return res; \
  }

#define MN_ABS_DstSrc_OPERATION_VEC4I_NEON(loopCode) { \
   mn_result_t res = MN_OK; \
   int32x4_t n_src; \
   int32x4_t n_dst; \
   for (; count != 0; count --) { \
     loopCode; \
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

#define MN_ABS_DstSrc_DO_COUNT_TIMES_VEC2I_NEON(loopCode1, loopCode2) { \
    MN_ASSERT_DS; /* check dst/src pointers does not overlap*/ \
    MN_ABS_DstSrc_OPERATION_VEC2I_NEON(  \
        MN_ABS_DstSrc_MAINLOOP_VEC2I_NEON(loopCode1); , \
        MN_ABS_DstSrc_SECONDLOOP_VEC2I_NEON(loopCode2); \
    ); \
}

#define MN_ABS_DstSrc_DO_COUNT_TIMES_VEC3F_NEON(loopCode1, loopCode2) { \
    MN_ASSERT_DS; /* check dst/src pointers does not overlap*/ \
    MN_ABS_DstSrc_OPERATION_VEC3F_NEON(  \
        MN_ABS_DstSrc_MAINLOOP_VEC3F_NEON(loopCode1); , \
        MN_ABS_DstSrc_SECONDLOOP_VEC3F_NEON(loopCode2); \
    ); \
}

#define MN_ABS_DstSrc_DO_COUNT_TIMES_VEC3I_NEON(loopCode1, loopCode2) { \
    MN_ASSERT_DS; /* check dst/src pointers does not overlap*/ \
    MN_ABS_DstSrc_OPERATION_VEC3I_NEON(  \
        MN_ABS_DstSrc_MAINLOOP_VEC3I_NEON(loopCode1); , \
        MN_ABS_DstSrc_SECONDLOOP_VEC3I_NEON(loopCode2); \
    ); \
}

#define MN_ABS_DstSrc_DO_COUNT_TIMES_VEC4F_NEON(loopCode) { \
    ; \
        MN_ABS_DstSrc_OPERATION_VEC4F_NEON( \
        MN_ABS_DstSrc_MAINLOOP_VEC4F_NEON(loopCode); \
    ); \
}

#define MN_ABS_DstSrc_DO_COUNT_TIMES_VEC4I_NEON(loopCode) { \
    ; \
        MN_ABS_DstSrc_OPERATION_VEC4I_NEON( \
        MN_ABS_DstSrc_MAINLOOP_VEC4I_NEON(loopCode); \
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
    n_src = vld1q_s32((int32_t*)src); /* load 4 int 32-bit elements */ \
    n_dst = vabsq_s32(n_src);           /* compute abs */ \
    vst1q_s32((int32_t*)dst, n_dst); /* store back */ \
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
    - Use (char*) for raw byte arithmetic (portable).
    - Use the original type pointer (float*, int*, etc.) for stepping by elements.
    - Never do arithmetic on (void*) → non-standard, MSVC rejects it.
*/

#define MN_ABS_DstSrc_MAINLOOP_VEC3F_NEON(loopCode) {                                  \
    n_src1 = vld1q_f32((float32_t*)src);                                               \
    src = (mn_float32_t*)((char*)src + 4 * sizeof(mn_float32_t));                      \
    n_src2 = vld1q_f32((float32_t*)src);                                               \
    src = (mn_float32_t*)((char*)src + 4 * sizeof(mn_float32_t));                      \
    n_src3 = vld1q_f32((float32_t*)src);                                               \
    src = (mn_float32_t*)((char*)src + 4 * sizeof(mn_float32_t));                      \
    loopCode;                                                                          \
    vst1q_f32((float32_t*)dst, n_dst1);                                                \
    dst = (mn_float32_t*)((char*)dst + 4 * sizeof(mn_float32_t));                      \
    vst1q_f32((float32_t*)dst, n_dst2);                                                \
    dst = (mn_float32_t*)((char*)dst + 4 * sizeof(mn_float32_t));                      \
    vst1q_f32((float32_t*)dst, n_dst3);                                                \
    dst = (mn_float32_t*)((char*)dst + 4 * sizeof(mn_float32_t));                      \
}


#define MN_ABS_DstSrc_MAINLOOP_VEC3I_NEON(loopCode) {                                  \
    n_src1 = vld1q_s32((int32_t*)src);                                                 \
    src = (mn_int32_t*)((char*)src + 4 * sizeof(mn_int32_t));                          \
    n_src2 = vld1q_s32((int32_t*)src);                                                 \
    src = (mn_int32_t*)((char*)src + 4 * sizeof(mn_int32_t));                          \
    n_src3 = vld1q_s32((int32_t*)src);                                                 \
    src = (mn_int32_t*)((char*)src + 4 * sizeof(mn_int32_t));                          \
    loopCode;                                                                          \
    vst1q_s32((int32_t*)dst, n_dst1);                                                  \
    dst = (mn_int32_t*)((char*)dst + 4 * sizeof(mn_int32_t));                          \
    vst1q_s32((int32_t*)dst, n_dst2);                                                  \
    dst = (mn_int32_t*)((char*)dst + 4 * sizeof(mn_int32_t));                          \
    vst1q_s32((int32_t*)dst, n_dst3);                                                  \
    dst = (mn_int32_t*)((char*)dst + 4 * sizeof(mn_int32_t));                          \
}

#define MN_ABS_DstSrc_MAINLOOP_VEC4F_NEON(loopCode) { \
     n_src = vld1q_f32( (float32_t*)src ); \
     src ++; \
     loopCode; \
     vst1q_f32 ( (float32_t*)dst , n_dst );  /* The main loop iterates through one 4D vector each time */ \
     dst ++; \
}

#define MN_ABS_DstSrc_MAINLOOP_VEC4I_NEON(loopCode) { \
     n_src = vld1q_s32( (int32_t*)src ); \
     src ++; \
     loopCode; \
     vst1q_s32 ( (int32_t*)dst , n_dst );  /* The main loop iterates through one 4D vector each time */ \
     dst ++; \
}
/*
    3. MN_SECONDLOOP_FLOAT/INT32_ABS
       ----------------------------
       - Handles leftover scalar elements (1-3 floats/int32 or vector) when count % 4 != 0.
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


#define MN_ABS_DstSrc_SECONDLOOP_VEC3F_NEON(loopCode) { \
     float32x2x3_t n_rest; \
     n_rest = vld3_lane_f32 ( (float32_t*)src, n_rest, 0); \
     loopCode; /* exceptional cases where the count isn't a multiple of 3 */ \
     vst3_lane_f32( (float32_t*)dst, n_rest, 0); \
     src++; \
     dst++; \
}

#define MN_ABS_DstSrc_SECONDLOOP_VEC3I_NEON(loopCode) { \
     int32x2x3_t n_rest; \
     n_rest = vld3_lane_s32 ( (int32_t*)src, n_rest, 0); \
     loopCode; /* exceptional cases where the count isn't a multiple of 3 */ \
     vst3_lane_s32( (int32_t*)dst, n_rest, 0); \
     src++; \
     dst++; \
}

// -----------------------------------------------------------------------------
// Addition Operation Macros
// -----------------------------------------------------------------------------

#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_FLOAT_NEON(loopCode1, loopCode2) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check dst/src1/src2 pointers don't overlap */ \
    float32x4_t n_src1, n_src2; \
    float32x4_t n_dst; \
    float32x2_t n_rest1, n_rest2, n_rest; \
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

#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_INT32_NEON(loopCode1, loopCode2) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check dst/src1/src2 pointers don't overlap */ \
    int32x4_t n_src1, n_src2; \
    int32x4_t n_dst; \
    int32x2_t n_rest1, n_rest2, n_rest; \
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

// Vector operation macros (similar to the ABS pattern)
#define MN_ADD_DstSrc1Src2_OPERATION_VEC2F_NEON(loopCode1, loopCode2) { \
   mn_result_t res = MN_OK; \
   float32x4_t n_src1, n_src2; \
   float32x4_t n_dst; \
   float32x2_t n_rest1, n_rest2, n_rest; \
   int dif = count % 2; \
   for (; count > dif; count -= 2) { \
    loopCode1; \
   } \
   if ( 0 != dif ) { \
    loopCode2; \
   } \
   return res; \
}

#define MN_ADD_DstSrc1Src2_OPERATION_VEC2I_NEON(loopCode1, loopCode2) { \
   mn_result_t res = MN_OK; \
   int32x4_t n_src1, n_src2; \
   int32x4_t n_dst; \
   int32x2_t n_rest1, n_rest2, n_rest; \
   int dif = count % 2; \
   for (; count > dif; count -= 2) { \
    loopCode1; \
   } \
   if ( 0 != dif ) { \
    loopCode2; \
   } \
   return res; \
}

#define MN_ADD_DstSrc1Src2_OPERATION_VEC3F_NEON(loopCode1, loopCode2) { \
  mn_result_t res = MN_OK; \
  float32x4_t n_src11, n_src12, n_src13; \
  float32x4_t n_src21, n_src22, n_src23; \
  float32x4_t n_dst1, n_dst2, n_dst3; \
  int dif = count % 4;  \
  for (; count > dif; count -= 4) { \
   loopCode1; \
  } \
  if ( 0 != dif ) { \
    unsigned int idx; \
    for ( idx = 0 ; idx < dif; idx++ ) { \
      loopCode2; \
    } \
  } \
  return res; \
}

#define MN_ADD_DstSrc1Src2_OPERATION_VEC3I_NEON(loopCode1, loopCode2) { \
  mn_result_t res = MN_OK; \
  int32x4_t n_src11, n_src12, n_src13; \
  int32x4_t n_src21, n_src22, n_src23; \
  int32x4_t n_dst1, n_dst2, n_dst3; \
  int dif = count % 4;  \
  for (; count > dif; count -= 4) { \
   loopCode1; \
  } \
  if ( 0 != dif ) { \
    unsigned int idx; \
    for ( idx = 0 ; idx < dif; idx++ ) { \
      loopCode2; \
    } \
  } \
  return res; \
}

#define MN_ADD_DstSrc1Src2_OPERATION_VEC4F_NEON(loopCode) { \
   mn_result_t res = MN_OK; \
   float32x4_t n_src1, n_src2; \
   float32x4_t n_dst; \
   for (; count != 0; count --) { \
     loopCode; \
    } \
   return res; \
}

#define MN_ADD_DstSrc1Src2_OPERATION_VEC4I_NEON(loopCode) { \
   mn_result_t res = MN_OK; \
   int32x4_t n_src1, n_src2; \
   int32x4_t n_dst; \
   for (; count != 0; count --) { \
     loopCode; \
    } \
   return res; \
}

// MAINLOOP macros for addition (load -> add -> store -> advance pointers)
#define MN_MAINLOOP_FLOAT_NEON_ADD { \
    n_src1 = vld1q_f32((float32_t*)src1); /* load 4 floats from src1 */ \
    n_src2 = vld1q_f32((float32_t*)src2); /* load 4 floats from src2 */ \
    n_dst = vaddq_f32(n_src1, n_src2);    /* compute addition */ \
    vst1q_f32((float32_t*)dst, n_dst);    /* store back */ \
    src1 += 4; \
    src2 += 4; \
    dst += 4; \
}

#define MN_MAINLOOP_INT32_NEON_ADD { \
    n_src1 = vld1q_s32((int32_t*)src1); /* load 4 int32 from src1 */ \
    n_src2 = vld1q_s32((int32_t*)src2); /* load 4 int32 from src2 */ \
    n_dst = vaddq_s32(n_src1, n_src2);  /* compute addition */ \
    vst1q_s32((int32_t*)dst, n_dst);    /* store back */ \
    src1 += 4; \
    src2 += 4; \
    dst += 4; \
}

#define MN_ADD_DstSrc1Src2_MAINLOOP_VEC2F_NEON(loopCode) { \
     n_src1 = vld1q_f32( (float32_t*)src1 ); /* load two vec2f (8 floats) */ \
     n_src2 = vld1q_f32( (float32_t*)src2 ); /* load two vec2f (8 floats) */ \
     src1 += 2; /* move to the next two vectors */ \
     src2 += 2; /* move to the next two vectors */ \
     loopCode; /* actual operation */ \
     vst1q_f32 ( (float32_t*)dst , n_dst ); /* store back */ \
     dst += 2; /* move to the next 2 vectors */ \
}

#define MN_ADD_DstSrc1Src2_MAINLOOP_VEC2I_NEON(loopCode) { \
     n_src1 = vld1q_s32( (int32_t*)src1 ); /* load two vec2i */ \
     n_src2 = vld1q_s32( (int32_t*)src2 ); /* load two vec2i */ \
     src1 += 2; /* move to the next two vectors */ \
     src2 += 2; /* move to the next two vectors */ \
     loopCode; /* actual operation */ \
     vst1q_s32 ( (int32_t*)dst , n_dst ); /* store back */ \
     dst += 2; /* move to the next 2 vectors */ \
}

#define MN_ADD_DstSrc1Src2_MAINLOOP_VEC3F_NEON(loopCode) {                             \
    n_src11 = vld1q_f32((float32_t*)src1);                                             \
    src1 = (mn_vec3f_t*)((char*)src1 + 4 * sizeof(mn_float32_t));                      \
    n_src12 = vld1q_f32((float32_t*)src1);                                             \
    src1 = (mn_vec3f_t*)((char*)src1 + 4 * sizeof(mn_float32_t));                      \
    n_src13 = vld1q_f32((float32_t*)src1);                                             \
    src1 = (mn_vec3f_t*)((char*)src1 + 4 * sizeof(mn_float32_t));                      \
    n_src21 = vld1q_f32((float32_t*)src2);                                             \
    src2 = (mn_vec3f_t*)((char*)src2 + 4 * sizeof(mn_float32_t));                      \
    n_src22 = vld1q_f32((float32_t*)src2);                                             \
    src2 = (mn_vec3f_t*)((char*)src2 + 4 * sizeof(mn_float32_t));                      \
    n_src23 = vld1q_f32((float32_t*)src2);                                             \
    src2 = (mn_vec3f_t*)((char*)src2 + 4 * sizeof(mn_float32_t));                      \
    loopCode;                                                                          \
    vst1q_f32((float32_t*)dst, n_dst1);                                                \
    dst = (mn_vec3f_t*)((char*)dst + 4 * sizeof(mn_float32_t));                        \
    vst1q_f32((float32_t*)dst, n_dst2);                                                \
    dst = (mn_vec3f_t*)((char*)dst + 4 * sizeof(mn_float32_t));                        \
    vst1q_f32((float32_t*)dst, n_dst3);                                                \
    dst = (mn_vec3f_t*)((char*)dst + 4 * sizeof(mn_float32_t));                        \
}

#define MN_ADD_DstSrc1Src2_MAINLOOP_VEC3I_NEON(loopCode) {                             \
    n_src11 = vld1q_s32((int32_t*)src1);                                               \
    src1 = (mn_vec3i_t*)((char*)src1 + 4 * sizeof(mn_int32_t));                        \
    n_src12 = vld1q_s32((int32_t*)src1);                                               \
    src1 = (mn_vec3i_t*)((char*)src1 + 4 * sizeof(mn_int32_t));                        \
    n_src13 = vld1q_s32((int32_t*)src1);                                               \
    src1 = (mn_vec3i_t*)((char*)src1 + 4 * sizeof(mn_int32_t));                        \
    n_src21 = vld1q_s32((int32_t*)src2);                                               \
    src2 = (mn_vec3i_t*)((char*)src2 + 4 * sizeof(mn_int32_t));                        \
    n_src22 = vld1q_s32((int32_t*)src2);                                               \
    src2 = (mn_vec3i_t*)((char*)src2 + 4 * sizeof(mn_int32_t));                        \
    n_src23 = vld1q_s32((int32_t*)src2);                                               \
    src2 = (mn_vec3i_t*)((char*)src2 + 4 * sizeof(mn_int32_t));                        \
    loopCode;                                                                          \
    vst1q_s32((int32_t*)dst, n_dst1);                                                  \
    dst = (mn_vec3i_t*)((char*)dst + 4 * sizeof(mn_int32_t));                          \
    vst1q_s32((int32_t*)dst, n_dst2);                                                  \
    dst = (mn_vec3i_t*)((char*)dst + 4 * sizeof(mn_int32_t));                          \
    vst1q_s32((int32_t*)dst, n_dst3);                                                  \
    dst = (mn_vec3i_t*)((char*)dst + 4 * sizeof(mn_int32_t));                          \
}

#define MN_ADD_DstSrc1Src2_MAINLOOP_VEC4F_NEON(loopCode) { \
     n_src1 = vld1q_f32( (float32_t*)src1 ); \
     n_src2 = vld1q_f32( (float32_t*)src2 ); \
     src1 ++; \
     src2 ++; \
     loopCode; \
     vst1q_f32 ( (float32_t*)dst , n_dst ); \
     dst ++; \
}

#define MN_ADD_DstSrc1Src2_MAINLOOP_VEC4I_NEON(loopCode) { \
     n_src1 = vld1q_s32( (int32_t*)src1 ); \
     n_src2 = vld1q_s32( (int32_t*)src2 ); \
     src1 ++; \
     src2 ++; \
     loopCode; \
     vst1q_s32 ( (int32_t*)dst , n_dst ); \
     dst ++; \
}

// SECONDLOOP macros for addition (handles leftover elements)
#define MN_SECONDLOOP_FLOAT_ADD { \
    *dst++ = *src1++ + *src2++; \
}

#define MN_SECONDLOOP_INT32_ADD { \
    *dst++ = *src1++ + *src2++; \
}

#define MN_ADD_DstSrc1Src2_SECONDLOOP_VEC2F_NEON(loopCode) { \
     n_rest1 = vld1_f32( (float32_t*)src1 ); \
     n_rest2 = vld1_f32( (float32_t*)src2 ); \
     loopCode; /* exceptional cases where the count isn't a multiple of 2 */ \
     vst1_f32( (float32_t*)dst, n_rest); \
}

#define MN_ADD_DstSrc1Src2_SECONDLOOP_VEC2I_NEON(loopCode) { \
     n_rest1 = vld1_s32( (int32_t*)src1 ); \
     n_rest2 = vld1_s32( (int32_t*)src2 ); \
     loopCode; /* exceptional cases where the count isn't a multiple of 2 */ \
     vst1_s32( (int32_t*)dst, n_rest); \
}

#define MN_ADD_DstSrc1Src2_SECONDLOOP_VEC3F_NEON(loopCode) { \
     float32x2x3_t n_rest1, n_rest2; \
     n_rest1 = vld3_f32( (float32_t*)src1 ); \
     n_rest2 = vld3_f32( (float32_t*)src2 ); \
     loopCode; /* exceptional cases where the count isn't a multiple of 4 */ \
     vst3_f32( (float32_t*)dst, n_rest1); /* store result */ \
     src1++; \
     src2++; \
     dst++; \
}

#define MN_ADD_DstSrc1Src2_SECONDLOOP_VEC3I_NEON(loopCode) { \
     int32x2x3_t n_rest1, n_rest2; \
     n_rest1 = vld3_s32( (int32_t*)src1 ); \
     n_rest2 = vld3_s32( (int32_t*)src2 ); \
     loopCode; /* exceptional cases where the count isn't a multiple of 4 */ \
     vst3_s32( (int32_t*)dst, n_rest1); /* store result */ \
     src1++; \
     src2++; \
     dst++; \
}

// High-level wrapper macros (following the DO_COUNT_TIMES pattern)
#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC2F_NEON(loopCode1, loopCode2) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check pointers don't overlap */ \
    MN_ADD_DstSrc1Src2_OPERATION_VEC2F_NEON(  \
        MN_ADD_DstSrc1Src2_MAINLOOP_VEC2F_NEON(loopCode1); , \
        MN_ADD_DstSrc1Src2_SECONDLOOP_VEC2F_NEON(loopCode2); \
    ); \
}

#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC2I_NEON(loopCode1, loopCode2) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check pointers don't overlap */ \
    MN_ADD_DstSrc1Src2_OPERATION_VEC2I_NEON(  \
        MN_ADD_DstSrc1Src2_MAINLOOP_VEC2I_NEON(loopCode1); , \
        MN_ADD_DstSrc1Src2_SECONDLOOP_VEC2I_NEON(loopCode2); \
    ); \
}

#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC3F_NEON(loopCode1, loopCode2) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check pointers don't overlap */ \
    MN_ADD_DstSrc1Src2_OPERATION_VEC3F_NEON(  \
        MN_ADD_DstSrc1Src2_MAINLOOP_VEC3F_NEON(loopCode1); , \
        MN_ADD_DstSrc1Src2_SECONDLOOP_VEC3F_NEON(loopCode2); \
    ); \
}

#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC3I_NEON(loopCode1, loopCode2) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check pointers don't overlap */ \
    MN_ADD_DstSrc1Src2_OPERATION_VEC3I_NEON(  \
        MN_ADD_DstSrc1Src2_MAINLOOP_VEC3I_NEON(loopCode1); , \
        MN_ADD_DstSrc1Src2_SECONDLOOP_VEC3I_NEON(loopCode2); \
    ); \
}

#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC4F_NEON(loopCode) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check pointers don't overlap */ \
        MN_ADD_DstSrc1Src2_OPERATION_VEC4F_NEON( \
        MN_ADD_DstSrc1Src2_MAINLOOP_VEC4F_NEON(loopCode); \
    ); \
}

#define MN_ADD_DstSrc1Src2_DO_COUNT_TIMES_VEC4I_NEON(loopCode) { \
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2); /* check pointers don't overlap */ \
        MN_ADD_DstSrc1Src2_OPERATION_VEC4I_NEON( \
        MN_ADD_DstSrc1Src2_MAINLOOP_VEC4I_NEON(loopCode); \
    ); \
}


// -----------------------------------------------------------------------------
// End of header guards
// -----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MN_MACRO_H
