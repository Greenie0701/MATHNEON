#include "MN_dtype.h"
#include "MN_macro.h"
#include "MN_math.h"
#include <assert.h>
#include <math.h>

/*
Function Input:
    dst   - Destination that store results
    src1  - Source that stores user input 1
    src2  - Source that stores user input 1
    count - Count is an integer that stores number of elements
 */

/*
    C Implementation of subtracting two input vectors.
    Supports 1-4 Dimensional vectors
*/

mn_result_t mn_sub_int32_c (mn_int32_t * dst, mn_int32_t * src1, mn_int32_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[itr] = (src1[itr]-src2[itr]);
    }
    return MN_SUCCESS;
}

mn_result_t mn_sub_vec2i_c (mn_vec2i_t * dst, mn_vec2i_t * src1, mn_vec2i_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = (src1[ itr ].x-src2[ itr ].x);
        dst[ itr ].y = (src1[ itr ].y-src2[ itr ].y);
    }
    return MN_SUCCESS;
}

mn_result_t mn_sub_vec3i_c (mn_vec3i_t * dst, mn_vec3i_t * src1, mn_vec3i_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = (src1[ itr ].x-src2[ itr ].x);
        dst[ itr ].y = (src1[ itr ].y-src2[ itr ].y);
        dst[ itr ].z = (src1[ itr ].z-src2[ itr ].z);
    }
    return MN_SUCCESS;
}

mn_result_t mn_sub_vec4i_c (mn_vec4i_t * dst, mn_vec4i_t * src1, mn_vec4i_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = (src1[ itr ].x-src2[ itr ].x);
        dst[ itr ].y = (src1[ itr ].y-src2[ itr ].y);
        dst[ itr ].z = (src1[ itr ].z-src2[ itr ].z);
        dst[ itr ].w = (src1[ itr ].w-src2[ itr ].w);
    }
    return MN_SUCCESS;
}

mn_result_t mn_sub_float_c (mn_float32_t * dst, mn_float32_t * src1, mn_float32_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[itr] = (src1[itr]-src2[itr]);
    }
    return MN_SUCCESS;
}

mn_result_t mn_sub_vec2f_c (mn_vec2f_t * dst, mn_vec2f_t * src1, mn_vec2f_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = (src1[ itr ].x-src2[ itr ].x);
        dst[ itr ].y = (src1[ itr ].y-src2[ itr ].y);
    }
    return MN_SUCCESS;
}

mn_result_t mn_sub_vec3f_c (mn_vec3f_t * dst, mn_vec3f_t * src1, mn_vec3f_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = (src1[ itr ].x-src2[ itr ].x);
        dst[ itr ].y = (src1[ itr ].y-src2[ itr ].y);
        dst[ itr ].z = (src1[ itr ].z-src2[ itr ].z);
    }
    return MN_SUCCESS;
}

mn_result_t mn_sub_vec4f_c (mn_vec4f_t * dst, mn_vec4f_t * src1, mn_vec4f_t * src2, mn_uint32_t count)
{
    MN_ASSERT_DS1S2(dst, src1, src2);;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = (src1[ itr ].x-src2[ itr ].x);
        dst[ itr ].y = (src1[ itr ].y-src2[ itr ].y);
        dst[ itr ].z = (src1[ itr ].z-src2[ itr ].z);
        dst[ itr ].w = (src1[ itr ].w-src2[ itr ].w);
    }
    return MN_SUCCESS;
}
