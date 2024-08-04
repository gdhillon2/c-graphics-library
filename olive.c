#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void olivec_fill(uint32_t *pixels, size_t width, size_t height,
                 uint32_t color) {
    for (size_t i = 0; i < height * width; i++) {
        pixels[i] = color;
    }
}

void olivec_fill_rect(uint32_t *pixels, size_t pixels_width,
                      size_t pixels_height, int x0, int y0, int w, int h,
                      uint32_t color) {
    int x;
    int y;
    for (int dy = 0; dy < h; dy++) {
        y = y0 + dy;
        if (y < (int)pixels_height) {
            for (int dx = 0; dx < w; dx++) {
                x = x0 + dx;
                if (0 <= x && x <= (int)pixels_width) {
                    pixels[y * pixels_width + x] = color;
                }
            }
        }
    }
}

#define return_defer(value)                                                    \
    do {                                                                       \
        result = (value);                                                      \
        goto defer;                                                            \
    } while (0)

int olivec_save_to_ppm_file(const uint32_t *pixels, size_t width, size_t height,
                            const char *file_path) {
    int result = 0;
    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("failed to open");
        return_defer(errno);
    }

    const char header[] = "P6\n";
    char dimensions[64];
    snprintf(dimensions, sizeof(dimensions), "%zu %zu \n255\n", width, height);

    if ((unsigned long)write(fd, header, strlen(header)) != strlen(header) ||
        (unsigned long)write(fd, dimensions, strlen(dimensions)) !=
            strlen(dimensions)) {
        perror("failed to write header");
        return_defer(errno);
    }

    for (size_t i = 0; i < width * height; i++) {
        uint32_t pixel = pixels[i];
        uint8_t r = (pixel >> 8 * 2) & 0xFF;
        uint8_t g = (pixel >> 8 * 1) & 0xFF;
        uint8_t b = (pixel >> 8 * 0) & 0xFF;
        uint8_t rgb[3] = {r, g, b};

        if (write(fd, rgb, sizeof(rgb)) != sizeof(rgb)) {
            perror("failed to write pixels");
            return_defer(errno);
        }
    }
defer:
    if (fd >= 0) {
        if (close(fd) < 0) {
            perror("failed to close file");
            if (result == 0) {
                result = errno;
            }
        }
    }
    return result;
}
