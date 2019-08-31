// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // factor
    int factor = strtol(argv[1], NULL, 10);
    if (factor < 0 || factor > 100)
    {
        fprintf(stderr, "n must be positive and less than 100\n");
        return 1;
    }

    printf("Factor: %i\n", factor);

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
    printf("bfSize 1: %x\n", bf.bfSize);

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

    // Save the height and width of the old bitmap
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    // Set the width and height of the resized bitmap
    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = bi.biHeight * factor;

    // Calculate the padding of the resized bitmap
    int resizePadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Set the size of the image and the size of the bitmap file
    printf("biSizeImage 1: %x\n", bi.biSizeImage);
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + resizePadding) * abs(bi.biHeight);
    printf("biSizeImage 2: %x\n", bi.biSizeImage);

    bf.bfSize = bf.bfOffBits + bi.biSizeImage;
    printf("bfSize 2: %x\n", bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    printf("Resize padding: %i\n", resizePadding);
    // iterate over infile's scanlines
    for (int i = 0, oldHeightLocal = abs(oldHeight); i < oldHeightLocal; i++)
    {
        for (int z = 0; z < factor; z++)
        {
            printf("Z: %i\n", z);
            int startPointer = ftell(inptr);
            printf("Ftell: %li\n", ftell(inptr));
            // iterate over pixels in scanline
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < factor; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // Add padding to end of line
            for (int k = 0; k < resizePadding; k++)
            {
                fputc(0x00, outptr);
            }
            // Set pointer back to start if its not the last iteration
            if (z != factor - 1)
            {
                fseek(inptr, startPointer, SEEK_SET);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
