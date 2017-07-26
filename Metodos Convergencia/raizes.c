#include <stdio.h>
#include <math.h>

typedef double (*Operacao)(double);

double calculaFuncao(double funcao[], Operacao op[], int Grau, double Z) {
    int i;
    double Y=0;
    for (i=Grau;i>=0;i--) {
		if (op[i] == NULL) {
			Y+=funcao[i]*pow(Z, i/1.0);
		} else {
			Y+=op[i](funcao[i]*pow(Z, i/1.0));
		}	
    }
    return Y;
}

double bissecao (double funcao[], Operacao op[], int Grau, double e, double a, double b) {
	double xi = 0;
	
	while (fabs(a-b) > e) {
		xi = (a+b)/2;
		if (calculaFuncao(funcao, op, Grau, xi)*calculaFuncao(funcao, op, Grau, a) < 0 ) {
			b = xi;
		} else {
			a = xi;
		}
	}
	
	return xi;
}

double falsa_posicao (double funcao[], Operacao op[], int Grau, double e, double a, double b) {
	double xi = 0, ex = 999999999, fa, fb, x_anterior = 0;
	
	while (ex > e) {
		fa = calculaFuncao(funcao, op, Grau, a);
		fb = calculaFuncao(funcao, op, Grau, b);
		xi = (a*fb - b*fa) / (fb + fa);
		if (calculaFuncao(funcao, op, Grau, xi) < 0) {
			a = xi;
		} else {
			b = xi;
		}
		ex = fabs(x_anterior - xi)/xi;
		x_anterior = xi;
	}
	
	return xi;
}

int main () {
	
	int Grau, i, funcao_especial;
	double a, b, e;

    printf("Informe o maior grau do polinomio F: ");
    scanf("%d", &Grau);

    double funcao[Grau+1];
	Operacao op[Grau+1];

    for (i=Grau;i>=0;i--) { // informa o coeficiente de cada grau do polinomio
	
		printf("1-logaritmo neperiano\n2-Seno\n3-Cosseno\n4-Raiz quadrada\n5-log10\n6- exponencial\n");
		printf("Escolha o tipo de funcao:\n");
		scanf("%d", &funcao_especial);
		
		switch (funcao_especial) {
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
		
		printf("Informe o coeficiente de grau %d de F: ", i);
		scanf("%lf", &funcao[i]);
    }	
	
	printf("Informe a tolerancia, a e b: ");
	scanf("%lf %lf %lf", &e, &a, &b);
	
	printf("Bissecao, raiz aproximada: %.5lf\n", bissecao(funcao, op, Grau, e, a, b));
	printf("Falsa posicao, raiz aproximada: %.5lf \n", falsa_posicao(funcao, op, Grau, e, a, b));
	double c = bissecao(funcao, op, Grau, e, a, b), d = falsa_posicao(funcao, op, Grau, e, a, b);
	printf("f(%.lf) = %.lf\n", c, calculaFuncao(funcao, op, Grau, c));
	printf("f(%.lf) = %.lf\n", d, calculaFuncao(funcao, op, Grau, d));
	
	return 0;
}