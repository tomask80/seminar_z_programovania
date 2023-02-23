#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int velkost1;
    int velkost2;
    int i;
    puts("Zadaj velkost prvej mnoziny:");
    scanf("%d", &velkost1);
    printf("\n");
    int A[velkost1];
    puts("Vypln mnozinu A:");
    for (i = 0; i < velkost1; i++)
    {
        scanf("%d", &A[i]);
    }

    puts("Zadaj velkost druhej mnoziny:");
    scanf("%d", &velkost2);
    int B[velkost2];
    puts("Vypln mnozinu B:");
    for (i = 0; i < velkost2; i++)
    {
        scanf("%d", &B[i]);
    }

    
}