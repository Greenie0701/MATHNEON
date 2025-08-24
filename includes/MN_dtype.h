// MN_dtype.h

#ifndef MN_DTYPES_H
#define MN_DTYPES_H

#include <assert.h>
#include <stdint.h>


/////////////////////////////////////////////////////////
//-------- Data Types used in MATHNEON Project ---------
/////////////////////////////////////////////////////////

typedef int      mn_result_t;
typedef int32_t  mn_int32_t;
typedef float    mn_float32_t;
typedef uint32_t mn_uint32_t;

/////////////////////////////////////////////////////////
// Return values to capture the state of program
/////////////////////////////////////////////////////////
#define MN_SUCCESS 0
#define MN_ERROR -1
#define MN_OK MN_SUCCESS

/**
 * @brief A 2-tuple of mn_int32_t values.
 */
typedef struct
{
    mn_int32_t x;
    mn_int32_t y;
} mn_vec2i_t;

/**
 * @brief A 3-tuple of mn_int32_t values.
 */
typedef struct
{
    mn_int32_t x;
    mn_int32_t y;
    mn_int32_t z;
} mn_vec3i_t;

/**
 * @brief A 4-tuple of mn_int32_t values.
 */
typedef struct
{
    mn_int32_t x;
    mn_int32_t y;
    mn_int32_t z;
    mn_int32_t w;
} mn_vec4i_t;

/**
 * @brief A 2-tuple of mn_float32_t values.
 */
typedef struct
{
    mn_float32_t x;
    mn_float32_t y;
} mn_vec2f_t;

/**
 * @brief A 3-tuple of mn_float32_t values.
 */
typedef struct
{
    mn_float32_t x;
    mn_float32_t y;
    mn_float32_t z;
} mn_vec3f_t;

/**
 * @brief A 4-tuple of mn_float32_t values.
 */
typedef struct
{
    mn_float32_t x;
    mn_float32_t y;
    mn_float32_t z;
    mn_float32_t w;
} mn_vec4f_t;

#endif // MN_DTYPES_H
