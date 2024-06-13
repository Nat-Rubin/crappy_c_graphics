//
// Created by Nathaniel Rubin on 6/13/24.
//

#include <printf.h>
#include <math.h>
#include "transformations.h"

double translation_mat[4][4] = {
                { 1, 0, 0, -1 },
                { 0, 1, 0, -1 },
                { 0, 0, 1, -1 },
                { 0, 0, 0,  1 },
};

double rotation_mat_x[4][4] = {
        { 1,  0,  0, 0 },
        { 0, -1, -1, 0 },
        { 0, -1, -1, 0 },
        { 0,  0,  0, 1 },
};

double rotation_mat_y[4][4] = {
        { -1,  0, -1, 0 },
        {  0, -1,  0, 0 },
        { -1,  0, -1, 0 },
        {  0,  0,  0, 1 },
};

double rotation_mat_z[4][4] = {
        { -1, -1, 0, 0 },
        { -1, -1, 0, 0 },
        {  0,  0, 1, 0 },
        {  0,  0, 0, 1 },
};

double scaling_mat[4][4] = {
        { -1,  0,  0, 0 },
        {  0, -1,  0, 0 },
        {  0,  0, -1, 0 },
        {  0,  0,  0, 1 },
};

int* matrix_vector_multiply(int m1_width, int m1_height, double m1[][m1_height], int m2_height, int m2[m2_height]) {
    int* result = (int*)calloc(m1_height*1, sizeof(int));
    for (size_t i = 0; i < m1_width; ++i) {
        for (size_t j = 0; j < m1_height; ++j) {

            double m1_i_j = m1[i][j];
            result[i] += (int)(m1[i][j]*m2[j]);
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
    free(coords_new);
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

void rotate_point(int point[3], int axis, double degrees) {
    int *coords_new;
    int coords_old[4];
    coords_old[0] = point[0];
    coords_old[1] = point[1];
    coords_old[2] = point[2];
    coords_old[3] = 1;

    switch (axis) {
        case 0:
            rotation_mat_x[1][1] = (int)cos(degrees*(M_PI/180));
            rotation_mat_x[1][2] = (int)-sin(degrees*(M_PI/180));
            rotation_mat_x[2][1] = (int)sin(degrees*(M_PI/180));
            rotation_mat_x[2][2] = (int)cos(degrees*(M_PI/180));
            coords_new = matrix_vector_multiply(4, 4, rotation_mat_x, 4, coords_old);
            break;
        case 1:
            rotation_mat_y[0][0] = (int)cos(degrees*(M_PI/180));
            rotation_mat_y[0][2] = (int)sin(degrees*(M_PI/180));
            rotation_mat_y[2][0] = (int)-sin(degrees*(M_PI/180));
            rotation_mat_y[2][2] = (int)cos(degrees*(M_PI/180));
            coords_new = matrix_vector_multiply(4, 4, rotation_mat_y, 4, coords_old);
            break;
        case 2:
            rotation_mat_z[0][0] = cos(degrees*(M_PI/180));
            rotation_mat_z[0][1] = -sin(degrees*(M_PI/180));
            rotation_mat_z[1][0] = sin(degrees*(M_PI/180));
            rotation_mat_z[1][1] = cos(degrees*(M_PI/180));
            coords_new = matrix_vector_multiply(4, 4, rotation_mat_z, 4, coords_old);
            break;
        default:
            printf("Bad Axis");
            return;
    }

    point[0] = coords_new[0];
    point[1] = coords_new[1];
    point[2] = coords_new[2];
    free(coords_new);
}

void rotate_triangle(Triangle *triangle, int axis, double degrees) {
    rotate_point(triangle->p1, axis, degrees);
    rotate_point(triangle->p2, axis, degrees);
    rotate_point(triangle->p3, axis, degrees);
}

// x-axis = 0, y-axis = 1, z-axis = 2
//TODO: check if positive and negative degrees works
void rotation(ShapeFromTriangles *shape, int axis, double degrees) {
    for (size_t i = 0; i < shape->num_triangles; ++i) {
        rotate_triangle(shape->triangles[i], axis, degrees);
    }
}

void scale_point(int point[3], int scale_factors[3]) {
    int *coords_new;
    int coords_old[4];
    coords_old[0] = point[0];
    coords_old[1] = point[1];
    coords_old[2] = point[2];
    coords_old[3] = 1;

    scaling_mat[0][0] = scale_factors[0];
    scaling_mat[1][1] = scale_factors[1];
    scaling_mat[2][2] = scale_factors[2];

    coords_new = matrix_vector_multiply(4, 4, scaling_mat, 4, coords_old);

    point[0] = coords_new[0];
    point[1] = coords_new[1];
    point[2] = coords_new[2];
    free(coords_new);
}

void scale_triangle(Triangle *triangle, int scale_factors[3]) {
    scale_point(triangle->p1, scale_factors);
    scale_point(triangle->p2, scale_factors);
    scale_point(triangle->p3, scale_factors);
}

// x-axis = 0, y-axis = 1, z-axis = 2
//TODO: check if positive and negative degrees works
void scaling(ShapeFromTriangles *shape, int scale_factors[3]) {
    for (size_t i = 0; i < shape->num_triangles; ++i) {
        scale_triangle(shape->triangles[i], scale_factors);
    }
}