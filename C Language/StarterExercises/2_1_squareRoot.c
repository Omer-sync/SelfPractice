#include <stdio.h>
#include<math.h>
int main() 
{
    float number;
    printf("******** Square Root Calculator ********\n");
    do
    {   
        printf("Enter a number ('-1' for exit): ");
        scanf(" %f",&number);
        if ((int)number == -1)
        {
            printf("Program has been closed....");
            break;
        }
        printf("Number: %.4f\n",number);
        number = sqrt(number);
        printf("Square Root of Number: %.4f\n",number);
        
    } while (1);
    
    return 0;
}
