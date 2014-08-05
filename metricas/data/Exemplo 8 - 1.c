#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int contdiv(int n){
		
	int i, cont = 0;

	for (i = 1; i < n+1; i++){
		if(n%i == 0) cont++;
		}
	return cont;
}				

int main(void){

	int n, m;
	scanf("%d", &m);
	n = m;

	int sum1 = 0, sum2 = 0, i;

	while(n > 0){
		
		if(contdiv(n) > 2 || contdiv(n) ==1) sum2 = sum2 + contdiv(n)*contdiv(n);
		else{
			sum1 = sum1 + n;
			sum2 = sum2 + contdiv(n)*contdiv(n);
		}
			
		n--;
	}

	printf("\nSoma dos primos menores que %d: %d\n", m, sum1);
	printf("Soma dos quadrados dos divisores dos numeros ate %d: %d\n", m, sum2);

	return 0;
	 

}
