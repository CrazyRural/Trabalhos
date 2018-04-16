#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "papi.h"
#define TAM 100

void heapsort(int n, long *vetor);
int calculaTamanho(int n);
long *criaVetorAleatorio(int size, long *vetor);

int main(){

	void *vetor;
   	int tamanho;
   	float itempo, tempo, iprocTempo, procTempo, imflops,mflops;
	long long flpops, iflpops;
   	long long int comeco, final;
   	size_t alinhamento = 64;

   	scanf("%d", &tamanho);

   	tamanho = calculaTamanho(tamanho);


   	posix_memalign(&vetor, alinhamento, tamanho*sizeof(long));


   	vetor = criaVetorAleatorio(tamanho, vetor);

   	comeco = PAPI_get_real_cyc();
	PAPI_flips(&itempo,&iprocTempo,&iflpops,&imflops);


   	heapsort(tamanho, vetor);


   	PAPI_flips(&tempo,&procTempo,&flpops,&mflops);
	final = PAPI_get_real_cyc();



   	printf("Acabou\n");

   	printf(" Tempo: %f\n Proc Tempo: %f\n Total flops: %lld\n MFLOPS: %f\n ", tempo, procTempo, flpops, mflops);
	printf("TOTAL DE CLOCKS É: %lld\en", final-comeco);
	printf("\n");

	return 0;
}

void heapsort(int n, long *vetor){

	int pai,filho,t;
    int i = n / 2;
    for (;;) {
   		if (i > 0) {
        	i--;
            t = vetor[i];
        }else{
            n--;
            if (n == 0) break;
            t = vetor[n];
            vetor[n] = vetor[0];
        }
	    pai = i;
	    filho = i * 2 + 1;
	    while (filho < n) {
		    if ((filho + 1 < n)  &&  (vetor[filho + 1] > vetor[filho]))
	                filho++;
	            if (vetor[filho] > t) {
	        	    vetor[pai] = vetor[filho];
	            pai = filho;
	               filho = pai * 2 + 1;
	        } else {
	            break;
	        }
        }
        vetor[pai] = t;
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