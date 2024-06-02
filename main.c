#include <stdio.h>
#include "canvas.h"
#include "colors.h"
#include "shapes.h"

int main(void) {
    printf("Hello, World!\n");
    Canvas canvas = canvas_init(1000, 1000, "background.ppm");
    canvas_fill(&canvas, 0xFF0000FF);
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
    Triangle triangle = triangle_init(p1, p2, p3);

    triangle_draw(&canvas, &triangle, 0x0000FFFF, false);

    int p21[2] = {350, 100};
    int p22[2] = {700, 300};
    int p23[2] = {100, 350};
    Triangle triangle2 = triangle_init(p21, p22, p23);

    triangle_draw(&canvas, &triangle2, colors.ORANGE, true);

    canvas_to_ppm(&canvas);

    canvas_free(&canvas);
    return 0;
}
