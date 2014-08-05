#include <stdio.h>

int main(void){
    
    int i,j, matriz[5][5], sum = 0;
    
    for (i = 0; i<5; i = i+1){
        for(j = 0; j<5; j++){
              
              if(i == j){
                    matriz[i][j] = 2;
                    sum = sum + 2;
                    }
              else if (i<j){
                    matriz[i][j] = 0;
                    }
              else{
                    matriz[i][j] = 1;
                    sum++;
                    }
        }
    }
    
    return 0;
}
    
