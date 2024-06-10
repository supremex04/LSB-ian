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
char input[] = "Two roads diverged in a yellow wood,\n"
"And sorry I could not travel both\n"
"And be one traveler, long I stood\n"
"And looked down one as far as I could\n"
"To where it bent in the undergrowth;\n"
"\n"
"Then took the other, as just as fair,\n"
"And having perhaps the better claim,\n"
"Because it was grassy and wanted wear;\n"
"Though as for that the passing there\n"
"Had worn them really about the same,\n"
"\n"
"And both that morning equally lay\n"
"In leaves no step had trodden black.\n"
"Oh, I kept the first for another day!\n"
"Yet knowing how way leads on to way,\n"
"I doubted if I should ever come back.\n"
"\n"
"I shall be telling this with a sigh\n"
"Somewhere ages and ages hence:\n"
"Two roads diverged in a wood, and I—\n"
"I took the one less traveled by,\n"
"And that has made all the difference.\n"
"-Robert Frost";
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
    char *bin_in = malloc(strlen(input)*8 +1);

    bin_in[0] = '\0';
    for (size_t i = 0; i < strlen(input); i++) {
        char *binary = getCharInBinary(input[i]);
        strcat(bin_in, binary);
        free(binary); // Free the allocated memory for each binary string
    }
    
    printf("Binary representation of the input string: %s\n", bin_in);
    
    int i = 0;
    for (unsigned char *p = img, *pg =manip_img; p != img + img_size; p++, pg++){
        
        if ( i< strlen(bin_in)){
            if (bin_in[i] == '1'){
                *pg = (*p | 0x01 );
            }
            if (bin_in[i] == '0'){
                *pg = (*p & 0xFE );
            }
            i++;
        }
        else{
            *pg = *p ;
        }
        
        
    }
    for (int i = 0; i < (strlen(input)*8); i++) {
        printf("Original: %s, Modified: %s\n",getCharInBinary(img[i]),  getCharInBinary(manip_img[i]));
    }
    stbi_write_png("hidden_message.png", width, height, channels, manip_img, width * channels);
    stbi_image_free(img);
    free(manip_img);
    
    
    return 0;
}