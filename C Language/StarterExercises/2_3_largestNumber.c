#include <stdio.h>
#include<stdlib.h>


int largest_number(int *,int );

int main()
{
    int i, size;
    int *list;
    printf("******** Largest Number Detector ********\n");
    printf("Input the size of list: ");
    
    scanf("%d", &size);
    
    list = malloc(size * sizeof(int));
    
    printf("Input elements of list: \n");
    
    for(i=0; i < size; i++)
    {
        scanf(" %d", &list[i]);
    }
    printf("Largest Number of list is %d",largest_number(list,size));
    free(list);
    return 0;
}

int largest_number(int *list,int size)
{
    int i, max;
    max = list[0];
    
    for ( i = 1; i < size; i++)
    {
        if (list[i] > max)
        {
            max = list[i];
        }
        
    }
    return max;
}