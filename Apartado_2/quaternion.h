typedef struct {
	float comp[4];
} quaternion;

float genera_float();
quaternion *genera_quaternion(float x, float y, float z, float w);
void imprime_quaternion(quaternion aux);
void libera_quaternion(quaternion *aux);
quaternion *genera_lista_quaternion(int N);
void anhade_elemento_lista(quaternion *lista, quaternion elemento, int pos);
void imprime_lista_quaternion(quaternion *lista, int N);
void libera_lista_quaternion(quaternion *lista);
void multiplica_lista_quaternion(quaternion *listaA, quaternion *listaB, quaternion *listaR, int N);
void segunda_computacion(quaternion *listaA, quaternion *listaAux, quaternion *listaR, int N);
