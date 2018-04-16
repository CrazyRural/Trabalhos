#include <stdio.h>
#include <math.h>
/*Feito por: João Victor Araújo e Julia Rodrigues */


typedef double (*Operando)(double);
double f(double funcao[], Operando op[], int grau, double d);
void defineEscolha(int grau, Operando op[], double funcao[]);
double metodoBissecao(double funcao[], Operando op[], int grau, double a, double b, double e);
double metodoFalsaPosicao(double funcao[], Operando op[], int grau, double a, double b, double e);

int main(){


	int aux, multiplicador, escolha, grau;
	double a,b, e, c;

	printf("Digite o Intervalo e o Erro: ");
	scanf("%lf %lf %lf", &a, &b, &e);

	printf("Digite o maior grau da expressão: ");
	scanf("%d", &grau);

	double funcao[grau+1];
	Operando op[grau+1];

	defineEscolha(grau, op, funcao);
	
	c = metodoBissecao(funcao, op, grau, a, b, e);
	printf("\nRaiz aproximada Bisseção: %.8lf\n", c);
	c = metodoFalsaPosicao(funcao, op, grau, a, b, e); 
	printf("Raiz aproximada Falsa Posição: %.8lf\n\n", c);

	return 0;
}


double f(double funcao[], Operando op[], int grau, double d){
	int i;
    double result = 0;
    for (i = grau;i >= 0;i--) {
		if (op[i] == NULL) {
			result += funcao[i] * pow(d, i/1.0);
		} else {
			result += op[i](funcao[i] * pow(d, i/1.0));
		}	
    }
    return result;
}
void defineEscolha(int grau, Operando op[], double funcao[]){
	int i, expressao;

	for (i = grau;i >= 0; i--) {

		printf("\nTipos de funções disponíveis: \n");
		printf("0- Polinominal \n1- Logaritmo Neperiano \n2- Seno \n3- Cosseno \n4- Raiz Quadrada \n5- Log \n6- Exponencial\n");
		printf("Insira o número correspondente a função desejada: ");
		scanf("%d", &expressao);
		
		switch (expressao) {
			case 1:
				op[i] = log;
				break;
			case 2:
				op[i] = sin;
				break;
			case 3:
				op[i] = cos;
				break;
			case 4:
				op[i] = sqrt;
				break;
			case 5:
				op[i] = log10;
				break;
			case 6:
				op[i] = exp;
				break;
			default :
				op[i] = NULL;
		}
		printf("Informe o coeficiente de %dº grau de F: ", i);
		scanf("%lf", &funcao[i]);
    }	
}

double metodoBissecao(double funcao[], Operando op[], int grau, double a, double b, double e){
	double fa = (funcao, op, grau, a), fb = (funcao, op, grau, b),c = 0.0;

	if(fa * fb < 0){
		 c = 0.0;
		 return c;
	}

	while (fabs(a - b) > e){
		c = (a+b)/2;
		if(f(funcao, op, grau, a) * f(funcao, op, grau, c) < 0){
			b = c;
			//fb = fc;
		}else{
			a = c;
			//fa = fc;
		}
	}

	return c;
}
double metodoFalsaPosicao(double funcao[], Operando op[], int grau, double a, double b, double e){

	double fa = f(funcao, op, grau, a), fb = f(funcao, op, grau, b), fc, c;
	c = ((fa*b)-(fb*a))/(fa-fb);
	

	while(fabs(f(funcao, op, grau, c)) > e){

		c = ((fa*b)-(fb*a))/(fa-fb);
		fc = f(funcao, op, grau, c);
		
		if(fa * fc < 0){
			b = c;
			fb = fc;
		}else{
			a = c;
			fa = fc;
		}
	}
	return c;
}