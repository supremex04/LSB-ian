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

void binaryToASCII(const char *binaryString) {
    size_t length = strlen(binaryString);
    char asciiString[length / 8 + 1]; // +1 for null terminator
    asciiString[length / 8] = '\0';

    for (size_t i = 0; i < length; i += 8) {
        char byte[9] = {0}; // 8 bits + null terminator
        strncpy(byte, binaryString + i, 8);
        asciiString[i / 8] = (char)strtol(byte, NULL, 2);
    }

    printf("ASCII representation: \n%s\n", asciiString);
}

int main(){
    read_image();
    int img_size = width * height * channels;
    int message_length = 745; // Length of the hidden message in characters
    char *bin_in = malloc((message_length * 8 + 1) * sizeof(char)); // 8 bits per character + null terminator
    bin_in[0] = '\0';

    int i = 0;
    for (unsigned char *p = img; p != img + img_size && i < message_length * 8; p++) {
        bin_in[i] = (*p & 0x01) ? '1' : '0';
        i++;
    }
    bin_in[i] = '\0';
    // printf("Binary representation of hidden message: %s\n", bin_in);
    binaryToASCII(bin_in);
    stbi_image_free(img);
    free(bin_in);

    return 0;
}