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
		_mm_free(aux);
}

quaternion *genera_lista_quaternion(int N) {
	quaternion *v = _mm_malloc(N * sizeof(quaternion),16);

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

void multiplica_quaternion(quaternion A, quaternion B, quaternion *R){
	__m128 m0,m1,m2,m3,mR;
	
	m0=_mm_set_ps(A.comp[0]*B.comp[0],A.comp[1]*-B.comp[1],A.comp[2]*-B.comp[2],A.comp[3]*-B.comp[3]);
	m1=_mm_set_ps(A.comp[0]*B.comp[1],A.comp[1]*B.comp[0],A.comp[2]*B.comp[3],A.comp[3]*-B.comp[2]);
	m2=_mm_set_ps(A.comp[0]*B.comp[2],A.comp[1]*-B.comp[3],A.comp[2]*B.comp[0],A.comp[3]*B.comp[1]);
	m3=_mm_set_ps(A.comp[0]*B.comp[3],A.comp[1]*B.comp[2],A.comp[2]*-B.comp[1],A.comp[3]*B.comp[0]);
	
	mR=_mm_setzero_ps();
	mR=_mm_add_ps(mR,m0);
	mR=_mm_add_ps(mR,m1);
	mR=_mm_add_ps(mR,m2);
	mR=_mm_add_ps(mR,m3);
	
	_mm_store_ps(R->comp,mR);
}

void multiplica_lista_quaternion(quaternion *listaA, quaternion *listaB, quaternion *listaR, int N){
    int i=0;    
    for(i=0; i<N; i=i+4){
        multiplica_quaternion(*(listaA + i), *(listaB + i), (listaR + i));
        multiplica_quaternion(*(listaA + i+1), *(listaB + i+1), (listaR + i+1));
    	multiplica_quaternion(*(listaA + i+2), *(listaB + i+2), (listaR + i+2));
        multiplica_quaternion(*(listaA + i+3), *(listaB + i+3), (listaR + i+3));	   
    }    
}

void suma_acumulada(quaternion *listaC, quaternion *dp, int N){
	int i=0;
	__m128 mC,mDP;
	mDP=_mm_setzero_ps();
    for(i=0; i<N; i++){      	
    	mC=_mm_load_ps((listaC+i)->comp);
    	mDP=_mm_add_ps(mDP,mC);
    }
    _mm_store_ps(dp->comp,mDP);
}

void segunda_computacion(quaternion *listaA, quaternion *listaAux, quaternion *dp, int N){
    multiplica_lista_quaternion(listaA, listaA, listaAux, N);
    suma_acumulada(listaAux, dp, N);
}
	
