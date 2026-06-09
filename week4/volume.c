// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // declare a container of 44 bytes to hold the read header data and write from
    uint8_t header[HEADER_SIZE];
    // read and write all 44 bytes as it is
    fread(header, 44, 1, input);
    fwrite(header, 44, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    // declare a container of 16 bit to hold the buffer data
    int16_t buffer;

    // read and write 16 bits (2 bytes) at a time till EOF
    while(fread(&buffer, 2, 1, input)){
        // multiple buffer by factor, to double the volume and then write it to output file
        buffer = buffer * factor;
        fwrite(&buffer, 2, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
