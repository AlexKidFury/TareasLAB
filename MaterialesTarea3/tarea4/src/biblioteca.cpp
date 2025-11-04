#include "../include/biblioteca.h"
#include <assert.h>

struct rep_biblioteca {
TColaReservas reservas; 
TAGGeneros arbol;
TABBLibros libros;
TLSESocios socios;
TLDEPrestamos prestamos;
};

// Función que crea un elemento de tipo TBiblioteca.
TBiblioteca crearTBiblioteca(){
TBiblioteca biblioteca = new rep_biblioteca;
biblioteca->reservas= crearTColaReservas();
biblioteca->arbol = crearTAGGeneros();
biblioteca->libros = crearTABBLibrosVacio();
biblioteca->socios = crearTLSESociosVacia();
biblioteca->prestamos = crearTLDEPrestamosVacia();
return biblioteca;
}

// Función que agrega un género a una biblioteca
// Pre: no existe en la biblioteca otro género con el mismo id
// Debe ejecutar en O(g) peor caso, siendo g la cantidad de géneros en la biblioteca
void agregarGeneroABiblioteca(TBiblioteca biblioteca, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]){ 
insertarGeneroTAGGeneros(biblioteca->arbol, idGeneroPadre, idGenero, nombreGenero);
}
// Función que agrega un libro a la biblioteca
//  - Agrega al libro al árbol de libros de la biblioteca.
// PRE: no existe un libro en la biblioteca con el mismo ISBN que el libro parámetro.
// Debe ejecutar en O(l) peor caso, siendo l la cantidad de libros en la biblioteca.
void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro){   
insertarLibroTABBLibros(biblioteca->libros, libro);
}
// Registra un socio en la biblioteca.
//  - Agrega al socio a la lista de socios de la biblioteca.
// PRE: no existe un socio de la biblioteca con el mismo ID que el socio parámetro.
// Debe ejecutar en O(s) peor caso, siendo s la cantidad de socios en la biblioteca.
void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio){ 
insertarTLSESocios(biblioteca->socios, socio);
}
// Función para prestar un libro en la biblioteca. Realiza las acciones necesarias para gestionar un
// préstamo:
//   - Crea una préstamo para el socio 'socio' y el libro 'isbnLibro' y la inserta en la lista de préstamos.
// PRE: existe un socio de id 'ciSocio' registrado en la biblioteca.
// PRE: existe un libro de isbn 'isbnLibro' en el árbol de libros de la biblioteca.
// Debe ejecutar en O(max(s, l, p)), siendo:
//   - s la cantidad de socios en la biblioteca.
//   - l la cantidad de libros en la biblioteca.
//   - p la cantidad de prestamos en la biblioteca.
void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo){

  TSocio miSocio = obtenerSocioTLSESocios(biblioteca->socios, ciSocio);
  TLibro miLibro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);

 TPrestamo nuevoPrestamo = crearTPrestamo(miSocio, miLibro, fechaPrestamo);
  insertarTLDEPrestamos(biblioteca->prestamos, nuevoPrestamo);


}

// Indica si un libro está disponible para ser prestado. Un libro se considera disponible
// si lo tiene la biblioteca y no se encuentra prestado.
// Debe ejecutar en O(l + p^2)), siendo:
//  - l la cantidad de libros en la biblioteca.
//  - p la cantidad de prestamos en la biblioteca.
bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro){
if (!existeLibroTABBLibros(biblioteca->libros, isbnLibro))
return false;

TLDEPrestamos filtrada = filtrarPrestamosTLDEPrestamos(biblioteca->prestamos, 1);
nat cant = cantidadTLDEPrestamos(filtrada);

for(nat i=1;i<=cant; i++){
TPrestamo p = obtenerNesimoTLDEPrestamos(filtrada, i);
  if (isbnTLibro(libroTPrestamo(p)) == isbnLibro){
    liberarTLDEPrestamos(filtrada);
    return false;
  }
}
liberarTLDEPrestamos(filtrada);
return true;
}
// Función para reservar un libro en la biblioteca. Realiza las acciones necesarias para gestionar una
// reserva:
//    - Crea una reserva para el socio 'socio' y el libro 'isbnLibro' y la inserta en al cola de reservas.
// PRE: el libro de isbn 'isbnLibro' se encuentra prestado.
// Debe ejecutar en O(max(s, l)), siendo:
//  - s la cantidad de socios en la biblioteca.
//  - l la cantidad de libros en la biblioteca.
void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro){

  TSocio miSocio = obtenerSocioTLSESocios(biblioteca->socios, ciSocio);
  TLibro miLibro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);
  TReserva miReserva = crearTReserva(miSocio, miLibro);
  encolarTColaReservas(biblioteca->reservas, miReserva);
}

// Realiza las acciones necesarias para devolver un libro:
//  - Marca el préstamo como retornado, actualizando la fecha de devolución. El préstamo
//    se identifica por socio, libro y fecha de préstamo. Se asume que no puede existir un préstamo del mismo libro
//    para la misma persona en la misma fecha.
// PRE: existe un socio de id 'ciSocio' registrado en la biblioteca.
// PRE: existe un libro de isbn 'isbnLibro' en el árbol de libros de la biblioteca.
// PRE: el libro de isbn 'isbnLibro' se encuentra actualmente prestado al socio de id 'ciSocio'
// Debe ejecutar en O(p), siendo p la cantidad de prestamos en la biblioteca.
/*void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
TLDEPrestamos filtrada = filtrarPrestamosTLDEPrestamos(biblioteca->prestamos, 1);

nat cant = cantidadTLDEPrestamos(filtrada);
for(nat i= 1;i<=cant; i++){
TPrestamo p = obtenerNesimoTLDEPrestamos(filtrada, i);
if(isbnTLibro(libroTPrestamo(p)) == isbnLibro){
actualizarFechaDevolucionTPrestamo(p, fechaDevolucion);
liberarTLDEPrestamos(filtrada);
return;
}
}

}*/
void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
  if (biblioteca == NULL) return;

  int n = cantidadTLDEPrestamos(biblioteca->prestamos);
  bool encontrado = false;

  for (int i = 1; i <= n && !encontrado; i++) {
    TPrestamo p = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, i);

    if (p != NULL) {
      TSocio s = socioTPrestamo(p);
      TLibro l = libroTPrestamo(p);

      if (s != NULL && l != NULL) {
        int ci = ciTSocio(s);
        int isbn = isbnTLibro(l);

        if (ci == ciSocio && isbn == isbnLibro && !fueRetornadoTPrestamo(p)) {
          actualizarFechaDevolucionTPrestamo(p, fechaDevolucion);
          encontrado = true;   // reemplaza al break
        }
      }
    }
  }
}


// Función que obtiene todos los libros de la biblioteca que pertenecen a un género y
// a sus respectivos sub-géneros.
// Debe ejecutar en O(g*l*l) siendo:
//  - g la cantidad de géneros en la biblioteca.
//  - l la cantidad de libros en la biblioteca.
TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero){
  return filtradoPorGeneroTABBLibros(biblioteca->libros, idGenero);
}

// Imprime los socios de la biblioteca según el formato de la función 'imprimirTLSESocios'
// Debe ejecutar en O(s), siendo s la cantidad de socios de la biblioteca.
void imprimirSociosTBiblioteca(TBiblioteca biblioteca){
imprimirTLSESocios(biblioteca->socios);
}

// Imprime los libros de la biblioteca según el formato de la función 'imprimprimirTABBLibrosimr'
// Debe ejecutar en O(l), siendo l la cantidad de socios de la biblioteca.
void imprimirLibrosTBiblioteca(TBiblioteca biblioteca){
imprimirTABBLibros(biblioteca->libros);
}

// Imprime los libros de la biblioteca según el formato de la función 'imprimirTColaReservas'
// Debe ejecutar en O(r), siendo r la cantidad de reservas de la biblioteca.
void imprimirReservasTBiblioteca(TBiblioteca biblioteca){
  imprimirTColaReservas(biblioteca->reservas);
}

// Imprime los libros de la biblioteca según el formato de la función 'imprimirTLDEPrestamos'
// Debe ejecutar en O(p), siendo p la cantidad de reservas de la biblioteca.
void imprimirPrestamosTBiblioteca(TBiblioteca biblioteca){
  imprimirTLDEPrestamos(biblioteca->prestamos);
}

// Función que libera la memoria asignada para la biblioteca.
// POST: el puntero biblioteca apunta a NULL.
// Debe ejecutar en O(max(s, l, p, g, r)), siendo:
//   - s la cantidad de socios en la biblioteca.
//   - l la cantidad de libros en la biblioteca.
//   - p la cantidad de prestamos en la biblioteca.
//   - g la cantidad de géneros en la biblioteca.
//   - r la cantidad de reservas en la biblioteca.
void liberarTBiblioteca(TBiblioteca &biblioteca){
  if (biblioteca == NULL)
  return;
  liberarTLSESocios(biblioteca->socios);
  liberarTColaReservasSoloEstructura(biblioteca->reservas);
  liberarTAGGeneros(biblioteca->arbol);
  liberarTABBLibros(biblioteca->libros);
  liberarTLDEPrestamosSoloEstructura(biblioteca->prestamos);
  delete biblioteca;
  biblioteca=NULL;
}