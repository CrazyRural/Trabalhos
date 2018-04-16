#include<stdio.h>
#include<math.h>

int main(){
    double t0,t = 0, theta = 0.5;
    double ac, v = 0; 
    int movimentos, contador = 1 ;
    scanf("%d", &movimentos);

    do{
        printf("%dº Movimento \n", contador);
        t0 = t;
        ac = (-1) * 1 * sin(theta);
        printf("Theta = %lf\nA = %lf\nV = %lf\nT = %.2lf \n\n", t, theta, v, ac);   
        t += 0.1;
        v = v + ac *(t - t0);
        theta = theta + v * (t - t0);
        contador++;
    }while(contador <= movimentos);

}