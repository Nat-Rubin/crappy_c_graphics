#ifndef C_GRAPHICS_CANVAS_H
#define C_GRAPHICS_CANVAS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Canvas {
    size_t width;
    size_t height;
    size_t total_pixels;
    uint32_t *pixels;
    char* file_path;
} Canvas;

void canvas_fill(Canvas *canvas, uint32_t color);
void canvas_update(Canvas *canvas);
bool canvas_to_ppm(Canvas *canvas);
Canvas canvas_init(size_t width, size_t height, char* file_path);
bool canvas_free(Canvas *canvas);

#endif //C_GRAPHICS_CANVAS_H
