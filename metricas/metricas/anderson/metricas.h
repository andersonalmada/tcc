#ifndef METRICAS_H_INCLUDED
#define METRICAS_H_INCLUDED

/* Estrutura contendo as métricas utilizadas */
struct vectorMetrics {
    float opDiff;
    float opTotal;
    float decDiff;
    float decTotal;
    float resDiff;
    float resTotal;
    float flowLoop;
    float vocabHalstead;
    float lengthHalstead;
    float diffHalstead;
    float volumeHalstead;
};
typedef struct vectorMetrics VectorMetrics;

struct content {
    int length;
    char **stringVector;
    char *id;
};
typedef struct content Content;

struct enableMetrics {
    int enable;
    float accuracy;
    char *id;
};
typedef struct enableMetrics EnableMetrics;

/* Protótipos das funções utilizadas */
FILE* readFile(char *str);
Content getContent(Content *cont, char *id);
void setVectorMetrics(char *str, Content *content, EnableMetrics *enable, int n, VectorMetrics *vectorMetrics);
void setEnableMetrics(char *str, EnableMetrics *enable);
void showVectorMetrics(VectorMetrics vectorMetrics);
void setContent(char *str, Content *cont);
int countLines(FILE *fd);
void readLine(FILE *fd, char *s);
void clearText(char *a);
void clearBlankLine(char *a);
void clearComment(char *a);
int getCountCharFile(FILE *fd);
void setText(char *str, FILE *fd);
int countString(char *a, char *b);
int countDiffContent(char *s, Content cont);
int countTotalContent(char *s, Content cont);
float similarity(VectorMetrics a, VectorMetrics b, EnableMetrics *enable, int n);
int similarityFloat(float a, float b, float p);
/*
int contafluloop(char *s, char**f,char**l);
int vocabulario(char *s, char **op, char **dec, char **rer);
int tamanho(char *s, char **op, char **dec, char **rer);
float volume(char *s, char **op, char **dec, char **rer);
float dificuldade(char *s, char **op, char **dec, char **rer);
int similarfloat(float a, float b, float p);
float similaridade(Vetor a, Vetor b);
void imprime(Vetor a);
*/
#endif // METRICAS_H_INCLUDED
