#define N 10

typedef struct {
	float comp[4];
} quaternion;

float genera_float();
quaternion *genera_quaternion(float x, float y, float z, float w);
void imprime_quaternion(quaternion aux);
void libera_quaternion(quaternion *aux);
quaternion *genera_lista_quaternion();
void anhade_elemento_lista(quaternion *lista, quaternion elemento, int pos);
void imprime_lista_quaternion(quaternion *lista);
void libera_lista_quaternion(quaternion *lista);
void suma_quaternion(quaternion sum1,quaternion sum2,quaternion *res);
void suma_lista_quaternion(quaternion *listaSum1,quaternion *listaSum2,quaternion *listaRes);
void multiplica_lista_quaternion(quaternion *listaA,quaternion *listaB,quaternion *listaR);
