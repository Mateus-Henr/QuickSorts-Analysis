#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
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
#define CAMINHO_ARQUIVO "..//arquivos//"
#define MINIMO_ARQ_VALIDO 4
#define INICIO_ARG "quicksort"
#define ARGS_ESPERADO "\nErro: %d argumentos esperados.\n"
#define ERRO_ARQUIVO_SAIDA "\nErro: Não foi possível gerar o arquivo de saída.\n"
#define ERRO_FORMATO "\nErro: O formato do argumento deve ser 'quicksort<semente1>saida_semente1.txt'.\n"


// Protótipos de funções.

double inicializaClock(void);

double calculaTempo(double tempoInicial);

void escreveNoArquivo(FILE *pArquivo, Tupla *valores);


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

    if (!string)
    {
        printf(ERRO_FORMATO);
        return INVALIDO;
    }

    string += strlen(INICIO_ARG);

    unsigned int tamanhoString = strlen(string);
    int loopAtual = ZERO;
    char seedString[CHAR_MAX];

    while (isdigit((int) *string) && loopAtual < tamanhoString)
    {
        seedString[loopAtual++] = (*string++);
    }

    // Checando se a semente e o nome do pArquivo são válidos.
    if (loopAtual == ZERO || loopAtual >= tamanhoString || strlen(string) <= MINIMO_ARQ_VALIDO)
    {
        printf(ERRO_FORMATO);
        return INVALIDO;
    }

    /// -------------------------------------------------------- FIM CHECAGEM ARGUMENTOS -------------------------------------------------------------

    // Declarando variáveis.
    unsigned int seed = ZERO;
    char arquivo[CHAR_MAX];

    // Atribuindo caminho do arquivo.
    strcpy(arquivo, CAMINHO_ARQUIVO);
    // Atribuindo nome do pArquivo.
    strcat(arquivo, string);
    // Atribuindo seed.
    sscanf(seedString, "%i", &seed);

    // Definindo a sequência aleatória.
    srand(seed);

    // Criando pArquivo de saída.
    FILE *pArquivo = fopen(arquivo, "a+");

    // Checando se pArquivo de saída é válido.
    if (!pArquivo)
    {
        printf(ERRO_ARQUIVO_SAIDA);
        return INVALIDO;
    }


    // Criando array com os tamanhos para teste.
    int tamanhos[] = {1000, 5000, 10000, 50000, 100000, 500000};

    for (int i = ZERO; i < (sizeof(tamanhos) / sizeof(tamanhos[ZERO])); i++)
    {
        int arrRandomNum[tamanhos[i]];

        // Gerando números aleatórios.
        for (int j = ZERO; j < tamanhos[i]; j++)
        {
            arrRandomNum[j] = rand();
        }

        Tupla valores;

        double clock = inicializaClock();
        inicializaTupla(&valores);
        quickSortRecursivo(arrRandomNum, ZERO, tamanhos[i] - UM, &valores);
        valores.tempo = calculaTempo(clock);
        escreveNoArquivo(pArquivo, &valores);

        clock = inicializaClock();
        inicializaTupla(&valores);
        quickSortMediana(arrRandomNum, TRES, ZERO, tamanhos[i] - UM, &valores);
        valores.tempo = calculaTempo(clock);
        escreveNoArquivo(pArquivo, &valores);

        clock = inicializaClock();
        inicializaTupla(&valores);
        quickSortMediana(arrRandomNum, CINCO, ZERO, tamanhos[i] - UM, &valores);
        valores.tempo = calculaTempo(clock);
        escreveNoArquivo(pArquivo, &valores);

        clock = inicializaClock();
        inicializaTupla(&valores);
        quickSortInsercao(arrRandomNum, DEZ, ZERO, tamanhos[i] - UM, &valores);
        valores.tempo = calculaTempo(clock);
        escreveNoArquivo(pArquivo, &valores);

        clock = inicializaClock();
        inicializaTupla(&valores);
        quickSortInsercao(arrRandomNum, CEM, ZERO, tamanhos[i] - UM, &valores);
        valores.tempo = calculaTempo(clock);
        escreveNoArquivo(pArquivo, &valores);

        clock = inicializaClock();
        inicializaTupla(&valores);
        quickSortEmpilha(arrRandomNum, ZERO, tamanhos[i] - UM, &valores);
        valores.tempo = calculaTempo(clock);
        escreveNoArquivo(pArquivo, &valores);

        clock = inicializaClock();
        inicializaTupla(&valores);
        quickSortIterativo(arrRandomNum, ZERO, tamanhos[i] - UM, &valores);
        valores.tempo = calculaTempo(clock);
        escreveNoArquivo(pArquivo, &valores);
    }


    // Fechando arquivo.
    fclose(pArquivo);
    pArquivo = NULL;

    return ZERO;
}


/*
 * Escreve dados em arquivo.
 *
 * @param    pArquivo    ponteiro para o arquivo.
 * @param    valores     conjunto de valores para serem escritos no arquivo.
 */
void escreveNoArquivo(FILE *pArquivo, Tupla *valores)
{
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