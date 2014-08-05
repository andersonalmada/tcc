#include <stdio.h>
#include <math.h>

int fat(int x){
    if (x == 1)  return 1;
    
    else return  x*fat(x-1);
 
 /*Fim da funcao fatorial*/
}

void main(void){
    
    printf("%d"  , fat(10));
    long int sum = 0; unsigned int nn = 1;
    while (sum < pow(10,7)){
          
          /*calculando..*/
          
          sum = sum + fat(nn);
          
          nn++;
          }
    
    /*Impressao de resultados*/
    
    printf("\nMinx: %d\n",nn);
    
    printf("Valor: %d", sum); 
    
    return 0;
    
}
    
         
