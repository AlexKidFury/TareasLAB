#include "../include/conjuntoGeneros.h"

 /*Un elemento de tipo TConjuntoGeneros es un conjunto acotado que almacena ids de géneros.

  El conjunto es acotado, y además, la cantidad máxima de elementos define el rango de 
  identificadores que almacena.
  Es decir, los identificadores almacenados por el conjunto cumplen 0 <= id < cantMax*/
struct rep_conjuntogeneros{
int cantMax;
bool* id;
int cant;
};

TConjuntoGeneros crearTConjuntoGeneros(int cantMax){
  TConjuntoGeneros c = new rep_conjuntogeneros;
  c->cantMax = cantMax;
  c->id = new bool[cantMax](); 
  c->cant=0;
  return c;    
}
// Función para determinar si un conjunto de géneros es vacío
// Devuelve true si el conjunto es vacío, false en otro caso
/* Debe ejecutar en O(1) peor caso. */
bool esVacioTConjuntoGeneros(TConjuntoGeneros c){
  return (c->cant == 0);
}
// Procedimiento para insertar el identificador "id" en el conjunto de géneros "c".
// Si "id" no pertenece al rango válido de ids del conjunto "c" la función no hace nada.
// Si "id" ya pertenece al conjunto, la función no hace nada.
/* Debe ejecutar en O(1) peor caso. */
void insertarTConjuntoGeneros(TConjuntoGeneros &c, int id){
if(id >= c->cantMax || id < 0) return;
if(c->id[id]) return;
c->id[id] = true;
c->cant++;
return;

}
// Procedimiento para borrar al "id" del conjunto de géneros "c"
// Si "id" no pertenece al conjunto "c" o al rango válido, la función no hace nada
/* Debe ejecutar en O(1) peor caso. */
void borrarDeTConjuntoGeneros(TConjuntoGeneros &c, int id){
if(c->id[id]==true && id < c->cantMax && id>=0){
  if(c->id[id]==c->cantMax-1)
  c->cantMax--;
c->id[id] = false;
c->cant--;
}

}

bool perteneceTConjuntoGeneros(TConjuntoGeneros c, int id){
  if (id < c->cantMax && id>=0)
  return c->id[id];
  else return false;
}
  // Función que retorna la cantidad de elementos del conjunto de géneros "c".
  /* Debe ejecutar en O(1) peor caso. */
  int cardinalTConjuntoGeneros(TConjuntoGeneros c){
  return c->cant;
}
// Función que retorna la cantidad máxima de elementos del conjunto de géneros "c".
/* Debe ejecutar en O(1) peor caso. */
int cantMaxTConjuntoGeneros(TConjuntoGeneros c){
  return c->cantMax;
}
// Procedimiento para imprimir el conjunto de géneros.
// Imprime los ids de los géneros del conjunto ordenado de menor a mayor.
// Deben imprimirse solamente los elementos, separados por un espacio
// (sin espacio después del último), con un salto de línea al final.
// Ejemplo: si el conjunto "c" tiene los elementos 7, 42, 29 y 75 la impresión debe ser "7 29 42 75" 
// y finalmente un salto de línea.
/* Debe ejecutar en O(n) peor caso, siendo "n" la cantidad máxima de elementos de "c". */
void imprimirTConjuntoGeneros(TConjuntoGeneros c){
    bool primero = true;
    for (int i = 0; i < c->cantMax; i++) {
        if (c->id[i]) {
            if (!primero)
                printf(" ");
            printf("%d", i);
            primero = false;
        }
    }
    printf("\n");
}

/*while (i < c->cantMax-1){   
if (c->id[i])
  printf("%d ", i);
i++;
}
printf("%d\n",i);
*/
// Procedimiento para liberar la memoria asignada a un conjunto de géneros.
// Luego de la ejecución deja 'c' apuntando a NULL;
/* Debe ejecutar en O(1) peor caso. */
void liberarTConjuntoGeneros(TConjuntoGeneros &c){
delete[] c->id;
c->cantMax = 0;
c->cant = 0;
delete c;
c = NULL;
}

// Función que retorna la unión entre los conjuntos de géneros "c1" y "c2".
// Ambos conjuntos tienen la misma cantidad máxima de elementos, "n".
// El conjunto resultado debe poder almacenar la misma cantidad máxima de elementos.
/* Debe ejecutar en O(n) peor caso, siendo n la cantidad máxima de elementos permitidos en el conjunto */


TConjuntoGeneros unionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros c3 = crearTConjuntoGeneros(c1->cantMax);
    int i = 0;
  while(i < c1->cantMax){
    if (c1->id[i] || c2->id[i])
    insertarTConjuntoGeneros(c3,i);
    i++;
  }

  return c3;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros c3 = crearTConjuntoGeneros(c1->cantMax);
  int i = 0;
  while(i < c1->cantMax){
    if (c1->id[i] && c2->id[i])
    insertarTConjuntoGeneros(c3,i);
    i++;
  }

  return c3;
}
// Función que retorna la diferencia entre los conjuntos de géneros "c1" y "c2". (c1 - c2)
// Ambos conjuntos tienen la misma cantidad máxima de elementos, "n".
// El conjunto resultado debe poder almacenar la misma cantidad máxima de elementos.
/* Debe ejecutar en O(n) peor caso, siendo n la cantidad máxima de elementos permitidos en el conjunto */
TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros c3 = crearTConjuntoGeneros(c1->cantMax);
    int i = 0;
  while(i < c1->cantMax){
    if (c1->id[i] && !c2->id[i])
    insertarTConjuntoGeneros(c3,i);
    i++;
  }

  return c3;
}
