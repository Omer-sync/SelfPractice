#include <stdio.h>
#include <ctype.h>
int main() {
  float sayi_1,sayi_2;
  char operator;

  while (operator != 'Q')
  {
    printf("İşlem yapmak istediğiniz sayıları giriniz: ");
    scanf("%f %f",&sayi_1,&sayi_2);
    
    printf("\nYapmak istediğiniz işlemi giriniz(+,-,*,/)(Çıkmak için 'q'): ");
    
    scanf(" %c",&operator);

    operator = toupper(operator);

    switch (operator) 
    {
      case '+' :
        printf("^^Sonuç^^\n%.2f + %.2f = %.2f\n",sayi_1,sayi_2,sayi_1+sayi_2);
        break;
      case '-' :
        printf("^^Sonuç^^\n%.2f - %.2f = %.2f\n",sayi_1,sayi_2,sayi_1-sayi_2);
        break;
      case '*' :
        printf("^^Sonuç^^\n%.2f * %.2f = %.2f\n",sayi_1,sayi_2,sayi_1 * sayi_2);
        break;
      case '/'  :
        if (sayi_2 != 0)
        {
          printf("^^Sonuç^^\n%.2f / %.2f = %.2f\n",sayi_1,sayi_2,sayi_1/sayi_2);
          break;
        }
        else
        {
          printf("!! Hatalı bölme işlemi !! (Sayı sıfıra bölünmez)\n");
          break;  
        }
      case 'Q':
        printf("Program kapandı..\n");
        break;
      default :
        printf("İstenen işlemlerden birini girmediniz!\n");
    }


  }

   return 0;
}