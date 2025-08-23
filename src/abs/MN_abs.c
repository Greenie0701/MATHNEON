#include "MN_dtype.h"

#include <assert.h>
#include <math.h>

/*
Function Input:
    dst   - Destination array that store results
    src   - Source array that stores user input
    count - Count is an integer that stores number of elements
    fabsf - Calculates the absolute value of the floating-point argument. Refer to MSVC Docs(https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fabsf-fabsff-fabsfl?view=msvc-170)
    abs   - Calculates the absolute value of the integer argument. Refer to MSVC Docs(https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/abs-labs-llabs-abs64?view=msvc-170)
 */

//C Implementation of abs function for int32(Supports upto 4-Dimensional Array)
//C Implementation for 1-Dimensional Array
MN_result_t MN_abs_int_c (MN_int32_t * dst, MN_int32_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[itr] = abs (src[itr]);
    }
    return MN_SUCCESS;
}

//C Implementation for 2-Dimensional Array
MN_result_t MN_abs_vec2i_c (MN_vec2i_t * dst, MN_vec2i_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = abs (src[ itr ].x);
        dst[ itr ].y = abs (src[ itr ].y);
    }
    return MN_SUCCESS;
}

//C Implementation for 3-Dimensional Array
MN_result_t MN_abs_vec3i_c (MN_vec3i_t * dst, MN_vec3i_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = abs (src[ itr ].x);
        dst[ itr ].y = abs (src[ itr ].y);
        dst[ itr ].z = abs (src[ itr ].z);
    }
    return MN_SUCCESS;
}

//C Implementation for 4-Dimensional Array
MN_result_t MN_abs_vec4i_c (MN_vec4i_t * dst, MN_vec4i_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = abs (src[ itr ].x);
        dst[ itr ].y = abs (src[ itr ].y);
        dst[ itr ].z = abs (src[ itr ].z);
        dst[ itr ].w = abs (src[ itr ].w);
    }
    return MN_SUCCESS;
}

//C Implementation of abs function for float32(Supports upto 4-Dimensional Array)
//C Implementation for 1-Dimensional Array
MN_result_t MN_abs_float_c (MN_float32_t * dst, MN_float32_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[itr] = fabsf (src[itr]);
    }
    return MN_SUCCESS;
}

//C Implementation for 2-Dimensional Array
MN_result_t MN_abs_vec2f_c (MN_vec2f_t * dst, MN_vec2f_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabsf (src[ itr ].x);
        dst[ itr ].y = fabsf (src[ itr ].y);
    }
    return MN_SUCCESS;
}

//C Implementation for 3-Dimensional Array
MN_result_t MN_abs_vec3f_c (MN_vec3f_t * dst, MN_vec3f_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabsf (src[ itr ].x);
        dst[ itr ].y = fabsf (src[ itr ].y);
        dst[ itr ].z = fabsf (src[ itr ].z);
    }
    return MN_SUCCESS;
}

//C Implementation for 4-Dimensional Array
MN_result_t MN_abs_vec4f_c (MN_vec4f_t * dst, MN_vec4f_t * src, MN_uint32_t count)
{
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = fabsf (src[ itr ].x);
        dst[ itr ].y = fabsf (src[ itr ].y);
        dst[ itr ].z = fabsf (src[ itr ].z);
        dst[ itr ].w = fabsf (src[ itr ].w);
    }
    return MN_SUCCESS;
}
