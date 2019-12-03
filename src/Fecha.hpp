#ifndef _FECHA
#define _FECHA

#include <iostream>

class Fecha {
	private:
		int dia, mes, ano, hora, minuto, segundo;
	public:
		Fecha();
		bool leer();
		void escribir();
		long long convierte_a_segundos();
		bool es_mayor(Fecha otra);
		bool es_menor(Fecha otra);
		bool es_igual(Fecha otra);
		bool operator<(Fecha otra);
		bool operator>(Fecha otra);
		bool operator==(Fecha otra);
};

#endif
