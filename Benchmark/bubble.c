#include <stdio.h>
#include <math.h>
//#include "papi.h"
#define TAM 100

void bubblesort(int n, long *v);
int calculaTamanho(int n);
long *criaVetorAleatorio(int size, long *vetor);

int main(){

	long *vetor;
   	int tamanho,t;
   	float itempo, tempo, iprocTempo, procTempo, imflops,mflops;
	long long flpops, iflpops;
   	long long int comeco, final;
   	size_t alinhamento = 32 * 1024;

   	scanf("%d", &tamanho);

   	t = (int)sizeof(long);

   	tamanho = calculaTamanho(tamanho);

   	posix_memalign((void**)&vetor, alinhamento, (tamanho/t)*sizeof(long));


   	vetor = criaVetorAleatorio(tamanho, vetor);

   	comeco = PAPI_get_real_cyc();
	PAPI_flips(&itempo,&iprocTempo,&iflpops,&imflops);


   	bubblesort(tamanho, vetor);


   	PAPI_flips(&tempo,&procTempo,&flpops,&mflops);
	final = PAPI_get_real_cyc();



   	printf("Acabou\n");

   	printf(" Tempo: %f\n Proc Tempo: %f\n Total flops: %lld\n MFLOPS: %f\n ", tempo, procTempo, flpops, mflops);
	printf("TOTAL DE CLOCKS É: %lld\en", final-comeco);
	printf("\n");

	return 0;
}

void bubblesort(int n, long *v){

	int fim,i;
	for (fim = n-1; fim > 0; fim--){
		for (i=0; i<fim; i++){
			if (v[i]>v[i+1]) {
				int temp = v[i]; /* troca */
				v[i] = v[i+1];
				v[i+1] = temp;
			}
		}
	}

}
int calculaTamanho(int n){
	
	int tamanho = 1;
	int i;
	for(i = 0; i < n; i++){
		tamanho += pow(2,i);
	}

	return tamanho;
}
long *criaVetorAleatorio(int size,long *vetor){
	
	srand(time(NULL));
	int i;

	for(i = 0; i < size; i++){
	      vetor[i] = rand() % TAM;
	      //printf("%d", vetor[i]);
	    }  
	return vetor;
}