#include <stdio.h>
#include <arm_neon.h>

int main() {
    float a[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    float b[4] = {5.0f, 6.0f, 7.0f, 8.0f};
    float result[4];
    float32x4_t va = vld1q_f32(a);
    float32x4_t vb = vld1q_f32(b);
    float32x4_t vr = vaddq_f32(va, vb);
    vst1q_f32(result, vr);
    return 0;
}
