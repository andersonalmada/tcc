#ifndef METRICAS_H_INCLUDED
#define METRICAS_H_INCLUDED

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
    char *id;
};

typedef struct vetor Vetor;
typedef struct content Content;

/* Protótipos das funções utilizadas */
FILE* readFile(char *str);
Content getContent(Content *cont, char *id);
void setContent(char *str, Content *cont, char *ch);
int countLinesContent(FILE *fd);
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

#endif // METRICAS_H_INCLUDED
