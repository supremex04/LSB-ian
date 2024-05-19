#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void zFill(char * dest, int num, int amount) // fills string with zeros
{
    char str [10];
    sprintf(str, "%d", num);
    int len = 0;
    while (len < amount - strlen(str))
    {
        strncat(dest, "0", 2);
        len++;
    }
    strncat(dest, str, strlen(str));
}

void save_frame(int frame, uint8_t * data) // Saves image
{
    char file[20];
    sprintf(file, "output/");
    zFill(file, frame, 6);
    strncat(file, ".png", 5);
    printf("%s\n", file);
    uint8_t image[1280 * 480 * 3]; // output image is upscales 8x
    int a = 0, b = 0;
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 160; x++)
        {
            for (int add_b = 0; add_b < 8; add_b++)
            {
                for (int add_a = 0; add_a < 8; add_a++)
                {
                    image[(a + add_a) * (b + add_b) * 1] = data[x * y * 1];
                    image[(a + add_a) * (b + add_b) * 2] = data[x * y * 2];
                    image[(a + add_a) * (b + add_b) * 3] = data[x * y * 3];
                }
            }
            a = a + 8;
        }
        a = 0;
        b = b + 8;
    }
    stbi_write_png(file, 1280, 480, 3, image, 1280 * 3);
}

int main()
{

    uint8_t image_data[160 * 60 * 3];

    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 160; x++)
        {
            image_data[x * y *1] = 128;
            image_data[x * y *2] = 128;
            image_data[x * y *3] = 128;
        }
    }

    save_frame(1, image_data);

    return 0;
}