#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

typedef struct 
{
    int pocet_prvkov;
    int *pole;    
} MNOZINA;

typedef struct 
{
    int pocet_prvkov;
    int *pole;    
} VYSTUPNA;

void zjednotenie(MNOZINA *A, MNOZINA *B, VYSTUPNA *C)
{
    C->pocet_prvkov=A->pocet_prvkov+B->pocet_prvkov;
    C->pole = malloc(C->pocet_prvkov*sizeof(int));
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
    C->pole = malloc((A->pocet_prvkov+B->pocet_prvkov)*sizeof(int));
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
    // upraceme
    C->pole = realloc(C->pole, C->pocet_prvkov*sizeof(int));
}

void vypis(VYSTUPNA *C)
{
    int i;
    for(i=0;i<C->pocet_prvkov;i++)
    {
        printf("%d ",C->pole[i]);
    }
    printf("\n");
}

void mnozinaFactory(MNOZINA* mnozina, int count, ...)
{
    va_list args;
    va_start(args, count);
    
    mnozina->pole = malloc(count*sizeof(int));
    mnozina->pocet_prvkov = count;
    for(int i = 0;i<count;i++) {
        mnozina->pole[i] = va_arg(args, int);
    }
    va_end(args);
}


void mnozinaDestroy(MNOZINA* mnozina) {
    free(mnozina->pole);
    mnozina->pocet_prvkov=0;
    mnozina->pole=NULL;
}

void vystupnaDestroy(VYSTUPNA* mnozina) {
    free(mnozina->pole);
    mnozina->pocet_prvkov=0;
    mnozina->pole=NULL;
}

int main()
{
    MNOZINA A;//={3,{1,2,3}};
    mnozinaFactory(&A, 4, 2,1,3,6);
    MNOZINA B;//={4,{1,2,3,4}};
    mnozinaFactory(&B, 9, 1,2,3,4,6,6,6,1,2);
    VYSTUPNA C;
    zjednotenie(&A,&B,&C);
    vypis(&C);
    prienik(&A,&B,&C);
    vypis(&C);
    mnozinaDestroy(&A);
    mnozinaDestroy(&B);
    vystupnaDestroy(&C);
}