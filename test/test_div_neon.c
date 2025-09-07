#include <stdio.h>
#include <stdlib.h>
#include "../includes/MN_dtype.h"
#include "../includes/MN_macro.h"
#include "../includes/MN_math.h"

int main(void)
{
    int count = 16;

    // ==== allocate arrays ====
    float* src1_f  = (float*)malloc(sizeof(float) * count);
    float* src2_f  = (float*)malloc(sizeof(float) * count);
    float* dst_f   = (float*)malloc(sizeof(float) * count);
    float* ref_f   = (float*)malloc(sizeof(float) * count);

    int* src1_i    = (int*)malloc(sizeof(int) * count);
    int* src2_i    = (int*)malloc(sizeof(int) * count);
    int* dst_i     = (int*)malloc(sizeof(int) * count);
    int* ref_i     = (int*)malloc(sizeof(int) * count);

    mn_vec2f_t* src1_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* src2_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* dst_v2f  = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* ref_v2f  = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);

    mn_vec2i_t* src1_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* src2_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* dst_v2i  = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* ref_v2i  = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);

    mn_vec3f_t* src1_v3f = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* src2_v3f = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* dst_v3f  = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* ref_v3f  = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);

    mn_vec3i_t* src1_v3i = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* src2_v3i = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* dst_v3i  = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* ref_v3i  = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);

    mn_vec4f_t* src1_v4f = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* src2_v4f = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* dst_v4f  = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* ref_v4f  = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);

    mn_vec4i_t* src1_v4i = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* src2_v4i = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* dst_v4i  = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* ref_v4i  = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);

    if (!src1_f || !src2_f || !dst_f || !ref_f || 
        !src1_i || !src2_i || !dst_i || !ref_i ||
        !src1_v2f || !src2_v2f || !dst_v2f || !ref_v2f ||
        !src1_v2i || !src2_v2i || !dst_v2i || !ref_v2i ||
        !src1_v3f || !src2_v3f || !dst_v3f || !ref_v3f ||
        !src1_v3i || !src2_v3i || !dst_v3i || !ref_v3i ||
        !src1_v4f || !src2_v4f || !dst_v4f || !ref_v4f ||
        !src1_v4i || !src2_v4i || !dst_v4i || !ref_v4i)
    {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }

    // ==== fill inputs ====
    for (int i = 0; i < count; i++) {
        src1_f[i] = (float)(i + 1);
        src2_f[i] = (float)(i + 2);   // avoid div-by-zero

        src1_i[i] = i + 10;
        src2_i[i] = (i + 2);          // avoid div-by-zero

        src1_v2f[i].x = (float)(i + 0.5f);
        src1_v2f[i].y = (float)(i + 1.5f);
        src2_v2f[i].x = (float)(i + 2.5f);
        src2_v2f[i].y = (float)(i + 3.5f);

        src1_v2i[i].x = i + 10;
        src1_v2i[i].y = i + 20;
        src2_v2i[i].x = i + 30;
        src2_v2i[i].y = i + 40;

        src1_v3f[i].x = (float)(i + 0.25f);
        src1_v3f[i].y = (float)(i + 1.25f);
        src1_v3f[i].z = (float)(i + 2.25f);
        src2_v3f[i].x = (float)(i + 3.25f);
        src2_v3f[i].y = (float)(i + 4.25f);
        src2_v3f[i].z = (float)(i + 5.25f);

        src1_v3i[i].x = i + 100;
        src1_v3i[i].y = i + 200;
        src1_v3i[i].z = i + 300;
        src2_v3i[i].x = i + 400;
        src2_v3i[i].y = i + 500;
        src2_v3i[i].z = i + 600;

        src1_v4f[i].x = (float)(i + 0.1f);
        src1_v4f[i].y = (float)(i + 1.2f);
        src1_v4f[i].z = (float)(i + 2.3f);
        src1_v4f[i].w = (float)(i + 3.4f);
        src2_v4f[i].x = (float)(i + 4.1f);
        src2_v4f[i].y = (float)(i + 5.2f);
        src2_v4f[i].z = (float)(i + 6.3f);
        src2_v4f[i].w = (float)(i + 7.4f);

        src1_v4i[i].x = i + 1000;
        src1_v4i[i].y = i + 2000;
        src1_v4i[i].z = i + 3000;
        src1_v4i[i].w = i + 4000;
        src2_v4i[i].x = i + 5000;
        src2_v4i[i].y = i + 6000;
        src2_v4i[i].z = i + 7000;
        src2_v4i[i].w = i + 8000;
    }

    // ==== reference (C) ====
    mn_div_float_c(ref_f, src1_f, src2_f, count);
    mn_div_int32_c(ref_i, src1_i, src2_i, count);
    mn_div_vec2f_c(ref_v2f, src1_v2f, src2_v2f, count);
    mn_div_vec2i_c(ref_v2i, src1_v2i, src2_v2i, count);
    mn_div_vec3f_c(ref_v3f, src1_v3f, src2_v3f, count);
    mn_div_vec3i_c(ref_v3i, src1_v3i, src2_v3i, count);
    mn_div_vec4f_c(ref_v4f, src1_v4f, src2_v4f, count);
    mn_div_vec4i_c(ref_v4i, src1_v4i, src2_v4i, count);

    // ==== NEON ====
    mn_div_float_neon(dst_f, src1_f, src2_f, count);
    mn_div_int32_neon(dst_i, src1_i, src2_i, count);
    mn_div_vec2f_neon(dst_v2f, src1_v2f, src2_v2f, count);
    mn_div_vec2i_neon(dst_v2i, src1_v2i, src2_v2i, count);
    mn_div_vec3f_neon(dst_v3f, src1_v3f, src2_v3f, count);
    mn_div_vec3i_neon(dst_v3i, src1_v3i, src2_v3i, count);
    mn_div_vec4f_neon(dst_v4f, src1_v4f, src2_v4f, count);
    mn_div_vec4i_neon(dst_v4i, src1_v4i, src2_v4i, count);

    // ==== validate ====
    for (int i = 0; i < count; i++) {
        if (dst_f[i] != ref_f[i] || dst_i[i] != ref_i[i]) {
            printf("Flat div test failed at %d\n", i); return 1;
        }
        if (dst_v2f[i].x != ref_v2f[i].x || dst_v2f[i].y != ref_v2f[i].y ||
            dst_v2i[i].x != ref_v2i[i].x || dst_v2i[i].y != ref_v2i[i].y) {
            printf("Vec2 div test failed at %d\n", i); return 1;
        }
        if (dst_v3f[i].x != ref_v3f[i].x || dst_v3f[i].y != ref_v3f[i].y || dst_v3f[i].z != ref_v3f[i].z ||
            dst_v3i[i].x != ref_v3i[i].x || dst_v3i[i].y != ref_v3i[i].y || dst_v3i[i].z != ref_v3i[i].z) {
            printf("Vec3 div test failed at %d\n", i); return 1;
        }
        if (dst_v4f[i].x != ref_v4f[i].x || dst_v4f[i].y != ref_v4f[i].y ||
            dst_v4f[i].z != ref_v4f[i].z || dst_v4f[i].w != ref_v4f[i].w ||
            dst_v4i[i].x != ref_v4i[i].x || dst_v4i[i].y != ref_v4i[i].y ||
            dst_v4i[i].z != ref_v4i[i].z || dst_v4i[i].w != ref_v4i[i].w) {
            printf("Vec4 div test failed at %d\n", i); return 1;
        }
    }

    printf("All div tests passed!\n");

    // cleanup
    free(src1_f); free(src2_f); free(dst_f); free(ref_f);
    free(src1_i); free(src2_i); free(dst_i); free(ref_i);
    free(src1_v2f); free(src2_v2f); free(dst_v2f); free(ref_v2f);
    free(src1_v2i); free(src2_v2i); free(dst_v2i); free(ref_v2i);
    free(src1_v3f); free(src2_v3f); free(dst_v3f); free(ref_v3f);
    free(src1_v3i); free(src2_v3i); free(dst_v3i); free(ref_v3i);
    free(src1_v4f); free(src2_v4f); free(dst_v4f); free(ref_v4f);
    free(src1_v4i); free(src2_v4i); free(dst_v4i); free(ref_v4i);

    return 0;
}
