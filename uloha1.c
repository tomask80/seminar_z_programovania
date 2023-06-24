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

int zjednotenie(MNOZINA *A, MNOZINA *B, MNOZINA *C)
{
    mnozinaDestroy(C);
    C->pocet_prvkov = A->pocet_prvkov + B->pocet_prvkov;
    C->pole = malloc(C->pocet_prvkov * sizeof(int));
    if(C->pole == NULL) {
        fprintf(stderr, "Zlyhala alokacia pamate!");
        return 0;
    }
    int i;
    for (i = 0; i < A->pocet_prvkov; i++)
    {
        C->pole[i] = A->pole[i];
    }

    for (i = 0; i < B->pocet_prvkov; i++)
    {
        C->pole[i + A->pocet_prvkov] = B->pole[i];
    }
    return 1;
}

int prienik(MNOZINA *A, MNOZINA *B, MNOZINA *C)
{
    mnozinaDestroy(C);
    C->pocet_prvkov = 0;
    C->pole = malloc((A->pocet_prvkov + B->pocet_prvkov) * sizeof(int));
    if(C->pole == NULL) {
        fprintf(stderr, "Zlyhala alokacia pamate!");
        return 0;
    }
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
    if(C->pole == NULL) {
        fprintf(stderr, "Zlyhala realokacia pamate!");
        return 1;
    }
    return 1;
}

void vypis(MNOZINA *C)
{
    int i;
    for (i = 0; i < C->pocet_prvkov; i++)
    {
        printf("%d ", C->pole[i]);
    }
    printf("\n");
}

int mnozinaFactory(MNOZINA *mnozina, int count, ...)
{
    va_list args;
    va_start(args, count);

    mnozina->pole = malloc(count * sizeof(int));
    if(mnozina->pole == NULL) {
        fprintf(stderr, "Zlyhala alokacia pamate!");
        return 0;
    }
    mnozina->pocet_prvkov = count;
    for (int i = 0; i < count; i++)
    {
        mnozina->pole[i] = va_arg(args, int);
    }
    va_end(args);
    return 1;
}

void mnozinaDestroy(MNOZINA *mnozina)
{
    if(mnozina->pole != NULL) {
        free(mnozina->pole);
        mnozina->pole = NULL;
    }
    mnozina->pocet_prvkov = 0;
}

void destroyMnozin(int count, ...) 
{
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        
        MNOZINA* mnozina= va_arg(args, MNOZINA*);
        mnozinaDestroy(mnozina);
    }
    va_end(args);
}


int pridaj(MNOZINA *mnozina, int prvok)
{
    mnozina->pole = realloc(mnozina->pole, (mnozina->pocet_prvkov + 1) * sizeof(int));
    if(mnozina->pole == NULL) {
        return 0;
    }
    mnozina->pole[mnozina->pocet_prvkov] = prvok;
    mnozina->pocet_prvkov++;
    return 1;
}

int odstran(MNOZINA *mnozina, int prvok)
{
    for (int i = 0; i < mnozina->pocet_prvkov; i++)
    {
        if (mnozina->pole[i] == prvok)
        {
            for (int j = i; j < (mnozina->pocet_prvkov) - 1; j++)
            {
                mnozina->pole[j] = mnozina->pole[j + 1];
            }
            break;
        }
    }
    mnozina->pocet_prvkov--;
    mnozina->pole = realloc(mnozina->pole, (mnozina->pocet_prvkov) * sizeof(int));
    if(mnozina->pole == NULL) {
        return 0;
    }
    return 1;
}

int test_prvku(MNOZINA *mnozina, int left, int right, int prvok)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (mnozina->pole[mid] == prvok)
        {
            return mid;
        }

        if (mnozina->pole[mid] < prvok)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    // Prvok sa nenasiel
    return -1;
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
 
    // SKUSKA HEAPSORTU
    MNOZINA A = {0,NULL};
    MNOZINA B = {0,NULL};
    MNOZINA C = {0,NULL};
    if(!mnozinaFactory(&A, 4, 2, 1, 3, 6)) 
    {
        fprintf(stderr, "nepodarilo sa vytvorit mnozinu A");
        exit(1);
    }
    if(!mnozinaFactory(&B, 3, 3, 6, 2))
    {
        fprintf(stderr, "nepodarilo sa vytvorit mnozinu A");
        mnozinaDestroy(&A);
        exit(1);
    }

    printf("Mnozina A: \n");
    vypis(&A);
    heapSort(A.pole, A.pocet_prvkov);
    printf("Zotriedene A: \n");
    vypis(&A);

    printf("\n");

    printf("Mnozina B: \n");
    vypis(&B);
    heapSort(B.pole, B.pocet_prvkov);
    printf("Zotriedene B: \n");
    vypis(&B);

    printf("\n");

    printf("Prienik A B: \n");
    if(!prienik(&A, &B, &C)) {
        fprintf(stderr, "nepodarilo sa vytvorit prienik A a B");
        destroyMnozin(3, &A, &B, &C);
        exit(1);        
    }
    vypis(&C);
    printf("Zjednotenie A B: \n");
    if(!zjednotenie(&A, &B, &C)) {
        fprintf(stderr, "nepodarilo sa vytvorit zjednotenie A a B");
        destroyMnozin(3, &A, &B, &C);
        exit(1);        
    }
    vypis(&C);

    printf("\n");

    printf("Pridane do A: \n");
    if(!pridaj(&A, 5)) {
        fprintf(stderr, "nepodarilo sa pridat prvok do mnoziny A");
        destroyMnozin(3, &A, &B, &C);
        exit(1);  
    }
    vypis(&A);
    printf("Odstranene z A: \n");
    if(!odstran(&A, 2)) {
        fprintf(stderr, "nepodarilo sa odstranit prvok z mnoziny A");
        destroyMnozin(3, &A, &B, &C);
        exit(1);          
    }
    vypis(&A);

    printf("\n");

    heapSort(A.pole, A.pocet_prvkov);
    int vysledok = test_prvku(&A, 0, A.pocet_prvkov - 1, 1);

    if (vysledok == -1)
    {
        printf("Prvok v mnozine nie je\n");
    }
    else
    {
        printf("Prvok sa nasiel na pozicii %d\n", vysledok + 1);
    }

    destroyMnozin(3, &A, &B, &C);
}