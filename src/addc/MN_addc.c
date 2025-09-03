#include "MN_types.h"
#include "macros.h"
#include <assert.h>

mn_result_t mn_addc_float_c (mn_float32_t * dst, mn_float32_t * src, const mn_float32_t cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ] = src[ itr ] + cst;
    }
    return MN_OK;
}

mn_result_t mn_addc_vec2f_c (mn_vec2f_t * dst, mn_vec2f_t * src, const mn_vec2f_t * cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = src[ itr ].x + cst->x;
        dst[ itr ].y = src[ itr ].y + cst->y;
    }
    return MN_OK;
}

mn_result_t mn_addc_vec3f_c (mn_vec3f_t * dst, mn_vec3f_t * src, const mn_vec3f_t * cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = src[ itr ].x + cst->x;
        dst[ itr ].y = src[ itr ].y + cst->y;
        dst[ itr ].z = src[ itr ].z + cst->z;
    }
    return MN_OK;
}

mn_result_t mn_addc_vec4f_c (mn_vec4f_t * dst, mn_vec4f_t * src, const mn_vec4f_t * cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = src[ itr ].x + cst->x;
        dst[ itr ].y = src[ itr ].y + cst->y;
        dst[ itr ].z = src[ itr ].z + cst->z;
        dst[ itr ].w = src[ itr ].w + cst->w;
    }
    return MN_OK;
}

mn_result_t mn_addc_int_c (mn_int32_t * dst, mn_int32_t * src, const mn_int32_t cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ] = src[ itr ] + cst;
    }
    return MN_OK;
}

mn_result_t mn_addc_vec2i_c (mn_vec2i_t * dst, mn_vec2i_t * src, const mn_vec2i_t * cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = src[ itr ].x + cst->x;
        dst[ itr ].y = src[ itr ].y + cst->y;
    }
    return MN_OK;
}

mn_result_t mn_addc_vec3i_c (mn_vec3i_t * dst, mn_vec3i_t * src, const mn_vec3i_t * cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = src[ itr ].x + cst->x;
        dst[ itr ].y = src[ itr ].y + cst->y;
        dst[ itr ].z = src[ itr ].z + cst->z;
    }
    return MN_OK;
}

mn_result_t mn_addc_vec4i_c (mn_vec4i_t * dst, mn_vec4i_t * src, const mn_vec4i_t * cst, mn_uint32_t count)
{
    MN_ASSERT_DS;
    for ( unsigned int itr = 0; itr < count; itr++ )
    {
        dst[ itr ].x = src[ itr ].x + cst->x;
        dst[ itr ].y = src[ itr ].y + cst->y;
        dst[ itr ].z = src[ itr ].z + cst->z;
        dst[ itr ].w = src[ itr ].w + cst->w;
    }
    return MN_OK;
}
