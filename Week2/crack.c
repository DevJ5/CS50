#include <stdio.h>
#include <ctype.h>
#include <crypt.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int isValidArgCount(int argc);
int isValidHash(char *hash);
void getHashWithoutSalt(char *str, size_t n);
int generatePasswords(char *hash, char *salt, int passwordLength);
int compare(char *password, char *hash, char *salt);

int main(int argc, char **argv)
{
    // Get the hash and the salt:
    char *hash = argv[1];
    char salt[3] = {hash[0], hash[1], '\0'};

    for (int i = 1; i <= 5; i++)
    {
        if (generatePasswords(hash, salt, i))
        {
            return 0;
        }
    }

    printf("Password could not be cracked.");
    return 1;
}

int generatePasswords(char *hash, char *salt, int passwordLength)
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabetlength = strlen(alphabet);

    for (int i = 0; i < alphabetlength; i++)
    {
        char a = alphabet[i];
        char password[passwordLength + 1];
        password[0] = a;
        password[1] = '\0';
        if (compare(password, hash, salt))
        {
            return 1;
        }

        if (passwordLength >= 2)
        {
            for (int j = 0; j < alphabetlength; j++)
            {
                char b = alphabet[j];
                password[1] = b;
                password[2] = '\0';

                if (compare(password, hash, salt))
                {
                    return 1;
                }

                if (passwordLength >= 3)
                {
                    for (int k = 0; k < alphabetlength; k++)
                    {
                        char c = alphabet[k];
                        password[2] = c;
                        password[3] = '\0';

                        if (compare(password, hash, salt))
                        {
                            return 1;
                        }

                        if (passwordLength >= 4)
                        {
                            for (int l = 0; l < alphabetlength; l++)
                            {
                                char d = alphabet[l];
                                password[3] = d;
                                password[4] = '\0';

                                if (compare(password, hash, salt))
                                {
                                    return 1;
                                }

                                if (passwordLength == 5)
                                {
                                    for (int m = 0; m < alphabetlength; m++)
                                    {
                                        char e = alphabet[m];
                                        password[4] = e;
                                        password[5] = '\0';

                                        if (compare(password, hash, salt))
                                        {
                                            return 1;
                                        }
                                    } // end of 5th for loop
                                }
                            } // end of 4th for loop
                        }
                    } // end of 3rd for loop
                }
            } // end of 2nd for loop
        }
    } // end of 1st for loop

    return 0;
}

int compare(char *password, char *hash, char *salt)
{
    char *hashedPassword = crypt(password, salt);

    if (strcmp(hashedPassword, hash) == 0)
    {
        printf("%s\n", password);
        return 1;
    }
    return 0;
}

// Unnecessary for this assignment:
void getHashWithoutSalt(char *str, size_t n)
{
    assert(n != 0 && str != 0);
    size_t len = strlen(str);
    if (n > len)
    {
        return;
    }
    memmove(str, str + n, len - n + 1);
}
