#include "quickSorts.h"
#include <stdlib.h>
#include <stdbool.h>

#define MENOS_UM (-1)
#define ZERO 0
#define UM 1
#define DOIS 2


// Protótipos de funções.

void criaParticao(int *arr, int inicio, int final, int *i, int *j, Tupla *valores);

void criaParticaoMediana(int *arr, int k, int inicio, int final, int *i, int *j, Tupla *valores);

void insercaoSort(int *arr, int inicio, int final);

int calculaMediana(const int *arr, int k, int inicio, int final);

void troca(int *a, int *b);


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


/*
 * Cria partição para quick sort algoritmo de forma recursiva.
 *
 * @param    arr        ponteiro para array.
 * @param    inicio     inicio do array.
 * @param    final      fim do array.
 * @param    i          ponteiro para cursor.
 * @param    j          ponteiro para cursor.
 * @param    valores    conjunto de valores para serem calculados.
 */
void criaParticao(int *arr, int inicio, int final, int *i, int *j, Tupla *valores)
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
            troca(arr + *i, arr + *j);
            (*i)++;
            (*j)--;
            valores->qtdMovimentacoes++;
        }
    } while (*i <= *j);
}


/*
 * Organiza array no estilo quick sort recursivo.
 *
 * @param    arr        ponteiro para array.
 * @param    inicio     inicio do array.
 * @param    final      fim do array.
 * @param    valores    conjunto de valores para serem calculados.
 */
void quickSortRecursivo(int *arr, int inicio, int final, Tupla *valores)
{
    int i, j;

    criaParticao(arr, inicio, final, &i, &j, valores);

    if (inicio < j)
    {
        quickSortRecursivo(arr, inicio, j, valores);
    }
    if (i < final)
    {
        quickSortRecursivo(arr, i, final, valores);
    }
}


/*
 * Calcula mediana de elementos aleatórios de um array.
 *
 * @param    arr        ponteiro para array.
 * @param    k          constante para algoritmos específicos.
 * @param    inicio     inicio do array.
 * @param    final      fim do array.
 */
int calculaMediana(const int *arr, const int k, int inicio, int final)
{
    int randArr[k];
    int idxRandArr = ZERO;

    while (idxRandArr < k)
    {
        int randNum = (rand() % final) + inicio;
        bool existe = false;

        for (int i = ZERO; i < k; i++)
        {
            if (randArr[i] == randNum)
            {
                existe = true;
            }
        }

        if (!existe)
        {
            randArr[idxRandArr++] = randNum;
        }
    }

    for (int i = ZERO; i < k; i++)
    {
        randArr[i] = arr[randArr[i]];
    }

    // Organiza array.
    insercaoSort(randArr, ZERO, k);

    return randArr[k / DOIS];
}


/*
 * Cria partição para quick sort algoritmo do tipo mediana.
 *
 * @param    arr        ponteiro para array.
 * @param    incio      inicio do array.
 * @param    final      fim do array.
 * @param    i          ponteiro para cursor.
 * @param    j          ponteiro para cursor.
 * @param    k          constante para algoritmos específicos.
 * @param    valores    conjunto de valores para serem calculados.
 */
void criaParticaoMediana(int *arr, const int k, int inicio, int final, int *i, int *j, Tupla *valores)
{
    *i = inicio;
    *j = final;

    int pivo = ZERO;

    if ((*j - *i) > k)
    {
        pivo = calculaMediana(arr, k, *i, *j);
    }
    else
    {
        pivo = arr[(*i + *j) / DOIS];
    }

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
            troca(arr + *i, arr + *j);
            (*i)++;
            (*j)--;
            valores->qtdMovimentacoes++;
        }
    } while (*i <= *j);
}


/*
 * Organiza array no estilo quick sort mediana.
 *
 * @param    arr        ponteiro para array.
 * @param    inicio     inicio do array.
 * @param    k          constante para quick sort algoritmo.
 * @param    final      fim do array.
 * @param    valores    conjunto de valores para serem calculados.
 */
void quickSortMediana(int *arr, const int k, int inicio, int final, Tupla *valores)
{
    int i, j;

    criaParticaoMediana(arr, k, inicio, final, &i, &j, valores);

    if (inicio < j)
    {
        quickSortMediana(arr, k, inicio, j, valores);
    }
    if (i < final)
    {
        quickSortMediana(arr, k, i, final, valores);
    }
}


/*
 * Organiza array no estilo quick sort inserção.
 *
 * @param    arr        ponteiro para array.
 * @param    inicio     inicio do array.
 * @param    m          constante para quick sort algoritmo.
 * @param    final      fim do array.
 * @param    valores    conjunto de valores para serem calculados.
 */
void quickSortInsercao(int *arr, const int m, int inicio, int final, Tupla *valores)
{
    if ((final - inicio) <= m)
    {
        insercaoSort(arr, inicio, final);

        return;
    }
    else
    {
        int i, j;

        criaParticao(arr, inicio, final, &i, &j, valores);

        if (inicio < j)
        {
            quickSortInsercao(arr, m, inicio, j, valores);
        }
        if (i < final)
        {
            quickSortInsercao(arr, m, i, final, valores);
        }
    }
}


/*
 * Organiza array no estilo quick sort empilha inteligente.
 *
 * @param    arr        ponteiro para array.
 * @param    inicio     inicio do array.
 * @param    final      fim do array.
 * @param    valores    conjunto de valores para serem calculados.
 */
void quickSortEmpilha(int *arr, int inicio, int final, Tupla *valores)
{
    int i, j;

    criaParticao(arr, inicio, final, &i, &j, valores);

    if ((j - inicio) > (final - i))
    {
        quickSortEmpilha(arr, inicio, j, valores);
    }
    if ((j - inicio) < (final - i))
    {
        quickSortEmpilha(arr, i, final, valores);
    }
}


/*
 * Organiza array no estilo quick sort iterativo.
 *
 * @param    arr        ponteiro para array.
 * @param    inicio     inicio do array.
 * @param    final      fim do array.
 * @param    valores    conjunto de valores para serem calculados.
 */
void quickSortIterativo(int *arr, int inicio, int final, Tupla *valores)
{
    int stack[final - inicio + UM];
    int topo = MENOS_UM;

    stack[++topo] = inicio;
    stack[++topo] = final;

    while (topo >= ZERO)
    {
        final = stack[topo--];
        inicio = stack[topo--];

        int i, j;

        criaParticao(arr, inicio, final, &i, &j, valores);

        if (inicio < j)
        {
            stack[++topo] = inicio;
            stack[++topo] = j;
        }
        if (i < final)
        {
            stack[++topo] = i;
            stack[++topo] = final;
        }
    }
}


/*
 * Organiza array no estilo insertion sort.
 *
 * @param    arr        ponteiro para array.
 * @param    inicio     inicio do array.
 * @param    final      fim do array.
 */
void insercaoSort(int *arr, int inicio, int final)
{
    for (int i = inicio + UM; i <= final; i++)
    {
        int temp = arr[i];
        int j = i;

        while ((j > inicio) && (temp < arr[j - UM]))
        {
            arr[j] = arr[j - UM];
            j--;
        }

        arr[j] = temp;
    }
}


/*
 * Troca os elementos de posição na memória.
 *
 * @param    a    ponteiro para valor.
 * @param    b    ponteiro para valor.
 */
void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
