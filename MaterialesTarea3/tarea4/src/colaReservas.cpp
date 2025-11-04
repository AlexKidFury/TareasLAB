#include "../include/colaReservas.h"

struct nodoReserva {
    TReserva reserva;         
    nodoReserva *sig;          
};
struct rep_colaReservas {
    nodoReserva *pri;          
    nodoReserva *ult;         
    nat cant;                  
};
// Función para crear un elemento de tipo TColaReservas vacío.
// Debe ejecutar en O(1) peor caso.
TColaReservas crearTColaReservas(){
  TColaReservas c = new rep_colaReservas;
  c->pri = c->ult = NULL;
  c->cant= 0;
  return c;
}

// Función que libera la memoria asignada para la cola de reservas.
// Debe ejecutar en O(n) peor caso, donde n es la cantidad de reservas en la cola.
void encolarTColaReservas(TColaReservas &colaReservas, TReserva reserva){
    if (reserva == NULL) return;
    
    nodoReserva *nuevo = new nodoReserva;
    nuevo->reserva = reserva;
    nuevo->sig = NULL;

    if (colaReservas->pri == NULL) {
        colaReservas->pri = nuevo;
    } else {
        colaReservas->ult->sig = nuevo;
    }

    colaReservas->ult = nuevo;
    colaReservas->cant++;
}

void desencolarTColaReservas(TColaReservas &colaReservas) {
    if (colaReservas->pri == NULL) return;

    nodoReserva *aBorrar = colaReservas->pri;
    colaReservas->pri = colaReservas->pri->sig;
    
    if (colaReservas->pri == NULL) {
        colaReservas->ult = NULL;
    }

    if (aBorrar->reserva != NULL) {
        liberarTReserva(aBorrar->reserva);
    }
    delete aBorrar;
    colaReservas->cant--;
}

TReserva frenteTColaReservas(TColaReservas colaReservas) {
        if (colaReservas->pri == NULL)
        return NULL; 
    return colaReservas->pri->reserva;
}

nat cantidadTColaReservas(TColaReservas colaReservas){
    return colaReservas->cant;
}
// Imprime la cola de reservas con el siguiente formato:
//   Cola de Reservas:
//   <imprimir imprimirTReserva en cada reserva>
// El orden de impresión es el que resultaría de desencolar
// sucesivamente las reservas e imprimirlos (orden de llegada).
// Debe ejecutar en O(n) peor caso, donde n es el numero de reservas en la cola
void imprimirTColaReservas(TColaReservas colaReservas){
    printf("Cola de Reservas:\n");
    if (colaReservas->cant == 0) return; // Cola vacía
    
    nodoReserva *actual = colaReservas->pri;
    while (actual != NULL) {
        if (actual->reserva != NULL) {
            imprimirTReserva(actual->reserva);
        }
        actual = actual->sig;
    }
}

// Función que libera la memoria asignada para la cola de reservas.
// Debe ejecutar en O(n) peor caso, donde n es la cantidad de reservas en la cola.
void liberarTColaReservas(TColaReservas &colaReservas){
  while(colaReservas->pri!=NULL)
desencolarTColaReservas(colaReservas);
delete colaReservas;
colaReservas = NULL;
}


// Función que elimina la colaReservas de forma segura.
// Libera la memoria asociada a todos los nodos y a las reservas que contienen,
// llamando a una función de liberación para cada reserva que NO libera
// los socios ni los libros asociados a la reserva.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) en el peor caso, donde n es la cantidad de reservas en la cola.
void liberarTColaReservasSoloEstructura(TColaReservas &colaReservas){
while(colaReservas->pri!=NULL){
liberarTReservaSoloEstructura(colaReservas->pri->reserva);
desencolarTColaReservas(colaReservas);
}
delete colaReservas;
}


// Función que quita el nodo del frente de la cola (el último) y devuelve el TReserva que contenía,
// liberando únicamente la memoria del nodo. A diferencia de 'desencolarTColaReservas', esta función
// no libera la reserva.
// Debe ejecutar en O(1) peor caso.
TReserva extraerFrenteTColaReservas(TColaReservas &colaReservas) {
    if (colaReservas->pri == NULL) {
        return NULL;
    }
    
    TReserva reservaExtraida = colaReservas->pri->reserva;
    nodoReserva *aBorrar = colaReservas->pri;
    colaReservas->pri = colaReservas->pri->sig;
    
    if (colaReservas->pri == NULL) {
        colaReservas->ult = NULL;
    }
    
    delete aBorrar;
    colaReservas->cant--;
    
    return reservaExtraida;
}
