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
	quaternion *q = _mm_malloc(sizeof(quaternion),16);
	
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


void multiplica_quaternion(quaternion A, quaternion B, quaternion *R){
	__m128 mA,mA1,mA2,mA3,mB,mB1,mB2,mB3,mC,mC1,mC2,mC3,mR;
	
	mA=_mm_set_ps(A.comp[0],A.comp[0],A.comp[0],A.comp[0]);
	mA1=_mm_set_ps(-A.comp[1],A.comp[1],-A.comp[1],A.comp[1]);
	mA2=_mm_set_ps(-A.comp[2],A.comp[2],A.comp[2],-A.comp[2]);
	mA3=_mm_set_ps(-A.comp[3],-A.comp[3],-A.comp[3],A.comp[3]);
	
	mB=_mm_set_ps(B.comp[0],B.comp[1],B.comp[2],B.comp[3]);
	mB1=_mm_set_ps(B.comp[1],B.comp[0],B.comp[3],B.comp[2]);
	mB2=_mm_set_ps(B.comp[2],B.comp[3],B.comp[0],B.comp[1]);
	mB3=_mm_set_ps(B.comp[3],B.comp[2],B.comp[1],B.comp[0]);
	
	mC=_mm_mul_ps(mA,mB);
	mC1=_mm_mul_ps(mA1,mB1);
	mC2=_mm_mul_ps(mA2,mB2);
	mC3=_mm_mul_ps(mA3,mB3);
	
	mR=_mm_setzero_ps();
	
	mR=_mm_add_ps(mC,mC1);
	mR=_mm_add_ps(mR,mC2);
	mR=_mm_add_ps(mR,mC3);
	
		
	_mm_store_ps(R->comp,mR);    
}

void multiplica_lista_quaternion(quaternion *listaA, quaternion *listaB, quaternion *listaR, int N){
    int i=0;
    for(i=0; i<N/8; i++){
        multiplica_quaternion(*(listaA + i), *(listaB + i), (listaR + i));
        multiplica_quaternion(*(listaA + i+1), *(listaB + i+1), (listaR + i+1));
     	multiplica_quaternion(*(listaA + i+2), *(listaB + i+2), (listaR + i+2));
	    multiplica_quaternion(*(listaA + i+3), *(listaB + i+3), (listaR + i+3));
	    multiplica_quaternion(*(listaA + i+4), *(listaB + i+4), (listaR + i+4));
        multiplica_quaternion(*(listaA + i+5), *(listaB + i+5), (listaR + i+5));
        multiplica_quaternion(*(listaA + i+6), *(listaB + i+6), (listaR + i+6));
        multiplica_quaternion(*(listaA + i+7), *(listaB + i+7), (listaR + i+7));
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
	
