#include<cs50.h>
#include<math.h>
#include<stdio.h>

// declaring functions
void calculateCoins(int n);

int main(void)
{
    float change = get_float("Please enter the amount of money you will recieve back: \n");
    // validates input for negative numbers
    while(change < 0)
    {
        change = get_float("Error! Please enter the amount of money you will receive back: \n");
    }
    printf("Change owed: %.2f\n", change);
    int coins = round(change * 100);
    calculateCoins(coins);
}

void calculateCoins(int n)
{
    int totalCoins = (n / 25);
    if(n % 25 > 0) 
    {
        n = (n % 25);
        totalCoins += (n / 10);
        if(n % 10 > 0)
        {
            n = (n % 10);
            totalCoins += (n / 5);
            if(n % 5 > 0)
            {
                n = (n % 5);
                totalCoins += (n);
            }
        }
    }
    printf("%i\n", totalCoins);
}