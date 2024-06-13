//
// Created by Nathaniel Rubin on 6/12/24.
//

#include <stdlib.h>
#include "shape_from_triangles.h"

ShapeFromTriangles ShapeFromTriangles_init(int id, Triangle **triangles, size_t num_triangles) {
    ShapeFromTriangles shape;
    shape.id = id;
    shape.num_triangles = num_triangles;
    shape.triangles = malloc(sizeof(Triangle*)*num_triangles);
    for (size_t i = 0; i < num_triangles; ++i) {
        shape.triangles[i] = triangles[i];
    }
    return shape;
}