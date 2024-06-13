//
// Created by Nathaniel Rubin on 6/13/24.
//

#include <printf.h>
#include "transformations.h"

int translation_mat[4][4] = {
                { 1, 0, 0, -1 },
                { 0, 1, 0, -1 },
                { 0, 0, 1, -1 },
                { 0, 0, 0,  1 },
};

int* matrix_vector_multiply(int m1_width, int m1_height, int m1[][m1_height], int m2_height, int m2[m2_height]) {
    int* result = (int*)calloc(m1_height*1, sizeof(int));
    for (size_t i = 0; i < m1_width; ++i) {
        for (size_t j = 0; j < m1_height; ++j) {
            int m1_i_j = m1[i][j];
            result[i] += m1[i][j]*m2[j];
        }
    }
    return result;
}

// TODO: make matrix struct?
//int* matrix_multiply(int **m1, int m1_width, int m1_height, int **m2, int m2_width, int m2_height) {
//    int* result = (int*)malloc(sizeof(int)*m1_height*m2_width);
//    for (size_t i = 0; i < m; ++i) {
//
//    }
//}

void translate_point(int point[3], int distances[3]){
    int T_x = distances[0];
    int T_y = distances[1];
    int T_z = distances[2];

    translation_mat[0][3] = T_x;
    translation_mat[1][3] = T_y;
    translation_mat[2][3] = T_z;

    int *coords_new;
    int coords_old[4];
    coords_old[0] = point[0];
    coords_old[1] = point[1];
    coords_old[2] = point[2];
    coords_old[3] = 1;

    coords_new = matrix_vector_multiply(4, 4, translation_mat, 4, coords_old);
    point[0] = coords_new[0];
    point[1] = coords_new[1];
    point[2] = coords_new[2];
}

void translate_triangle(Triangle *triangle, int distances[3]) {
    translate_point(triangle->p1, distances);
    translate_point(triangle->p2, distances);
    translate_point(triangle->p3, distances);
}

void translation(ShapeFromTriangles *shape, int distances[3]) {
    for (size_t i = 0; i < shape->num_triangles; ++i) {
        translate_triangle(shape->triangles[i], distances);
    }
}