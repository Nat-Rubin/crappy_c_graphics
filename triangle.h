#include <stdint.h>

#ifndef C_GRAPHICS_TRIANGLE_H
#define C_GRAPHICS_TRIANGLE_H

typedef struct Triangle {
    // clockwise
    int p1[2];
    int p2[2];
    int p3[2];
    uint32_t color;
} Triangle;

Triangle triangle_init_tri(const int *p1, const int *p2, const int *p3, uint32_t color);

#endif //C_GRAPHICS_TRIANGLE_H
