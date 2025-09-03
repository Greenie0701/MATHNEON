#ifndef MN_MACRO_H
#define MN_MACRO_H

#include "MN_factor.h"

#ifdef __cplusplus
extern "C" {
#endif

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
