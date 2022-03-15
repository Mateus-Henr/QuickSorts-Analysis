#include "quickSorts.h"
#include <stdlib.h>
#define ZERO 0
#define UM 1
#define DOIS 2


int Mediana(int i, int *pInt, Tupla *valores);

/*
 * Inicializa Tupla estrutura.
 *
 * @param    valores     ponteiro para uma Tupla estrutura.
 */
void inicializaTupla(Tupla *valores)
{
    valores->tempo = ZERO;
    valores->qtdComparacoes = ZERO;
    valores->qtdMovimentacoes = ZERO;
}


void particao(int *arr, int inicio, int final, int *i, int *j, Tupla *valores)
{
    *i = inicio;
    *j = final;

    int pivo = arr[(*i + *j) / DOIS];

    do
    {
        while (pivo > arr[*i])
        {
            (*i)++;
        }
        while (pivo < arr[*j])
        {
            (*j)--;
        }

        valores->qtdComparacoes++;
        if (*i <= *j)
        {
            int aux = arr[*i];
            arr[*i] = arr[*j];
            arr[*j] = aux;
            (*i)++;
            (*j)--;
            valores->qtdMovimentacoes++;
        }
    } while (*i <= *j);
}


void quickSortRecursivo(int *arr, int inicio, int final, Tupla *valores)
{
    int i, j;

    particao(arr, inicio, final, &i, &j, valores);

    if (inicio < j)
    {
        quickSortRecursivo(arr, inicio, j, valores);
    }
    if (i < final)
    {
        quickSortRecursivo(arr, i, final, valores);
    }
}

void quickSortMediana(int *arr, int k, int inicio, int final, Tupla *valores)
{
    int i, j;

    particao(arr, inicio, final, &i, &j, valores);

    if (inicio < j)
    {
        quickSortMediana(arr, k, inicio, j, valores);
    }
    if (i < final)
    {
        quickSortMediana(arr, k, i, final, valores);
    }
}

void particaoMediana(int *arr, int inicio, int final, int *i, int *j, Tupla *valores)
{
    *i = inicio;
    *j = final;

    int pivo = Mediana(5, arr, final);

    do
    {
        while (pivo > arr[*i])
        {
            (*i)++;
        }
        while (pivo < arr[*j])
        {
            (*j)--;
        }

        valores->qtdComparacoes++;
        if (*i <= *j)
        {
            int aux = arr[*i];
            arr[*i] = arr[*j];
            arr[*j] = aux;
            (*i)++;
            (*j)--;
            valores->qtdMovimentacoes++;
        }
    } while (*i <= *j);
}

int Mediana(int quantidade,int *arr,int final){
    int *random, comparador, mediana, true,chav, mise;
    true=1;
    while(true)
    { int l=0,contador=0;
        for (int i = 0; i < quantidade; ++i)
        {
            random[i]= rand() %final;
        }
        for (int j = 0; j < quantidade; ++j){
            for (int k = 0; k < quantidade-1; ++k){
                 if(random[j]==random[k] && j!=k){
                     contador++;
                }
            }
        }
        if(contador<=0){
            true=0;
        }
    }

    for (int i = 0; i < quantidade; ++i)
    {
        int j =0;
        chave= random[i];
        j = j-1;
        while (j>=0 && random[j]> chave){
            random[j+1]= random[j];
            j= j-1;
        }
        random[j+1]=chave;
    }
    mediana = random[mid];
    return mediana;
}