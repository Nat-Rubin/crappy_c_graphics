//
// Created by Nathaniel Rubin on 6/12/24.
//

#ifndef C_GRAPHICS_SHAPE_FROM_TRIANGLES_H
#define C_GRAPHICS_SHAPE_FROM_TRIANGLES_H

#include <stdlib.h>
#include "triangle.h"

typedef struct ShapeFromTriangles {
    int id;
    uint64_t num_triangles;
    Triangle **triangles;
}ShapeFromTriangles;

ShapeFromTriangles ShapeFromTriangles_init(int id, Triangle **triangles, size_t num_triangles);
// void addTriangles(Triangle *triangles);
//TODO: add free function

#endif //C_GRAPHICS_SHAPE_FROM_TRIANGLES_H
