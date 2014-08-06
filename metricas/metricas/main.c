#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

/* Estrutura contendo as 10 métricas utilizadas */
struct vetor {
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
struct content {
    int length;
    char **stringVector;
};

typedef struct vetor Vetor;
typedef struct content Content;

/* Protótipos das funções utilizadas */
FILE* readFile(char *str);
Content explode(char *str, char *ch);
int countLinesFile(FILE *fd);
void readLine(FILE *fd, char *s);
void clearText(char *a);
void clearBlankLine(char *a);
void clearComment(char *a);
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
    FILE *p, *q, *dados; /* File descriptor dos arquivos */
    Vetor vp, vq; /* Vetores com as informacoes */
    char *textop, *textoq; /* Strings contendo o conteudo dos arquivos */
    char str[200];
    int i = 0;
    Content *content;

    /* Abertura de arquivos */
    if(!(dados = readFile(argv[1])))
        exit(EXIT_FAILURE);
    if(!(p = readFile(argv[2])))
        exit(EXIT_FAILURE);
    if(!(q = readFile(argv[3])))
        exit(EXIT_FAILURE);

    /* Alocacao dinamica da memoria para os arquivos */
    if((textop = (char *) calloc(getCountCharFile(p),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[1]);
        exit(1);
    }
    if((textoq = (char *) calloc(getCountCharFile(q),sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[2]);
        exit(1);
    }

    if(countLinesFile(dados) > 0) { // Tem linhas no arquivo
        if((content = (Content *) calloc(countLinesFile(dados),sizeof(Content))) == NULL) {
            printf("Erro na alocacao dinamica. Arquivo: %s\n", argv[2]);
            exit(1);
        }
        rewind(dados);

        while(!feof(dados)) {
            readLine(dados, str);
            printf(str);
            explode(str," ");
            i++;
        };

        /* Seta as strings com os textos dos arquivos*/
        setText(textop, p);
        setText(textoq, q);
/*
    clearText(textop);
    clearText(textoq);
    printf("\n%s", textop);
    printf("\n%s", textoq);

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

FILE* readFile(char *str) {
    FILE *aux = NULL;

    if((aux = fopen(str,"r")) == NULL) {
       	printf("Erro na abertura do arquivo: %s.\n", str);
    }

    return aux;
}

Content explode(char *str, char *ch) {
    int i, j = 0, n = 0;
    char **aux, *p;
    Content content;

    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] == ch[0])
            n++;
    }
    n++;
    printf("\n\n");

    if((aux = (char **) calloc(n,sizeof(char*))) == NULL) {
        printf("Erro na alocacao dinamica !!\n");
        exit(1);
    }

    p = strtok(str,ch);
    while(j < n) {
        aux[j] = p;
        printf ("%s\n", aux[j]);
        p = strtok (NULL,ch);
        j++;
    }

    content.length = n;
    content.stringVector = aux;
    return content;
}

int countLinesFile(FILE *fd) {
    int i, n = 1;
    char ch;

    while((ch = fgetc(fd)) != EOF) {
        if((char)ch == '\n')
            n++;
    }

    return n;
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
