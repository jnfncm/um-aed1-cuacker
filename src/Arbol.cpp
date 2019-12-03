#include "Arbol.hpp"

Arbol::Arbol() {
    raiz = NULL;
}

Arbol::~Arbol() {
    delete raiz;
}

void Arbol::insertar(Cuac * cuac) {
    if (raiz == NULL) {
   	 raiz = new Nodo(cuac->fecha);
    }
    raiz->insertar(cuac);
    raiz = raiz->balancear();
}

void Arbol::last(int n) {
    int count = 0;
    raiz->inordenLast(true, n, &count);
    cout << "Total: " << count << " cuac" << endl;
}

void Arbol::date(Fecha f1, Fecha f2) {
    cout << "date "; f1.escribir(); cout << " "; f2.escribir(); cout << endl;
    int count = 0;
    raiz->inordenDate(f1, f2, & count);
    cout << "Total: " << count << " cuac" << endl;
}
