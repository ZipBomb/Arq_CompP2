#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <unistd.h>
#include <pmmintrin.h>
#include <omp.h>

typedef struct {
	__m128 comp;
} quaternion;

float genera_float() {
	float random = ((float) rand()) / (float) RAND_MAX;

	return random;
}

quaternion *genera_quaternion(float x, float y, float z, float w) {	
	quaternion *q = malloc(sizeof(quaternion));

	if(q != NULL) {
        float k[4]__attribute__((aligned(16)))={x,y,z,y};
	    q->comp=_mm_load_ps(&k[0]);
	}	
	return q;
}


void imprime_quaternion(quaternion aux) {
    float p[4]__attribute__((aligned(16)));
    _mm_store_ps(&p[0],aux.comp);
	printf("{ %f, %f, %f, %f }\n", p[0], p[1], p[2], p[3]);
}

void libera_quaternion(quaternion *aux) {
	if(aux != NULL)
		free(aux);
}

quaternion *genera_lista_quaternion(int N) {
	quaternion *v = malloc(N * sizeof(quaternion));

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
    free(lista);
}


void suma_quaternion(quaternion A, quaternion B, quaternion *R){ 
    R->comp=_mm_add_ps(A.comp,B.comp);
}


void suma_lista_quaternion(quaternion *listaA, quaternion *listaB, quaternion *listaR, int N){
    int i=0;
   
		for(i=0; i<N; i++){
		    suma_quaternion(*(listaA + i), *(listaB + i), (listaR + i));
		}
    }
}

void multiplica_quaternion(quaternion A, quaternion B, quaternion *R){
	float p[4]__attribute__((aligned(16)));
    _mm_store_ps(&p[0],A.comp);
    float q[4]__attribute__((aligned(16)));
    _mm_store_ps(&p[0],B.comp);
    float r[4]__attribute__((aligned(16)));
    
    r[0] = p[0] * q[0] - p[1] * q[1] - p[2] * q[2] - p[3] * q[3];
    r[1] = p[0] * q[1] + p[1] * q[0] + p[2] * q[3] - p[3] * q[2];
    r[2] = p[0] * q[2] - p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
    r[3] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];  
    
    R->comp=_mm_load_ps(&r[0]);      
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
	
