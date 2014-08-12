#ifndef METRICAS_H_INCLUDED
#define METRICAS_H_INCLUDED

/* Estrutura contendo as métricas utilizadas */
struct vectorMetrics {
    double opDiff;
    double opTotal;
    double decDiff;
    double decTotal;
    double resDiff;
    double resTotal;
    double flowLoop;
    double numberLines;
    double numberCallFunctions;
    double numberBlocks;
    double vocabHalstead;
    double lengthHalstead;
    double estimatedLengthHalstead;
    double diffHalstead;
    double volumeHalstead;
    double potencialVolumeHalstead;
    double programLevelHalstead;
    double estimatedProgramLevelHalstead;
    double programDifficultyHalstead;
    double intelligenceContentHalstead;
    double programmingEffortHalstead;
    double estimatedProgrammingTimeHalstead;
    double languageLevelHalstead;
    double numberBugsHalstead;
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
void setVectorMetrics(FILE *fd, char *str, Content *content, EnableMetrics *enable, int n, VectorMetrics *vectorMetrics);
void setEnableMetrics(char *str, EnableMetrics *enable);
void showVectorMetrics(VectorMetrics vectorMetrics);
Content *getContent(Content *cont, char *id);
void setContent(char *str, Content *cont);
int countLinesFile(FILE *fd);
int countLinesText(char *str);
int getNumberCallFunctions(char *str, Content *content);
int getNumberBlocks(char *str);
void readLine(FILE *fd, char *s);
void clearText(char *a);
void clearBlankLine(char *a);
void clearComment(char *a);
int getCountCharFile(FILE *fd);
void setText(char *str, FILE *fd);
double countString(char *a, char *b);
double countDiffContent(char *s, Content *cont);
double countTotalContent(char *s, Content *cont);
double similarity(VectorMetrics a, VectorMetrics b, EnableMetrics *enable, int n);
int similarityFloat(double a, double b, double p);
double n1(char* str, Content *content);
double n2(char* str, Content *content);
double N1(char* str, Content *content);
double N2(char* str, Content *content);
double volumeHalstead(char* str, Content* content);
double potencialVolumeHalstead(char* str, Content* content);
double programLevelHalstead(char* str, Content* content);
double estimatedProgramLevelHalstead(char* str, Content* content);
double programmingEffortHalstead(char* str, Content* content);

#endif // METRICAS_H_INCLUDED
