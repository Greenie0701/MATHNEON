#include "MN_dtype.h"
#include "MN_macro.h"
#include "MN_math.h"
#include <assert.h>
#include <math.h>

/*
Function Input:
    dst   - Destination that store result
    src   - Source that stores user input
    count - Count is an integer that stores number of elements
    fabsf - Calculates the absolute value of the floating-point argument. Refer to MSVC Docs(https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fabsf-fabsff-fabsfl?view=msvc-170)
    abs   - Calculates the absolute value of the integer argument. Refer to MSVC Docs(https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/abs-labs-llabs-abs64?view=msvc-170)
 */


mn_result_t mn_abs_int32_c (mn_int32_t * dst, mn_int32_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[itr] = abs (src[itr]);
    }
    return MN_SUCCESS;
}

mn_result_t mn_abs_vec2i_c (mn_vec2i_t * dst, mn_vec2i_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = abs (src[ itr ].x);
        dst[ itr ].y = abs (src[ itr ].y);
    }
    return MN_SUCCESS;
}

mn_result_t mn_abs_vec3i_c (mn_vec3i_t * dst, mn_vec3i_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = abs (src[ itr ].x);
        dst[ itr ].y = abs (src[ itr ].y);
        dst[ itr ].z = abs (src[ itr ].z);
    }
    return MN_SUCCESS;
}

mn_result_t mn_abs_vec4i_c (mn_vec4i_t * dst, mn_vec4i_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = abs (src[ itr ].x);
        dst[ itr ].y = abs (src[ itr ].y);
        dst[ itr ].z = abs (src[ itr ].z);
        dst[ itr ].w = abs (src[ itr ].w);
    }
    return MN_SUCCESS;
}

mn_result_t mn_abs_float_c (mn_float32_t * dst, mn_float32_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[itr] = fabsf (src[itr]);
    }
    return MN_SUCCESS;
}

mn_result_t mn_abs_vec2f_c (mn_vec2f_t * dst, mn_vec2f_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabsf (src[ itr ].x);
        dst[ itr ].y = fabsf (src[ itr ].y);
    }
    return MN_SUCCESS;
}

mn_result_t mn_abs_vec3f_c (mn_vec3f_t * dst, mn_vec3f_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabsf (src[ itr ].x);
        dst[ itr ].y = fabsf (src[ itr ].y);
        dst[ itr ].z = fabsf (src[ itr ].z);
    }
    return MN_SUCCESS;
}

mn_result_t mn_abs_vec4f_c (mn_vec4f_t * dst, mn_vec4f_t * src, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabsf (src[ itr ].x);
        dst[ itr ].y = fabsf (src[ itr ].y);
        dst[ itr ].z = fabsf (src[ itr ].z);
        dst[ itr ].w = fabsf (src[ itr ].w);
    }
    return MN_SUCCESS;
}
