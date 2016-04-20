#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

#define N 10

typedef struct  {
	float comp[4];
} quaternion;

float genera_float() {
	float random = ((float) rand()) / (float) RAND_MAX;

	return random;
}

quaternion *genera_quaternion(float x, float y, float z, float w) {	
	quaternion *q = malloc(sizeof(quaternion));
	
	if(q != NULL) {
		q->comp[0] = x; q->comp[1] = y; q->comp[2] = z; q->comp[3] = w;
	}	
	return q;
}

quaternion *multiplica_quaternion(quaternion a, quaternion b) {

}

quaternion *suma_quaternion(quaternion a, quaternion b) {

}

void imprime_quaternion(quaternion aux) {
	printf("{ %f, %f, %f, %f }\n", aux.comp[0], aux.comp[1], aux.comp[2], aux.comp[3]);
}

void libera_quaternion(quaternion *aux) {
	if(aux != NULL)
		free(aux);
}

quaternion *genera_lista_quaternion() {
	quaternion *v = malloc(N * sizeof(quaternion));

	return v;
}

void anhade_elemento_lista(quaternion *lista, quaternion elemento, int pos) {
	if(lista != NULL)
		*(lista + pos) = elemento;
}

void imprime_lista_quaternion(quaternion *lista) {
	quaternion aux;
	int i;
	for(i=0; i<N; i++) {
		aux = *(lista + i);
		imprime_quaternion(aux);
	}		
}

void libera_lista_quaternion(quaternion *lista) {
	int i;
	for(i=0; i<N; i++) {
		libera_quaternion(lista + i);		
	}
}

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
