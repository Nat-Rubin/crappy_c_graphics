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
    uint32_t BLACK;
    uint32_t WHITE;
} Colors;

Colors colors = {
        .RED = 0xFF0000FF,
        .GREEN = 0x00FF00FF,
        .BLUE = 0x0000FFFF,
        .YELLOW = 0xFFFF00FF,
        .PURPLE = 0xFF00FFFF,
        .CYAN = 0x00FFFFFF,
        .ORANGE = 0xFFA500FF,
        .BLACK = 0x000000FF,
        .WHITE = 0xFFFFFFFF,
};

uint32_t get_color_rand(void);

#endif //C_GRAPHICS_COLORS_H
