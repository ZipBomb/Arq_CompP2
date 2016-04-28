#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "quaternion.h"
#include "rutinas_clock.h"

int main() {	
	quaternion *lista_A;
	quaternion *lista_B;
	quaternion *lista_C;	
    quaternion *lista_DP;
	int i;	
	float x, y, z, w;
    double ck=0;
	
    FILE *fp;
    if((fp = fopen("puntos.txt","a+")) == NULL)
        perror("en la apertura del archivo");


	lista_A = genera_lista_quaternion();
	lista_B = genera_lista_quaternion();
	lista_C = genera_lista_quaternion();
    lista_DP = genera_lista_quaternion();

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
		x = genera_float(); y = genera_float(); z = genera_float(); w = genera_float();
		aux = genera_quaternion(x, y, z, w);	
		anhade_elemento_lista(lista_C, *aux, i);		
	}
    for(i=0; i<N ;i++){
        x = 0; y = 0; z = 0; w = 0;
        aux = genera_quaternion(x, y, z, w);
        anhade_elemento_lista(lista_DP, *aux, i);
    }
	
	
	for(i=0; i<N ;i++){
        x = 0; y = 0; z = 0; w = 0;
        aux = genera_quaternion(x, y, z, w);
        anhade_elemento_lista(lista_DP, *aux, i);
    }
    
    
    start_counter();
    for(i=0; i<20; i++){
        multiplica_lista_quaternion(lista_A,lista_B,lista_C);        
        segunda_computacion(lista_C, lista_DP, lista_DP);
    }
    ck=get_counter();
    ck=ck/(N*20);

    printf("Ciclos de acceso a un quaternion: %f\n",ck);
    
    fprintf(fp,"%f  ",ck);
    fprintf(fp,"%d\n",N);
    fclose(fp);
    
    printf("LISTA 1:\n");
    imprime_lista_quaternion(lista_A);
    printf("LISTA 2:\n");
    imprime_lista_quaternion(lista_B);
    printf("LISTA 3:\n");
    imprime_lista_quaternion(lista_C);
    printf("LISTA FINAL:\n");
    imprime_lista_quaternion(lista_DP);

	libera_lista_quaternion(lista_A);
	libera_lista_quaternion(lista_B);
	libera_lista_quaternion(lista_C);
}	
