#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*Constantes da linguagem C indicando o número de alguns tipos de componente*/

#define NOP 41
#define NDEC 10
#define NRER 16
#define NLOOP 2
#define NFLUX 4

/*Vetores com os diferentes tipos de componente*/

char *operadores[] = {"(","[",".",",","->","++","--","~","!","*","&","+","-","<<",">>","<",">","<=",">=","/","/*","*/","%","==","!=","^","|","||","&&","?","=","*=","/=","%=","+=","-=",">>=", "<<=", "&=", "^=", "!="};
char *declaracoes[] = {"char","const","double","float","int","long","signed","unsigned","void", "short"};
char *lacos[] = {"while","for"};
char *flux[] = {"if","else","switch","case"};
char *reservadas[] = {"auto","break","continue","default","do","enum","extern","goto","register","return","sizeof","static","struct","typedef","union","volatile"};

/*Estrutura contendo as 10 métricas utilizadas*/

struct vetor
{
    int operadoresDistintos;
    int totalOperadores;
    int decdist;
    int dectotal;
    int restotal;
    int fluloop;
    int vocab;
    int tam;
    float dific;
    float vol;
};

typedef struct vetor Vetor;

// Protótipos das funções utilizadas.
int getCountCharFile(FILE *fd);
void setText(char *str, FILE *fd);
int contaString(char *a, char *b);
int opdist(char *s, char **op);
int optotal(char *s, char **op);
int declaradist(char *s, char **dec);
int declaratotal(char *s, char **dec);
int reservadist(char *s, char **rer);
int reservatotal(char *s, char **rer);
int contaloop(char *s, char **l);
int contafluxo(char *s, char **f);
int contafluloop(char *s, char**f,char**l);
int vocabulario(char *s, char **op, char **dec, char **rer);
int tamanho(char *s, char **op, char **dec, char **rer);
float volume(char *s, char **op, char **dec, char **rer);
float dificuldade(char *s, char **op, char **dec, char **rer);
int similarfloat(float a, float b, float p);
float similaridade(Vetor a, Vetor b);
void imprime(Vetor a);

int main(int argc, char** argv) {
    FILE *p, *q; /* File descriptor dos arquivos */
    Vetor vp, vq; /* Vetores com as informacoes */
    char *textop, *textoq; /* Strings contendo o conteudo dos arquivos */

    /* Abrindo os arquivos */
    if((p = fopen(argv[1],"r")) == NULL) {
       	printf("Erro na abertura do arquivo: %s.\n", argv[1]);
		exit(1);
    }
    if((q = fopen(argv[2],"r")) == NULL) {
       	printf("Erro na abertura do arquivo: %s.\n", argv[2]);
		exit(1);
    }

    /* Alocacao Dinamica da memoria para os arquivos */
    if((textop = (char *) calloc(getCountCharFile(p),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[1]);
        exit(1);
    }
    if((textoq = (char *) calloc(getCountCharFile(q),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[2]);
        exit(1);
    }

    /* Seta as strings com os textos dos arquivos*/
    setText(textop, p);
    setText(textoq, q);

    printf("\n---- 4 ---- \n");
    printf("\n%d", opdist(textop, operadores));
    printf("\n%d", optotal(textop, operadores));
    printf("\n%d", declaradist(textop, declaracoes));
    printf("\n%d", declaratotal(textop, declaracoes));
    printf("\n%d", reservatotal(textop, reservadas));
    printf("\n%d", vocabulario(textop, operadores, declaracoes, reservadas));
    printf("\n%d", tamanho(textop, operadores, declaracoes, reservadas));
    printf("\n%.2f", volume(textop, operadores, declaracoes, reservadas));
    printf("\n%.2f", dificuldade(textop, operadores, declaracoes, reservadas));
    printf("\n%d", contafluloop(textop,flux,lacos));

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

    return 0;
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
double log2( double n )
{
    // log(n)/log(2) is log2.
    return log(n)/log(2.0);
}

void clearText(char *a) {
    int i, j;
    char *aux;

    if((aux = (char *) calloc(strlen(a),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica !!\n");
        exit(1);
    }

    for(i = 0; i < strlen(a); i++) {
        if((i + 1) != strlen(a) && a[i] == '/' && a[i + 1] == '/') {
            while(a[i] != '\n') {
                i++;
            }
        }
    }
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
/*
//Conta quantas vezes a string b aparece na string a.
int contaString(char *a, char *b) {
    int i, j, k = 0, size_a = strlen(a), size_b = strlen(b), equal = 0, cont = 0;

    for(i = 0; i < size_b; i++) {
        for(j = 0; j < size_a; j++) {
            k = 0;
            equal = 0;

            for(k = 0; k < size_b; k++) {
                if(a[j+k] == b[i+k])
                    equal++;
                if(equal == size_b)
                    cont++;
            }
        }
    }

    return cont;
}
*/
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

    for(i = 0; i < NOP; i++) {

        if(i == 6 || i == 19 || i ==20 || i==22 || i == 23 || i ==26 || (((i>32)&&(i!=38))&&(i!=39)))
            c = -2;
        else if(i == 7 || i == 8 || i == 25 || i == 29 || i == 30)
            c = -1;
        else if (i == 38 || i == 39)
            c = 2;
        else
            c = 1;

        sum = sum+c*contaString(s,*(op+i));
    }

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

    return sum - 1;
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
