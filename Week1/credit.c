#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
// American Express 15 digits, starts with 34 or 37
// MasterCard 16 digits, starts with 51, 52, 53, 54, 55
// Visa 13 and 16 digits, starts with 4
// Luhns algorithm
// Requirements:
// 1) Ask user to input a credit card number
// 2) As output print to the screen AMEX\n or MASTERCARD\n or VISA\n or INVALID\n
// 3) No input validation required
// 4) Use a long integer
 
int getNumberOfDigits(long int cc);
string getType(long int cc, int numberOfDigits);
int getStartingDigits(long int cc, int numberOfDigits, int numberOfStartingDigits);
bool checkSum(long int cc);
 
int main(void)
{
    // Ask user to input a credit card number
    long int cc = get_long("Number: ");
    
    // Get the number of digits in the credit card number
    int numberOfDigits = getNumberOfDigits(cc);
    string type = getType(cc, numberOfDigits);

    // If there is no type found, print invalid and quit the program
    if (strcmp(type, "INVALID") == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // The type is valid, we proceed to checking if the actual number is valid
    bool isValidNumber = checkSum(cc);
    // If the number is valid print the type, else print invalid
    isValidNumber ? printf("%s\n", type) : printf("INVALID\n");
}

int getNumberOfDigits(long int cc)
{
    int numberOfDigits = 0;
    while (cc >= 1)
    {
        cc /= 10;
        numberOfDigits++;
    }
    
    return numberOfDigits;
}

string getType(long int cc, int numberOfDigits)
{
    // American Express if there are 15 digits and it starts with 34 or 37
    if (numberOfDigits == 15)
    {
        int startingDigits = getStartingDigits(cc, numberOfDigits, 2);
        if (startingDigits == 34 || startingDigits == 37)
        {
            return "AMEX";
        }
    }
    
    // MasterCard if there are 16 digits, and it starts with either 51, 52, 53, 54 or 55
    if (numberOfDigits == 16)
    {
        int startingDigits = getStartingDigits(cc, numberOfDigits, 2);
        if (startingDigits >= 51 && startingDigits <= 55)
        {
            return "MASTERCARD";
        }
    }

    // Visa if there are 13 or 16 digits, and it starts with 4
    if (numberOfDigits == 13 || numberOfDigits == 16)
    {
        int startingDigit = getStartingDigits(cc, numberOfDigits, 1);
        if (startingDigit == 4)
        {
            return "VISA";
        }
    }

    return "INVALID";
}



int getStartingDigits(long int cc, int numberOfDigits, int numberOfStartingDigits)
{
    if (numberOfStartingDigits == 1)
    {
        return cc / pow(10, numberOfDigits - 1);
    }
    else if (numberOfStartingDigits == 2)
    {
        return cc / pow(10, numberOfDigits - 2);
    }
    else
    {
        return 0;
    }
}

bool checkSum(long int cc)
{
    int total = 0;
    bool multiplyByTwo = false;
    while (cc >= 1)
    {
        int digit = cc % 10;
        if(multiplyByTwo)
        {
            if (digit < 5)
            {
                total += digit * 2;
            }
            else
            {
                // Add the first digit of the product:
                total += digit * 2 / 10;
                // Add the second digit of the product:
                total += digit * 2 % 10; 
            }
            multiplyByTwo = false;
        }
        else
        {
            total += digit;
            multiplyByTwo = true;
        }
        cc /= 10;
    }

    return total % 10 == 0;
}
