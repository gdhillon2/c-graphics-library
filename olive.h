#ifndef OLIVE_H
#define OLIVE_H

#include <stddef.h>
#include <stdint.h>

/**
 * Fills the pixel array with the given color.
 *
 * @param pixels Pointer to the pixel array.
 * @param width Width of the image.
 * @param height Height of the image.
 * @param color Color to fill the pixels with.
 */
void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color);

/**
 * Saves the pixel array to a PPM file.
 *
 * @param pixels Pointer to the pixel array.
 * @param width Width of the image.
 * @param height Height of the image.
 * @param file_path Path to the output file.
 * @return 0 on success, or a non-zero error code on failure.
 */
int olivec_save_to_ppm_file(const uint32_t *pixels, size_t width, size_t height,
                            const char *file_path);

/**
 * Fills a rectangle area in the pixel array with the given color.
 *
 * @param pixels Pointer to the pixel array.
 * @param pixels_width Width of the pixel array.
 * @param pixels_height Height of the pixel array.
 * @param x0 X-coordinate of the top-left corner of the rectangle.
 * @param y0 Y-coordinate of the top-left corner of the rectangle.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 * @param color Color to fill the rectangle with.
 */
void olivec_fill_rect(uint32_t *pixels, size_t pixels_width,
                      size_t pixels_height, int x0, int y0, int w, int h,
                      uint32_t color);
#endif /* OLIVE_H */
