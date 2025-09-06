#include <stdio.h>
#include <stdlib.h>
#include "../includes/MN_dtype.h"
#include "../includes/MN_macro.h"
#include "../includes/MN_math.h"

int main(void)
{
    int count = 16;

    // ==== allocate arrays ====
    float* src_f  = (float*)malloc(sizeof(float) * count);
    float* dst_f  = (float*)malloc(sizeof(float) * count);
    float* ref_f  = (float*)malloc(sizeof(float) * count);

    int* src_i    = (int*)malloc(sizeof(int) * count);
    int* dst_i    = (int*)malloc(sizeof(int) * count);
    int* ref_i    = (int*)malloc(sizeof(int) * count);

    mn_vec2f_t* src_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* dst_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* ref_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);

    mn_vec2i_t* src_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* dst_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* ref_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);

    mn_vec3f_t* src_v3f = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* dst_v3f = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* ref_v3f = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);

    mn_vec3i_t* src_v3i = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* dst_v3i = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* ref_v3i = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);

    mn_vec4f_t* src_v4f = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* dst_v4f = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* ref_v4f = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);

    mn_vec4i_t* src_v4i = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* dst_v4i = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* ref_v4i = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);

    if (!src_f || !dst_f || !ref_f || !src_i || !dst_i || !ref_i ||
        !src_v2f || !dst_v2f || !ref_v2f || !src_v2i || !dst_v2i || !ref_v2i ||
        !src_v3f || !dst_v3f || !ref_v3f || !src_v3i || !dst_v3i || !ref_v3i ||
        !src_v4f || !dst_v4f || !ref_v4f || !src_v4i || !dst_v4i || !ref_v4i)
    {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }

    // ==== constants ====
    float      cst_f  = 1.5f;
    int        cst_i  = 42;
    mn_vec2f_t cst_v2f = { 0.5f, -1.5f };
    mn_vec2i_t cst_v2i = { 5, -10 };
    mn_vec3f_t cst_v3f = { 0.1f, 0.2f, 0.3f };
    mn_vec3i_t cst_v3i = { 7, 8, 9 };
    mn_vec4f_t cst_v4f = { 1.0f, -2.0f, 3.0f, -4.0f };
    mn_vec4i_t cst_v4i = { 100, 200, 300, 400 };

    // ==== fill inputs ====
    for (int i = 0; i < count; i++) {
        src_f[i] = (float)i;
        src_i[i] = i;

        src_v2f[i].x = (float)(i + 0.5f);
        src_v2f[i].y = (float)(i + 1.5f);

        src_v2i[i].x = i + 10;
        src_v2i[i].y = i + 20;

        src_v3f[i].x = (float)(i + 0.25f);
        src_v3f[i].y = (float)(i + 1.25f);
        src_v3f[i].z = (float)(i + 2.25f);

        src_v3i[i].x = i + 100;
        src_v3i[i].y = i + 200;
        src_v3i[i].z = i + 300;

        src_v4f[i].x = (float)(i + 0.1f);
        src_v4f[i].y = (float)(i + 1.2f);
        src_v4f[i].z = (float)(i + 2.3f);
        src_v4f[i].w = (float)(i + 3.4f);

        src_v4i[i].x = i + 1000;
        src_v4i[i].y = i + 2000;
        src_v4i[i].z = i + 3000;
        src_v4i[i].w = i + 4000;
    }

    // ==== reference (C) ====
    mn_subc_float_c(ref_f, src_f, cst_f, count);
    mn_subc_int32_c(ref_i, src_i, cst_i, count);
    mn_subc_vec2f_c(ref_v2f, src_v2f, &cst_v2f, count);
    mn_subc_vec2i_c(ref_v2i, src_v2i, &cst_v2i, count);
    mn_subc_vec3f_c(ref_v3f, src_v3f, &cst_v3f, count);
    mn_subc_vec3i_c(ref_v3i, src_v3i, &cst_v3i, count);
    mn_subc_vec4f_c(ref_v4f, src_v4f, &cst_v4f, count);
    mn_subc_vec4i_c(ref_v4i, src_v4i, &cst_v4i, count);

    // ==== NEON ====
    mn_subc_float_neon(dst_f, src_f, cst_f, count);
    mn_subc_int32_neon(dst_i, src_i, cst_i, count);
    mn_subc_vec2f_neon(dst_v2f, src_v2f, &cst_v2f, count);
    mn_subc_vec2i_neon(dst_v2i, src_v2i, &cst_v2i, count);
    mn_subc_vec3f_neon(dst_v3f, src_v3f, &cst_v3f, count);
    mn_subc_vec3i_neon(dst_v3i, src_v3i, &cst_v3i, count);
    mn_subc_vec4f_neon(dst_v4f, src_v4f, &cst_v4f, count);
    mn_subc_vec4i_neon(dst_v4i, src_v4i, &cst_v4i, count);

    // ==== validate ====
    for (int i = 0; i < count; i++) {
        if (dst_f[i] != ref_f[i] || dst_i[i] != ref_i[i]) {
            printf("Flat subc test failed at %d\n", i); return 1;
        }
        if (dst_v2f[i].x != ref_v2f[i].x || dst_v2f[i].y != ref_v2f[i].y ||
            dst_v2i[i].x != ref_v2i[i].x || dst_v2i[i].y != ref_v2i[i].y) {
            printf("Vec2 subc test failed at %d\n", i); return 1;
        }
        if (dst_v3f[i].x != ref_v3f[i].x || dst_v3f[i].y != ref_v3f[i].y || dst_v3f[i].z != ref_v3f[i].z ||
            dst_v3i[i].x != ref_v3i[i].x || dst_v3i[i].y != ref_v3i[i].y || dst_v3i[i].z != ref_v3i[i].z) {
            printf("Vec3 subc test failed at %d\n", i); return 1;
        }
        if (dst_v4f[i].x != ref_v4f[i].x || dst_v4f[i].y != ref_v4f[i].y ||
            dst_v4f[i].z != ref_v4f[i].z || dst_v4f[i].w != ref_v4f[i].w ||
            dst_v4i[i].x != ref_v4i[i].x || dst_v4i[i].y != ref_v4i[i].y ||
            dst_v4i[i].z != ref_v4i[i].z || dst_v4i[i].w != ref_v4i[i].w) {
            printf("Vec4 subc test failed at %d\n", i); return 1;
        }
    }

    printf("All subc tests passed!\n");

    // cleanup
    free(src_f); free(dst_f); free(ref_f);
    free(src_i); free(dst_i); free(ref_i);
    free(src_v2f); free(dst_v2f); free(ref_v2f);
    free(src_v2i); free(dst_v2i); free(ref_v2i);
    free(src_v3f); free(dst_v3f); free(ref_v3f);
    free(src_v3i); free(dst_v3i); free(ref_v3i);
    free(src_v4f); free(dst_v4f); free(ref_v4f);
    free(src_v4i); free(dst_v4i); free(ref_v4i);

    return 0;
}
