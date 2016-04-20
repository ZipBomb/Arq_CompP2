#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "quaternion.h"

int main() {	
	quaternion *lista_op_1;
	quaternion *lista_op_2;
	quaternion *lista_res;	
	int i;	
	float x, y, z, w;
	
	lista_op_1 = genera_lista_quaternion();
	lista_op_2 = genera_lista_quaternion();
	lista_res = genera_lista_quaternion();

	srand(time(NULL));

	quaternion *aux;
	for(i=0; i<N; i++) {
		x = genera_float(); y = genera_float(); z = genera_float(); w = genera_float();
		aux = genera_quaternion(x, y, z, w);	
		anhade_elemento_lista(lista_op_1, *aux, i);		
	}
	for(i=0; i<N; i++) {
		x = genera_float(); y = genera_float(); z = genera_float(); w = genera_float();
		aux = genera_quaternion(x, y, z, w);	
		anhade_elemento_lista(lista_op_2, *aux, i);		
	}
	for(i=0; i<N; i++) {
		x = genera_float(); y = genera_float(); z = genera_float(); w = genera_float();
		aux = genera_quaternion(x, y, z, w);	
		anhade_elemento_lista(lista_res, *aux, i);		
	}
	
	printf("LISTA 1:\n");
	imprime_lista_quaternion(lista_op_1);
	printf("LISTA 2:\n");
	imprime_lista_quaternion(lista_op_2);
	printf("LISTA 3:\n");
	imprime_lista_quaternion(lista_res);

	libera_lista_quaternion(lista_op_1);
	libera_lista_quaternion(lista_op_2);
	libera_lista_quaternion(lista_res);
}	
