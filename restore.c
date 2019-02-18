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
    int buffer;
    int picCount = 0;
    
    // loops through the raw file to look for JPEGS and writes the JPEG files for those it finds
    while (fread(&buffer, 512, 1, inptr) == 512) 
    {
        // check the first 4 bytes of each 512 byte block for JPEG headers
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // for creating outfiles for jpegs
            sprintf(filename, "%03i.jpg", picCount);
            //char *outfile = filename;
            FILE *img = fopen(filename, "w");
            fwrite(&buffer, 512, 1, img);
            fclose(img);
            picCount++;
        } 
    } 
    
    // if checkForEOF is not 512, that means we have reached the end of file so we should terminate the program
    fclose(inputr);
        
    // program success
    return 0;
}
