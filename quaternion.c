#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

#define N 10

typedef struct {
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
	return NULL;
}

quaternion *suma_quaternion(quaternion a, quaternion b) {
	return NULL;
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
	
