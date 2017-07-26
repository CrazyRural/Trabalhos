/*
				Feito por João Victor Araújo, Julia Rodrigues e Victor Diniz
*/
#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 25

typedef struct PCB PCB;
typedef struct elemento Elemento;
typedef struct fila Fila;

struct PCB{
	pid_t PID;
	double CUT;
	int IRT;
	int WT;
};

struct elemento{
	PCB* processo;
	Elemento* proximo;
};

struct fila{
	Elemento* primeiro;
	Elemento* ultimo;
	int tamanho;
};

int filaVazia(Fila *f){
	return (f == NULL);
}
int filaCheia(Fila *f){
	return(f->tamanho == TAMANHO);
}
Fila* criaFila(){
	Fila* f = (Fila*) malloc(sizeof(Fila));
	f->primeiro = f->ultimo = NULL;
	return f;
}

void insereFila(Fila* f, PCB* pcb){
	if(filaCheia(f)) 
		exit(1);
	Elemento* n = (Elemento*) malloc(sizeof(Elemento));
	n->processo = pcb; 	
	n->proximo = NULL; 
	if (f->ultimo != NULL)
		f->ultimo->proximo = n;
	else 
		f->primeiro = n;
	f->ultimo = n;
	f->tamanho++;
}
PCB* removeFila(Fila* f){
	Elemento* t;
	PCB* pcb;
	if (filaVazia(f)) 
		exit(1); 
	t = f->primeiro;
	pcb = t->processo;
	f->primeiro = t->proximo;
	if (f->primeiro == NULL)
		f->ultimo = NULL;
	free(t);
	return pcb;
}

void liberaFila(Fila* f){
	Elemento* q = f->primeiro;
	while (q!=NULL) {
		Elemento* t = q->proximo;
		free(q);
		q = t;
	}
	free(f);
}

PCB* criaProcesso(pid_t PID){
	PCB* processo = (PCB*) malloc(sizeof(PCB));
	processo->PID = PID;
	processo->CUT = processo->IRT = processo->WT = 0;
	return processo;
}
PCB* insereValores(PCB* pcb, double cut , int irt, int wt ){
	pcb->CUT = cut;
	pcb->IRT = irt;
	pcb->WT =wt;
	return pcb;

}

void imprimeProcesso(PCB* processo){
	printf("Processo %d foi executado em %lf segundos, com %d IRT e %d WT\n", processo->PID, processo->CUT, processo->IRT, processo->WT);
}

void imprimeFila(Fila* f){
	Elemento* aux = f->primeiro;
	int i = 0;
	while(aux != NULL){
		printf("PID: %d\n", aux->processo->PID);
		printf("CUT: %lf\n", aux->processo->CUT);
		printf("IRT: %d\n", aux->processo->IRT);
		printf("WT: %d\n", aux->processo->WT);
		aux = aux->proximo;
		i++;
	}
	printf("\n-----------------------------\n");
}