#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    long int a = 0, b = 1;
    float i;
    int c;
    
    while(b < 1000){
              c = b+a;
              a = b;
              b = c;
    }

    unsigned int s;
    s = 0;
    for (i = 0; i<b; i++) s = s+i;
    
    return 0;
    
}
    
