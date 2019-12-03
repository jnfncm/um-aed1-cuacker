#include "Nodo.hpp"
#include <algorithm>

Nodo::Nodo(Fecha fecha) {
	altura = 0;
	this->fecha = fecha;
	der = NULL;
	izq = NULL;
}

Nodo::~Nodo() {
	delete der;
	delete izq;
}

int Nodo::checkAltura() {
	if (this == NULL) {
		return -1;
	} else {
		return altura;
	}
}

Nodo * Nodo::RSI() {
	Nodo * B = this->izq;
	this->izq = B->der;
	B->der = this;
	this->altura = 1 + max(this->izq->checkAltura(), this->der->checkAltura());
	B->altura = 1 + max(this->checkAltura(), B->izq->checkAltura());
	return B;
}

Nodo * Nodo::RSD() {
	Nodo * B = this->der;
	this->der = B->izq;
	B->izq = this;
	this->altura = 1 + max(this->izq->checkAltura(), this->der->checkAltura());
	B->altura = 1 + max(this->checkAltura(), B->der->checkAltura());
	return B;
}

Nodo * Nodo::RDD() {
	this->der = this->der->RSI();
	return this->RSD();
}

Nodo * Nodo::RDI() {
	this->izq = this->izq->RSD();
	return this->RSI();
}

Nodo * Nodo::balancear() {
	if (abs(izq->checkAltura() - der->checkAltura()) >= 2) {
		if (der->checkAltura() - izq->checkAltura() == 2) {
			if (der->der->checkAltura() - der->izq->checkAltura() == 1) {
				return RSD();
			} else {
				return RDD();
			}
		}
		else if (izq->checkAltura() - der->checkAltura() == 2) {
			if (izq->izq->checkAltura() - izq->der->checkAltura() == 1) {
				return RSI();
			}
			else {
				return RDI();
			}
		}
	}
	return this;
}


bool comparadorPunteroCuac(Cuac * a, Cuac * b) {
	return a->es_anterior(* b);
}


void Nodo::insertar(Cuac * cuac) {
	if (cuac->fecha == this->fecha) {
		cuacs.push_back(cuac);
		cuacs.sort(comparadorPunteroCuac);
	} else if (cuac->fecha < this->fecha) {
		if (izq == NULL) {
			izq = new Nodo(cuac->fecha);
			if (altura == -1) { altura = 0; }
		}
		izq->insertar(cuac);
		izq = izq->balancear();
	} else if (cuac->fecha > this->fecha) {
		if (der == NULL) {
			der = new Nodo(cuac->fecha);
			if (altura == -1) { altura = 0; }
		}
		der->insertar(cuac);
		der = der->balancear();
	}
	int a1, a2;
	if (izq == NULL) { a1 = -1; } else { a1 = izq->altura; }
	if (der == NULL) { a2 = -1; } else { a2 = der->altura; }
	altura = 1 + max(a1, a2);
}

void Nodo::inordenLast(bool lastB, int lastM, int * lastC) {
	if (this != NULL) {
		der->inordenLast(lastB, lastM, lastC);
		list<Cuac *>::iterator it = cuacs.begin();
		while(it != cuacs.end()) {
			if (lastB && (*lastC >= lastM)) {
				return;
			}
			(* lastC)++;
			cout << * lastC << ". ";
			(* * it).escribir();
			it++;
		}
		izq->inordenLast(lastB, lastM, lastC);
	}
}

void Nodo::inordenDate(Fecha f1, Fecha f2, int * count) {
	if (this != NULL) {
		der->inordenDate(f1, f2, count);
		if (!(f1 > fecha) && !(fecha > f2)) {
			list<Cuac *>::iterator it = cuacs.begin();
			while (it != cuacs.end()) {
				(*count)++;
				cout << *count << ". ";
				(** it).escribir();
				it++;
			}
		}
		izq->inordenDate(f1, f2, count);
	}
}
