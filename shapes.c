#include <stdint.h>
#include <math.h>
#include <string.h>
#include "canvas.h"
#include "shapes.h"

Line line_init(int x1, int y1, int x2, int y2, uint32_t thickness) {
    Line line = {
            .x1 = x1,
            .y1 = y1,
            .x2 = x2,
            .y2 = y2,
            .thickness = thickness,
    };
    return line;
}

void line_draw(Canvas *canvas, Line *line, uint32_t color) {
    // TODO: Fix horizontal and vertical lines
    // y = mx+b
    float x2 = (float)line->x2;
    float x1 = (float)line->x1;
    float y2 = (float)line->y2;
    float y1 = (float)line->y1;
    uint32_t *pixels = canvas->pixels;
    float m = (y2 - y1) / (x2 - x1);
    for (size_t i = (size_t) y1; i < canvas->height; ++i) {
        for (size_t j = 0; j < canvas->width; ++j) {
            float b = y1-m*x1;
            size_t x = (size_t)(((float)i - b) / m);
            x = i*canvas->width+x;
            int current_index = (int)((i*canvas->width+j));
            size_t lower_bound = x-line->thickness/2;
            size_t upper_bound = x+line->thickness/2;
            if (lower_bound > upper_bound) lower_bound = 0;
            if (lower_bound <= current_index && current_index <= upper_bound) {
                pixels[current_index] = color;
            }
            if ((float)i*(float)canvas->width >= y2*(float)canvas->width && (float)j > x2) {
                break;
            }
        }
    }
}

Rectangle rect_init(int x_pos, int y_pos, int width, int height) {
    Rectangle rect = {
        .x_pos = x_pos,
        .y_pos = y_pos,
        .width = width,
        .height = height,
    };
    return rect;
}

Rectangle rect_fill(Canvas *canvas, Rectangle *rect, uint32_t color) {
    uint32_t *pixels = canvas->pixels;
    size_t x2 = rect->x_pos+rect->width-1;
    size_t y2 = rect->y_pos+rect->height-1;
    for (size_t i = 0; i < canvas->width; ++i) {
        for (size_t j = 0; j < canvas->height; ++j) {
            if ((rect->x_pos <= j && j <= x2) && (rect->y_pos <= i && i <= y2)) {
                pixels[i*canvas->width+j] = color;
            }
        }

    }
}

void rect_fill_x(Canvas *canvas, size_t x, size_t y, size_t width, size_t height, uint32_t color) {
    uint32_t *pixels = canvas->pixels;
    size_t x2 = x+width-1;
    size_t y2 = y+height-1;
    for (size_t i = 0; i < canvas->width; ++i) {
        for (size_t j = 0; j < canvas->height; ++j) {
            if ((j >= x && j <= x2) && (i >= y && i <= y2)) {
                pixels[i*canvas->width+j] = color;
            }
        }

    }
}

Circle circle_init(int x_center, int y_center, int radius) {
    Circle circle = {
            .x_center = x_center,
            .y_center = y_center,
            .radius = radius,
    };
    return circle;
}

void circle_draw(Canvas *canvas, Circle *circle, uint32_t color) {
    // F(p) = x^2 + y^2 - r^2
    int r = circle->radius;
    uint32_t *pixels = canvas->pixels;

    for (size_t i = 0; i < canvas->height; ++i) {
        for (size_t j = 0; j < canvas->width; ++j) {
//            int y = (int) i;//(int)i*(int)canvas->width;
//            int x = h + (int)(sqrt(pow(r,2) - pow((y-k),2)));
//            int current_index = (int)((i*canvas->width+j));
//            if (current_index == x*canvas->width) {
//                pixels[current_index] = color;
//            }
            if ((pow((double)i-circle->y_center,2) + pow((double)j-circle->x_center,2) - pow(r,2)) <= 0) {
                int current_index = (int)((i*canvas->width+j));
                pixels[current_index] = color;
            }
        }
    }
}

Triangle triangle_init(const int p1[2], const int p2[2], const int p3[2]) {
    Triangle triangle;
    memcpy(triangle.p1, p1, sizeof(int)*2);
    memcpy(triangle.p2, p3, sizeof(int)*2);
    memcpy(triangle.p3, p2, sizeof(int)*2);
    return triangle;
}

int edge(const int p1[2], const int p2[2], const int p3[2]) {
    return (p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0]);
}

void triangle_draw(Canvas *canvas, Triangle *triangle, uint32_t color) {
    // Currently clock-wise. idk why cuz should be edge >=0 but is currently edge <= 0
    int *p1 = triangle->p1;
    int *p2 = triangle->p2;
    int *p3 = triangle->p3;
    uint32_t *pixels = canvas->pixels;

    int point[2];
    for (size_t i = 0; i < canvas->height; ++i) {
        for (size_t j = 0; j < canvas->width; ++j) {
            point[0] = (int)j;
            point[1] = (int)i;
            int p1p2 = edge(p1, p2, point);
            int p2p3 = edge(p2, p3, point);
            int p3p1 = edge(p3, p1, point);

            if (p1p2 <= 0 && p2p3 <= 0 && p3p1 <= 0) {
                int current_index = (int)((i*canvas->width+j));
                pixels[current_index] = color;
            }
        }
    }



//    // for 3d, back facing triangles
//    if (edge < 0) {
//        return;
//    }
//    if (edge >= 0) {
//        //point inside edge
//    }


}