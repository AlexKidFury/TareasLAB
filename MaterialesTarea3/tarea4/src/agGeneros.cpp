
#include "../include/agGeneros.h"
#include <assert.h>


struct rep_agGeneros {
  TAGGeneros ph;
  TAGGeneros sh;
  int id;
  char genero[MAX_NOMBRE];
};


// Función para crear un nuevo arbol general
// Devuelve un nuevo árbol general vacío
// Debe ejecutar en O(1) peor caso.
TAGGeneros crearTAGGeneros(){
  return NULL;
}
// Función para insertar un nuevo género idGenero en el árbol general,
// como primer anterior del nodo que representa el idGenero 'idGeneroPadre'. Si
// idGeneroPadre == '-1', idGenero se almacena como nodo raíz.
// PRE: El género con cod 'idGenero' no está en el árbol.
// PRE: Si el árbol es vacío, la primer inserción será con idGeneroPadre = -1
// PRE: Si el árbol no es vacío, el género con idGeneroPadre pertenece al árbol
// Debe ejecutar en O(n) peor caso, siendo n la cantidad de géneros en el árbol.
void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]) {
    // Caso 1: insertar la raíz
    if (arbolGeneros == NULL && idGeneroPadre == -1) {
        arbolGeneros = new rep_agGeneros;
        arbolGeneros->id = idGenero;
        strcpy(arbolGeneros->genero, nombreGenero);
        arbolGeneros->ph = NULL;
        arbolGeneros->sh = NULL;
        return;
    }

    if (arbolGeneros == NULL)
        return;

    // Caso 2: encontramos al padre -> insertamos como primer anterior
    if (arbolGeneros->id == idGeneroPadre) {
        TAGGeneros nuevo = new rep_agGeneros;
        nuevo->id = idGenero;
        strcpy(nuevo->genero, nombreGenero);
        nuevo->ph = NULL;
        nuevo->sh = arbolGeneros->ph; // nuevo queda como primer anterior
        arbolGeneros->ph = nuevo;
        return;
    }

    // Caso 3: seguir buscando en hijos y hermanos
    insertarGeneroTAGGeneros(arbolGeneros->ph, idGeneroPadre, idGenero, nombreGenero);
    insertarGeneroTAGGeneros(arbolGeneros->sh, idGeneroPadre, idGenero, nombreGenero);
}


// Función para imprimir el árbol general. Los hermanos se imprimen según
// el orden inverso de creación (el último hermano en ser agregado se imprime primero).
// La impresión de cada género debe tener el siguiente formato:
// <cod género> - <nombre género>
// Este formato debe ser usado para imprimir el árbol completo de la siguiente forma:
// Árbol de géneros:
// <género raíz>
//     <género anterior 1 (primer nivel)>
//         <género anterior 1 (segundo nivel)>
//         <género anterior 2 (segundo nivel)>
//             <género anterior 1 (tercer nivel)>
//             ...
//         <género anterior 3 (segundo nivel)>
//         ...
//     <género anterior 2 (primer nivel)>
//     ...
// Notar que la separación entre niveles se realiza con 4 espacios en blanco ('    ')
// Debe ejecutar en O(n) peor caso, siendo n la cantidad de géneros en el árbol.
void imprimirTAGGenerosAux(TAGGeneros nodo, int nivel) {
    if (nodo == NULL)
        return;

    for (int i = 0; i < nivel; i++)
        printf("    ");
    printf("%d - %s\n", nodo->id, nodo->genero);
    imprimirTAGGenerosAux(nodo->ph, nivel + 1);
    imprimirTAGGenerosAux(nodo->sh, nivel );
}


void imprimirTAGGeneros(TAGGeneros arbolGeneros) {
    printf("Árbol de géneros:\n");
    imprimirTAGGenerosAux(arbolGeneros, 0);
}


// Función para liberar la memoria asignada a un árbol de géneros.
// Luego de la función, el puntero arbolGeneros debe apuntar NULL.
// Debe ejecutar en O(n) peor caso, siendo n la cantidad de géneros en el árbol.
void liberarTAGGeneros(TAGGeneros &arbolGeneros){
if(arbolGeneros != NULL){
  liberarTAGGeneros(arbolGeneros->ph);
  liberarTAGGeneros(arbolGeneros->sh);
    delete arbolGeneros;
    arbolGeneros= NULL;
}
}

bool existeGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  if (arbolGeneros==NULL)
    return false;
  if(arbolGeneros->id==idGenero)
    return true; 

  return (existeGeneroTAGGeneros(arbolGeneros->ph, idGenero) || existeGeneroTAGGeneros(arbolGeneros->sh, idGenero));
}
// Función que devuelve el nombre de un género dado su id.
// En caso de que el género no pertenezca al árbol, devuelve NULL.
// Debe ejecutar en O(n) peor caso, siendo n la cantidad de géneros en el árbol.
char* nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  if (arbolGeneros == NULL)
  return NULL;
  if(arbolGeneros->id == idGenero)
    return arbolGeneros->genero;
  char* resultado = nombreGeneroTAGGeneros(arbolGeneros->ph, idGenero);
    if (resultado != NULL) {
        return resultado;
    }
    return nombreGeneroTAGGeneros(arbolGeneros->sh, idGenero);
}

nat alturaTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros == NULL)
  return 0;
  nat max = 0;
  for(TAGGeneros anterior = arbolGeneros->ph; anterior != NULL; anterior = anterior->sh){
  nat altHijo = alturaTAGGeneros(anterior);
  if (altHijo>max)
    max = altHijo;
  }
  return 1 + max;
}
nat cantidadTAGGeneros(TAGGeneros arbolGeneros){
  if(arbolGeneros == NULL)
  return 0;

  return 1 + cantidadTAGGeneros(arbolGeneros->ph) + cantidadTAGGeneros(arbolGeneros->sh);
}
// Función para obtener un subarbol de géneros dado.
// Retorna el subárbol cuya raíz tiene el idGenero pasado por parámetro
// PRE: existeGeneroTAGGeneros(arbolGeneros, idGenero) == true
// Debe ejecutar en O(n) peor caso, siendo n la cantidad de géneros en el árbol.
TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
    if (arbolGeneros == NULL)
        return NULL;

    if (arbolGeneros->id == idGenero)
        return arbolGeneros;

    TAGGeneros resultado = obtenerSubarbolTAGGeneros(arbolGeneros->ph, idGenero);
    if (resultado != NULL)
        return resultado;

    return obtenerSubarbolTAGGeneros(arbolGeneros->sh, idGenero);
}

// Función para obtener un conjunto de géneros a partir de árbol de géneros.
// El conjunto de géneros retornado esta formado por los géneros que pertenecen al 
// subarbol cuya raíz tiene el idGenero pasado por parámetro
// Función auxiliar recursiva
void agregarGenerosAlConjunto(TAGGeneros arbol, TConjuntoGeneros&c) {
    if (arbol == NULL)
        return;

    insertarTConjuntoGeneros(c, arbol->id);

    agregarGenerosAlConjunto(arbol->ph, c);
    agregarGenerosAlConjunto(arbol->sh, c);
}

// Función principal
TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero) {
    // Obtenemos el subárbol de interés
    TAGGeneros arbolAux = obtenerSubarbolTAGGeneros(arbolGeneros, idGenero);

    // Si no existe el subárbol, retornamos un conjunto vacío seguro
    if (arbolAux == NULL)
        return crearTConjuntoGeneros(0);

    // Obtenemos el valor máximo de ID del subárbol
    nat max = obtenerMaxTAGGeneros(arbolAux);

    // Creamos el conjunto con capacidad suficiente
    TConjuntoGeneros con = crearTConjuntoGeneros(max + 1);

    // Llenamos el conjunto recorriendo el subárbol
    agregarGenerosAlConjunto(arbolAux, con);

    return con;
}


// Función para obtener el mayor idGenero de un árbol de géneros
// Debe ejecutar en O(n) peor caso, siendo n la cantidad de géneros en el árbol.
int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros) {
    if (arbolGeneros == NULL)
        return 0;

    int maxActual = arbolGeneros->id;

    int maxHijos = obtenerMaxTAGGeneros(arbolGeneros->ph);

    int maxHermanos = obtenerMaxTAGGeneros(arbolGeneros->sh);

    if (maxHijos > maxActual)
       maxActual = maxHijos;
       
    if(maxHermanos > maxActual)
       maxActual = maxHermanos;   
        
    return maxActual;
}





// Función para eliminar un género del árbol de géneros.
// En caso de el género tenga hijos, estos también son eliminados.
// PRE: existeGeneroTAGGeneros(arbolGeneros, idGenero) == true
// Debe ejecutar en O(n) peor caso, siendo n la cantidad de géneros en el árbol.
void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero) {
  if (arbolGeneros == NULL)
    return;

  // Caso: encontramos el nodo a eliminar
  if (arbolGeneros->id == idGenero) {
    liberarTAGGeneros(arbolGeneros);  // libera el nodo y su subárbol
    return;
  }

  // Recorremos los hijos
  TAGGeneros actual = arbolGeneros->ph;
  TAGGeneros anterior = NULL;

  while (actual != NULL) {
    if (actual->id == idGenero) {
      if (anterior == NULL)
        arbolGeneros->ph = actual->sh;   // era el primer actual
      else
        anterior->sh = actual->sh;       // saltar el nodo eliminado

      actual->sh= NULL;
      liberarTAGGeneros(actual);
      return; // ya lo eliminamos, salimos
    }
    anterior = actual;
    actual = actual->sh;
  }
    removerGeneroTAGGeneros(arbolGeneros->ph, idGenero);
    removerGeneroTAGGeneros(arbolGeneros->sh, idGenero);
}
