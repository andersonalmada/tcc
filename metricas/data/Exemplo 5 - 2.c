#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    int a = 0, b = 1, l, d, m;
    int i, j, k;
    
    while(b < 1000){
              m = b+a;
              a = b;
              b = m;
    }

    int s;
    float u;
    char r[10];
    
    s = 0;
    for (i = 0; i<b; i++) s = s+i;
    
    return 0;
    
}
    
