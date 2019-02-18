#include <stdio.h>
#include <stdlib.h>

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
    
    // start reading the image file by 512 bytes
    int checkForEOF = fread(buffer, 512, 1, inptr);
    
    if (checkForEOF != 512) 
    {
        // check the first 4 bytes of each 512 byte block for JPEG headers
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            int picCount = 0;
            sprintf(filename, "%03i.jpg", picCount);
            FILE *img = fopen(filename, "w");
            // for creating outfiles for jpegs
            //char *outfile = "";
        } else {
            fread(buffer, 512, 1, inptr);
    } else {
        // if checkForEOF is not 512, that means we have reached the end of file so we should terminate the program
        fclose(inputr);
        
        // program success
        return 0;

    }
}
