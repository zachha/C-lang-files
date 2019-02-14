// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    int factor = atoi(argv[1]);
    // ensure proper usage
    if (argc != 4 || (factor < 1 || factor > 100))
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n factor= %i\n", factor);
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding that was in the file to be copied (old padding)
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // changing our header variables based on the multiplication factor
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    
    // determine new padding to be used in the scanlines of the new file (new padding)
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change the image size and file size according to what the new size will be after the pixels are factored by n
    bi.biSizeImage = (bi.biWidth * abs(bi.biHeight) * sizeof(RGBTRIPLE)) + (newPadding * abs(bi.biHeight));
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = (abs(bi.biHeight) / factor); i < biHeight; i++)
    {
        int counter = 0;
        printf("NEW PADDING: %i\n FACTOR: %i\n", newPadding, factor);
        do {
            // iterate over pixels in scanline
            for (int j = 0; j < (bi.biWidth / factor); j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write appropriate amount of pixels to outfile to resize horizontally
                for (int k = 0; k < factor; k++) 
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); 
                }
            }

            // then add the necessary bytes of padding
            for (int l = 0; l < newPadding; l++) 
            {
                fputc(0x00, outptr);
            }
            // reverses the file seek pointer back to the same line so the loop can continue to write lines to resize
            fseek(inptr, -((bi.biWidth / factor) * sizeof(RGBTRIPLE)), SEEK_CUR);
            // increment counter
            counter ++;
        } while (counter < factor);
     
        // skip over the old padding, if any in the input file
        fseek(inptr, oldPadding, SEEK_CUR);
        // reset counter back to 0 for next 'new' row to resize if there is one
        counter = 0;
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}