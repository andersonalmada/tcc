#include <stdio.h>

#include <stdio.h>

/*Soma de elementos da matriz base*/

int main(void){

    int i, j;
    float matriz[10][10], s = 0;

    /*Loop*/

    for (i = 0; i<10; i++){
        for(j = 0; j<10; j = j+1){

              matriz[i][j] = 1/(i+j+1);
              s = s+matriz[i][j];
              }

              }

    printf("%f", s);
    return 0;
}
