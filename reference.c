#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define COUNT 10

// isalpha
// isdigit
// isupper
// islower


// strcat:
char greeting[100] = "Hey ";
strcat(greeting, "how are you?\n");
printf("%s", greeting);

// strcpy:
char greeting[50] = "Hi";
strcpy(greeting, "Heya");

// scanf can't take spaces as input
// Solution: puts and fgets!
    char greeting[100];
    char name[30];
    char sentence[75] = "";

    puts("Whats the greeting: ");
    fgets(greeting, 100, stdin);
    greeting[strcspn(greeting, "\n")] = 0; // fgets inserts a newline character, so we get rid of it.

    puts("Whats the name: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;

    strcat(sentence, greeting);
    strcat(sentence,  " ");
    strcat(sentence, name);


    printf("%s", sentence);

// floor and ceil for rounding:
float float1 = 3.4556766;
float float2 = 3.2345345;
floor(float1);
ceil(float2);

// Math abs:
abs(4 - 10) // 6

// Power and Square root:
pow(2, 3); //  8
sqrt(64) // 8

// Random numbers:
srand ( time(NULL)); // Uses the internal clock so we dont get the same random numbers every time.
for (int i = 0; i < 10; i++)
{
    int diceRoll = rand() % 6 + 1;
    printf("%d\n", diceRoll);
}
