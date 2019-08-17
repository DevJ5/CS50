#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int isValidArgCount(int argc);
int isValidKey(char *key);
char *encryptMessage(char *message, char *key);

int main(int argc, char **argv)
{

    char *key = argv[1];
    // Validate input:
    if (!isValidArgCount(argc) || !isValidKey(key))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    char message[200];
    puts("plaintext: ");
    fgets(message, 200, stdin);
    message[strcspn(message, "\n")] = 0;

    const char *cypherText = encryptMessage(message, key);

    printf("ciphertext: %s\n", cypherText);

    return 0;
}

int isValidArgCount(int argc)
{
    return argc == 2;
}

int isValidKey(char *key)
{
    int valid = 1;
    if (strlen(key) == 0)
    {
        valid = 0;
    }

    int i = 0;
    while (key[i] != '\0')
    {
        if (!isalpha(key[i]))
        {
            valid = 0;
            break;
        }
        i++;
    }

    return valid;
}

char *encryptMessage(char *message, char *key)
{
    int messageLength = strlen(message);

    char *ciphertext = malloc(strlen(message) + 1); // +1 because of '\0' at the end
    strcpy(ciphertext, message);

    int keyLength = strlen(key);

    // Loop through message:
    for (int i = 0, j = 0; i < messageLength; i++)
    {
        int messageChar = message[i];
        int keyChar = isupper(key[j % keyLength]) ? key[j % keyLength] - 'A' : key[j % keyLength] - 'a';

        if (isupper(messageChar))
        {
            messageChar = (messageChar - 'A' + keyChar) % 26;
            ciphertext[i] = messageChar + 'A';
            j++;
        }
        else if (islower(messageChar))
        {
            messageChar = (messageChar - 'a' + keyChar) % 26;
            ciphertext[i] = messageChar + 'a';
            j++;
        }
        else
        {
            ciphertext[i] = messageChar;
            // No increment of j, because key char has to stay the same.
        }
    }

    return ciphertext;
}
