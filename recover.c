#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //checks that one card was entered and nothing more than that.
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //opens memory card for reading
    FILE *raw_file = fopen(argv[1], "r");
    //checks that card was indeed opened and returns an error if it wasn't
    //fopen returns a pointer if successful and null if it wasn't successful
    if (raw_file == NULL)
    {
        printf("Could not open file\n");
        return 5;
    }

    //a buffer that stores 512 chunks of data
    BYTE buffer[512];

    //counts the images that were produced
    int jpeg = 0;

    //malloc is 8 times the size of char including the null character '\0' which denotes the end of a string
    char *filename = malloc(8 * sizeof(BYTE));

    //An uninitialized file pointer to use to output data gotten from the input file.
    FILE *out_file = NULL;

    // size is the size of each element to read and number is the number of elements to read at once
    //  so below we're reading 512 char sized chunks of data
    // when fread reaches the end of a file it returns an integer less than 1
    while (fread(buffer, sizeof(BYTE), 512, raw_file) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]&0xf0) == 0xE0)
        {
            //takes the string we want to write to, format string and what we want to subsitute
            sprintf(filename, "%03i.jpg", jpeg);
            out_file = fopen(filename, "w");
            jpeg++;d
        }
        if (out_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, out_file);
        }
    }

    free(filename);
    //we want to close out file down here after we've used it for all the images. Don't close it for each because we didn't make a program to reopen it for it.
    fclose(out_file);
    fclose(raw_file);
    return 0;
}