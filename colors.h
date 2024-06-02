#include <stdint.h>

#ifndef C_GRAPHICS_COLORS_H
#define C_GRAPHICS_COLORS_H

typedef struct Colors{
    uint32_t RED;
    uint32_t GREEN;
    uint32_t BLUE;
    uint32_t YELLOW;
    uint32_t PURPLE;
    uint32_t CYAN;
    uint32_t ORANGE;
} Colors;

Colors colors = {
        .RED = 0xFF000000,
        .GREEN = 0x00FF0000,
        .BLUE = 0x0000FF00,
        .YELLOW = 0xFFFF0000,
        .PURPLE = 0xFF00FF00,
        .CYAN = 0x00FFFF00,
        .ORANGE = 0xFFA50000,
};

uint32_t get_color_rand(void);

#endif //C_GRAPHICS_COLORS_H
