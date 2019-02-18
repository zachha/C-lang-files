#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    // open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    
    typedef uint8_t  BYTE;

    //card.raw is in 512 byte blocks.
    BYTE *buffer = malloc(512 * sizeof(BYTE));
    //buffer = malloc(512);

    // declare our variables
    int picFound = 0;
    char filename[8];
    int picCount = 0;
    FILE *img = NULL;
    
    // loops through the raw file to look for JPEGS and writes the JPEG files for those it finds
    while (fread(buffer, 1, 512, inptr) == 512) 
    {
        // check the first 4 bytes of each 512 byte block for JPEG headers
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // begins to write everything new files now that the first headers have been found
            picFound = 1;
            // closes image file if one is already opened
            if (img != NULL) 
            {
                fclose(img);
                picCount++;
            }
            // keeps track of filename for each image
            sprintf(filename, "%03i.jpg", picCount);
            char *outfile = filename;
            // for creating outfiles for jpegs
            img = fopen(outfile, "w");
            fwrite(buffer, 1, 512, img);
            
        } 
        else
        {
            // continues writing to JPEG until the next headers are found
            if (picFound == 1) 
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    } 
    // if checkForEOF is not 512, that means we have reached the end of file so we should terminate the program
    fclose(inptr);
    fclose(img);
    // free up memory allocated to buffer
    free(buffer);
    
        
    // program success
    return 0;
}

