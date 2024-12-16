#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <stdint.h>
#include <stddef.h>

typedef struct __attribute__((packed)) bitmap_header {
    uint16_t indicator;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
} bitmap_header_t;

typedef struct __attribute__((packed)) bitmap_dib_header {
    /* implementing BITMAPINFOHEADER header type */
    uint32_t size;
     int32_t bitmap_width;
     int32_t bitmap_height;

    uint16_t num_of_color_panes;
    uint16_t bits_per_pixel;

    uint32_t compression_method;
    uint32_t raw_bitmap_size;
     int32_t horizontal_resolution;
     int32_t vertical_resolution;
    uint32_t number_of_color_palette_colors;
    uint32_t num_of_important_colors;

} bitmap_dib_header_t;

void bitmap_write(int fd, int32_t width, int32_t height, uint16_t bpp,
                  int32_t h_resolution, int32_t v_resolution,
                  void* bitmap, size_t bitmap_size /* in bytes */);


#endif /* __BITMAP_H__ */
