//
// Created by Nathaniel Rubin on 6/13/24.
//

#ifndef C_GRAPHICS_TRANSLATIONS_H
#define C_GRAPHICS_TRANSLATIONS_H

#include "shape_from_triangles.h"

typedef struct TransformationM {
    int matrix[4][4];
} TransformationM;

int* matrix_vector_multiply(int m1_width, int m1_height, double m1[][m1_height], int m2_height, int m2[m2_height]);
void translate_triangle(Triangle *triangle, int distances[3]);
void translation(ShapeFromTriangles *shape, int distances[3]);
void rotate_triangle(Triangle *triangle, int axis, double degrees);
void rotation(ShapeFromTriangles *shape, int axis, double degrees);
#endif //C_GRAPHICS_TRANSLATIONS_H
