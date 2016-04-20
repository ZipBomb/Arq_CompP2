#define N 10

typedef struct {
	float comp[4];
} quaternion;

float genera_float();
quaternion *genera_quaternion(float x, float y, float z, float w);
quaternion *multiplica_quaternion(quaternion a, quaternion b);
quaternion *suma_quaternion(quaternion a, quaternion b);
void imprime_quaternion(quaternion aux);
void libera_quaternion(quaternion *aux);
quaternion *genera_lista_quaternion();
void anhade_elemento_lista(quaternion *lista, quaternion elemento, int pos);
void imprime_lista_quaternion(quaternion *lista);
void libera_lista_quaternion(quaternion *lista);
