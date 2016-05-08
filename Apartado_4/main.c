#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "quaternion.h"
#include "rutinas_clock.h"

int main(int argc, char *argv[]) {
	int N;

	if(argc != 2) {
		printf("Uso correcto: ./test <N>");
		exit(0);
	}
	else
		N = atoi(argv[1]);

	quaternion *lista_A;
	quaternion *lista_B;
	quaternion *lista_C;	
    quaternion *lista_Aux;
	int i;	
	float x, y, z, w;
    double ck=0;

	lista_A = genera_lista_quaternion(N);
	lista_B = genera_lista_quaternion(N);
	lista_C = genera_lista_quaternion(N);
    lista_Aux = genera_lista_quaternion(N);

	srand(time(NULL));
	
	quaternion *aux;
	
	for(i=0; i<N; i++) {
		x = genera_float(); y = genera_float(); z = genera_float(); w = genera_float();
		aux = genera_quaternion(x, y, z, w);	
		anhade_elemento_lista(lista_A, *aux, i);		
	}	
	for(i=0; i<N; i++) {
		x = genera_float(); y = genera_float(); z = genera_float(); w = genera_float();
		aux = genera_quaternion(x, y, z, w);	
		anhade_elemento_lista(lista_B, *aux, i);		
	}
	for(i=0; i<N; i++) {
		x = 0; y = 0; z = 0; w = 0;
		aux = genera_quaternion(x, y, z, w);	
		anhade_elemento_lista(lista_C, *aux, i);		
	}
    for(i=0; i<N ;i++){
        x = 0; y = 0; z = 0; w = 0;
        aux = genera_quaternion(x, y, z, w);
        anhade_elemento_lista(lista_Aux, *aux, i);
    }
    
    quaternion *dp;
    x = 0; y = 0; z = 0; w = 0;
    dp = genera_quaternion(x, y, z, w);
       
    start_counter();
    for(i=0; i<20; i++){
        multiplica_lista_quaternion(lista_A,lista_B,lista_C, N);    
        segunda_computacion(lista_C, lista_Aux, dp, N);
    }
    ck=get_counter();
    ck=ck/(N*20);

    printf("\nCiclos de acceso a un quaternion [N = %d]: %f\n",N, ck);
    printf("Valores de DP: ");
    imprime_quaternion(*dp);
    
    libera_lista_quaternion(lista_A);
    libera_lista_quaternion(lista_B);
    libera_lista_quaternion(lista_C);
    libera_lista_quaternion(lista_Aux);
    libera_quaternion(dp);
	
    return 1;
}	
