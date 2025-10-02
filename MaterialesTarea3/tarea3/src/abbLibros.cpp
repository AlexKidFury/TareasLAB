
#include "../include/abbLibros.h"

struct rep_abbLibros {
    TLibro l;
    TABBLibros izq;
    TABBLibros der;
};

TABBLibros crearTABBLibrosVacio(){
return NULL;
}
// Función para insertar un libro en el árbol, ordenado por ISBN.
// PRE: El libro con ese isbn no está en el árbol.
/* Requisitos específicos de la implementación solicitada: */
void insertarLibroTABBLibros(TABBLibros &abbLibros, TLibro libro){
    if (abbLibros == NULL) {
        abbLibros = new rep_abbLibros;
        abbLibros->l = libro;
        abbLibros->izq = abbLibros->der = NULL;
    }
else if (isbnTLibro(libro) < isbnTLibro(abbLibros->l))
    insertarLibroTABBLibros(abbLibros->izq, libro);
else if (isbnTLibro(libro) > isbnTLibro(abbLibros->l))
    insertarLibroTABBLibros(abbLibros->der, libro);
}

// Función para imprimir los libros del árbol en orden, según su ISBN. La impresión
// de los libros se realiza con la función 'imprimirTLibro'.
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, donde n es la cantidad de libros en el árbol.
void imprimirTABBLibros(TABBLibros abbLibros){
if (abbLibros != NULL){
    imprimirTABBLibros(abbLibros->izq);
    imprimirTLibro(abbLibros->l);
    imprimirTABBLibros(abbLibros->der);
}
}

void liberarTABBLibros(TABBLibros &abbLibros){
    if (abbLibros != NULL) {
        liberarTABBLibros(abbLibros->izq);
        liberarTABBLibros(abbLibros->der);
        liberarTLibro(abbLibros->l);
        delete abbLibros;
        abbLibros = NULL;
    }
}
// Función que determina si un libro está en el árbol.
// Devuelve true si el libro está en el árbol, false en caso contrario.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(log(n)) caso promedio, siendo n la cantidad de libros en el árbol.
bool existeLibroTABBLibros(TABBLibros abbLibros, int isbn){
    if (abbLibros == NULL) 
     return false;
    else if (isbn ==  isbnTLibro(abbLibros->l))
return true;
else
if (isbn < isbnTLibro(abbLibros->l))
    return existeLibroTABBLibros(abbLibros->izq, isbn);
else
    return existeLibroTABBLibros(abbLibros->der, isbn);
}

// Función para obtener un libro del árbol.
// PRE: el libro está en el árbol
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(log(n)) caso promedio, siendo n la cantidad de libros en el árbol.

TLibro obtenerLibroTABBLibros(TABBLibros abbLibros, int isbn){
    if(abbLibros == NULL)
        return NULL;    
    int isbnNodo = isbnTLibro(abbLibros->l);
    if(isbn == isbnNodo)
        return abbLibros->l;
    else if (isbn < isbnNodo)
        return obtenerLibroTABBLibros(abbLibros->izq, isbn);
    else
        return obtenerLibroTABBLibros(abbLibros->der, isbn);
}

// Funcion para obtener la altura del árbol.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(n) peor caso, siendo n la cantidad de libros en el árbol.
nat alturaTABBLibros(TABBLibros abbLibros){
   if (abbLibros == NULL) {
        return 0;
    } else {
        nat alturaIzq = alturaTABBLibros(abbLibros->izq);
        nat alturaDer = alturaTABBLibros(abbLibros->der);

        if (alturaIzq > alturaDer) {
            return 1 + alturaIzq;
        } else {
            return 1 + alturaDer;
        }
    }
}

// Función para obtener el libro con el ISBN más grande del árbol.
// PRE: el árbol no es vacío
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(n) peor caso, siendo n la cantidad de libros en el árbol.
TLibro maxISBNLibroTABBLibros(TABBLibros abbLibros){
    if (abbLibros->der == NULL) {
        return abbLibros->l;
    } else {
        return maxISBNLibroTABBLibros(abbLibros->der);
    }
}



// Función para eliminar un libro del árbol.
// En caso de que el nodo a remover tenga ambos subárboles no vacíos, se
// reemplaza por el libro con el ISBN más grande del subárbol izquierdo. 
// PRE: El libro está en el árbol
/* Requisitos específicos de la implementación solicitada: */
// La función es O(n) peor caso, donde n es la cantidad de libros en el árbol.
void removerLibroTABBLibros(TABBLibros &abbLibros, int isbn){
    if (abbLibros == NULL) return; // caso base 

    if (isbn < isbnTLibro(abbLibros->l)) {
        removerLibroTABBLibros(abbLibros->izq, isbn);
    } 
    else if (isbn > isbnTLibro(abbLibros->l)) {
        removerLibroTABBLibros(abbLibros->der, isbn);
    } 
    else {
        // caso 1: hoja sin hijos
        if (abbLibros->izq == NULL && abbLibros->der == NULL) {
            liberarTLibro(abbLibros->l);
            delete abbLibros;
            abbLibros = NULL;
        }
        // caso 2: un solo hijo izquierdo o derecho
        else if (abbLibros->izq == NULL) {
            TABBLibros temp = abbLibros;
            abbLibros = abbLibros->der;
            liberarTLibro(temp->l);
            delete temp;
        } 
        else if (abbLibros->der == NULL) {
            TABBLibros temp = abbLibros;
            abbLibros = abbLibros->izq;
            liberarTLibro(temp->l);
            delete temp;
        }
        // caso 3: dos hijos
        else {
            TLibro maxIzq = maxISBNLibroTABBLibros(abbLibros->izq);
            liberarTLibro(abbLibros->l);
            abbLibros->l = copiarTLibro(maxIzq); 
            removerLibroTABBLibros(abbLibros->izq, isbnTLibro(maxIzq));
        }
    }
}


// Función para obtener la cantidad de libros en el árbol.
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(n) peor caso, siendo n la cantidad de libros en el árbol.
int cantidadTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL)
    return 0;
     else {
        nat cantidadIzq = cantidadTABBLibros(abbLibros->izq);
        nat cantidadDer = cantidadTABBLibros(abbLibros->der);

        return (1 + cantidadIzq + cantidadDer);
            
    }
}
// Función para obtener el libro Nésimo del árbol. 
// La numeración de los libros se considera por orden de 'ISBN', iniciando en 1.
// Ejemplos:  
//  obtenerNesimoLibroTABBLibros(abbLibros, 1) devuelve el libro con menor ISBN
//  obtenerNesimoLibroTABBLibros(abbLibros, 2) devuelve el segundo libro con menor ISBN
//  obtenerNesimoLibroTABBLibros(abbLibros, cantidadTABBLibros(abbLibros)) devuelve el 
//  libro con mayor ISBN.
// PRE: cantidadTABBLibros(abbLibros) >= n
// PRE: n > 0 
/* Requisitos específicos de la implementación solicitada: */
// La funcion es O(m) peor caso, siendo m la cantidad de libros en el árbol.
void obtenerNesimoLibroAux(TABBLibros abbLibros, int n, int *contador, TLibro *resultado) {
    if (abbLibros==NULL)
    return;
    obtenerNesimoLibroAux(abbLibros->izq, n, contador, resultado);

    (*contador)++;
    if (*contador == n) {
        *resultado = abbLibros->l;
        return; 
    }
    obtenerNesimoLibroAux(abbLibros->der, n, contador, resultado);
}

TLibro obtenerNesimoLibroTABBLibros(TABBLibros abbLibros, int n){
    int contador = 0;
    TLibro resultado;
    obtenerNesimoLibroAux(abbLibros, n, &contador, &resultado);
    return resultado;
}
TABBLibros filtradoPorGeneroTABBLibros(TABBLibros abbLibros, int genero) {
    if (abbLibros == NULL) return NULL;

    // filtrado de subárboles
    TABBLibros izqFiltrado = filtradoPorGeneroTABBLibros(abbLibros->izq, genero);
    TABBLibros derFiltrado = filtradoPorGeneroTABBLibros(abbLibros->der, genero);

    // si el nodo cumple con el genero lo usamos como raíz
    if (idGeneroTLibro(abbLibros->l) == genero) {
        TABBLibros nodo = new rep_abbLibros;
        nodo->l = copiarTLibro(abbLibros->l);
        nodo->izq = izqFiltrado;
        nodo->der = derFiltrado;
        return nodo;
    }

    // si el nodo no cumple fusionamos los subárboles izquierdo y derecho
    if (!izqFiltrado) return derFiltrado;
    if (!derFiltrado) return izqFiltrado;

    // si ambos existen escogemos uno como raiz y el otro como subárbol derecho minimo
    TABBLibros raiz = izqFiltrado;
    TABBLibros temp = raiz;
    while (temp->der) temp = temp->der;
    temp->der = derFiltrado;
    return raiz;
}

