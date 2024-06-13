#include <stdint.h>
#include "graphics.h"
#include "colors.h"

uint32_t *render(Canvas *canvas) {
    int p1[3] = {0,0, 0};
    int p2[3] = {50, 10, 0};
    int p3[3] = {35,30, 0};
    Triangle tri = triangle_init(p1, p2, p3, colors.GREEN);
    triangle_draw(canvas, &tri, false);
    return canvas->pixels;
}