#include <stdio.h>
#include <cs50.h>

long int inputCreditCardNumber(void);
bool isValid(long int);
string typeOfCard(long int);
int calculateLength(long int);
int findFirstNumber(long int);

int main(void)
{
    // Ask user to input credit card number
    long int cc = inputCreditCardNumber();
    bool valid = isValid(cc);
    if (!valid)
    {
        printf("INVALID\n");   
    }
    else
    {
        string type = typeOfCard(cc);
        printf("%s", type);
    }  
}

long int inputCreditCardNumber()
{
    long int cc = 0;
    do
    {
        cc = get_long("Number: ");  
    }
    while (cc == 0);
    return cc; 
}

bool isValid(long int cc)
{
    // Make a copy of cc number
    int num = cc;
    
    int sum = 0;
    int digit;
    
    // If the length is even, we include the first digit
    if (num % 2 == 0)
    {
        while (num >= 10)
        {
            // The total sum of every other digit multiplied by two
            // Ex. 123456 / 10 % 10 = 4; 1234 / 10 % 10 = 3; 123 / 10 % 10 = 2; 12
            digit = num / 10 % 10;
            sum += digit * 2;
            num /= 10;
        }
        
        // Reset num back to cc number
        num = cc;
     
        while (num >= 100)
        {
            // Add all the digits that werent multiplied by 2 to the sum
            digit = num % 10;
            sum += digit;
            num /= 10;
        }
    }
    else
    {
        while (num >= 100)
        {
            digit = num / 10 % 10;
            sum += digit * 2;
            num /= 10;
        }
        
        // Reset num back to cc number
        num = cc;
        
        while (num >= 10)
        {
            // Add all the digits that werent multiplied by 2 to the sum
            digit = num % 10;
            sum += digit;
            num /= 10;
        }    
    }
    return sum % 10 == 0;
}

string typeOfCard(long int cc)
{
    int length = calculateLength(cc);
    int firstNumber = findFirstNumber(cc);
    if (length == 16 && firstNumber != 4)
    {
        return "MASTERCARD\n";    
    }
    else if (length == 15)
    {
        return "AMEX\n";    
    }
    else
    {
        return "VISA\n";   
    }
}

int calculateLength(long int number)
{
    int counter = 0;
    while (number > 0)
    {
        number /= 10;
        counter++;
    }
    return counter;
}

int findFirstNumber(long int number)
{
    while (number >= 10)
    {
        number /= 10;
    }
    
    return number;
}
