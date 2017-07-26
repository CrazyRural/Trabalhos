#include <stdio.h>
#include <math.h>
/*Feito por: João Victor Araújo e Julia Rodrigues */

void metodoNewton_Raphson(int escolha, double X_anterior, double tolerancia, double iteracoes);
double calculaFuncao(double valor, int escolha);
double calculaFuncaoDerivada(double valor, int escolha);

int main(){

	int escolha, iteracoes;
	double X_anterior, tolerancia, resultado;

    printf("1- x^3+3x-1 \n2- x*log(x)-1 \n3- x^3-9x+4 \n4- x^2+4x-5 \n");
	printf ("\nDigite o numero da funcao desejada: ");
	scanf("%d", &escolha);
    printf("Chute um X: ");
    scanf("%lf", &X_anterior);
    printf("Informe uma tolerancia para o Metodo Newton-Raphson: ");
    scanf("%lf", &tolerancia);
    printf("Informe o numero maximo de iteracoes a serem feitas: ");
    scanf("%d", &iteracoes);
    metodoNewton_Raphson(escolha, X_anterior, tolerancia, iteracoes);
	return 0;
}

void metodoNewton_Raphson(int escolha, double X_anterior, double tolerancia, double iteracoes){

    int a=1;
    double X;

    do {
        if (a>1) { // O X atual nao vai para o anterior quando o algoritmo esta na primeira iteracao.
            X_anterior=X;
        }

        X=X_anterior-(calculaFuncao(X_anterior, escolha)/calculaFuncaoDerivada(X_anterior, escolha));

        if (a>iteracoes) {
            printf("\nO metodo nao convergiu com o numero de iteracoes dado pelo usuario.\n");
        }
        a++;

    } while(fabs(X-X_anterior)>tolerancia && iteracoes>a);
        printf("\nRaiz encontrada: %lf.\n", X);

}

double calculaFuncao(double valor, int escolha){
	double resultado;

	switch(escolha){
	 case 1:
	 resultado = pow(valor, 3) + (3* valor) -1;
	 break;
	case 2:
	 resultado = (valor* log(valor)) -1;
	 break;
	case 3:
	 resultado = pow(valor, 3) - (9* valor) +4;
	 break;
	case 4:
	 resultado = pow(valor, 2) + (4* valor) -5;
	 break;
	}

	return resultado;
}

double calculaFuncaoDerivada(double valor, int escolha){
	double resultado;

	switch(escolha){
	 case 1:
	 resultado = 3* pow(valor, 2) + 3;
	 break;
	case 2:
	 resultado = log(valor) + 1;
	 break;
	case 3:
	 resultado = 3* pow(valor, 2) -9 ;
	 break;
	case 4:
	 resultado = 2* (valor) + 4;
	 break;
	}
	return resultado;
}




