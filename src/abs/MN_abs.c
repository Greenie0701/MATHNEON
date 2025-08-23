#include "MN_dtype.h"

#include <assert.h>

#include <math.h>

//C Implementation of abs function for float32(Supports upto 4-Dimensional Array)

MN_result_t MN_abs_float_c (MN_float32_t * dst, MN_float32_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[itr] = fabs (src[itr]);
    }
    return MN_SUCCESS;
}

MN_result_t MN_abs_vec2f_c (MN_vec2f_t * dst, MN_vec2f_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabs (src[ itr ].x);
        dst[ itr ].y = fabs (src[ itr ].y);
    }
    return MN_OK;
}

MN_result_t MN_abs_vec3f_c (MN_vec3f_t * dst, MN_vec3f_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabs (src[ itr ].x);
        dst[ itr ].y = fabs (src[ itr ].y);
        dst[ itr ].z = fabs (src[ itr ].z);
    }
    return MN_OK;
}

MN_result_t MN_abs_vec4f_c (MN_vec4f_t * dst, MN_vec4f_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabs (src[ itr ].x);
        dst[ itr ].y = fabs (src[ itr ].y);
        dst[ itr ].z = fabs (src[ itr ].z);
        dst[ itr ].w = fabs (src[ itr ].w);
    }
    return MN_OK;
}
