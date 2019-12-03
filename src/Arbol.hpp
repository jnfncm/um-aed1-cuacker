#ifndef _ARBOL
#define _ARBOL

#include "Nodo.hpp"
#include "Fecha.hpp"
#include <iostream>
using namespace std;

class Arbol {
	private:
		Nodo * raiz;
	public:
		Arbol();
		~Arbol();
		void insertar(Cuac * cuac);
		void last(int n);
		void date(Fecha f1, Fecha f2);
};

#endif
