#pragma once
#include "Observer.h"
#include <iostream>
#include <list>

using namespace std;

/*
* Subject
* Clase abstracta que defije un sujeto, de quien heredan los modelos para tener
* observers y notificar cambios de estado de los mismos modelso.
*/
class Subject {

public:

	/*
	* Constructores y destructores
	*/
	Subject(void){}
	virtual ~Subject(void);

	/*
	* attach
	* Agrega observers al sujeto
	*/
	void attach(Observer* ptr);

	/*
	* dettach
	* Remueve un observer del sujeto
	*/
	bool dettach(Observer* ptr);

	/*
	*dettachAll
	*Remueve todos los observers del sujeto
	*/
	void dettachAll(void);

	/*
	* ping
	* llamada externa a notifyAllObservers
	*/
	virtual void ping(void);

protected:

	/*
	* notifyObservers
	* Notifica a todos los observers de un cambio
	* ejecutando los metodos update() de cada uno.
	*/
	void notifyObservers(void);

private:
	list<Observer*> observers;

	//Subject(const Subject&){} // impide la copia
};