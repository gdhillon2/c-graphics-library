#include "olive.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define ROWS 6
#define COLS 8

#define CELL_WIDTH (WIDTH / COLS)
#define CELL_HEIGHT (HEIGHT / ROWS)

uint32_t pixels[WIDTH * HEIGHT];

void checker_example(void) {
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF202020);

    for (int i = 0; i < ROWS * COLS; i++) {
        int col = i % COLS;
        int row = i / COLS;

        if ((row + col) % 2 == 1) {
            olivec_fill_rect(pixels, WIDTH, HEIGHT, col * CELL_WIDTH,
                             row * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT,
                             0xFF2020FF);
        }
    }
}

int main(void) {
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF202020);
    checker_example();
    if (olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, "output.ppm") != 0) {
        perror("failed to save ppm file");
    }
    return 0;
}
