#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Input is a word/sentence and a cyphernumber
// The cyphernumber rotates the characters clockwise
// Output is a cyphered word/sentence
// Edge cases: A space in the key, no key, key which is not a number.

bool isValidArgumentCount(int n);
bool isValidKey(string key);
void printInvalidInputMessage(void);
string encryptMessage(string message, int intKey);

int main(int argc, string argv[])
{
    string strKey = argv[1];
    // Validate the key
    if (!isValidArgumentCount(argc) || !isValidKey(strKey))
    {
        printInvalidInputMessage();   
        return 1;
    }

    // Convert the string key into an integer key
    int intKey = 0;
    for (int i = 0, len = strlen(strKey); i < len; i++)
    {
        intKey *= 10;
        intKey += strKey[i] - '0';
    }

    printf("%i\n", intKey);
        
    // Get a string from the user
    string plainMessage = get_string("plaintext: ");
    char *cypheredMessage = encryptMessage(plainMessage, intKey);

    // Print out the cyphered text
    printf("ciphertext: %s\n", cypheredMessage);
}

bool isValidArgumentCount(int n)
{
    return n == 2;
}

bool isValidKey(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (key[i] < '0' || key[i] > '9')
        {
            return false;
        }
    }
    
    return true;
}

void printInvalidInputMessage()
{
    printf("Usage: ./caesar key\n");
}
        
char *encryptMessage(string message, int intKey)
{
    int messageLength = strlen(message);
        
    // Transform the message with the key
    static char cyphertext[1000];
    for (int i = 0; i < messageLength; i++)
    {
        char c = message[i];
              
        if ((message[i] >= 'A' && message[i] < 'Z') ||
            (message[i] >= 'a' && message[i] <= 'z'))
        {
            // Uppercase character:
            if (isupper(message[i]))
            {
                printf("is upper: %c", message[i]);
                c = (message[i] - 'A' + intKey) % 26;
                c += 'A';
            }
            // Lowercase character:
            else
            {
                printf("is lower:%c\n", message[i]);
                c = (message[i] - 'a' + intKey) % 26;
                c += 'a';
            }
        }
 
        // Place the cyphered character into the cyphertext array
        cyphertext[i] = c;
    }
    
    return cyphertext;
}
