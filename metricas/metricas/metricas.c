#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "metricas.h"

FILE* readFile(char *str) {
    FILE *aux = NULL;

    if((aux = fopen(str,"r")) == NULL) {
       	printf("Erro na abertura do arquivo: %s.\n", str);
    }

    return aux;
}

Content getContent(Content *cont, char *id) {
    int i = 0;

    while(strcmp(cont[i].id, id) != 0)
        i++;

    return *(cont+i);
}

void setContent(char *str, Content *cont, char *ch) {
    int i, j = 0, n = 0;
    char **aux, *p;

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] == ch[0])
            n++;
    }
    cont->length = n;

    if((cont->stringVector = (char **) calloc(n,sizeof(char*))) == NULL) {
        printf("Erro na alocacao dinamica !!\n");
        exit(1);
    }

    p = strtok(str,"#");
    if((cont->id = (char *) calloc(strlen(p)+1,sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica !!\n");
        exit(1);
    }
    strcpy(cont->id,p);
    p = strtok(NULL,ch);
    while(j < n) {
        if((cont->stringVector[j] = (char *) calloc(strlen(p)+1,sizeof(char))) == NULL) {
            printf("Erro na alocacao dinamica !!\n");
            exit(1);
        }
        strcpy(cont->stringVector[j],p);
        p = strtok(NULL,ch);
        j++;
    }
}

int countLinesContent(FILE *fd) {
    int i = 0;
    char str[300];

    while(!feof(fd)) {
        readLine(fd, str);
        if(strcmp(str,"##") == 0)
            break;
        i++;
    };
    rewind(fd);
    return i;
}

void readLine(FILE *fd, char *str) {
    int i = 0;
    char ch;

    while((ch = fgetc(fd)) != EOF && ((char)ch != '\n')) {
        *(str + i) = (char)ch;
        i++;
    }
    *(str + i) = '\0';
}

int getCountCharFile(FILE *fd) {
	int i = 0;

    while(fgetc(fd) != EOF)
        i++;
    rewind(fd);

	return i;
}

void setText(char *str, FILE *fd) {
	int i = 0;
    char ch;

    while((ch = fgetc(fd)) != EOF) {
        *(str + i) = (char) ch;
        i++;
    }
    *(str + i) = '\0';
}

// Calculates log2 of number.
double log2( double n ) {
    return log(n)/log(2.0);
}

int countLines(char *a) {
    int i, n = 1;

    for(i = 0; i < strlen(a); i++) {
        if(a[i] == '\n')
            n++;
    }

    return n;
}

void clearText(char *a) {
    clearComment(a);
    clearBlankLine(a);
}
void clearBlankLine(char *a) {
    int i, j, k = 0, ai, af, flag = 0;
    char *aux;

    if((aux = (char *) calloc(strlen(a),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica !!\n");
        exit(1);
    }

    for(i = 0; i < strlen(a); i++) {
        if(i == 0)
            ai = 0;
        else if((i + 1) != strlen(a) && a[i] == '\n') {
            af = i;

            for(j = ai; j < af; j++) {
                if(a[j] > 32) {
                    flag = 1;
                    break;
                }
            }
            if(flag) {
                for(j = ai; j < af; j++, k++)
                    aux[k] = a[j];
                flag = 0;
            }
            ai = af;
        }
    }
    for(j = ai; j < strlen(a); j++) {
        if(a[j] > 32) {
            flag = 1;
            break;
        }
    }
    if(flag) {
        for(j = ai; j < strlen(a); j++, k++)
            aux[k] = a[j];
    }
    aux[k] = '\0';
    strcpy(a, aux);
}

void clearComment(char *a) {
    int i, j, k;
    char *aux;

    if((aux = (char *) calloc(strlen(a),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica !!\n");
        exit(1);
    }

    for(i = 0, k = 0; i < strlen(a); i++, k++) {
        if((i + 1) != strlen(a) && a[i] == '/' && a[i + 1] == '*') {
            i += 2;
            while((i + 1) != strlen(a) && (a[i] != '*' || a[i + 1] != '/'))
                i++;
            i += 2;
        }
        else if((i + 1) != strlen(a) && a[i] == '/' && a[i + 1] == '/') {
            i += 2;
            while((i + 1) != strlen(a) && a[i] != '\n')
                i++;
            i++;
        }
        aux[k] = a[i];
    }
    aux[k] = '\0';
    strcpy(a, aux);
}

/* Conta String */
int contaString(char *a, char *b) {
    int i, j, n = 0;
    char *str;

    if((str = (char *) calloc(strlen(b), sizeof(char))) == NULL) { // String para comparacao
        printf("Erro na alocacao de string !!");
        exit(1);
    }

    for(i = 0; i < strlen(a); i++) {
        if(a[i] == b[0]) {
            for(j = 0; j < strlen(b); j++, i++)
                *(str + j) = a[i];
            *(str + j) = '\0';
            if(!strcmp(str, b))
                n++;
        }
    }
    return n;
}

/* Contador de operadores distintos */
int opdist(char *s, char **op) {
    int i, sum = 0;

    for(i = 0; i < NOP; i++) {
        if((contaString(s,*(op+i))) != 0)
            sum++;
    }

    return sum;
}

/* Contador do número total de operadores. Utiliza o princípio da inclusão-exclusão para realizar a contagem. */
int optotal(char *s, char **op) {
    int i,c, sum = 0;

    for(i = 0; i < NOP; i++)
        sum += contaString(s,*(op+i));

    return sum;
}

/*Contador de palavras de declaração distintas */
int declaradist(char *s, char **dec) {
    int i, sum = 0;

    for(i = 0; i < NDEC; i++) {
        if((contaString(s,*(dec+i))) != 0)
            sum++;
    }

    return sum;
}

/* Contador do número total de palavras de declaração */
int declaratotal(char *s, char **dec) {
    int i, sum = 0;

    for(i = 0; i < NDEC; i++)
        sum += contaString(s,*(dec+i));

    return sum;
}

/* Contador de palavras reservadas distintas. Essa função não foi utilizada. */
int reservadist(char *s, char **rer) {
    int i, sum = 0;

    for(i = 0; i < NRER; i++) {
        if((contaString(s,*(rer+i))) != 0)
            sum++;
    }

    return sum;
}

/* Contador do número total de palavras reservadas não contadas anteriormente */
int reservatotal(char *s, char **rer) {
    int i, sum = 0;

    for(i = 0; i < NRER; i++)
        sum += contaString(s,*(rer+i));

    return sum;
}

/* Estimador do número de loops do programa */
int contaloop(char *s, char **l) {
    int i, sum = 0;

    for(i = 0; i < NLOOP; i++)
        sum += contaString(s,*(l+i));

    return sum;
}

/* Estimador do número de estruturas de controle de fluxo do programa */
int contafluxo(char *s, char **f) {
    int i, sum = 0;

    for(i = 0; i < NFLUX; i++)
        sum += contaString(s,*(f+i));

    return sum;
}

/* Estimador do número total de estruturas semânticas */
int contafluloop(char *s, char**f,char**l) {
    return contafluxo(s,f)+contaloop(s,l);
}

/* Vocabulário de Halstead */
int vocabulario(char *s, char **op, char **dec, char **rer) {
    return opdist(s,op) + declaradist(s,dec) + reservadist(s,rer);
}

/* Tamanho de Halstead */
int tamanho(char *s, char **op, char **dec, char **rer){
    return 2*optotal(s,op) + declaratotal(s,dec) + reservatotal(s,rer);
}

/* Volume de Halstead */
float volume(char *s, char **op, char **dec, char **rer) {
    return tamanho(s,op,dec,rer)*log2(vocabulario(s,op,dec,rer));
}

/* Dificuldade de Halstead */
float dificuldade(char *s, char **op, char **dec, char **rer) {
    return (opdist(s,op)/2)*((optotal(s,op) + declaratotal(s,dec) + reservatotal(s,rer))/(declaradist(s,dec) + reservadist(s,rer)));
}

/* Avaliador de similaridade entre dois números A e B com variável de precisão P */
int similarfloat(float a, float b, float p) {
    if(a == 0 && b == 0)
        return 1;
    else if((a == 0) || (b == 0))
        return 0;
    else if((((b-a)/a < p+0.0001)&&((b-a)/a > -p-0.0001)))
        return 1;
    else if((((b-a)/b < p+0.0001)&&((b-a)/b > -p-0.0001)))
        return 1;

    return 0;
}

/*Contabilizador de similaridade. Maior ou igual a 0.5 é considerado. Menor que 0.5 é considerado nulo. */

float similaridade(Vetor a, Vetor b) {
    float sum = 0;

    sum += similarfloat(a.operadoresDistintos, b.operadoresDistintos, 0.15);
    sum += similarfloat(a.totalOperadores, b.totalOperadores, 0.15);
    sum += similarfloat(a.decdist, b.decdist, 0.15);
    sum += similarfloat(a.dectotal, b.dectotal, 0.25);
    sum += similarfloat(a.restotal, b.restotal, 0.15);
    sum += similarfloat(a.fluloop, b.fluloop, 0.01);
    sum += similarfloat(a.vocab, b.vocab, 0.1);
    sum += similarfloat(a.tam, b.tam, 0.1);
    sum += similarfloat(a.dific, b.dific, 0.1);
    sum += similarfloat(a.vol, b.vol, 0.1);

    if(sum/10 > 0.4)
        return sum/10;

    return 0;
}

/*Impressão de vetores de similaridade*/

void imprime(Vetor a) {
     printf("\nOperadores distintos: %d", a.operadoresDistintos);
     printf("\nTotal de operadores: %d", a.totalOperadores);
     printf("\nDeclaracoes distintas: %d", a.decdist);
     printf("\nDeclaracoes totais: %d", a.dectotal);
     printf("\nReservadas totais: %d", a.restotal);
     printf("\nVocabulario: %d", a.vocab);
     printf("\nTamanho: %d", a.tam);
     printf("\nVolume: %.2f", a.vol);
     printf("\nDificuldade: %.2f", a.dific);
     printf("\nFluxo de loops: %d\n", a.fluloop);
}
