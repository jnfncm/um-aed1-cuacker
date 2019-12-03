#ifndef _PAR
#define _PAR

#include "Cuac.hpp"
#include <list>
using namespace std;

class Par {
	friend class TablaHash;
	private:
		string usuario;
		list<Cuac *> l;
	public:
		Par(string usuario);
		void inserta(Cuac * cuac);
		list<Cuac *> consultar();
};

#endif
