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
    

    size_t img_size = width * height *channels;
    int grey_channels = channels == 4 ? 2 : 1;
    size_t grey_img_size = width * height * grey_channels;
    unsigned char *grey_img = malloc(grey_img_size);
    if (grey_img == NULL){
        printf("Error allocating space to greyscale image!");
    }
    unsigned int combined_color = (img[0] << 16) | (img[1] << 8) | img[2];
    printf("First pixel RGB: #%06X\n", combined_color);
    
    for (unsigned char *p = img, *pg =grey_img; p != img +img_size; p += channels, pg += grey_channels ){

        *pg = (uint8_t)((*p + *(p+1) +*(p+2))/3.0);
        if (channels == 4){
            *(pg+1) = *(p+3);
        }
    }
    stbi_write_jpg("sunflower_grey.png", width, height, grey_channels, grey_img, 100);
    stbi_image_free(img);
    free(grey_img);
    return 0;
}
