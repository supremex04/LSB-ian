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
    read_image();
    size_t img_size = width * height *channels;
    manip_img = malloc(img_size);
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
    for (unsigned char *p = img, *pg =manip_img; p != img + img_size; p += 1, pg +=1){

        *pg = (uint8_t)(*p | (0x7F) );
        
    }
    stbi_write_jpg("sunflower_manip.png", width, height, channels, manip_img, 100);
    stbi_image_free(img);
    free(manip_img);
    
    
    return 0;
}