#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "metricas.h"

/* Constantes da linguagem C indicando o número de alguns tipos de componente */
#define NOP 40
#define NDEC 10
#define NRER 13
#define NLOOP 2
#define NFLUX 6

/* Vetores com os diferentes tipos de componente */
char *operadores[] = {"sizeof","(","[",".",",","->","++","--","~","!","*","&","+","-","<<",">>","<",">","<=",">=","/","%","==","!=","^","|","||","&&","?","=","*=","/=","%=","+=","-=",">>=","<<=","&=","^=","|="};
char *declaracoes[] = {"char","const","double","float","int","long","signed","unsigned","void", "short"};
char *lacos[] = {"while","for"};
char *flux[] = {"if","else","switch","case","break","continue"};
char *reservadas[] = {"auto","default","do","enum","extern","goto","register","return","static","struct","typedef","union","volatile"};



int main(int argc, char** argv) {
    FILE *fd1, *fd2, *dados; /* File descriptor dos arquivos */
    Vetor vp, vq; /* Vetores com as informacoes */
    char *textFd1, *textFd2; /* Strings contendo o conteudo dos arquivos */
    char str[300];
    int i = 0, n = 0;
    Content *content, aux;

    /* Abertura de arquivos */
    if(!(dados = readFile(argv[1])))
        exit(EXIT_FAILURE);
    if(!(fd1 = readFile(argv[2])))
        exit(EXIT_FAILURE);
    if(!(fd2 = readFile(argv[3])))
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

    n = countLinesContent(dados);

    if(n > 0) { // Tem linhas no arquivo
        if((content = (Content *) calloc(n,sizeof(Content))) == NULL) {
            printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[2]);
            exit(1);
        }

        while(i < n) {
            readLine(dados, str);
            setContent(str, content+i, " ");
            i++;
        };

        aux = getContent(content, "res");

        printf("\n%d", aux.length);
        printf("\n%s", aux.id);
        for(i = 0; i < aux.length; i++)
            printf("\n%s", aux.stringVector[i]);

        /* Seta as strings com os textos dos arquivos*/
        setText(textFd1, fd1);
        setText(textFd2, fd2);

        clearText(textFd1);
        clearText(textFd2);
        printf("\n%s", textFd1);
        printf("\n%s", textFd2);
/*
    // Inicialização dos dois vetores de similaridade
	vp.operadoresDistintos = opdist(textop, operadores);
    vp.totalOperadores = optotal(textop, operadores);
    vp.decdist = declaradist(textop, declaracoes);
    vp.dectotal = declaratotal(textop,declaracoes);
    vp.restotal = reservatotal(textop, reservadas);
    vp.vocab = vocabulario(textop, operadores, declaracoes, reservadas);
    vp.tam = tamanho(textop, operadores, declaracoes, reservadas);
    vp.vol = volume(textop, operadores, declaracoes, reservadas);
    vp.dific = dificuldade(textop, operadores, declaracoes, reservadas);
    vp.fluloop = contafluloop(textop,flux,lacos);

    vq.operadoresDistintos = opdist(textoq, operadores);
    vq.totalOperadores = optotal(textoq, operadores);
    vq.decdist = declaradist(textoq, declaracoes);
    vq.dectotal = declaratotal(textoq,declaracoes);
    vq.restotal = reservatotal(textoq, reservadas);
    vq.vocab = vocabulario(textoq, operadores, declaracoes, reservadas);
    vq.tam = tamanho(textoq, operadores, declaracoes, reservadas);
    vq.vol = volume(textoq, operadores, declaracoes, reservadas);
    vq.dific = dificuldade(textoq, operadores, declaracoes, reservadas);
    vq.fluloop = contafluloop(textoq,flux,lacos);

    //Impressão dos resultados
    printf("\n**************** Resultados **************** \n");
    printf("\nVetor[1]:\n");
    imprime(vp);
    printf("\nVetor[2]:\n");
    imprime(vq);
    printf("\nSimilaridade: %.2f\n",similaridade(vp, vq));
    printf("\n******************************************** \n");
*/
    }
    return 0;
}
