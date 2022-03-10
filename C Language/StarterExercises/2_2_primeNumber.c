#include <stdio.h>
#include <ctype.h>
#include<math.h>
#include<stdbool.h>

bool is_prime(int number);

int main() 
{
    int number;

    printf("******** Prime Number Detector ********\n");

    do
    {   
        printf("Enter a number ('-1' for exit): ");
        scanf(" %d",&number);
        if (number == -1)
        {
            printf("Program has been closed....");
            break;
        }
        if (is_prime(number))
        {
            printf("%d is a prime number\n",number);
        }        
        
    } while (1);

    return 0;
}

bool is_prime(int number)
{
    int i;
    for ( i = 2; i < (number/2) + 1; i++)
    {
        if (number % i == 0)
        {
            return false;
        }        
    }
    
    return true;
}