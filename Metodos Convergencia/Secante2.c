#include <stdio.h>
#include <math.h>
/*Feito por: João Victor Araújo e Julia Rodrigues */

void metodoDaSecante(int escolha, double a, double b, double tolerancia, int iteracoes);
double calculaFuncao(double valor, int escolha);

int main(){

	int escolha, iteracoes;
	double a, b, tolerancia, resultado;

    printf("1- x^3+3x-1 \n2- x*log(x)-1 \n3- x^3-9x+4 \n4- x^2+4x-5 \n");
	printf ("\nDigite o numero da funcao desejada: ");
	scanf("%d", &escolha);
    printf("Chute o intervalo a e b: ");
    scanf("%lf", &a);
    scanf("%lf", &b);
    printf("Informe uma tolerancia para o Metodo da Secante: ");
    scanf("%lf", &tolerancia);
    printf("Informe o numero maximo de iteracoes: ");
    scanf("%d", &iteracoes);
    metodoDaSecante(escolha, a, b, tolerancia, iteracoes);

	return 0;
}

void metodoDaSecante(int escolha, double a, double b, double tolerancia, int iteracoes){
    int k = 0;
    double c, f_a = 0, f_b = 0, f_c;
    while(k < iteracoes){
        f_a = calculaFuncao(a, escolha);
        f_b = calculaFuncao(b , escolha);
        c = (b*f_a - a*f_b)/(f_a-f_b);
        if ( fabs(c-b) < tolerancia){
            printf("\nA raiz e: %lf.\n", c);
            break;
        }
        a = b;
        b = c;
        k++;
    }
     if (k >= iteracoes){
        printf("\nO numero maximo de iteracoes foi atingido.\n");
   }

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





