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

int main(void)
{
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
    strcat(sentence, " ");
    strcat(sentence, name);

    printf("%s", sentence);

    // floor and ceil for rounding:
    float float1 = 3.4556766;
    float float2 = 3.2345345;
    floor(float1);
    ceil(float2);

    // Math abs:
    int a = abs(4 - 10); // 6

    // Power and Square root:
    int b = pow(2, 3); //  8
    int c = sqrt(64);  // 8

    // Random numbers:
    srand(time(NULL)); // Uses the internal clock so we dont get the same random numbers every time.
    for (int i = 0; i < 10; i++)
    {
        int diceRoll = rand() % 6 + 1;
        printf("%d\n", diceRoll);
    }

    // Pointers:
    int number = 21;

    int *pNumber = &number; // pointer to number

    printf("Address: %p \t Name: %s \t Value: %i \n", pNumber, "number", number);
    printf("Address: %p \t Name: %s \t Value: %p \n", &pNumber, "number", pNumber); // The pointer also has a memory address

    printf("%i\n", *pNumber); // Dereference the pointer back to the value

    *pNumber = 26;
    printf("%i\n", number);

    int lotteryNumbers[5] = {2, 43, 54, 23, 32};

    for (int i = 0; i < 5; i++)
    {
        printf("lotteryNumbers[%d]: \t %p \t %d \n", i, &lotteryNumbers[i], lotteryNumbers[i]);
    }

    printf("%i", *lotteryNumbers);

    char name[] = "Bert";
    printf("%p\n", name);
    printf("%c\n", *(name + 3));
    printf("%i\n", *name);

    // We cant set name to something else because it is a pointer constant (use strcpy for that)
    // We can however make a pointer variable like so and set it to something else:
    char *name2 = "Ernie";
    name2 = "Bluebird";

    // Pointer is already set to the first element:
    int numbers[] = {1, 3, 6, 8};
    int *p = numbers;

    for (; p < &numbers[4]; p++)
    {
        printf("%d\n", *p);
    }

    // Declaring a character array with a pointer, stores this as a constant in the text segment of the applications memory.
    char *name = "Bert";

    // You cant change this constant
    name[1] = 'a'; // This gives a write memory access error.
}

// Returning a pointer:
char *printName()
{
    return "Bert";
}
