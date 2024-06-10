#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int width, height, channels;
unsigned char *img;

void read_image(){
    img = stbi_load("hidden_message.png", &width, &height, &channels,0);
    if (img == NULL){
        printf("Error in loading the image \n");
        exit(1);
    }
    printf("[IMAGE LOAD SUCCESS] \nWidth: %dpx, Height: %dpx and Channels: %d \n", width, height, channels);
}


int main(){
    read_image();
    char *bin_in = malloc(200 * sizeof(char));
    bin_in[0] = '\0';

    int i = 0;
    for (unsigned char *p = img; p != img + 300; p++){
        if (i < 200) {
            bin_in[i] = (*p & 0x01) ? '1' : '0';
            i++;
        }
    }
    bin_in[i] = '\0';
    printf("Binary representation: %s\n", bin_in);
    stbi_image_free(img);
    free(bin_in);

    return 0;
}