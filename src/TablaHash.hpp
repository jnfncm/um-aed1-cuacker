#ifndef _TABLA_HASH
#define _TABLA_HASH

#include "Cuac.hpp"
#include "Par.hpp"
#include <list>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

class TablaHash {
	private:
		int M, nElem;
		list<Par> *T;
		int hashCode(Cuac * nuevo);
		int hashCode(string nombre);
		void reestructurar();
	public:
		TablaHash();
		~TablaHash();
		void insertar(Cuac * nuevo);
		void consultar(string nombre);
		int numElem (void) {
			return nElem;
		}
};

#endif
