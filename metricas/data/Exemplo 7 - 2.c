#include <stdio.h>

int main(void){
    
    int i = 0,j = 4, c, matriz[5][5], sum = 0;
    
    while (i<5){
          while(j >-1){
                  
                  if(i==j) c = 2;
                  else if (i>j) c = 1;
                  else c = 0;
                  matriz[i][j] = c;
                  
                  switch(c){
                         case 0:
                              break;
                         case 1:
                              sum +=1;
                              break;
                         case 2:
                              sum+=2;
                              break;
                              }
                  j--;
                  }
          i++;
          }
          
}
                  
    

    
