#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <ctype.h>

#include "quickSorts.h"

#define INVALIDO (-1)
#define ZERO 0
#define UM 1
#define DOIS 2
#define TRES 3
#define CINCO 5
#define DEZ 10
#define CEM 100
#define DELIMITADORES "<>"
#define CAMINHO_ARQUIVO "..//arquivos//"
#define MINIMO_ARQ_VALIDO 4
#define NULL_TERMINATOR 1
#define INICIO_ARG "quicksort"
#define ARGS_ESPERADO "\nErro: %d argumentos esperados.\n"
#define ERRO_ARQUIVO_SAIDA "\nErro: Não foi possível gerar o arquivo de saída.\n"
#define ERRO_FORMATO "\nErro: O formato do argumento deve ser 'quicksort<semente1>saida_semente1.txt'.\n"


// Protótipos de funções.

double inicializaClock(void);

double calculaTempo(double tempoInicial);

void escreveNoArquivo(FILE *pArquivo, Tupla *valores, int tamanho, char *string);

void quickSortsSemK(FILE *pArquivo, Tupla *valores, void (*quickSortType)(int *, int, int, Tupla *), int *arr, int tamanho, char *string);

void quickSortsComK(FILE *pArquivo, Tupla *valores, void (*quickSortType)(int *, int, int, int, Tupla *), int *arr, int k, int tamanho, char *string);

void geraNumerosAleatorios(int *arr, int tamanho);


/*
 * A função principal. Tem como função a leitura de informações de um arquivo e manipulação dos dados.
 *
 * @return          0 se executado com sucesso, -1 se ocorrer algum erro.
 */
int main(int argc, char *argv[])
{
    /// ----------------------------------------------------------- CHECAGEM ARGUMENTOS --------------------------------------------------------------

    // Checando se a quantidade de argumentos é a esperada.
    if (argc != DOIS)
    {
        printf(ARGS_ESPERADO, UM);
        return INVALIDO;
    }

    char *string = strstr(argv[UM], INICIO_ARG);

    if (!string || !strtok(string, DELIMITADORES))
    {
        printf(ERRO_FORMATO);
        return INVALIDO;
    }

    char *seedString = strtok(NULL, DELIMITADORES);

    if (!seedString)
    {
        printf(ERRO_FORMATO);
        return INVALIDO;
    }

    for (int i = ZERO; i < strlen(seedString); i++)
    {
        if (!isdigit((int) seedString[i]))
        {
            printf(ERRO_FORMATO);
            return INVALIDO;
        }
    }

    char *nomeArquivo = strtok(NULL, DELIMITADORES);

    if (!nomeArquivo || strlen(nomeArquivo) < MINIMO_ARQ_VALIDO)
    {
        printf(ERRO_FORMATO);
        return INVALIDO;
    }

    /// -------------------------------------------------------- FIM CHECAGEM ARGUMENTOS -------------------------------------------------------------

    // Declarando variáveis.
    unsigned int seed = ZERO;
    char arquivo[strlen(CAMINHO_ARQUIVO) + strlen(nomeArquivo) + NULL_TERMINATOR];

    // Atribuindo caminho do arquivo.
    strcpy(arquivo, CAMINHO_ARQUIVO);
    // Atribuindo nome do pArquivo.
    strcat(arquivo, nomeArquivo);
    // Atribuindo seed.
    sscanf(seedString, "%i", &seed);

    // Definindo a sequência aleatória.
    srand(seed);

    // Criando ponteiro para arquivo de saída.
    FILE *pArquivo = fopen(arquivo, "a+");

    // Checando se o ponteiro para o arquivo de saída é válido.
    if (!pArquivo)
    {
        printf(ERRO_ARQUIVO_SAIDA);
        return INVALIDO;
    }


    // Criando array com os tamanhos para teste.
    int tamanhos[] = {1000, 5000, 10000};

    for (int i = ZERO; i < (sizeof(tamanhos) / sizeof(tamanhos[ZERO])); i++)
    {
        int arrRandomNum[tamanhos[i]];

        // Gerando números aleatórios.
        geraNumerosAleatorios(arrRandomNum, tamanhos[i]);

        // Criando uma variável da estrutura tupla para juntar valores de análise.
        Tupla valores;

        // QuickSort Recursivo
        quickSortsSemK(pArquivo,
                       &valores,
                       quickSortRecursivo,
                       arrRandomNum,
                       tamanhos[i],
                       "\nQuickSort Recursivo - %d elementos\n");

        geraNumerosAleatorios(arrRandomNum, tamanhos[i]);
//
//        // QuickSort Mediana (k = 3)
//        quickSortsComK(pArquivo,
//                       &valores,
//                       quickSortMediana,
//                       arrRandomNum,
//                       TRES,
//                       tamanhos[i],
//                       "\nQuickSort Mediana (k = 3) - %d elementos\n");
//
//        geraNumerosAleatorios(arrRandomNum, tamanhos[i]);
//
//        // QuickSort Mediana (k = 5)
//        quickSortsComK(pArquivo,
//                       &valores,
//                       quickSortMediana,
//                       arrRandomNum,
//                       CINCO,
//                       tamanhos[i],
//                       "\nQuickSort Mediana (k = 5) - %d elementos\n");
//
//        geraNumerosAleatorios(arrRandomNum, tamanhos[i]);
//
//        // QuickSort Inserção (m = 10)
//        quickSortsComK(pArquivo,
//                       &valores,
//                       quickSortMediana,
//                       arrRandomNum,
//                       DEZ,
//                       tamanhos[i],
//                       "\nQuickSort Inserção (m = 10) - %d elementos\n");
//
//        geraNumerosAleatorios(arrRandomNum, tamanhos[i]);
//
//        // QuickSort Inserção (m = 100)
//        quickSortsComK(pArquivo,
//                       &valores,
//                       quickSortMediana,
//                       arrRandomNum,
//                       CEM,
//                       tamanhos[i],
//                       "\nQuickSort Inserção (m = 100) - %d elementos\n");
//
//        geraNumerosAleatorios(arrRandomNum, tamanhos[i]);
//
//        // QuickSort Empilha Inteligente
//        quickSortsSemK(pArquivo,
//                       &valores,
//                       quickSortEmpilha,
//                       arrRandomNum,
//                       tamanhos[i],
//                       "\nQuickSort Empilha Inteligente - %d elementos\n");
//
//        geraNumerosAleatorios(arrRandomNum, tamanhos[i]);
//
        // QuickSort Iterativo
        quickSortsSemK(pArquivo,
                       &valores,
                       quickSortIterativo,
                       arrRandomNum,
                       tamanhos[i],
                       "\nQuickSort Iterativo - %d elementos\n");

        printf("HEY");
    }

    printf("FIM");

    // Fechando arquivo.
    fclose(pArquivo);
    pArquivo = NULL;

    return ZERO;
}


/*
 * Executa função quickSort (sem constante k) passada como parâmetro e salva detalhes.
 *
 * @param    pArquivo           ponteiro para o arquivo.
 * @param    valores            conjunto de valores para serem escritos no arquivo.
 * @param    quickSortType      ponteiro para função quickSort para ser executada.
 * @param    arr                ponteiro para array com números aleatórios.
 * @param    tamanho            tamanho do array.
 * @param    string             contém informações do algoritmo.
 */
void quickSortsSemK(FILE *pArquivo, Tupla *valores, void (*quickSortType)(int *, int, int, Tupla *), int *arr, int tamanho, char *string)
{
    double clock = inicializaClock();
    inicializaTupla(valores);

    (*quickSortType)(arr, ZERO, tamanho - UM, valores);
    valores->tempo = calculaTempo(clock);

    escreveNoArquivo(pArquivo, valores, tamanho, string);
}


/*
 * Executa função quickSort (com constante k) passada como parâmetro e salva detalhes.
 *
 * @param    pArquivo           ponteiro para o arquivo.
 * @param    valores            conjunto de valores para serem escritos no arquivo.
 * @param    quickSortType      ponteiro para função quickSort para ser executada.
 * @param    arr                ponteiro para array com números aleatórios.
 * @param    k                  constante para quickSort algoritmo.
 * @param    tamanho            tamanho do array.
 * @param    string             contém informações do algoritmo.
 */
void quickSortsComK(FILE *pArquivo, Tupla *valores, void (*quickSortType)(int *, int, int, int, Tupla *), int *arr, int k, int tamanho, char *string)
{
    double clock = inicializaClock();
    inicializaTupla(valores);

    (*quickSortType)(arr, k, ZERO, tamanho - UM, valores);
    valores->tempo = calculaTempo(clock);

    escreveNoArquivo(pArquivo, valores, tamanho, string);
}


/*
 * Escreve dados em arquivo.
 *
 * @param    pArquivo    ponteiro para o arquivo.
 * @param    valores     conjunto de valores para serem escritos no arquivo.
 * @param    tamanho     tamanho do array.
 * @param    string      contém informações do algoritmo.
 */
void escreveNoArquivo(FILE *pArquivo, Tupla *valores, int tamanho, char *string)
{
    fprintf(pArquivo, string, tamanho);
    fprintf(pArquivo, "%lf %d %d\n", valores->tempo, valores->qtdComparacoes, valores->qtdMovimentacoes);
}


/*
 * Inicia o clock.
 * @return      valor de quando a função "clock()" é chamada.
 */
double inicializaClock(void)
{
    return (double) clock();
}


/*
 * Finaliza o clock e calcula o tempo total.
 *
 * @param    tempoInicial    valor da primeira vez que a função "clock()" foi chamada.
 * @return                   valor calculado referente ao tempo entre o tempo inicial e o tempo final.
 */
double calculaTempo(double tempoInicial)
{
    return (double) (clock() - tempoInicial) / CLOCKS_PER_SEC;
}


/*
 * Gera números aleatórios no array especificado.
 *
 * @param    arr         ponteiro para array com números aleatórios.
 * @param    tamanho     tamanho do array.
 */
void geraNumerosAleatorios(int *arr, int tamanho)
{
    for (int j = ZERO; j < tamanho; j++)
    {
        arr[j] = rand();
    }
}