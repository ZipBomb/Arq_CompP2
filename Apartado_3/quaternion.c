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
    free(lista);
}


void multiplica_quaternion(quaternion A, quaternion B, quaternion *R){
	__m128 mA,mB,mAux1,mAux2,mAux3,mAux4,mAux5,mR;
	
	mA=_mm_load_ps(A.comp);
	mB=_mm_load_ps(B.comp);
	
	mAux1=_mm_shuffle_ps(mA,mA,_MM_SHUFFLE(0,1,2,3));
	mAux2=_mm_shuffle_ps(mB,mB,_MM_SHUFFLE(0,1,0,1));
	mAux3=_mm_shuffle_ps(mB,mB,_MM_SHUFFLE(2,3,2,3));
	
	mAux4=_mm_hsub_ps(_mm_mul_ps(mA,mAux2),_mm_mul_ps(mAux1,mAux3));
	mAux5=_mm_hadd_ps(_mm_mul_ps(mA,mAux3),_mm_mul_ps(mAux1,mAux2));
	
	mR=_mm_addsub_ps(_mm_shuffle_ps(mAux5,mAux4,_MM_SHUFFLE(3,2,1,0)),_mm_shuffle_ps(mAux5,mAux4,_MM_SHUFFLE(2,3,0,1)));	
	mR=_mm_shuffle_ps(mR,mR,_MM_SHUFFLE(2,1,3,0));
	
	
		
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
	
