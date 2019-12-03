#ifndef _DICCIONARIO_CUACS
#define _DICCIONARIO_CUACS
 
#include "TablaHash.hpp"
#include "Arbol.hpp"
 
class DiccionarioCuacs {
    private:
   	 TablaHash tabla;
   	 Arbol arbol;
    public:
   	 void insertar(Cuac * nuevo);
   	 void follow(string nombre);
   	 void last(int n);
   	 void date(Fecha f1, Fecha f2);
   	 int numElem();
};
 
#endif
