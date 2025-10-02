#include "../include/ldePrestamos.h"

struct nodoDoble{
    TPrestamo prestamo;
    nodoDoble* ant;
    nodoDoble* sig;
};

struct rep_ldePrestamos {    
nodoDoble* primero;
nodoDoble* ultimo;
nat cantidad; 
};

/* ********** FUNCIONES NUEVAS TAREA 3 ********** */
// Función que elimina la ldePrestamos de forma segura.
// Libera la memoria asociada a todos los nodos y a los préstamos que contienen,
// llamando a una función de liberación para cada préstamo que NO libera la memoria de
// los socios ni los libros asociados al nodo.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) en el peor caso.
void liberarTLDEPrestamosSoloEstructura(TLDEPrestamos &ldePrestamos){
    if (ldePrestamos == NULL) return;
    nodoDoble* actual = ldePrestamos->primero;
    while (actual != NULL) {
        nodoDoble* sig = actual->sig; 
        liberarTPrestamoSoloEstructura(actual->prestamo);
        delete actual; 
        actual = sig;
    }
    delete ldePrestamos; 
    // Función que elimina la ldePrestamos. También libera
// la memoria asociada a todos los préstamos.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, donde n es la cantidad de préstamos en la lista.
}

// Función para crear una nueva TLDEPrestamos vacía
// Devuelve una instancia de TLDEPrestamos vacía.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(1) peor caso.
TLDEPrestamos crearTLDEPrestamosVacia(){
    TLDEPrestamos nueva = new rep_ldePrestamos;
    nueva->primero = NULL;
    nueva->ultimo = NULL;
    nueva->cantidad = 0;
    return nueva;
}

// Función para insertar ordenadamente de menor a mayor un préstamo en la lista de préstamos, 
// según la fecha de préstamo (fecha de retiro). Si ya existe uno o más préstamos para la misma fecha,
// el nuevo preéstamo es agregado al final de los demás préstamos con la misma fecha.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, siendo n la cantidad de préstamos en la lista
void insertarTLDEPrestamos(TLDEPrestamos &ldePrestamos, TPrestamo prestamo) {
    nodoDoble *nuevo = new nodoDoble; 
    nuevo->prestamo = prestamo;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    nodoDoble* A = NULL;
    nodoDoble* S = ldePrestamos->primero;

    // avanzar hasta encontrar lugar (mayor fecha o final)
    while (S != NULL && 
           compararTFechas(fechaRetiroTPrestamo(prestamo),
                           fechaRetiroTPrestamo(S->prestamo)) > 0) {
        A = S;
        S = S->sig;
    }

    if (ldePrestamos->primero == NULL) {
        // caso lista vacía
        ldePrestamos->primero = nuevo;
        ldePrestamos->ultimo = nuevo;
    }
    else if (S == ldePrestamos->primero) {
        // insertar al inicio
        nuevo->sig = ldePrestamos->primero;
        ldePrestamos->primero->ant = nuevo;
        ldePrestamos->primero = nuevo;
    }
    else if (S == NULL) {
        // insertar al final
        A->sig = nuevo;
        nuevo->ant = A;
        ldePrestamos->ultimo = nuevo;
    }
    else {
        // insertar en el medio
        nuevo->sig = S;
        nuevo->ant = A;
        A->sig = nuevo;
        S->ant = nuevo;
    }
    ldePrestamos->cantidad++;
}

// Función que elimina la ldePrestamos. También libera
// la memoria asociada a todos los préstamos.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, donde n es la cantidad de préstamos en la lista.
void liberarTLDEPrestamos(TLDEPrestamos &ldePrestamos){
    if (ldePrestamos == NULL) return;
    nodoDoble* actual = ldePrestamos->primero;
    while (actual != NULL) {
        nodoDoble* sig = actual->sig; 
        liberarTPrestamo(actual->prestamo);
        delete actual; 
        actual = sig;
    }
    delete ldePrestamos;  
}

void imprimirTLDEPrestamos(TLDEPrestamos ldePrestamos) {
    printf("LDE Préstamos:\n"); 

    nodoDoble* aux = ldePrestamos->primero;
    while (aux != NULL) {
        imprimirTPrestamo(aux->prestamo);
        aux = aux->sig;
    }
}

void imprimirInvertidoTLDEPrestamos(TLDEPrestamos ldePrestamos) {
    printf("LDE Préstamos:\n"); 

    nodoDoble* aux = ldePrestamos->ultimo;
    while (aux != NULL) {
        imprimirTPrestamo(aux->prestamo);
        aux = aux->ant;
    }
}

nat cantidadTLDEPrestamos(TLDEPrestamos ldePrestamos){
  return ldePrestamos->cantidad;
}

TPrestamo obtenerPrimeroTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->primero->prestamo;
}

TPrestamo obtenerUltimoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->ultimo->prestamo;
}

TPrestamo obtenerNesimoTLDEPrestamos(TLDEPrestamos &ldePrestamos, int n){
    nodoDoble* actual = ldePrestamos->primero;
    while (actual != NULL && n > 1) {
        actual = actual->sig;
        n--;
    }
    return actual->prestamo;
}

// criterio = 0 -> prestamos retornados
// criterio = 1 -> prestamos no retornados


// Función que retorna una nueva lista únicamente con los préstamos
// que cumplen el criterio pasado por parámetro.
// La lista filtrada no comparte memoria con la lista original
// Los préstamos retornados en la nueva lista son copias limpias
// de los que pertenecen a la lista parámetro.
// criterio = 0 -> préstamos retornados
// criterio = 1 -> préstamos no retornados
//
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(n) peor caso, siendo n la cantidad de préstamos en la lista árbol.
TLDEPrestamos filtrarPrestamosTLDEPrestamos(TLDEPrestamos &ldePrestamos, int criterio){
   TLDEPrestamos nueva = crearTLDEPrestamosVacia();
    nodoDoble* S = ldePrestamos->primero;
    if (criterio==0){// prestamos retornados, fueretornado = true
        while (S!=NULL){
            if (fueRetornadoTPrestamo(S->prestamo)){
                insertarTLDEPrestamos(nueva, copiarTPrestamo(S->prestamo));
            }
                S = S->sig;
        }
    } else if (criterio==1){
        while (S!=NULL){
            if (! fueRetornadoTPrestamo(S->prestamo)){
            insertarTLDEPrestamos(nueva, copiarTPrestamo(S->prestamo));
            }
            S = S->sig;
        }
    }
    return nueva;
}
