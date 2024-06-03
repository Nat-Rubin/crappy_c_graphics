#ifndef C_GRAPHICS_CANVAS_H
#define C_GRAPHICS_CANVAS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "triangle.h"

typedef struct Canvas {
    size_t width;
    size_t height;
    size_t total_pixels;
    uint32_t *pixels;
    char* file_path;
    uint32_t background_color;
    uint64_t max_triangles;
    uint64_t num_triangles;
    Triangle *triangles; // TODO: maybe **triangles
} Canvas;

Canvas canvas_init(size_t width, size_t height, uint32_t color, char* file_path);
bool canvas_to_ppm(Canvas *canvas);
bool canvas_free(Canvas *canvas);
void canvas_fill(Canvas *canvas, uint32_t color);
void add_triangle(Canvas *canvas, Triangle *triangle);
void canvas_update(Canvas *canvas);

#endif //C_GRAPHICS_CANVAS_H
