#include <stdio.h>

int sq(int u){
    
    return u*u+1;
    
}

int triang(int u){
    
    if(u == 0) return 0;
    else return u+ triang(u-1);
    
}

int main(void){
 
    int i,j, m = 9, n, cont1 = 0, cont2 = 0, sum = 0;
    int matriz[10][10];
    
    for (i = 0; i<10; i = i+1){
        for (j = i; j<10; j = j+1){
            
            matriz[i][j] = triang(i+j);
            cont1++;
            sum = sum+matriz[i][j];
            }
            }
    while (m > -1){
          n = m-1;
          while(n > -1){
                  matriz[m][n] = sq(m+n);
                  n = n-1;
                  cont2 = cont2 + 1;
                  sum = sum - matriz[m][n];
                  }
                  }
          
     sum = (cont1 + cont2)*(sum-1);
     
     return 0;
     
}
           
           
           
           
            
                  
