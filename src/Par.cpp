#include "Par.hpp"

Par::Par(string usuario) {
	this->usuario = usuario;
}

void Par::inserta(Cuac * cuac) {
	list<Cuac *>::iterator it = l.begin();
	while (it != l.end() && * * it < * cuac) { 
		it++;
	}
	if (it == l.end()) {
		l.push_back(cuac);
	} else {
		l.insert(it, cuac);
	}
}

list<Cuac *> Par::consultar() {
	list<Cuac *> r = l;
	return r;
}
