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

void rect_fill(Canvas *canvas, Rectangle *rect, uint32_t color) {
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
            if ((pow((double)i-circle->y_center,2) + pow((double)j-circle->x_center,2) - pow(r,2)) <= 0) {
                int current_index = (int)((i*canvas->width+j));
                pixels[current_index] = color;
            }
        }
    }
}

Triangle triangle_init(const int *p1, const int *p2, const int *p3, uint32_t color) {
    return triangle_init_tri(p1, p2, p3, color);
}

/***
 * Finds the min of 3 values
 * @return
 */
int min_3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

/***
 * Finds the max of 3 values
 * @return
 */
int max_3(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

int edge(const int p1[2], const int p2[2], const int p3[2]) {
    return (p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0]);
}

void triangle_draw(Canvas *canvas, Triangle *triangle, bool interpolated) {
    // Currently clock-wise. idk why cuz should be edge >=0 but is currently edge <= 0
    int *p1 = triangle->p1;
    int *p2 = triangle->p2;
    int *p3 = triangle->p3;
    uint32_t *pixels = canvas->pixels;

    int min_x = min_3(p1[0], p2[0], p3[0]);
    int max_x = max_3(p1[0], p2[0], p3[0]);
    int min_y = min_3(p1[1], p2[1], p3[1]);
    int max_y = max_3(p1[1], p2[1], p3[1]);

    int point[2];
    for (size_t i = min_y; i < max_y; ++i) {
        for (size_t j = min_x; j < max_x; ++j) {
            point[0] = (int)j;
            point[1] = (int)i;
            int p1p2p3 = edge(p1, p2, p3);
            int p1p2 = edge(p1, p2, point);
            int p2p3 = edge(p2, p3, point);
            int p3p1 = edge(p3, p1, point);

            if (p1p2 <= 0 && p2p3 <= 0 && p3p1 <= 0) {
                int current_index = (int)(i*canvas->width+j);

                if (interpolated) {
                    float weight_p1 = (float)p2p3 / (float)p1p2p3;
                    float weight_p2 = (float)p3p1 / (float)p1p2p3;
                    float weight_p3 = (float)p1p2 / (float)p1p2p3;

                    uint8_t color_r = (uint8_t)(0xFF*weight_p1);
                    uint8_t color_g = (uint8_t)(0xFF*weight_p2);
                    uint8_t color_b = (uint8_t)(0xFF*weight_p3);

                    uint32_t inter_color = (color_r << 3*8) | (color_g << 2*8) | (color_b << 1*8) | 0xFF;
                    pixels[current_index] = inter_color;
                } else {
                    float triangle_alpha = (float)(triangle->color & 0xFF)/255;  // over
                    uint32_t alpha = (uint32_t)(triangle_alpha*(float)(triangle->color >> 1*8) + (float)(pixels[current_index] >> 1*8)*(1-triangle_alpha));
                    alpha = (alpha << 1*8) | 0xFF;
                    pixels[current_index] = alpha;
                    //pixels[current_index] = triangle->color;
                }
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
