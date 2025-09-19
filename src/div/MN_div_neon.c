#include "MN_dtype.h"
#include "MN_macro.h"
#include "MN_math.h"
#include <arm_neon.h>
#include <assert.h>

/*
Input Arguments:
    dst    - Destination pointer that stores the results
    src1   - Source pointer to array 1 (dividend)
    src2   - Source pointer to array 2 (divisor)
    count  - Number of elements to process
    
Note: For integer division, we use floating point conversion since NEON
      doesn't have native integer division intrinsics.
      For float division, we use reciprocal approximation for better performance.
Please refer to: https://stackoverflow.com/questions/6759897/divide-by-floating-point-number-using-neon-intrinsics [Current implementation]

Intrinsics used:
    float32 routines:
        vld1q_f32 - NEON intrinsic to load 4 float32 values from memory
        vst1q_f32 - NEON intrinsic to store 4 float32 values back to memory
        vrecpeq_f32 - NEON reciprocal approximation
        vrecpsq_f32 - NEON reciprocal step for Newton-Raphson refinement
    int32 routines:
        vld1q_s32 - NEON intrinsic to load 4 int32 values from memory
        vst1q_s32 - NEON intrinsic to store 4 int32 values back to memory
        vcvtq_f32_s32 - Convert int32 to float32
        vcvtq_s32_f32 - Convert float32 to int32
        
Supported routines: Int and Float 32-bit data types [1 to 4 Dimensional arrays]
*/

mn_result_t mn_div_float_neon(mn_float32_t * dst, mn_float32_t * src1, mn_float32_t * src2, uint32_t count) {
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_FLOAT_NEON(
        /* Use reciprocal approximation for better performance */
        float32x4_t reciprocal = vrecpeq_f32(n_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        n_dst = vmulq_f32(n_src1, reciprocal);,
        /* scalar leftover elements */
        *dst = *src1 / *src2;
    );
}

mn_result_t mn_div_int32_neon(mn_int32_t * dst, mn_int32_t * src1, mn_int32_t * src2, uint32_t count) {
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_INT32_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        float32x4_t f_src1 = vcvtq_f32_s32(n_src1);
        float32x4_t f_src2 = vcvtq_f32_s32(n_src2);
        float32x4_t reciprocal = vrecpeq_f32(f_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        float32x4_t f_result = vmulq_f32(f_src1, reciprocal);
        n_dst = vcvtq_s32_f32(f_result);,
        /* scalar leftover elements */
        *dst = *src1 / *src2;
    );
}

mn_result_t mn_div_vec2f_neon(mn_vec2f_t * dst, mn_vec2f_t * src1, mn_vec2f_t * src2, uint32_t count) {
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC2F_NEON(
        /* Use reciprocal approximation for 2-element vector division */
        float32x2_t reciprocal = vrecpe_f32(n_src2);
        reciprocal = vmul_f32(vrecps_f32(n_src2, reciprocal), reciprocal);
        reciprocal = vmul_f32(vrecps_f32(n_src2, reciprocal), reciprocal);
        n_dst = vmul_f32(n_src1, reciprocal);,
        /* Scalar division for leftover elements */
        dst->x = src1->x / src2->x;
        dst->y = src1->y / src2->y;
    );
}

mn_result_t mn_div_vec2i_neon(mn_vec2i_t * dst, mn_vec2i_t * src1, mn_vec2i_t * src2, uint32_t count) {
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC2I_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        float32x2_t f_src1 = vcvt_f32_s32(n_src1);
        float32x2_t f_src2 = vcvt_f32_s32(n_src2);
        float32x2_t reciprocal = vrecpe_f32(f_src2);
        reciprocal = vmul_f32(vrecps_f32(f_src2, reciprocal), reciprocal);
        reciprocal = vmul_f32(vrecps_f32(f_src2, reciprocal), reciprocal);
        float32x2_t f_result = vmul_f32(f_src1, reciprocal);
        n_dst = vcvt_s32_f32(f_result);,
        /* Scalar division for leftover elements */
        dst->x = src1->x / src2->x;
        dst->y = src1->y / src2->y;
    );
}

// FIXED VEC3F - Process element by element to avoid memory issues
mn_result_t mn_div_vec3f_neon(mn_vec3f_t * dst, mn_vec3f_t * src1, mn_vec3f_t * src2, uint32_t count) {
    mn_result_t res = MN_OK;
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2);
    
    // Process 4 vec3f at a time using scalar approach with SIMD for components
    uint32_t simd_count = count - (count % 4);
    uint32_t i;
    
    for (i = 0; i < simd_count; i += 4) {
        // Load X components
        float32x4_t x1 = {src1[i].x, src1[i+1].x, src1[i+2].x, src1[i+3].x};
        float32x4_t x2 = {src2[i].x, src2[i+1].x, src2[i+2].x, src2[i+3].x};
        float32x4_t x_rec = vrecpeq_f32(x2);
        x_rec = vmulq_f32(vrecpsq_f32(x2, x_rec), x_rec);
        x_rec = vmulq_f32(vrecpsq_f32(x2, x_rec), x_rec);
        float32x4_t x_result = vmulq_f32(x1, x_rec);
        
        // Load Y components
        float32x4_t y1 = {src1[i].y, src1[i+1].y, src1[i+2].y, src1[i+3].y};
        float32x4_t y2 = {src2[i].y, src2[i+1].y, src2[i+2].y, src2[i+3].y};
        float32x4_t y_rec = vrecpeq_f32(y2);
        y_rec = vmulq_f32(vrecpsq_f32(y2, y_rec), y_rec);
        y_rec = vmulq_f32(vrecpsq_f32(y2, y_rec), y_rec);
        float32x4_t y_result = vmulq_f32(y1, y_rec);
        
        // Load Z components
        float32x4_t z1 = {src1[i].z, src1[i+1].z, src1[i+2].z, src1[i+3].z};
        float32x4_t z2 = {src2[i].z, src2[i+1].z, src2[i+2].z, src2[i+3].z};
        float32x4_t z_rec = vrecpeq_f32(z2);
        z_rec = vmulq_f32(vrecpsq_f32(z2, z_rec), z_rec);
        z_rec = vmulq_f32(vrecpsq_f32(z2, z_rec), z_rec);
        float32x4_t z_result = vmulq_f32(z1, z_rec);
        
        // Store results
        float x_values[4], y_values[4], z_values[4];
        vst1q_f32(x_values, x_result);
        vst1q_f32(y_values, y_result);
        vst1q_f32(z_values, z_result);
        
        for (int j = 0; j < 4; j++) {
            dst[i+j].x = x_values[j];
            dst[i+j].y = y_values[j];
            dst[i+j].z = z_values[j];
        }
    }
    
    // Handle remaining elements
    for (; i < count; i++) {
        dst[i].x = src1[i].x / src2[i].x;
        dst[i].y = src1[i].y / src2[i].y;
        dst[i].z = src1[i].z / src2[i].z;
    }
    
    return res;
}

// FIXED VEC3I - Process element by element to avoid memory issues
mn_result_t mn_div_vec3i_neon(mn_vec3i_t * dst, mn_vec3i_t * src1, mn_vec3i_t * src2, uint32_t count) {
    mn_result_t res = MN_OK;
    MN_CHECK_Dst1SRC1SRC2(dst, src1, src2);
    
    // Process 4 vec3i at a time using scalar approach with SIMD for components
    uint32_t simd_count = count - (count % 4);
    uint32_t i;
    
    for (i = 0; i < simd_count; i += 4) {
        // Load and convert X components
        int32x4_t x1 = {src1[i].x, src1[i+1].x, src1[i+2].x, src1[i+3].x};
        int32x4_t x2 = {src2[i].x, src2[i+1].x, src2[i+2].x, src2[i+3].x};
        float32x4_t f_x1 = vcvtq_f32_s32(x1);
        float32x4_t f_x2 = vcvtq_f32_s32(x2);
        float32x4_t x_rec = vrecpeq_f32(f_x2);
        x_rec = vmulq_f32(vrecpsq_f32(f_x2, x_rec), x_rec);
        x_rec = vmulq_f32(vrecpsq_f32(f_x2, x_rec), x_rec);
        int32x4_t x_result = vcvtq_s32_f32(vmulq_f32(f_x1, x_rec));
        
        // Load and convert Y components
        int32x4_t y1 = {src1[i].y, src1[i+1].y, src1[i+2].y, src1[i+3].y};
        int32x4_t y2 = {src2[i].y, src2[i+1].y, src2[i+2].y, src2[i+3].y};
        float32x4_t f_y1 = vcvtq_f32_s32(y1);
        float32x4_t f_y2 = vcvtq_f32_s32(y2);
        float32x4_t y_rec = vrecpeq_f32(f_y2);
        y_rec = vmulq_f32(vrecpsq_f32(f_y2, y_rec), y_rec);
        y_rec = vmulq_f32(vrecpsq_f32(f_y2, y_rec), y_rec);
        int32x4_t y_result = vcvtq_s32_f32(vmulq_f32(f_y1, y_rec));
        
        // Load and convert Z components
        int32x4_t z1 = {src1[i].z, src1[i+1].z, src1[i+2].z, src1[i+3].z};
        int32x4_t z2 = {src2[i].z, src2[i+1].z, src2[i+2].z, src2[i+3].z};
        float32x4_t f_z1 = vcvtq_f32_s32(z1);
        float32x4_t f_z2 = vcvtq_f32_s32(z2);
        float32x4_t z_rec = vrecpeq_f32(f_z2);
        z_rec = vmulq_f32(vrecpsq_f32(f_z2, z_rec), z_rec);
        z_rec = vmulq_f32(vrecpsq_f32(f_z2, z_rec), z_rec);
        int32x4_t z_result = vcvtq_s32_f32(vmulq_f32(f_z1, z_rec));
        
        // Store results
        int32_t x_values[4], y_values[4], z_values[4];
        vst1q_s32(x_values, x_result);
        vst1q_s32(y_values, y_result);
        vst1q_s32(z_values, z_result);
        
        for (int j = 0; j < 4; j++) {
            dst[i+j].x = x_values[j];
            dst[i+j].y = y_values[j];
            dst[i+j].z = z_values[j];
        }
    }
    
    // Handle remaining elements
    for (; i < count; i++) {
        dst[i].x = src1[i].x / src2[i].x;
        dst[i].y = src1[i].y / src2[i].y;
        dst[i].z = src1[i].z / src2[i].z;
    }
    
    return res;
}

mn_result_t mn_div_vec4f_neon(mn_vec4f_t * dst, mn_vec4f_t * src1, mn_vec4f_t * src2, uint32_t count) {
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC4F_NEON(
        /* Use reciprocal approximation - Each vec4f fits exactly in 128-bit register */
        float32x4_t reciprocal = vrecpeq_f32(n_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(n_src2, reciprocal), reciprocal);
        n_dst = vmulq_f32(n_src1, reciprocal);
    );
}

mn_result_t mn_div_vec4i_neon(mn_vec4i_t * dst, mn_vec4i_t * src1, mn_vec4i_t * src2, uint32_t count) {
    MN_DIV_DstSrc1Src2_DO_COUNT_TIMES_VEC4I_NEON(
        /* Convert to float, divide using reciprocal, convert back */
        float32x4_t f_src1 = vcvtq_f32_s32(n_src1);
        float32x4_t f_src2 = vcvtq_f32_s32(n_src2);
        float32x4_t reciprocal = vrecpeq_f32(f_src2);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        reciprocal = vmulq_f32(vrecpsq_f32(f_src2, reciprocal), reciprocal);
        float32x4_t f_result = vmulq_f32(f_src1, reciprocal);
        n_dst = vcvtq_s32_f32(f_result);
    );
}
