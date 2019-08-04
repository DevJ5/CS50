#include <stdio.h>
#include <cs50.h>
// Create the left hand of a pyramid.
// Ask user for input between 1 and 8 inclusive.
// Print the height
// Print spaces and #'s on each line followed by 2 spaces and then again the same amount of #'s
// Print x amount of lines, x being the user inputted number
void printPyramid(int height);
void printSpaces(int n);
void printHashes(int n);
void printGap();
void printNewLine(void);

int main(void)
{
    // Get the height from the user that is between 1 and 8
    int height;
    do
    {
        height = get_int("Enter a number between 1 and 8 inclusive: ");   
    } 
    while (height < 1 || height > 8);
    
    printPyramid(height);
}

// Takes a height and prints a pyramid
void printPyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        printSpaces(height - i - 1);
        printHashes(i + 1);
        printGap();
        printHashes(i + 1);
        printNewLine();
    }
}

// Takes a number and prints this amount of spaces
void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// Takes a number and prints this amount of hashes
void printHashes(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

// Prints the middle gap
void printGap()
{
    printf("  ");
}

// Prints a newline character
void printNewLine(void)
{
    printf("\n");
}
