#include <stdio.h>
#include <cs50.h>
// Checks the input credit card number
// Checks if the card is Visa or MasterCard or American Express
// Checks using Luhn’s Algorithm
void card_type(long num);

long number;
int main(void)
{

    number = get_long("Enter your credit card number: ");
    // card_type(number);
    int sum = 0;
    for (long i = 10 ; i < 10000000000000000 ; i *= 100)
    {
        int double_dig = ((number / i) % 10) * 2;
        for (int j = 1 ; j < 99 ; j *= 10)
        {
            // printf("i is %li and j is %i\n", i ,j);
            sum += ((double_dig / j) % 10);
        }
    }
    for (long k = 1 ; k < 10000000000000000 ; k *= 100)
    {
        int other_digits = (number  / k) % 10 ;
        // printf("k is %li\n",k);
        sum += other_digits ;
    }
    printf("%i\n",sum);
    if ((sum % 10) == 0)
    {
        if (number / 10000000000000 == 34 || number / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else if (number / 100000000000000 == 51 ||  number / 100000000000000 == 52 ||  number / 100000000000000 == 53 ||
                 number / 100000000000000 == 54 || number / 100000000000000 == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (number / 1000000000000 == 4 || number / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");

    }

}
