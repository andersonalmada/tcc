#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Funcao que calcula o fatorial*/

int fatorial(int n){
     
    if (n == 1) return 1;
    else return n*fatorial(n-1);
    
}

/*Main*/

int main(void){
    
    printf("%d", fatorial(10));
    
    int k = 0;
    int n = 1;
    
    /*Loop para calcular soma dos fatoriais que não excede 10^10*/
    
    while (k < pow(10,7)){
          
          k = k + fatorial(n);
          n++;
          }
    
    printf("\nMin: %d\n",n);
    printf("Valor: %d", k); 
    
    return 0;
    
}
    
         
