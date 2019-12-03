# Cuacker

Algoritmos y Estructuras de Datos 1
(Curso 2018 - 2019)

Grado en Ingeniería Informática
Universidad de Murcia

Por: Juan Francisco Carrión Molina y Eloy Abellán Mayor

Profesores: José Antonio García Díaz y Norberto Marín Pérez

## Memoria de las prácticas

### 1. Análisis y diseño del problema

El programa principal se ubica en `Cuacker.cpp` e incluye un intérprete para consola de comandos. Este intérprete se encargará de ejecutar los métodos adecuados según la entrada para así generar la salida esperada.

Para componer el resto del programa, se ha definido un total de 7 clases:

-	La clase `Fecha` (`Fecha.hpp`, `Fecha.cpp`) almacena una fecha y una hora, con sus distintas operaciones de lectura, escritura y comparación de fechas.
-	La clase `Cuac` (`Cuac.hpp`, `Cuac.cpp`) es el tipo de datos fundamental de la aplicación. Representa los mensajes y almacena el nombre del usuario, la fecha y la hora de envío y un texto de máximo 140 caracteres. Esta clase incluye distintas operaciones de lectura, escritura y comparación de cuacs.
-	La clase `DiccionarioCuacs` (`DiccionarioCuacs.hpp`, `DiccionarioCuacs.cpp`) se encarga de repartir las operaciones de inserción y recuperación de cuacs en las diferentes estructuras que componen la memoria de la aplicación, adecuada cada una a unas circunstancias para conseguir la eficiencia deseada.
-	La clase `TablaHash` (`TablaHash.hpp`, `TablaHash.cpp`) define un contenedor de tipo tabla de dispersión para almacenar cuacs utilizando una función de dispersión dependiente del usuario que inserta el cuac. Esta clase se utiliza en las operaciones de recuperación de cuacs por nombre de usuario.
-	La clase Par (Par.hpp, Par.cpp) se utiliza en TablaHash como estructura para almacenar una lista de cuacs para un mismo usuario.
-	La clase `Arbol` (`Arbol.hpp`, `Arbol.cpp`) define un contenedor de tipo árbol para almacenar cuacs según la fecha de éstos. Se ha implementado, como se explicará más adelante, un árbol binario de búsqueda balanceado AVL. Esta clase se utiliza en las operaciones de recuperación de cuacs por proximidad de las fechas o por rango de estas.
-	La clase `Nodo` (`Nodo.hpp`, `Nodo.cpp`) se utiliza en Arbol como estructura nodo de árbol para almacenar una lista de cuacs para una misma fecha.

Cabe destacar que en las listas de cuacs de las clases Par y Nodo, se utiliza un orden de menor a mayor siguiendo el comparador implementado en la clase Cuac.

También es necesario especificar que en las operaciones de lectura de cuacs estos se crean mediante memoria dinámica y, a partir de aquí, se trabaja con punteros a cuacs (las listas no son de cuacs `list<Cuac>`, sino de punteros a cuacs `list<Cuac *>`).

La relación entre las clases es la siguiente (no se incluyen las clases por defecto de C++):

_Imagen no disponible_

Se han definido 7 módulos correspondientes, cada uno, a cada clase definida (los nombres son equivalentes). Cada módulo cuenta con su fichero de cabecera .hpp y su fichero de código .cpp, cada uno con sus correspondientes especificaciones de tipos (clases) e implementaciones de operaciones (métodos).

La relación entre todos los ficheros que componen la aplicación es la siguiente (no se incluyen los ficheros por defecto de C++ ni el fichero `Makefile`, que se especifica más adelante):

_Imagen no disponible_

A la hora de compilar el programa, se utiliza un fichero `Makefile` y cada módulo se compila con todas sus dependencias, dando lugar a ficheros objeto independientes que luego se enlazan en uno único de salida a.out.

En la clase `TablaHash` se ha usado una tabla de dispersión abierta. No vimos gran ventaja en usar la dispersión cerrada y además es más sencilla de implementar al olvidarnos de redispersar. Cada elemento de la tabla es una lista de pares que almacenan el nombre del usuario y una lista con sus cuacs. De este modo la búsqueda por nombre es casi directa al no mezclar distintos usuarios y las colisiones no son especialmente críticas.

Para dispersar se utiliza la función iterativa djb2a. También se han probado otras similares ofreciendo parejo rendimiento. Con anterioridad hicimos uso del método de suma posicional, pero consumía más tiempo y producía valores muy altos llegando a desbordar el tipo entero. Lo bueno de djb2a es que realiza operaciones sencillas y rápidas (multiplicación y XOR) tratando con números primos para menores colisiones.

Cuando la tabla llega al 75% de su capacidad realizamos la reestructuración, ampliándola al doble. Para ello hacemos tres recorridos anidados, uno para las diferentes entradas de la tabla y dentro de éste otro para los pares y el correspondiente a los cuacs almacenados en cada par y así llamar a la función de inserción.

El objeto `TablaHash` se libera llamando al destructor de la tabla (array de C++), `delete[]`.

Para las recuperaciones con fechas, se utiliza un árbol binario de búsqueda balanceado AVL. Para nosotros, parecía la implementación más obvia y con la que más hemos trabajado en clase. Además, ofrece buen rendimiento para las operaciones requeridas.

La clase `Árbol` se define como un simple tipo con un puntero a un nodo que es la raiz. Las operaciones de inserción y consulta por fechas se canalizan desde esta clase hacia los nodos, quienes se encargan realmente de llevarlas a cabo.

Así, la clase `Nodo` contiene las operaciones de inserción, cálculo de altura, rotaciones, comprobación de balanceo e impresión inorden. Destacar que la operación `Nodo::checkAltura` permite devolver -1 si el nodo no existe; la operación `Nodo::balancear` permite la modificación del puntero al nodo tras hacer las comprobaciones y realizar las rotaciones correspondientes; y la operación `comparadorPunteroCuac` se implementa en esta clase porque es la que la necesita para ordenar la lista de cuacs de un nodo mediante `std::list::sort`.

Tras cada inserción se llama a la operación `Nodo::balancear` para el nodo correspondiente. Esta operación lanza las rotaciones necesarias, recalcula las alturas y devuelve un puntero al nodo. De esta manera se realiza el balanceo que en pseudocódigo necesitaría la modificación del puntero `this`.

El destructor de `Árbol` simplemente llama al destructor del nodo raíz, que llama recursivamente al destructor de `Nodo` para cada nodo del árbol.

La única variable global que se utiliza a lo largo del programa final es `DiccionarioCuacs dic`, que constituye la estructura de almacenamiento de los cuacs.

### 2. Informe de desarrollo

Dado que fue muy difícil llevar a cabo el proyecto desde el principio de las prácticas, nos ha sido imposible contabilizar las horas empleadas y su distribución en los distintos apartados de análisis, diseño, implementación y validación. Si hemos de destacar que, en determinadas ocasiones y con ánimo de sacar adelante el proyecto, hemos estado varios días dando vueltas e ideando soluciones a un mismo problema e incluso hemos llegado a altas horas de la madrugada intentando resolverlo.

Aunque la práctica conste de diversos ejercicios existe una gran dependencia entre ellos, por lo que en general no se puede paralelizar la resolución de los mismos. En vez de ello, la dinámica principal ha sido que cada cual realizase la implementación oportuna, apoyándose en el otro para resolver las dudas o problemas que fueran surgiendo.

La realización de los primeros apartados fue sencilla, si bien hizo falta acostumbrarse un poco al lenguaje C++. El primer inconveniente surgió a la hora de realizar la división en módulos, ya desde el ejercicio número 5, pero una vez hecho supone una ventaja al ser más sencillo comparado con la gente que lo pospusiera hasta el ejercicio 200.

Para los ejercicios 5 y 6 adoptamos el código proporcionado por el aula virtual. En este momento ya se tiene un sencillo intérprete de comandos y un diccionario de cuacs implementado con el tipo list<T> de las STL de C++. Aunque no sea una implementación muy eficiente, este primer acercamiento al manejo de listas es clave de cara a saber manejarlas en estructuras posteriores, donde sí pueden resultar un buen aliado.

Las turbulencias sacuden a partir del ejercicio 200. Empezamos realizando la implementación sencilla para la tabla de dispersión (abierta) pero optamos finalmente por utilizar pares de cuacs como elementos de las cubetas al no implicar una complejidad mucho mayor pero sí aportar una reducción de tiempo considerable para casos de colisiones. Destacar que tratamos con memoria dinámica y que se reestructura en caso de llegar al 75% de llenado, tareas clave son la realización correcta de la reestructuración y la eliminación para no comprometer el correcto funcionamiento de éste y posteriores enunciados.

El ejercicio de mayor dificultad seguramente haya sido el número 300. Desde el primer momento pensamos en utilizar árboles AVL, con buen rendimiento para las operaciones de inserción y consulta. Quizás el tipo trie también se hubiera adaptado bien, sobre todo si se envían mensajes en periodos cortos de tiempo, dando lugar a muchos sinónimos. Sin embargo, AVL ha sido el tipo de árbol más trabajado en clase y nos empeñamos en su uso.

En primer lugar surgen las dudas de dónde realizar qué operaciones, al tener una clase `Nodo` y otra `Árbol` que la envuelva. Empezamos implementando las rotaciones en el árbol. El problema viene a la hora de la inserción. Insertamos un nodo sobre un árbol recursivamente, además de comprobar la condición de balanceo a la vuelta de la recursividad. Pasamos la acción principal para insertar a la clase `Nodo` y ésta arrastró la de las rotaciones. Experimentamos diversos problemas para realizarlas debido a que en el proceso cambia la raíz pero el apuntador this no puede mutar, así que lo evitamos y devolvemos la nueva raíz para cambiarla desde donde sí podamos. Topamos con la querida violación de segmento sin saber por qué y hubo que hacer un uso introductorio del gdb, hallando que el problema estaba en las rotaciones dobles, expresadas como dos rotaciones.

Uno de los grandes problemas con los que nos topamos durante la implementación del programa es el trabajo con referencias y punteros. En la convocatoria dentro de plazo se nos hizo muy difícil llevar a cabo el problema 300, por lo que hemos tenido que utilizar la convocatoria fuera de plazo. Concretamente, nuestro problema estaba en que la memoria reservada para los cuacs no se conservaba tras la inserción, y en la lectura se devolvía información incorrecta (basura de memoria).

Una vez resuelto este problema, fue más sencilla la terminación de este ejercicio y la implementación de las funciones `inordenLast` e `inordenDate` para el 300 y el 301.

### 3. Conclusiones y valoraciones personales

El lenguaje C++ y sus diferencias con respecto a otros lenguajes, sobre todo la necesidad de tener una idea muy clara de la memoria que usa el programa, han sido factores muy influyentes en la manera de idear las soluciones e implementarlas.

Esto tiene su lado bueno, en el sentido de que nos hace ser conscientes de qué estamos haciendo exactamente en el computador, pero también su lado menos bueno, ya que no tener una formación previa en el lenguaje y no comprenderlo completamente ha requerido utilizar gran parte del tiempo solucionando errores propios del lenguaje.

Con respecto al contenido de la práctica, nos ha permitido utilizar los conceptos de estructuras de datos vistos en teoría, teniendo así una idea más clara de estos.

Personalmente, ambos autores coincidimos en que ha sido una práctica muy completa, pero también bastante dura por el tiempo, las fechas y la atención. Se han dado momentos muy constructivos y de iluminación computacional en los que las ideas han fluido, la teoría estaba clara y al llevarla a la práctica todo funcionaba correctamente (excepto algún error en el caso C...). Para terminar, solo decir que ha sido muy enriquecedora tanto en contenidos de la asignatura como en el lenguaje C++.
