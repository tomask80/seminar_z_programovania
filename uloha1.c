#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>

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
    C->pocet_prvkov = A->pocet_prvkov + B->pocet_prvkov;
    C->pole = malloc(C->pocet_prvkov * sizeof(int));
    int i;
    for (i = 0; i < A->pocet_prvkov; i++)
    {
        C->pole[i] = A->pole[i];
    }

    for (i = 0; i < B->pocet_prvkov; i++)
    {
        C->pole[i + A->pocet_prvkov] = B->pole[i];
    }
}

void prienik(MNOZINA *A, MNOZINA *B, VYSTUPNA *C)
{
    C->pocet_prvkov = 0;
    C->pole = malloc((A->pocet_prvkov + B->pocet_prvkov) * sizeof(int));
    int i = 0;
    int j = 0;
    bool hasNext = true;
    while (i < A->pocet_prvkov && j < B->pocet_prvkov && hasNext)
    {
        hasNext = false;
        if (A->pole[i] == B->pole[j])
        {
            C->pole[C->pocet_prvkov] = B->pole[j]; // tu bola chyba B[i]  ale i plati len pre A
            C->pocet_prvkov++;
            // posun cez A
            int a = A->pole[i];
            while (i + 1 < A->pocet_prvkov && (hasNext = true) && A->pole[++i] == a)
                ;
            // posun cez B
            while (j + 1 < B->pocet_prvkov && (hasNext = true) && B->pole[++j] == a)
                ;
            continue;
        }
        else
        {
            if (A->pole[i] < B->pole[j])
            {
                // posun cez A
                int a = A->pole[i];
                while (i + 1 < A->pocet_prvkov && (hasNext = true) && A->pole[++i] == a)
                    ;
            }
            else
            {
                // posun cez B
                int b = B->pole[j];
                while (j + 1 < B->pocet_prvkov && (hasNext = true) && B->pole[++j] == b)
                    ;
            }
        }
    }
    // upraceme
    C->pole = realloc(C->pole, C->pocet_prvkov * sizeof(int));
}

void vypis(VYSTUPNA *C)
{
    int i;
    for (i = 0; i < C->pocet_prvkov; i++)
    {
        printf("%d ", C->pole[i]);
    }
    printf("\n");
}

void mnozinaFactory(MNOZINA *mnozina, int count, ...)
{
    va_list args;
    va_start(args, count);

    mnozina->pole = malloc(count * sizeof(int));
    mnozina->pocet_prvkov = count;
    for (int i = 0; i < count; i++)
    {
        mnozina->pole[i] = va_arg(args, int);
    }
    va_end(args);
}

void mnozinaDestroy(MNOZINA *mnozina)
{
    free(mnozina->pole);
    mnozina->pocet_prvkov = 0;
    mnozina->pole = NULL;
}

void vystupnaDestroy(VYSTUPNA *mnozina)
{
    free(mnozina->pole);
    mnozina->pocet_prvkov = 0;
    mnozina->pole = NULL;
}

void pridaj(MNOZINA *mnozina, int prvok)
{
    mnozina->pole = realloc(mnozina->pole, (mnozina->pocet_prvkov + 1) * sizeof(int));
    mnozina->pole[mnozina->pocet_prvkov] = prvok;
    mnozina->pocet_prvkov++;
}

void odstran(MNOZINA *mnozina, int prvok)
{
    for (int i = 0; i < mnozina->pocet_prvkov; i++)
    {
        if (mnozina->pole[i] == prvok)
        {
            for (int j = i; j < (mnozina->pocet_prvkov)-1; j++)
            {
                mnozina->pole[j] = mnozina->pole[j + 1];
            }
            break;
        }
    }
    mnozina->pocet_prvkov--;
    mnozina->pole = realloc(mnozina->pole, (mnozina->pocet_prvkov) * sizeof(int));
}

// HEAPSORT
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int N, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < N && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, N, largest);
    }
}

void heapSort(int arr[], int N)
{
    for (int i = N / 2 - 1; i >= 0; i--)
    {
        heapify(arr, N, i);
    }

    for (int i = N - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    // MNOZINA A; //={3,{1,2,3}};
    // mnozinaFactory(&A, 4, 2, 1, 3, 6);
    //  MNOZINA B; //={4,{1,2,3,4}};
    //  mnozinaFactory(&B, 9, 1, 2, 3, 4, 6, 6, 6, 1, 2);
    //  VYSTUPNA C;
    //  zjednotenie(&A, &B, &C);
    //  vypis(&C);
    //  prienik(&A, &B, &C);
    //  vypis(&C);
    //  mnozinaDestroy(&A);
    //  mnozinaDestroy(&B);
    //  vystupnaDestroy(&C);

    // SKUSKA HEAPSORTU
    MNOZINA A;
    MNOZINA B;
    VYSTUPNA C;
    mnozinaFactory(&A, 4, 2, 1, 3, 6);
    mnozinaFactory(&B, 3, 3, 6, 2);

    printf("Mnozina A: \n");
    vypis((MNOZINA *)&A);
    heapSort(A.pole, A.pocet_prvkov);
    printf("Zotriedene A: \n");
    vypis((VYSTUPNA *)&A);

    printf("\n");

    printf("Mnozina B: \n");
    vypis((MNOZINA *)&B);
    heapSort(B.pole, B.pocet_prvkov);
    printf("Zotriedene B: \n");
    vypis((VYSTUPNA *)&B);

    printf("Prienik A B: \n");
    prienik(&A, &B, &C);
    vypis(&C);
    printf("Pridane do A: \n");
    pridaj(&A, 5);
    vypis((MNOZINA *)&A);
    printf("Odstranene z A: \n");
    odstran(&A,2);
    vypis((MNOZINA *)&A);

    mnozinaDestroy(&A);
    mnozinaDestroy(&B);
    vystupnaDestroy(&C);
}