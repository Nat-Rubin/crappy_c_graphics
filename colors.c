#include <time.h>
#include <stdlib.h>
#include <unistd.h>

uint32_t get_color_rand(void) {
    srand(time(NULL));
    return rand() % 16777216;
}
