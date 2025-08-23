// MN_dtype.h

#ifndef MN_DTYPES_H
#define MN_DTYPES_H

#include <assert.h>
#include <stdint.h>


/////////////////////////////////////////////////////////
//-------- Data Types used in MATHNEON Project ---------
/////////////////////////////////////////////////////////

typedef int      MN_result_t;
typedef float    MN_float32_t;
typedef uint32_t MN_uint32_t;

/////////////////////////////////////////////////////////
// Return values to capture the state of program
/////////////////////////////////////////////////////////
#define MN_SUCCESS 0
#define MN_ERROR -1


/**
 * @brief A 2-tuple of MN_float32_t values.
 */
typedef struct
{
    MN_float32_t x;
    MN_float32_t y;
} MN_vec2f_t;

/**
 * @brief A 3-tuple of MN_float32_t values.
 */
typedef struct
{
    MN_float32_t x;
    MN_float32_t y;
    MN_float32_t z;
} MN_vec3f_t;

/**
 * @brief A 4-tuple of MN_float32_t values.
 */
typedef struct
{
    MN_float32_t x;
    MN_float32_t y;
    MN_float32_t z;
    MN_float32_t w;
} MN_vec4f_t;

#endif // MN_DTYPES_H
