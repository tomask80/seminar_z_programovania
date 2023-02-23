#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct 
{
    int pocet_prvkov;
    int pole[10];    
}MNOZINA;

typedef struct 
{
    int pocet_prvkov;
    int pole[20];    
}VYSTUPNA;

void zjednotenie(MNOZINA *A, MNOZINA *B, VYSTUPNA *C)
{
    C->pocet_prvkov=A->pocet_prvkov+B->pocet_prvkov;
    int i;
    for(i=0;i<A->pocet_prvkov;i++)
    {
        C->pole[i]=A->pole[i];
    }

    for(i=0;i<B->pocet_prvkov;i++)
    {
        C->pole[i+A->pocet_prvkov]=B->pole[i];
    }
}

void prienik(MNOZINA *A, MNOZINA *B, VYSTUPNA *C)
{
    C->pocet_prvkov=0;
    int i,j;
    for(i=0;i<A->pocet_prvkov;i++)
    {
        for(j=0;i<B->pocet_prvkov;j++)
        {
            if(A->pole[i]==B->pole[j])
            {
                C->pole[C->pocet_prvkov]=B->pole[j];
                C->pocet_prvkov++;
                break;
            }
            
        
        }
       
    }

}

void vypis(VYSTUPNA *C)
{
    int i;
    for(i=0;i<C->pocet_prvkov;i++)
    {
        printf("%d\t",C->pole[i]);
    }
    printf("\n");
}

int main()
{
    MNOZINA A={3,{1,2,3}};
    MNOZINA B={4,{1,2,3,4}};
    VYSTUPNA C;
    zjednotenie(&A,&B,&C);
    vypis(&C);
    prienik(&A,&B,&C);
    vypis(&C);


}