#ifndef RANDOM_H
#define RANDOM_H

//Devuelve un valor entero pseudo-aleatorio entre a y b.
int randIntBetween(int a, int b);

//Devuelve un valor real pseudo-aleatorio entre 0 y 1.
double randNormalize();

//Devuelve un valor real pseudo-aleatorio entre a y b.
double randDoubleBetween(double a, double b);

//Cambia la seed. Ejecutar una sola vez antes de utilizar caulquier funcion de la libreria.
void randomize();

//Dado un arreglo de ints, los mezcla de manera aleatoria.
void shuffleIntArray(int input[], int dim);

#endif