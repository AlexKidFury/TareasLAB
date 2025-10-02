#include "../include/conjuntoGeneros.h"

struct rep_conjuntogeneros{
int cantMax;
int id;
};

TConjuntoGeneros crearTConjuntoGeneros(int cantMax){
  TConjuntoGeneros c = new rep_conjuntogeneros;
  c->cantMax = cantMax;
  c->id = 0;
  return nuevo;    
}
// Función para determinar si un conjunto de géneros es vacío
// Devuelve true si el conjunto es vacío, false en otro caso
/* Debe ejecutar en O(1) peor caso. */
bool esVacioTConjuntoGeneros(TConjuntoGeneros c){
  return c->cantMax == 0;
}
// Procedimiento para insertar el identificador "id" en el conjunto de géneros "c".
// Si "id" no pertenece al rango válido de ids del conjunto "c" la función no hace nada.
// Si "id" ya pertenece al conjunto, la función no hace nada.
/* Debe ejecutar en O(1) peor caso. */
void insertarTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (id < cantMax){
    
  }

}

void borrarDeTConjuntoGeneros(TConjuntoGeneros &c, int id){

}

bool perteneceTConjuntoGeneros(TConjuntoGeneros c, int id){
  return true;
}

int cardinalTConjuntoGeneros(TConjuntoGeneros c){
  return 0;
}

int cantMaxTConjuntoGeneros(TConjuntoGeneros c){
  return 0;
}

void imprimirTConjuntoGeneros(TConjuntoGeneros c){

}

void liberarTConjuntoGeneros(TConjuntoGeneros &c){

}

TConjuntoGeneros unionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  return NULL;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  return NULL;
}

TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  return NULL;
}
