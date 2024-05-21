#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printCharInBinary(unsigned char c) {
    for (int i = 7; i >= 0; i--) {
        // bitwise and with each bit
        printf("%d",(c & (1 << i)) ? 1 : 0);
    }
}

int main(){
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