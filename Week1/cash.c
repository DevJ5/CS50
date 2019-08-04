#include <stdio.h>
#include <cs50.h>
#include <math.h>
// Ask user input how much change is owed
// Print minimum number of coins
// Possible coins: quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)
// Input must be larger than 0
// Float comparison is not precise, use integers

int calculateNumberOfCoins(int cents);
int main(void)
{
    float change;
    // Ask user input until a value larger than 0 has been given
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
        
    // Transform the floating point number to an integer
    int cents = round(change * 100);

    printf("%i\n", calculateNumberOfCoins(cents));
}

int calculateNumberOfCoins(int cents)
{
    int numberOfCoins = 0;
    // Apply a greedy algorithm of the largest coins
    if (cents / 25 >= 1)
    {
        numberOfCoins += cents / 25;
        cents %= 25;
    }
    if (cents / 10 >= 1)
    {
        numberOfCoins += cents / 10;
        cents %= 10;
    }
    if (cents / 5 >= 1)
    {
        numberOfCoins += cents / 5;
        cents %= 5;
    }
    if (cents / 1 >= 1)
    {
        numberOfCoins += cents / 1;
    }
    
    return numberOfCoins;
}