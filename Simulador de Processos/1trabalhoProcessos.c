/*
				Feito por João Victor Araújo e Julia Rodrigues
*/
#include "pcb.h"
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#define TEMPO 10000
#define FORKS 25

void seno(int x);
void theKill(pid_t pid);
void processo();


int main(){
	processo();

	return 0;
}


void seno(int x){
	int i;
	for (i = 0; i< x; i++)
		sin(x);
}

void theKill(pid_t pid){
	int nada = kill(pid, SIGKILL);
}	


void processo(void){

	int i = 0, irt = 0, wt = 0, numero; 
	
	PCB* processo;
	
	double comeco, final;
	
	Fila* prontos = criaFila();
	Fila* IO = criaFila();

	while(i < FORKS){

		int pid = fork();
		
		processo = criaProcesso(getpid());
		insereFila(prontos, processo);

		if(pid != 1){

			comeco = (double)clock();
			seno(rand()%TEMPO);
			final = (double)clock();

			numero = (rand()%13);
			wt = numero;
			processo = insereValores(processo, ((final - comeco)/CLOCKS_PER_SEC), irt, wt);
			
			switch(numero){
				case 0:
					imprimeProcesso(processo);
					theKill(processo->PID);
					break;
				case 1:
					insereFila(prontos, processo);
					break;
				default:
					insereFila(IO, processo);
					irt += 1;
					wt += rand() % 20;
					processo = insereValores(processo,((final - comeco)/CLOCKS_PER_SEC), irt, wt);
					wait(wt);
					insereFila(prontos, removeFila(IO));
					break;
			}
		}
		
		i++;
	}
}