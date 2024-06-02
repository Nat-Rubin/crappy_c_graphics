//
// Created by Nathaniel Rubin on 6/2/24.
//

#ifndef C_GRAPHICS_TRIANGLE_H
#define C_GRAPHICS_TRIANGLE_H

typedef struct Triangle {
    // clockwise
    int p1[2];
    int p2[2];
    int p3[2];
} Triangle;

Triangle triangle_init_tri(const int *p1, const int *p2, const int *p3);

#endif //C_GRAPHICS_TRIANGLE_H
