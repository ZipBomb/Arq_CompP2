#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <unistd.h>
#include <pmmintrin.h>

typedef struct {
	float comp[4];
} quaternion;

float genera_float() {
	float random = ((float) rand()) / (float) RAND_MAX;

	return random;
}

quaternion *genera_quaternion(float x, float y, float z, float w) {	
	quaternion *q = _mm_malloc(sizeof(quaternion),512);
	
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
		_mm_free(aux);
}

quaternion *genera_lista_quaternion(int N) {
	quaternion *v = _mm_malloc(N * sizeof(quaternion),512);

	return v;
}

void anhade_elemento_lista(quaternion *lista, quaternion elemento, int pos) {
	if(lista != NULL)
		*(lista + pos) = elemento;
}

void imprime_lista_quaternion(quaternion *lista, int N) {
	quaternion aux;
	int i;
	for(i=0; i<N; i++) {
		aux = *(lista + i);
		imprime_quaternion(aux);
	}		
}

void libera_lista_quaternion(quaternion *lista) {
    _mm_free(lista);
}


void suma_quaternion(quaternion A, quaternion B, quaternion *R){
    int i=0;
    for(i=0; i<4; i++){
        R->comp[i] = A.comp[i] + B.comp[i];
    }
}


void suma_lista_quaternion(quaternion *listaA, quaternion *listaB, quaternion *listaR, int N){
    int i=0;
    for(i=0; i<N/2; i++){
        suma_quaternion(*(listaA + i), *(listaB + i), (listaR + i));
        suma_quaternion(*(listaA + (i+1)), *(listaB + (i+1)), (listaR + (i+1)));
    }
}

void multiplica_quaternion(quaternion A, quaternion B, quaternion *R){
    R->comp[0] = A.comp[0] * B.comp[0] - A.comp[1] * B.comp[1] - A.comp[2] * B.comp[2] - A.comp[3] * B.comp[3];
    R->comp[1] = A.comp[0] * B.comp[1] + A.comp[1] * B.comp[0] + A.comp[2] * B.comp[3] - A.comp[3] * B.comp[2];
    R->comp[2] = A.comp[0] * B.comp[2] - A.comp[1] * B.comp[3] + A.comp[2] * B.comp[0] + A.comp[3] * B.comp[1];
    R->comp[3] = A.comp[0]*B.comp[3] + A.comp[1]*B.comp[2] - A.comp[2]*B.comp[1] + A.comp[3]*B.comp[0];  
}

void multiplica_lista_quaternion(quaternion *listaA, quaternion *listaB, quaternion *listaR, int N){
    int i=0;
    for(i=0; i<N; i++){
        multiplica_quaternion(*(listaA + i), *(listaB + i), (listaR + i));
    }
}

void segunda_computacion(quaternion *listaA, quaternion *listaAux, quaternion *listaR, int N){
    multiplica_lista_quaternion(listaA, listaA, listaAux, N);
    suma_lista_quaternion(listaAux, listaR, listaR, N);
}
	
