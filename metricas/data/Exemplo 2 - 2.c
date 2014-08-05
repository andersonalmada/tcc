#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    int xx = 0, xy = 1;
    int loop;
    int count;
    
    while(xy < 1000){
              count = xx+xy;
              xx = xy;
              xy = count;
    }

    int sum;
    sum = 0;
    for (loop = 0; loop<xy; loop++) sum = sum+loop;
    
    return 0;
    
}
    
