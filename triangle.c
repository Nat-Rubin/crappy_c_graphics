#include "string.h"
#include "triangle.h"

Triangle _triangle_init_(const int p1[3], const int p2[3], const int p3[3], uint32_t color) {
    Triangle triangle;
    memcpy(triangle.p1, p1, sizeof(int)*3);
    memcpy(triangle.p2, p3, sizeof(int)*3);
    memcpy(triangle.p3, p2, sizeof(int)*3);
    triangle.color = color;
    return triangle;
}