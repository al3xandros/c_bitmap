#include <stddef.h>
#include <assert.h>
#include <unistd.h>

#include "bitmap.h"


void bitmap_write(int fd, int32_t width, int32_t height, uint16_t bpp,
                  int32_t h_resolution, int32_t v_resolution,
                  void* bitmap, size_t bitmap_size /* in bytes */) {
    bitmap_header_t     hdr     = {0};
    bitmap_dib_header_t dib_hdr = {0};

    assert(bpp == 1 || bpp == 4 || bpp == 8 || bpp == 16 || bpp == 24
            || bpp == 32);

    hdr.indicator   = 0x4D42; // BM
    hdr.filesize    = sizeof(hdr) + sizeof (dib_hdr) + bitmap_size;
    hdr.data_offset = sizeof(hdr) + sizeof (dib_hdr);
    
    dib_hdr.size = sizeof(dib_hdr);  // should be 40
    dib_hdr.bitmap_width = width;
    dib_hdr.bitmap_height = height;
    dib_hdr.num_of_color_panes = 1;
    dib_hdr.bits_per_pixel = bpp;
    dib_hdr.compression_method = 0;  // BI_RGB
    dib_hdr.raw_bitmap_size = 0;  // because its a BI_RGB
    dib_hdr.horizontal_resolution = h_resolution;
    dib_hdr.vertical_resolution = v_resolution;
    dib_hdr.number_of_color_palette_colors = 0;
    dib_hdr.num_of_important_colors = 0;

    write(fd, &hdr, sizeof(hdr));
    write(fd, &dib_hdr, sizeof(dib_hdr));
    write(fd, bitmap, bitmap_size);
}

