#include <stdio.h>
#include <stdlib.h>

int foundFirstJPEG(FILE *inputFile);
void createJPEG(int counter);
void writeToFile(FILE *inputFile, FILE *outputFile);
int checkIsEndOfJPEG(FILE *inputFile);
int isEndOfFile(FILE *inputFile);

int main(int argc, char *argv[])
{
    // 1 command line argument, the name of the forensic image                                      [x]
    // error handling for > 1 argument. print to stderr, main returns 1                             [x]
    // if the forensic image cannot be opened for reading, fprintf to stderr, main returns 2        [x]
    // if using malloc, must be freed                                                               [ ]

    // Check if there is 1 command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Check if the forensic image can be opened for reading
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 2;
    }

    // Find the first JPEG
    int foundFirst = foundFirstJPEG(inputFile);

    if (foundFirst)
    {
        int counter = 0;
        while (1)
        {
            createJPEG(counter);
            counter++;
            if (isEndOfFile(inputFile))
            {
                break;
            }
        }
    }
    else
    {
        printf("No JPEG present inside this file.");
        return 1;
    }

    fclose(inputFile);

    return 0;
}

// --- End of main --- //

int foundFirstJPEG(FILE *inputFile)
{
    unsigned char c0 = fgetc(inputFile);
    printf("%ld: %x\n", ftell(inputFile), c0);
    if (c0 == 0xff)
    {
        unsigned char c1 = fgetc(inputFile);
        if (c1 == 0xd8)
        {
            unsigned char c2 = fgetc(inputFile);
            if (c2 == 0xff)
            {
                unsigned char c3 = fgetc(inputFile);
                // If this 4th byte is correct, we have identified the start of a JPEG
                if (c3 >= 0xe0 || c3 <= 0xef)
                {
                    // Put the pointer back to the first byte of the JPEG
                    fseek(inputFile, -4, SEEK_CUR);
                    return 1;
                }
            }
        }
    }

    // Return 0 if we reached the end of the file without finding a JPEG
    if (isEndOfFile(inputFile)
    {
        return 0;
    }

    // Recurse until a JPEG is found
    return foundFirstJPEG(inputFile);
}

void createJPEG(int counter)
{
    // Create new JPEG file
    char *strCounter[12] sprintf(strCounter, "%d", counter);
    char *filename =
        FILE *outputFile = fopen("000.jpg", "w");
    printf("We write from: %ld\n", ftell(inputFile));
    writeToFile(inputFile, outputFile);
    printf("We are now at: %ld\n", ftell(inputFile));

    while (1)
    {
        // Check if we reached the end of a JPEG
        if (checkIsEndOfJPEG(inputFile))
        {
            break;
        }
        else
        {
            writeToFile(inputFile, outputFile);
            printf("This should print now: %ld\n", ftell(inputFile));
        }
    }

    return;
}

void writeToFile(FILE *inputFile, FILE *outputFile)
{
    // Define character block of 512 bytes
    char bytes[512];
    // Read a block of 512 bytes
    fread(bytes, 1, 512, inputFile);
    // Write a block of 512 bytes
    fwrite(bytes, 1, 512, outputFile);

    return;
}

int checkIsEndOfJPEG(FILE *inputFile)
{
    unsigned char c0 = fgetc(inputFile);
    if (c0 == 0xff)
    {
        unsigned char c1 = fgetc(inputFile);
        if (c1 == 0xd8)
        {
            unsigned char c2 = fgetc(inputFile);
            if (c2 == 0xff)
            {
                unsigned char c3 = fgetc(inputFile);
                // If this 4th byte is correct, we have identified the start of a new JPEG
                if (c3 >= 0xe0 || c3 <= 0xef)
                {
                    // Put the pointer back to the first byte of the JPEG
                    fseek(inputFile, -4, SEEK_CUR);
                    return 1;
                }
            }
            else
            {
                fseek(inputFile, -3, SEEK_CUR);
            }
        }
        else
        {
            fseek(inputFile, -2, SEEK_CUR);
        }
    }
    else
    {
        fseek(inputFile, -1, SEEK_CUR);
    }

    return 0;
}

int isEndOfFile(FILE *inputFile)
{
    if (feof(inputFile))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
