#include <math.h>
#include <stdio.h>

long int teto;
int numdivide(int a, int b);
int numdivisores(long int n);

int main(void){

	int loop;
	long int somaprimos, somaquaddiv;
	somaprimos = 0;
	somaquaddiv = 0;
	int pot = 2, l;
	scanf("%ld", &teto);
	for(loop = 1; loop < teto+1; loop = loop + 1){
		if(loop == 1) somaquaddiv++;
		else if(numdivisores(loop) == 2){
					somaquaddiv = somaquaddiv + numdivisores(loop)*numdivisores(loop);
					somaprimos = somaprimos+loop;
				}
		else somaquaddiv = somaquaddiv + pow(numdivisores(loop),pot);
		}
		
	printf("%d\n", somaprimos);
	printf("%d\n", somaquaddiv);
	return 0;	
}
	
int numdivide(int a, int b){
	if(a%b==0) return 1;
	else return 0;
}

int numdivisores (long int n){

	int conta = 0;
	long int j;
	for (j = n; j > 0; j--){
		if(numdivide(n,j) == 1) conta++;
	}
	return conta;
}
