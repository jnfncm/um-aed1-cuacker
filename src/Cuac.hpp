#ifndef _CUAC
#define _CUAC

#include "Fecha.hpp"
#include <iostream>
using namespace std;

class Cuac {
	private:
		Fecha fecha;
		string usuario;
		string texto;
		string pcuac_a_texto(int num);
		int pcuac_a_numero(string cadena);
	public:
		Cuac();
		~Cuac();
		friend class Par;
		friend class TablaHash;
		friend class Arbol;
		friend class Nodo;
		bool leer_mcuac();
		bool leer_pcuac();
		void escribir();
		bool es_anterior(Cuac otro);
		bool operator<(Cuac otro);
		bool operator>(Cuac otro);
};

#endif
