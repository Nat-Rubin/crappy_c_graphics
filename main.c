#include <stdio.h>
#include <stddef.h>
#include "colors.h"
#include "graphics.h"
#include "transformations.h"

int main(void) {
    printf("Hello, World!\n");

    /*
    // 2D testing
    Canvas canvas = canvas_init(2, 1000, 1000, colors.WHITE, "background.ppm");
    //canvas_fill(&canvas, 0xFF0000FF);
    rect_fill_x(&canvas, 100, 100, 300, 400, 0x00FF00FF);

    Rectangle rect = rect_init(600, 700, 350, 250);
    rect_fill(&canvas, &rect, 0x00FF00FF);

    Line line1 = line_init(0, 0, (int)canvas.width/4, canvas.height, 10);
    Line line2 = line_init((int)canvas.width/4, 0, 0, canvas.height, 10);
    Line line3 = line_init((int)canvas.width*3/4, 0, canvas.width, canvas.height, 10);
    Line line4 = line_init(canvas.width, 0, (int)canvas.width*3/4, canvas.height, 10);
    Line line5 = line_init(0, 500, 1000, 500, 10);
    Line line6 = line_init(500, 0, 500, 1000, 10);
    line_draw(&canvas, &line1, 0x000000FF);
    line_draw(&canvas, &line2, 0x000000FF);
    line_draw(&canvas, &line3, 0x000000FF);
    line_draw(&canvas, &line4, 0x000000FF);
    //line_draw(&canvas, &line5, 0x000000FF);
    //line_draw(&canvas, &line6, 0x000000FF);

    Circle circle = circle_init(500, 500, 200);
    circle_draw(&canvas, &circle, 0xFFFFFFFF);

    int p1[2] = {100, 100};
    int p2[2] = {800, 100};
    int p3[2] = {100, 900};
    Triangle triangle = triangle_init(p1, p2, p3, 0xFF0000FF);

    //triangle_draw(&canvas, &triangle, false);

    int p21[2] = {350, 100};
    int p22[2] = {700, 300};
    int p23[2] = {100, 350};
    Triangle triangle2 = triangle_init(p21, p22, p23, 0x0000FF80);

    //triangle_draw(&canvas, &triangle2, true);

    add_triangle(&canvas, &triangle);
    add_triangle(&canvas, &triangle2);

    canvas_update(&canvas);

    canvas_to_ppm(&canvas);

    canvas_free(&canvas);

    // 3D testing
    //
    canvas = canvas_init(3, 600, 400, colors.WHITE, "3d-test.ppm");

    int p3d1[3] = {10, 10, 50};
    int p3d2[3] = {300, 100, 0};
    int p3d3[3] = {10, 300, 20};
    Triangle tri3d_1 = triangle_init(p3d1, p3d2, p3d3, 0x00FF00FF);

    add_triangle(&canvas, &tri3d_1);

    canvas_update(&canvas);

    canvas_to_ppm(&canvas);

    canvas_free(&canvas);

    */

    //int* matrix_vector_multiply(int **m1, int m1_width, int m1_height, int *m2, int m2_height)
//    int m1[4][4] = {
//            {0, 1, 2, 3},
//            {4, 5, 6, 7},
//            {8, 9, 10, 11},
//            {12, 13, 14, 15},
//    };
//
//    int m2[4] = {
//            11,
//            22,
//            33,
//            44
//    };
//
//    int *result = matrix_vector_multiply(4, 4, m1, 4, m2);

    #include "transformations.h"

    Canvas canvas_tri_trans = canvas_init(2, 1000, 1000, colors.WHITE, "tri_1.ppm");
    canvas_fill(&canvas_tri_trans, colors.WHITE);

    int p1_1[3] = {500, 0, 0};
    int p1_2[3] = {750, 0, 0};
    int p1_3[3] = {500, 500, 0};
    Triangle tri_t = triangle_init(p1_1, p1_2, p1_3, colors.RED);
    triangle_draw(&canvas_tri_trans, &tri_t, false);
    canvas_to_ppm(&canvas_tri_trans);

    canvas_tri_trans.file_path = "tri_2.ppm";
    int distances[3] = {-400, 0, 0};
    translate_triangle(&tri_t, distances);
    canvas_fill(&canvas_tri_trans, colors.WHITE);
    triangle_draw(&canvas_tri_trans, &tri_t, false);
    canvas_to_ppm(&canvas_tri_trans);

    canvas_tri_trans.file_path = "tri_3.ppm";
    rotate_triangle(&tri_t, 2, 90);
    canvas_fill(&canvas_tri_trans, colors.WHITE);
    triangle_draw(&canvas_tri_trans, &tri_t, false);
    canvas_to_ppm(&canvas_tri_trans);

    canvas_tri_trans.file_path = "tri_4.ppm";
    int scale_factors[3] = {100, 100, 100};
    scale_triangle(&tri_t, scale_factors);
    canvas_fill(&canvas_tri_trans, colors.WHITE);
    triangle_draw(&canvas_tri_trans, &tri_t, false);
    canvas_to_ppm(&canvas_tri_trans);
    return 0;
}
