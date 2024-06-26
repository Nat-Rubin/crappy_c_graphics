//
// Created by Nathaniel Rubin on 5/28/24.
//

#ifndef C_GRAPHICS_SHAPES_H
#define C_GRAPHICS_SHAPES_H

#include <stdint.h>
#include "canvas.h"
#include "triangle.h"

typedef struct Line{
    int x1;
    int y1;
    int x2;
    int y2;
    uint32_t thickness;
} Line;

typedef struct Rectangle{
    int x_pos;
    int y_pos;
    int width;
    int height;
} Rectangle;

typedef struct Circle {
    int x_center;
    int y_center;
    int radius;
} Circle;


Line line_init(int x1, int y1, int x2, int y2, uint32_t thickness);
void line_draw(Canvas *canvas, Line *line, uint32_t color);
Rectangle rect_init(int x_pos, int y_pos, int width, int height);
void rect_fill(Canvas *canvas, Rectangle *rect, uint32_t color);
void rect_fill_x(Canvas *canvas, size_t x, size_t y, size_t width, size_t height, uint32_t color);
Circle circle_init(int x_center, int y_center, int radius);
void circle_draw(Canvas *canvas, Circle *circle, uint32_t color);
Triangle _triangle_init(const int *p1, const int *p2, const int *p3, uint32_t color);
void triangle_draw(Canvas *canvas, Triangle *triangle, bool interpolated);

#endif //C_GRAPHICS_SHAPES_H
