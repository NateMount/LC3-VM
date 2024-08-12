#include <stdint.h>
#include <stdio.h>

#include "core.h"
#include "image-manager.h"
#include "util.h"

void read_image_file(FILE* file){
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, file);
    origin = swap16(origin);

    uint16_t max_read = MEM_MAX - origin;
    uint16_t* p = memory + origin;
    size_t read = fread(p, sizeof(uint16_t), max_read, file);

    // Swap to little endian
    while (read-- > 0){
        *p = swap16(*p);
        ++p;
    }
}

int read_image(const char* image_path){
    FILE* file = fopen(image_path, "rb");
    if (!file) {return 0;}
    read_image_file(file);
    fclose(file);
    return 1;
}