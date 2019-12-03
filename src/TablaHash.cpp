#include "TablaHash.hpp"
using namespace std;

TablaHash::TablaHash() {
	M = 11177;
	nElem = 0;
	T = new list<Par>[M];
}

TablaHash::~TablaHash() {
	delete[] T;
}

int TablaHash::hashCode(Cuac * nuevo) {
	return hashCode(nuevo->usuario);
}

int TablaHash::hashCode(string usuario) {
	int valorHash = 5381;
	for(unsigned i=0; i < usuario.length(); i++) {
		valorHash *= 33;
		valorHash ^= usuario[i];
	}
	return abs(valorHash) % M;
}

void TablaHash::reestructurar() {
	int N = M;
	list<Par> *TN;
	M = M * 2;
	TN = T;
	T = new list<Par>[M];
	nElem = 0;
	for(int i = 0; i < N; i++) {
		list<Par>::iterator it = TN[i].begin();
		while(it != TN[i].end()) {
			list<Cuac *>::iterator ip = it->l.begin();
			while(ip != it->l.end()) {
				insertar(* ip);
				ip++;
			}
			it++;
		}
	}
	delete[] TN;
}

void TablaHash::insertar(Cuac * cuac) {
	int codigo = hashCode(cuac);
	list<Par>::iterator it = T[codigo].begin();
	while (it != T[codigo].end() && it->usuario != cuac->usuario) {
		it++;
	}
	if (it != T[codigo].end() && it->usuario == cuac->usuario) {
		(*it).inserta(cuac);
		nElem++;
	} else {
		Par par = Par(cuac->usuario);
		par.inserta(cuac);
		nElem++;
		T[codigo].insert(it, par);
	}
	if (nElem > 0.75 * M) {
		reestructurar();
	}
}

void TablaHash::consultar(string usuario) {
	int codigo = hashCode(usuario);
	list<Par>::iterator it = T[codigo].begin();
	while (it != T[codigo].end() && it->usuario != usuario) {
		it++;
	}
	int total = 0;
	if (it != T[codigo].end() && it->usuario == usuario) {
		list<Cuac *> cuacs = it->consultar();
		list<Cuac *>::iterator itCuacs = cuacs.begin();
		while (itCuacs != cuacs.end()) {
			total++;
			cout << total << ". ";
			(* itCuacs)->escribir();
			itCuacs++;

		}
	}
	cout << "Total: " << total << " cuac" << endl;
}

