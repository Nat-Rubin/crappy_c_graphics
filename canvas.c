#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "canvas.h"
#include "shapes.h"

Canvas canvas_init(uint32_t mode, size_t width, size_t height, uint32_t background_color, char* file_path) {
    Canvas canvas;
    canvas.mode = mode;
    canvas.width = width;
    canvas.height = height;
    canvas.total_pixels = width*height;
    canvas.file_path = file_path;
    canvas.pixels = malloc(sizeof(uint32_t)*canvas.total_pixels);
    canvas.background_color = background_color;
    canvas.max_shapes = 1000;
    canvas.num_shapes = 0;
    //canvas.triangles = malloc(sizeof(Triangle)*canvas.max_triangles); // TODO: align with 32-bytes
    canvas.shapes = malloc(sizeof(ShapeFromTriangles)*canvas.max_shapes);

    return canvas;
}

bool canvas_to_ppm(Canvas *canvas) {
    FILE *file = NULL;

    file = fopen(canvas->file_path, "wb");
    if (file == NULL) {
        printf("NULL");
    }

    fprintf(file, "P6\n%zu %zu\n255\n", canvas->width, canvas->height);
    for (size_t i = 0; i < canvas->width * canvas->height; ++i) {
        uint32_t pixel = canvas->pixels[i];
        uint8_t bytes[3] = {
                (pixel>>(8*3))&0xFF,
                (pixel>>(8*2))&0xFF,
                (pixel>>(8*1))&0xFF,
        };

        fwrite(bytes, sizeof(bytes),1, file);
        if (ferror(file)) printf("Error!");
    }
    fclose(file);

    return true;
}

bool canvas_free(Canvas *canvas) {
    // Doesn't actually "free" the canvas because canvas is allocated on stack. Only frees canvas.pixels
    free(canvas->pixels);
    return true;
}

void canvas_fill(Canvas *canvas, uint32_t color) {
    for (size_t i = 0; i < canvas->total_pixels; ++i) {
        canvas->pixels[i] = color;
    }
}

/***
 * Updates the canvas. Draws background and then draws triangles.
 * @param canvas
 */
void canvas_update(Canvas *canvas) {
    canvas_fill(canvas, canvas->background_color);
    for (size_t i = 0; i < canvas->num_shapes; ++i) {
        ShapeFromTriangles *shape = &canvas->shapes[i];
        for (size_t j = 0; j < shape->num_triangles; ++j) {
            triangle_draw(canvas, shape->triangles[i], false);
        }
    }
}

//TODO: store pointers not copies?
void add_shapes(Canvas *canvas, Triangle *shape) {
    memcpy(&canvas->shapes[canvas->num_shapes], shape, sizeof(Triangle));
    canvas->num_shapes++;

    if (canvas->num_shapes == canvas->max_shapes) {
        canvas->max_shapes += 1000;
        realloc(canvas->shapes, sizeof(Triangle)*canvas->max_shapes);
    }
}

