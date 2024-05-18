#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

int main() {
    // Open the JPEG file
    FILE *infile = fopen("test.jpg", "rb");
    if (!infile) {
        fprintf(stderr, "Error: Unable to open file\n");
        return 1;
    }

    // Initialize libjpeg structures
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Specify the source of the compressed data (the file)
    jpeg_stdio_src(&cinfo, infile);

    // Read the JPEG header
    jpeg_read_header(&cinfo, TRUE);

    // Start decompressor
    jpeg_start_decompress(&cinfo);

    // Allocate memory for the pixel buffer
    int row_stride = cinfo.output_width * cinfo.output_components;
    unsigned char *buffer = (unsigned char *)malloc(row_stride * cinfo.output_height);

    // Read scanlines one at a time
    unsigned char *row_pointer = buffer;
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, &row_pointer, 1);
        row_pointer += row_stride;
    }

    // Finish decompression
    jpeg_finish_decompress(&cinfo);

    // Destroy the decompression structure
    jpeg_destroy_decompress(&cinfo);

    // Close the input file
    fclose(infile);

    // Print pixel values
    printf("Pixel values:\n");
    for (int y = 0; y < cinfo.output_height; y++) {
        unsigned char *row = buffer + y * row_stride;
        for (int x = 0; x < cinfo.output_width; x++) {
            printf("(%02X,%02X,%02X) ", row[x * cinfo.output_components], row[x * cinfo.output_components + 1], row[x * cinfo.output_components + 2]);
        }
        printf("\n");
    }

    // Free the allocated memory
    free(buffer);

    return 0;
}
