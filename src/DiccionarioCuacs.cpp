#include "DiccionarioCuacs.hpp"
 
void DiccionarioCuacs::insertar(Cuac * nuevo) {
	tabla.insertar(nuevo);
	arbol.insertar(nuevo);
}
void DiccionarioCuacs::follow(string nombre) {
	tabla.consultar(nombre);
}
void DiccionarioCuacs::last(int n) {
	arbol.last(n);
}
void DiccionarioCuacs::date(Fecha f1, Fecha f2) {
	arbol.date(f1, f2);
}
int DiccionarioCuacs::numElem() {
	return tabla.numElem();
}
