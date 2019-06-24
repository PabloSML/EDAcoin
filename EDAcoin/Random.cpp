#include <cstdlib>
#include <ctime>
#include "random.h"

//Devuelve un valor entero pseudo-aleatorio entre a y b.
int randIntBetween(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

//Devuelve un valor real pseudo-aleatorio entre 0 y 1.
double randNormalize()
{
	return rand() / (double)RAND_MAX;
}

//Devuelve un valor real pseudo-aleatorio entre a y b.
double randDoubleBetween(double a, double b)
{
	return randNormalize()*(b - a) + a;
}

//Cambia la seed. Ejecutar una sola vez antes de utilizar caulquier funcion de la libreria.
void randomize()
{
	srand((unsigned int)time(NULL));
}

//Dado un arreglo de ints, los mezcla de manera aleatoria.
void shuffleIntArray(int input[], int dim)
{
	int aux, rand;

	for (int i = 0; i < dim; i++)
	{
		rand = randIntBetween(0, dim - 1);
		aux = input[i];
		input[i] = input[rand];
		input[rand] = aux;
	}
}
