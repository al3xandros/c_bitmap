#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>
#include<assert.h>
#include <unistd.h>
#include <fcntl.h>

#include"../lib/bitmap.h"

#define IMG_WIDTH 1084
#define IMG_HEIGHT 2412
#define IMG_BPP 32
#define IMG_BPP_T uint8_t


typedef struct rgb {
    IMG_BPP_T r;
    IMG_BPP_T g;
    IMG_BPP_T b;
    IMG_BPP_T a;
} rgb_t;



rgb_t t1 (int x, int y){
    rgb_t v;
    IMG_BPP_T i = (x ^ y) % 256;
    if (i > 128)
        v.g = v.b = v.r = i;
    else
        v.g = v.b = v.r = (255-i);

    return v;
}

int array_idx(int y, int x, int z) { 
    return (y * IMG_WIDTH * 4) + x * 4 + z;
}

int main(int argc, char* argv[]){

    IMG_BPP_T* image = malloc(IMG_WIDTH * IMG_HEIGHT * 4);
    size_t img_size = IMG_WIDTH * IMG_HEIGHT * 4;

    rgb_t (*func) (int, int) = t1;

    rgb_t v;

    for (int x = 0; x < IMG_WIDTH; x++){
        for (int y = 0; y < IMG_HEIGHT; y++){
            v = func(x, y);
            /* image[y][x][0] = v.b; */
            /* image[y][x][1] = v.g; */
            /* image[y][x][2] = v.r; */
            /* image[y][x][3] = v.a; */
            image[array_idx(y, x, 0)] = v.b;
            image[array_idx(y, x, 1)] = v.g;
            image[array_idx(y, x, 2)] = v.r;
            image[array_idx(y, x, 3)] = v.a;
        }
    }


    FILE* file = fopen("image.bmp", "w");
    bitmap_write(fileno(file), IMG_WIDTH, IMG_HEIGHT, IMG_BPP, 96, 96,
                 image, img_size);
    fclose(file);
    free(image);
    return 0;
}

