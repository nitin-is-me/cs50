#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if(argc != 2){
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if(card == NULL){
        printf("There was a problem opening the memory card");
        return 1;
    }

    // Create a buffer for block of data
    uint8_t buffer[512];

    // global File variable
    FILE *output = NULL;
    // starting jpegcount with one so first increment leads to 0
    int jpegCount = -1;
    char filename[8];

    // While there's still data left to read from the memory card
    while(fread(buffer, 1, 512, card) == 512){
        // run this whenever a new signature is found out
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef){
            // close if a file is already open
            if(output != NULL){
                fclose(output);
            }
            jpegCount++; // increment jpegCount to increment the filename
            sprintf(filename, "%03i.jpg", jpegCount); // assign jpegCount to filename
            output = fopen(filename, "w"); // open the filename
        }
        // if any file is open, keep writing the bytes
        if(output != NULL){
        fwrite(buffer, 1, 512, output);
        }
    }
    fclose(output);
    fclose(card);

}
