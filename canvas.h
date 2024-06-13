#ifndef C_GRAPHICS_CANVAS_H
#define C_GRAPHICS_CANVAS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "triangle.h"
#include "shape_from_triangles.h"

typedef struct Canvas {
    uint32_t mode;  // 2 = 2D, 3 = 3D
    size_t width;
    size_t height;
    size_t total_pixels;
    uint32_t *pixels;
    char* file_path;
    uint32_t background_color;
    uint64_t max_shapes;
    uint64_t num_shapes;
    //Triangle *triangles; // TODO: maybe **triangles
    ShapeFromTriangles *shapes;
} Canvas;

Canvas canvas_init(uint32_t mode, size_t width, size_t height, uint32_t background_color, char* file_path);
bool canvas_to_ppm(Canvas *canvas);
bool canvas_free(Canvas *canvas);
void canvas_fill(Canvas *canvas, uint32_t color);
void add_shapes(Canvas *canvas, Triangle *triangle);
void canvas_update(Canvas *canvas);

#endif //C_GRAPHICS_CANVAS_H
