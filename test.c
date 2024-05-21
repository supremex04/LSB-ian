#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int width, height, channels;
unsigned char *img;
unsigned char *manip_img;

char *getCharInBinary(unsigned char c) {
    char *binary = malloc(9); // 8 bits + null terminator
    if (binary == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    binary[8] = '\0'; // Null terminator
    return binary;
}

void read_image(){
    img = stbi_load("sunflower.jpg", &width, &height, &channels,0);
    if (img == NULL){
        printf("Error in loading the image \n");
        exit(1);
    }
    printf("[IMAGE LOAD SUCCESS] \nWidth: %dpx, Height: %dpx and Channels: %d \n", width, height, channels);
}

int main(){
    read_image();
    size_t img_size = width * height *channels;
    manip_img = malloc(img_size);
    char input[100];
    // printf("Enter a string: ");
    // // Read input until a newline is encountered or buffer is full
    // scanf("%255[^\n]", input);
    // printf("Binary representation of the string:\n");
    // // size_t is unsigned integer type
    // for (size_t i = 0; i < strlen(input); i++) {
    //     printCharInBinary(input[i]);
    //     printf(" "); 
    // }
    printf("\n");
    for (unsigned char *p = img, *pg =manip_img; p != img + img_size; p++, pg++){

        *pg = (*p & 0xF0 );
        
    }
    for (int i = 0; i < 10; i++) {
    printf("Original: %s, Modified: %s\n",getCharInBinary(img[i]),  getCharInBinary(manip_img[i]));
    }
    stbi_write_jpg("sunflower_manip.png", width, height, channels, manip_img, 100);
    stbi_image_free(img);
    free(manip_img);
    
    
    return 0;
}