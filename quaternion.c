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


void suma_quaternion(quaternion sum1,quaternion sum2,quaternion *res){
    int i=0;
    for(i=0;i<4;i++){
        res->comp[i] = sum1.comp[i] + sum2.comp[i];
    }
}


void suma_lista_quaternion(quaternion *listaSum1,quaternion *listaSum2,quaternion *listaRes){
    int i=0;
    for(i=0;i<N;i++){
        suma_quaternion(*(listaSum1 + i),*(listaSum2 + i),(listaRes + i));
    }
}
	
