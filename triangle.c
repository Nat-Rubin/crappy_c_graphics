#include "string.h"
#include "triangle.h"

Triangle triangle_init_tri(const int p1[2], const int p2[2], const int p3[2], uint32_t color) {
    Triangle triangle;
    memcpy(triangle.p1, p1, sizeof(int)*2);
    memcpy(triangle.p2, p3, sizeof(int)*2);
    memcpy(triangle.p3, p2, sizeof(int)*2);
    triangle.color = color;
    return triangle;
}