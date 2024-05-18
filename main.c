#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main() {
    int width, height, channels;
    unsigned char *img = stbi_load("sunflower.jpg", &width, &height, &channels,0);
    if (img == NULL){
        printf("Error in loading the image \n");
        exit(1);
    }
    printf("[IMAGE LOAD SUCCESS] \nWidth: %dpx, Height: %dpx and channels: %d \n", width, height, channels);
    return 0;
}
