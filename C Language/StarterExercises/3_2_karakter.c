#include <stdio.h>
#include <string.h>
#include<stdbool.h>


char* convert(char* name)
{   
    int lenght = strlen(name);
    int i;
    int array[5] = {1,2,3,2,1};
    int incre;
    for ( i = 0; i < lenght; i++)
    {
        incre = array[i % 5];
        name[i] = name[i ] + incre ;
    }
    return name;
}



int main()
{
    char name[50];
    bool control = true;
    do
    {
        printf("Please enter a name and surname in unified form ('q' for exit!!): ");
        scanf("%s",&name);
        if (!strcmp(name,"q") || !strcmp(name,"Q"))
        {
            break;
        }
        
        printf("Converted name: %s\n",convert(name));

    } while (true);

    return 0;
}