#include <stdio.h>
#include <stdlib.h>
#include <time.h>
	
double **alocaMatriz(int p);
double **criaMatriz(int p, double **mat);
int calculaTamanho(int n);
void multiplicaMatrizes(double **m1, double **m2,double **m3,int p);


int main(){
	
	int n;
	
	printf("DIGITE N\n");
	scanf("%d",&n);
	
	n = calculaTamanho(n);
	double **mat,**mat2,**resultado; 

	mat = alocaMatriz(n);
	mat2 = alocaMatriz(n);
	resultado = alocaMatriz(n);
	
			
	mat = criaMatriz(n,mat);
	printf("\n");
	mat2 =  criaMatriz(n,mat2);
	printf("\n");				
	multiplicaMatrizes(mat,mat2,resultado,n);
		
	return 0;
	
}

double **alocaMatriz(int p){

	int i;
	double **mat = (double**)malloc(p * sizeof (double));
	
	for(i = 0; i< p;i++){
		mat[i] = (double**)malloc(p * sizeof (double));
	}
	return mat;
}
	
double **criaMatriz(int p, double **mat){
	
	srand(time(NULL));
	int n=p ,i,j;
	double a=0,b=0;
			
	for(i=0;i<n;i++){
		 for(j=0;j<n;j++){
		   a = rand() ;
		   b = rand() ;
		   mat[i][j]=a/b;
		  } 
	}
	
	
	/*for(i=0;i<n;i++){
			for(j=0;j<n;j++){
			 printf("%.2f  ",mat[i][j]);
			 }
		printf("\n");
	} */ 
	return  mat;
}

int calculaTamanho(int n){
	
	int tamanho = 1;
	int i;
	for(i = 0; i < n; i++){
		tamanho += pow(2,i);
	}

	return tamanho;
}
	
void multiplicaMatrizes(double **m1, double **m2, double **m3,int p){

	int n = p,i,j,x;		
				
	for(i=0; i< n; i++){
	    for(j=0; j< n; j++){
		   	for(x=0; x < n; x++){
	        	m3[i][j]= m3[i][j] + m1[i][x] * m2[x][j];
		   	}
       }
    }
	for(i=0;i<n;i++){
			for(j=0;j<n;j++){
			 printf("%.2f  ",m3[i][j]);
			 }
		printf("\n");
	}  		
}

