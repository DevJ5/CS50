#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool isValidNumberOfArguments(int argc);
bool isValidArgument(string arg);
string encryptWord(string encryptedWord, int key);

// Run the program with 1 command line argument, i.e. a positive integer
int main(int argc, string argv[])
{
    // If the argument is somehow not valid return 1
    if (!isValidNumberOfArguments(argc) || !isValidArgument(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // The cryptographic key, aka the command line argument
    int key = atoi(argv[1]);
    // Ask the user to input a word which will be encrypted
    string word = get_string("plaintext: ");
    
    printf("ciphertext: %s\n", encryptWord(word, key));
    return 0;
}

bool isValidNumberOfArguments(int argc)
{
    return argc == 2;
}

bool isValidArgument(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
        {
            return false;
        }
    } 
    return true;
}

string encryptWord(string encryptedWord, int key)
{ 
    // Loop through string and add key to each ascii character
    for (int i = 0, n = strlen(encryptedWord); i < n; i++)
    {
        // Make copy of character
        char character = encryptedWord[i];
        // For lowercase:
        if (character >= 'a' && character <= 'z')
        {
            character -= 97;
            character = (character + key) % 26 + 97;
        }
        else if (character >= 'A' && character <= 'Z')
        {
            character -= 65;
            character = (character + key) % 26 + 65;
        }
        // If the character is not a letter do nothing
        encryptedWord[i] = character;
    }

    return encryptedWord;
}
