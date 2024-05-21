#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int width, height, channels;
unsigned char *img;

void printCharInBinary(unsigned char c) {
    for (int i = 7; i >= 0; i--) {
        // bitwise and with each bit
        printf("%d",(c & (1 << i)) ? 1 : 0);
    }
}

void read_image(){
    img = stbi_load("sunflower.jpg", &width, &height, &channels,0);
    if (img == NULL){
        printf("Error in loading the image \n");
        exit(1);
    }
    printf("[IMAGE LOAD SUCCESS] \nWidth: %dpx, Height: %dpx and channels: %d \n", width, height, channels);
}

int main(){
    int width, height, channels;
    unsigned char *img = stbi_load("sunflower.jpg", &width, &height, &channels,0);
    if (img == NULL){
        printf("Error in loading the image \n");
        exit(1);
    }
    printf("[IMAGE LOAD SUCCESS] \nWidth: %dpx, Height: %dpx and channels: %d \n", width, height, channels);
    char input[100];
    printf("Enter a string: ");
    // Read input until a newline is encountered or buffer is full
    scanf("%255[^\n]", input);
    printf("Binary representation of the string:\n");
    // size_t is unsigned integer type
    for (size_t i = 0; i < strlen(input); i++) {
        printCharInBinary(input[i]);
        printf(" "); 
    }

    printf("\n");
    
    return 0;
}