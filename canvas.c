#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "canvas.h"
#include "shapes.h"

Canvas canvas_init(size_t width, size_t height, uint32_t background_color, char* file_path) {
    Canvas canvas;
    canvas.width = width;
    canvas.height = height;
    canvas.total_pixels = width*height;
    canvas.file_path = file_path;
    canvas.pixels = malloc(sizeof(uint32_t)*canvas.total_pixels);
    canvas.background_color = background_color;
    canvas.max_triangles = 1000;
    canvas.num_triangles = 0;
    canvas.triangles = malloc(sizeof(Triangle)*canvas.max_triangles); // TODO: align with 32-bytes

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
    for (int i = 0; i < canvas->num_triangles; ++i) {
        triangle_draw(canvas, &canvas->triangles[i], false);
    }
}

void add_triangle(Canvas *canvas, Triangle *triangle) {
    memcpy(&canvas->triangles[canvas->num_triangles], triangle, sizeof(Triangle));
    canvas->num_triangles++;

    if (canvas->num_triangles == canvas->max_triangles) {
        canvas->max_triangles += 1000;
        realloc(canvas->triangles, sizeof(Triangle)*canvas->max_triangles);
    }
}

