#include<stdio.h>
#include <stdbool.h>
#include<conio.h>

int main()
{
    unsigned int puan;

    
    while (true)
    {
        printf("\n(0-100 arasında sayılarda çalışır aksi halde otomatik kapanır!!)\nÖğrencinin notunu girin: ");
        scanf("%d",&puan);
        
        if ((puan < 0) || (puan > 100))
        {
            printf("Program kapandı !!!\n");
            break;
        }            
        else if (puan < 30)
            printf("Notun: F\nKaldın, birdaha almak zorundasın !!\n\n");
        else if (puan >= 30 && puan < 50 )
            printf("Notun: D\nDaha iyi olabilirdi!\n\n");
        else if (puan >= 50 && puan < 70)
            printf("Notun: C\nOrtalamadasın!!\n\n");
        else if (puan >= 70 && puan < 85)
            printf("Notun: B\nÇok çalışmışsın ama kimse kusursuz değildir unutma!!\n\n");
        else 
            printf("Notun: A\nGeleceğin çok parlak görünüyor!!\n\n");    
    }

    return 0;
}

