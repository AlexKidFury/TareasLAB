#include "../include/libro.h"

struct rep_libro {
    int isbn, idDeGenero;
    char título[MAX_TITULO];
    char nombreDelAutor[MAX_NOMBRE_AUTOR];
    char apellidoDelAutor[MAX_APELLIDO_AUTOR];
    char descripción[MAX_DESCRIPCION];
    TFecha fechaDeEdición;
};

// Crea y retorna un elemento de tipo TLibro con los valores dados
TLibro crearTLibro(int isbn, const char titulo[MAX_TITULO], const char nombreAutor[MAX_NOMBRE_AUTOR], const char apellidoAutor[MAX_APELLIDO_AUTOR], const char descripcion[MAX_DESCRIPCION], int idGeneroLibro, TFecha fechaEdicion){
     TLibro nuevoLibro = new rep_libro;
    nuevoLibro->isbn=isbn;
    strcpy(nuevoLibro->título, titulo);
    strcpy(nuevoLibro->nombreDelAutor, nombreAutor);
    strcpy(nuevoLibro->apellidoDelAutor, apellidoAutor);
    strcpy(nuevoLibro->descripción, descripcion);
    nuevoLibro->idDeGenero=idGeneroLibro;
    nuevoLibro->fechaDeEdición=fechaEdicion;
    
    return nuevoLibro;
}

// Libera la memoria asignada para el libro 'l'
// Debe liberar también la memoria de la fecha asociada
void liberarTLibro(TLibro &l){
     if (l != NULL) {
        liberarTFecha(l->fechaDeEdición);
        delete l;
        l = NULL;
    }
}

// Retorna el isbn del libro 'l'
int isbnTLibro(TLibro l){
     return l->isbn;
}

// Retorna el titulo del libro 'l'
// El titulo retornado comparte memoria con el parámetro. 
char* tituloTLibro(TLibro l){
    return l->título;
}

// Retorna la descripción del libro 'l'
// La descripción retornada comparte memoria con el parámetro. 
char* descripcionTLibro(TLibro l){
    return l->descripción; 

}

// Retorna el nombre del autor del libro 'l'
// El nombre retornado comparte memoria con el parámetro. 
char* nombreAutorTLibro(TLibro l){
    return l->nombreDelAutor;
}

// Retorna el apellido del autor del libro 'l'
// El apellido retornado comparte memoria con el parámetro. 
char* apellidoAutorTLibro(TLibro l){
    return l-> apellidoDelAutor;

}

// Retorna el id del género del libro 'l'
int idGeneroTLibro(TLibro l){
    return l->idDeGenero;

}

// Retorna la fecha de edición del libro 'l'.
// La fecha retornada comparte memoria con el parámetro. 
TFecha fechaEdicionTLibro(TLibro l){
    return l->fechaDeEdición;
}

// Imprime la información del libro 'l' en el siguiente formato:
// Libro <isbn> 
// Título: <título>
// Autor: <nombre autor> <apellido autor>
// Descripción: <descripcion>
// Género: <id género>
// Fecha de edición: <fecha de edición>
void imprimirTLibro(TLibro l){
    printf("Libro %d\n", l->isbn);
    printf("Título: %s\n", l->título);
    printf("Autor: %s %s\n", l->nombreDelAutor, l->apellidoDelAutor);
    printf("Descripción: %s\n", l->descripción);
    printf("Género: %d\n", l->idDeGenero);
    printf("Fecha de edición: ");
    imprimirTFecha(l->fechaDeEdición);
}

// Retorna una copia del libro 'l' que no comparte memoria con el parámetro.
TLibro copiarTLibro(TLibro l){
      TLibro copiaLibro = new rep_libro;
    copiaLibro->isbn = l->isbn;
    strcpy(copiaLibro->título, l->título);
    strcpy(copiaLibro->nombreDelAutor, l->nombreDelAutor);
    strcpy(copiaLibro->apellidoDelAutor, l->apellidoDelAutor);
    strcpy(copiaLibro->descripción, l->descripción);
    copiaLibro->idDeGenero = l->idDeGenero;
    copiaLibro->fechaDeEdición = copiarTFecha(l->fechaDeEdición);
    return copiaLibro;
}
