#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "metricas.h"

int main(int argc, char** argv) {
    FILE *fd1, *fd2, *dados, *metricas; /* File descriptor dos arquivos */
    char *textFd1, *textFd2; /* Strings contendo o conteudo dos arquivos */
    char str[300]; /* Variavel para ler linhas dos arquivos */
    int i = 0, n = 0; /* Variavel para auxiliar */
    Content *content; /* Variavel contendo o conteudo da linguagem */
    EnableMetrics *enableMetrics; /* Variavel contendo as metricas analisadas e a precisao */
    VectorMetrics vectorMetrics[2]; /* Vetores contendo as contagens dos parametros */

    /* Abertura de arquivos */
    if(!(dados = readFile(argv[1])))
        exit(EXIT_FAILURE);
    if(!(metricas = readFile(argv[2])))
        exit(EXIT_FAILURE);
    if(!(fd1 = readFile(argv[3])))
        exit(EXIT_FAILURE);
    if(!(fd2 = readFile(argv[4])))
        exit(EXIT_FAILURE);

    /* Alocacao dinamica da memoria para os arquivos */
    if((textFd1 = (char *) calloc(getCountCharFile(fd1),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[1]);
        exit(1);
    }
    if((textFd2 = (char *) calloc(getCountCharFile(fd2),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[2]);
        exit(1);
    }

    n = countLines(dados); /* Conta as linhas do arquivo que contem o conteudo da linguagem */

    if(n > 0) { // Tem conteudo
        if((content = (Content *) calloc(n,sizeof(Content))) == NULL) {
            printf("Erro na alocacao dinamica 1.\n");
            exit(1);
        }
        while(i < n) {
            readLine(dados, str);
            setContent(str, content+i);
            i++;
        };
        i = 0; n = 0;
        n = countLines(metricas); /* Conta as linhas do arquivo que contem as metricas */

        if(n > 0) { // Tem metricas
            if((enableMetrics = (EnableMetrics *) calloc(n,sizeof(EnableMetrics))) == NULL) {
                printf("Erro na alocacao dinamica 2.\n");
                exit(1);
            }
            while(i < n) {
                readLine(metricas, str);
                setEnableMetrics(str, enableMetrics+i);
                i++;
            };

            /* Seta as strings com os textos dos arquivos */
            setText(textFd1, fd1);
            setText(textFd2, fd2);

            /* Limpa os textos */
            clearText(textFd1);
            clearText(textFd2);

            setVectorMetrics(textFd1, content, enableMetrics, n, &vectorMetrics[0]);
            setVectorMetrics(textFd2, content, enableMetrics, n, &vectorMetrics[1]);

            /* Imprime os vetores e o resultado */
            printf("\n**************** Results **************** \n");
            printf("\nVectorMetrics[1]:\n");
            showVectorMetrics(vectorMetrics[0]);
            printf("\nVectorMetrics[2]:\n");
            showVectorMetrics(vectorMetrics[1]);
            printf("\nSimilarity: %.2f\n", similarity(vectorMetrics[0], vectorMetrics[1], enableMetrics, n));
            printf("\n******************************************** \n");
        }
        else
            printf("\nSem metricas !!\n\n");
    }
    else
        printf("\nSem conteudo !!\n\n");
    return 0;
}
