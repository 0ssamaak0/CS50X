#include <stdio.h>
#include <cs50.h>
// Takes a hight such that 1<= hight <= 8
int main(void)
{
    int n ;
    do 
    {
        n = get_int("Enter the hight of the pyramid: ");
    }
    while (n < 1 || n > 8);
        
    n = n + 1 ;
    for (int i = 1; i < n ; i++)
    {
        for (int j = n - i; j > 1 ; j--)
        
        {
            printf(" ");
        }
        // printf("\b");
        for (int k = 0; k < i ; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int a = 0 ; a < i ; a++)
        {
            printf("#");
        }
        // for (int b = n-i; b>1 ; b--)
        // {
        //     printf(" ");
        // }
        printf("\n");
    }

}