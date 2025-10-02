#include "../include/socio.h"

struct rep_socio {
    int ci;
    char nombre[MAX_NOMBRE_SOCIO];
    char apellido[MAX_APELLIDO_SOCIO];
    TFecha Alta;
    int generos[MAX_GENEROS_FAVORITOS];
    int tope;
};
 
TSocio crearTSocio(int ci, const char nombre[MAX_NOMBRE_SOCIO], const char apellido[MAX_APELLIDO_SOCIO], nat diaAlta, nat mesAlta, nat anioAlta){
    TSocio nuevoSocio = new rep_socio;
    nuevoSocio->ci = ci;
    strcpy(nuevoSocio->nombre, nombre);
    strcpy(nuevoSocio->apellido, apellido);
    nuevoSocio->Alta = crearTFecha(diaAlta, mesAlta, anioAlta);
    for (int i = 0; i < MAX_GENEROS_FAVORITOS; i++) {
        nuevoSocio->generos[i] = -1;
    }
    nuevoSocio->tope = 0;
    return nuevoSocio;
}

void imprimirTSocio(TSocio socio){
    printf("Socio %d: %s %s\n", socio->ci, socio->nombre, socio->apellido);
    printf("Fecha de alta: ");
    imprimirTFecha(socio->Alta);
    printf("Géneros favoritos: ");
    for (int i = 0; i < socio->tope; i++) {
        printf("%d ", socio->generos[i]);
    }
    printf("\n");
}



void liberarTSocio(TSocio &socio){
if (socio!= NULL) {
        liberarTFecha(socio->Alta);
        delete socio;
        socio = NULL;
    }
}

int ciTSocio(TSocio socio){
    return socio->ci;
}

char* nombreTSocio(TSocio socio){
    return socio->nombre;
}

char* apellidoTSocio(TSocio socio){
    return socio->apellido;
}

TFecha fechaAltaTSocio(TSocio socio){
    return socio->Alta;
}

void agregarGeneroFavoritoTSocio(TSocio &socio, int idGenero){
if (socio->tope < MAX_GENEROS_FAVORITOS) { 
    socio->generos[socio->tope] = idGenero;
    socio->tope++;
}
}

bool tieneGeneroFavoritoTSocio(TSocio socio, int idGenero){
    for (int i = 0; i < socio->tope; i++) {
        if (socio->generos[i] == idGenero) {
            return true;
        }
    }
    return false;
}

int cantidadGenerosFavoritosTSocio(TSocio socio){
    return socio->tope;
}

TSocio copiarTSocio(TSocio socio){
    TSocio copiaSocio = new rep_socio;
    copiaSocio->ci = socio->ci;
    strcpy(copiaSocio->nombre, socio->nombre);
    strcpy(copiaSocio->apellido, socio->apellido);
    copiaSocio->Alta = copiarTFecha(socio->Alta);
    for (int i = 0; i < socio->tope; i++) {
        copiaSocio->generos[i] = socio->generos[i];
    }
    copiaSocio->tope = socio->tope;
    return copiaSocio;
}