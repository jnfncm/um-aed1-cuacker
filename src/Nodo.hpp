#ifndef _NODO
#define _NODO

#include "Cuac.hpp"
#include "Fecha.hpp"
#include <list>
#include <iostream>
using namespace std;

class Nodo {
	friend class Arbol;
	private:
		int altura;
		Fecha fecha;
		list<Cuac *> cuacs;
		Nodo * der;
		Nodo * izq;
		int checkAltura();
		Nodo * RSI();
		Nodo * RSD();
		Nodo * RDI();
		Nodo * RDD();
		Nodo * balancear();
		void inordenLast(bool lastB, int lastM, int * lastC);
		void inordenDate(Fecha f1, Fecha f2, int * count);
	public:
		Nodo(Fecha fecha);
		~Nodo();
		void insertar(Cuac * cuac);
};

#endif
