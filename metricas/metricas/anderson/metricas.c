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

void setContent(char *str, Content *cont) {
    int i, j = 0, n = 0;
    char *p, ch[2] = " ";

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

void setVectorMetrics(char *str, Content *content, EnableMetrics *enable, int n, VectorMetrics *vectorMetrics) {
    int i;

    for(i = 0; i < n; i++) {
        if(strcmp(enable[i].id,"opDiff") == 0) {
            if(enable[i].enable)
                vectorMetrics->opDiff = countDiffContent(str, getContent(content, "op"));
            else
                vectorMetrics->opDiff = -1;
        }
        else if(strcmp(enable[i].id,"opTotal") == 0) {
            if(enable[i].enable)
                vectorMetrics->opTotal = countTotalContent(str, getContent(content, "op"));
            else
                vectorMetrics->opTotal = -1;
        }
        else if(strcmp(enable[i].id,"decDiff") == 0) {
            if(enable[i].enable)
                vectorMetrics->decDiff = countDiffContent(str, getContent(content, "dec"));
            else
                vectorMetrics->decDiff = -1;
        }
        else if(strcmp(enable[i].id,"decTotal") == 0) {
            if(enable[i].enable)
                vectorMetrics->decTotal = countTotalContent(str, getContent(content, "dec"));
            else
                vectorMetrics->decTotal = -1;
        }
        else if(strcmp(enable[i].id,"resDiff") == 0) {
            if(enable[i].enable) {
                vectorMetrics->resDiff = countDiffContent(str, getContent(content, "res")) +
                                         countDiffContent(str, getContent(content, "flow")) +
                                         countDiffContent(str, getContent(content, "loop")) +
                                         countDiffContent(str, getContent(content, "dec"));
            }
            else
                vectorMetrics->resDiff = -1;
        }
        else if(strcmp(enable[i].id,"resTotal") == 0) {
            if(enable[i].enable) {
                vectorMetrics->resTotal = countTotalContent(str, getContent(content, "res")) +
                                          countTotalContent(str, getContent(content, "flow")) +
                                          countTotalContent(str, getContent(content, "loop")) +
                                          countTotalContent(str, getContent(content, "dec"));
            }
            else
                vectorMetrics->resTotal = -1;
        }
        else if(strcmp(enable[i].id,"flowLoop") == 0) {
            if(enable[i].enable)
                vectorMetrics->flowLoop = countTotalContent(str, getContent(content, "loop"))+countTotalContent(str, getContent(content, "flow"));
            else
                vectorMetrics->flowLoop = -1;
        }
        else if(strcmp(enable[i].id,"vocabHalstead") == 0) {
            if(enable[i].enable) {
                vectorMetrics->vocabHalstead = countDiffContent(str, getContent(content, "op")) +
                                               countDiffContent(str, getContent(content, "res")) +
                                               countDiffContent(str, getContent(content, "flow")) +
                                               countDiffContent(str, getContent(content, "loop")) +
                                               2 * countDiffContent(str, getContent(content, "dec"));
            }
            else
                vectorMetrics->vocabHalstead = -1;
        }
        else if(strcmp(enable[i].id,"lengthHalstead") == 0) {
            if(enable[i].enable) {
                vectorMetrics->lengthHalstead = countTotalContent(str, getContent(content, "op")) +
                                                countTotalContent(str, getContent(content, "res")) +
                                                countTotalContent(str, getContent(content, "flow")) +
                                                countTotalContent(str, getContent(content, "loop")) +
                                                2 * countTotalContent(str, getContent(content, "dec"));
            }
            else
                vectorMetrics->lengthHalstead = -1;
        }
        else if(strcmp(enable[i].id,"diffHalstead") == 0) {
            if(enable[i].enable) {
                int i = countDiffContent(str, getContent(content, "dec"));
                if(i > 0) {
                    vectorMetrics->diffHalstead = ((float)(countDiffContent(str, getContent(content, "op")) +
                                                    countDiffContent(str, getContent(content, "res")) +
                                                    countDiffContent(str, getContent(content, "flow")) +
                                                    countDiffContent(str, getContent(content, "loop")) +
                                                    2*countDiffContent(str, getContent(content, "dec"))) / 2) *
                                                  ((float)countTotalContent(str, getContent(content, "dec")) / i);
                }
            }
            else
                vectorMetrics->diffHalstead = -1;
        }
        else if(strcmp(enable[i].id,"volumeHalstead") == 0) {
            if(enable[i].enable) {
                vectorMetrics->volumeHalstead = (countTotalContent(str, getContent(content, "op")) +
                                                 countTotalContent(str, getContent(content, "res")) +
                                                 countTotalContent(str, getContent(content, "flow")) +
                                                 countTotalContent(str, getContent(content, "loop")) +
                                                 2 * countTotalContent(str, getContent(content, "dec"))) *
                                                 log2(countDiffContent(str, getContent(content, "op")) +
                                                 countDiffContent(str, getContent(content, "res")) +
                                                 countDiffContent(str, getContent(content, "flow")) +
                                                 countDiffContent(str, getContent(content, "loop")) +
                                                 2 * countDiffContent(str, getContent(content, "dec")));
            }
            else
                vectorMetrics->volumeHalstead = -1;
        }
    }
}

void setEnableMetrics(char *str, EnableMetrics *enable) {
    char *p, ch[2] = " ";

    p = strtok(str,"#");
    if((enable->id = (char *) calloc(strlen(p)+1,sizeof(char))) == NULL) {
        printf("Erro na alocacao dinamica !!\n");
        exit(1);
    }
    strcpy(enable->id,p); // Parametro
    enable->enable = atoi(strtok(NULL,ch)); // Habilitado
    enable->accuracy = atof(strtok(NULL,ch)); // Precisao
}

int countLines(FILE *fd) {
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
    int i, k;
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
int countString(char *a, char *b) {
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

int countDiffContent(char *s, Content cont) {
    int i, count = 0;

    for(i = 0; i < cont.length; i++) {
        if((countString(s, cont.stringVector[i])) != 0)
            count++;
    }

    return count;
}

int countTotalContent(char *s, Content cont) {
    int i, sum = 0;

    for(i = 0; i < cont.length; i++)
        sum += countString(s, cont.stringVector[i]);

    return sum;
}

void showVectorMetrics(VectorMetrics vectorMetrics) {
    if(vectorMetrics.opDiff != -1)
        printf("\nDifferent operators = %.1f", vectorMetrics.opDiff);
    if(vectorMetrics.opTotal != -1)
        printf("\nTotal operators = %.1f", vectorMetrics.opTotal);
    if(vectorMetrics.decDiff != -1)
        printf("\nDifferent statements = %.1f", vectorMetrics.decDiff);
    if(vectorMetrics.decTotal != -1)
        printf("\nTotal statements = %.1f", vectorMetrics.decTotal);
    if(vectorMetrics.resDiff != -1)
        printf("\nDifferent keyword = %.1f", vectorMetrics.resDiff);
    if(vectorMetrics.resTotal != -1)
        printf("\nTotal keyword = %.1f", vectorMetrics.resTotal);
    if(vectorMetrics.flowLoop != -1)
        printf("\nFlowLoops = %.1f", vectorMetrics.flowLoop);
    if(vectorMetrics.vocabHalstead != -1)
        printf("\nVocabulary Halstead = %.1f", vectorMetrics.vocabHalstead);
    if(vectorMetrics.lengthHalstead != -1)
        printf("\nLength Halstead = %.1f", vectorMetrics.lengthHalstead);
    if(vectorMetrics.diffHalstead != -1)
        printf("\nDifficulty Halstead = %.2f", vectorMetrics.diffHalstead);
    if(vectorMetrics.volumeHalstead != -1)
        printf("\nVolume Halstead = %.2f\n", vectorMetrics.volumeHalstead);
}

/* Avaliador de similaridade entre dois números A e B com variável de peso P */
int similarityFloat(float a, float b, float p) {
    if(a == 0 && b == 0)
        return 1;
    else if((a == 0) || (b == 0))
        return 0;
    else {
        if(fmax(fabs(b - a)/a, fabs(b - a)/b) <= p)
            return 1;
        else
            return 0;
    }
    return 0;
}

/* Similaridade */
float similarity(VectorMetrics a, VectorMetrics b, EnableMetrics *enable, int lines) {
    int i, n = 0;
    float sum = 0;

    for(i = 0; i < lines; i++) {
        if(enable[i].enable)
            n++;
    }

    if(n) {
        for(i = 0; i < lines; i++) {
            if(enable[i].enable) {
                if(strcmp(enable[i].id,"opDiff") == 0)
                    sum += similarityFloat(a.opDiff, b.opDiff, enable[i].accuracy);
                if(strcmp(enable[i].id,"opTotal") == 0)
                    sum += similarityFloat(a.opTotal, b.opTotal, enable[i].accuracy);
                if(strcmp(enable[i].id,"decDiff") == 0)
                    sum += similarityFloat(a.decDiff, b.decDiff, enable[i].accuracy);
                if(strcmp(enable[i].id,"decTotal") == 0)
                    sum += similarityFloat(a.decTotal, b.decTotal, enable[i].accuracy);
                if(strcmp(enable[i].id,"resDiff") == 0)
                    sum += similarityFloat(a.resDiff, b.resDiff, enable[i].accuracy);
                if(strcmp(enable[i].id,"resTotal") == 0)
                    sum += similarityFloat(a.resTotal, b.resTotal, enable[i].accuracy);
                if(strcmp(enable[i].id,"flowLoop") == 0)
                    sum += similarityFloat(a.flowLoop, b.flowLoop, enable[i].accuracy);
                if(strcmp(enable[i].id,"vocabHalstead") == 0)
                    sum += similarityFloat(a.vocabHalstead, b.vocabHalstead, enable[i].accuracy);
                if(strcmp(enable[i].id,"lengthHalstead") == 0)
                    sum += similarityFloat(a.lengthHalstead, b.lengthHalstead, enable[i].accuracy);
                if(strcmp(enable[i].id,"diffHalstead") == 0)
                    sum += similarityFloat(a.diffHalstead, b.diffHalstead, enable[i].accuracy);
                if(strcmp(enable[i].id,"volumeHalstead") == 0)
                    sum += similarityFloat(a.volumeHalstead, b.volumeHalstead, enable[i].accuracy);
            }
        }

        return sum/n;
    }
    else {
        printf("\nSem metricas ativadas\n");
        return -1;
    }
}


