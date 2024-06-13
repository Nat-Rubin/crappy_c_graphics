#include <stdio.h>
#include <stdint.h>
#include "graphics.h"

Triangle triangle_init(const int *p1, const int *p2, const int *p3, uint32_t color) {
    return _triangle_init(p1, p2, p3, color);
}