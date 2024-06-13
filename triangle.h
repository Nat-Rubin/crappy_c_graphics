#include <stdint.h>

#ifndef C_GRAPHICS_TRIANGLE_H
#define C_GRAPHICS_TRIANGLE_H

typedef struct Triangle {
    // clockwise
    int p1[3];
    int p2[3];
    int p3[3];
    uint32_t color;
} Triangle;

Triangle _triangle_init_(const int *p1, const int *p2, const int *p3, uint32_t color);

#endif //C_GRAPHICS_TRIANGLE_H
