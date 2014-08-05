
#include <stdio.h>
#include <string.h>

int main(void){
    
    int i,j ;
    
    float matriz[10][10], s = 0;
    
    for (i = 0; i<10; i++){
        
        for(j = 0; j<10; j = j+1){
              
              /*Formula e incremento do valor de s   */
              
              matriz[i][j] =  1/(i+j+1); s = s+matriz[i][j];
              }
              }
    /*Fim do Loop*/
    
    printf("%f",s);    
    
    return 0;

/*     Fim      */
    
}
    
