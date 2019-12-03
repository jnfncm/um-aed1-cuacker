#include "Cuac.hpp"
#include "DiccionarioCuacs.hpp"
using namespace std;

DiccionarioCuacs dic;

void procesar_mcuac() {
    	Cuac * nuevo = new Cuac;
    	nuevo->leer_mcuac();
    	dic.insertar(nuevo);
    	cout << dic.numElem() << " cuac" << endl;
}

void procesar_pcuac() {
Cuac * nuevo = new Cuac;
  	nuevo->leer_pcuac();
dic.insertar(nuevo);
    	cout << dic.numElem() << " cuac" << endl;
}

void procesar_last() {
	int n;
	cin >> n;
	cout << "last " << n << endl;
	dic.last(n);
}

void procesar_follow() {
	string nombre;
	cin >> nombre;
	cout << "follow " << nombre << endl;
	dic.follow(nombre);
}

void procesar_date() {
	Fecha fechaMin, fechaMax;
	fechaMin.leer();
	fechaMax.leer();
	dic.date(fechaMin, fechaMax);
}

void procesar_tag() {
	Cuac actual;
	string com;
	cin >> com;
	cout << "tag " << com << endl;
	cout << "1. ";
	actual.escribir();
    	cout << "Total: 1 cuac" << endl;
}

void Interprete(string comando) {
    if (comando == "pcuac") {
   	 procesar_pcuac(); return;
    } else if (comando == "follow") {
   	 procesar_follow(); return;
    } else if (comando == "mcuac") {
   	 procesar_mcuac(); return;
    } else if (comando == "last") {
   	 procesar_last(); return;
    } else if (comando == "date") {
   	 procesar_date(); return;
    } else if (comando == "tag") {
   	 procesar_tag(); return;
    }
}

int main(void) {
    string comando;
    while (cin >> comando && comando != "exit") {
        Interprete(comando);
    }
}