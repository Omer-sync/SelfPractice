#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include <locale.h>


struct person
{
    char name[32];
    char number[11];
};

int index_first(char Array[30], char value)
{
    
    
    setlocale(LC_ALL, "Turkish");
    int i = 0, index = -1;
    while (Array[i] != '\0')
    {
        if (Array[i] == value)
        {
            
            index = i;
            break;
        }
        i++;
    }
    return index;
}
int stringCompare(char *word1, char *word2)
{
    setlocale(LC_ALL, "Turkish");
    char *big_letters[] = {"A", "B", "C", "Ç", "D", "E", "F", "G", "Ğ", "H", "I", "İ", "J", "K"," L", "M", "N", "O", "Ö", "P", "R", "S", "Ş", "T", "U", "Ü" ,"V", "Y", "Z"};
    int big_letters_ch[30] ;
    char *small_letters[] = {"a", "b", "c", "ç", "d", "e", "f", "g", "ğ", "h", "ı", "i", "j", "k", "l", "m", "n", "o" ,"ö", "p", "r", "s", "ş", "t", "u", "ü", "v", "y", "z"};
    int small_letters_ch[30] ;
    int b;
    for ( b = 0; b < 30; b++)
    {
        big_letters_ch[b] = big_letters[b];
        small_letters_ch[b] = big_letters[b];
    }
    int lenght_word1 = strlen(word1);
    int lenght_word2 = strlen(word2);
    int control_lenght,i;
    int firstchar1,firstchar2;
    int character1,character2;
    bool pass=false;
    if (lenght_word1 < lenght_word2)
    {
        control_lenght = lenght_word1;
    }
    else
    {                                                                                                                                                               
        control_lenght = lenght_word2;
    }
/*Ceyhun , 5326790965Çağatay
Çağatay , 5068907876Ümit
Ümit , 5433458909Özgür
Özgür , 5327896578Deniz
Deniz , 5072123454İnci
İnci , 5056786543Sercan
Sercan , 5056786532Serkan
Serkan , 5333456790Şinasi
Şinasi , 5416734562Umut
Umut , 5442123456

İnci , 5056786543
Deniz , 5072123454
Ceyhun , 5326790965
Umut , 5442123456
Serkan , 5333456790
Ümit , 5433458909
Çağatay , 5068907876
Şinasi , 5416734562
Özgür , 5327896578
Sercan , 5056786532*/

    firstchar1 = index_first(big_letters_ch,word1[0]); 
    firstchar2 = index_first(big_letters_ch,word2[0]);
    if (firstchar1 < firstchar2)
    {
        pass = false;
        return 0;
    }
    else if (firstchar2 < firstchar1)
    {
        return -1;
    }
    else
    {
        pass = true;
    }
    
    
    while(pass)
    {
        for ( i = 1; i < control_lenght; i++)
        {
            character1 = index_first(small_letters_ch,word1[i]);
            character2 = index_first(small_letters_ch,word2[i]);
            if (character1 < character2)
            {
                pass = false;
                i = control_lenght;
                return 0;
            }
            else if (character2 < character1)
            {
                return -1;
            }
            
        
        }
        if (i == control_lenght)
        {
            return 0;
        }
        
        
    }
    
    
    





}

int main()
{
    
    setlocale(LC_ALL, "Turkish");
    struct person temp,contact[10] = {"İnci","5056786543","Deniz","5072123454","Ceyhun","5326790965","Umut","5442123456","Serkan","5333456790","Ümit","5433458909","Çağatay","5068907876","Şinasi","5416734562","Özgür","5327896578","Sercan","5056786532"};
    //char *people[] = {"İnci","5056786543","Deniz","5072123454","Ceyhun","5326790965","Umut","5442123456","Serkan","5333456790","Ümit","5433458909","Çağatay","5068907876","Şinasi","5416734562","Özgür","5327896578","Sercan","5056786532"};
    
    int k,i,j,t;
    for ( t = 0, k = 0; k < 10; k++,t+=2)
    {
       
        printf("%s , %s\n", contact[k].name,contact[k].number);
        //printf("%s\n",people[k]);
    }
    printf("sorted\n");
    for ( t = 0, k = 0; k < 10; k++,t+=2)
    {
        
        printf("%s , %s\n", contact[k].name,contact[k].number);
        //printf("%s\n",people[k]);
    }
    
    int size= 9;
	for(i=1;i<size;++i)
    {
        for(j=0;j<size-i;j++)
        {
            if(stringCompare(contact[j].name,contact[j+1].name) < 0)
            {
                temp=contact[j];
                contact[j]=contact[j+1];
                contact[j+1]=temp;
            }
        }
    }
    
    
    printf("sorted_____2\n");
    for ( t = 0, k = 0; k < 10; k++,t+=2)
    {
        
        printf("%s , %s\n", contact[k].name,contact[k].number);
        //printf("%s\n",people[k]);
    }

  
    

    return 0;
}