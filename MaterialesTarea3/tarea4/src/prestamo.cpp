
#include "../include/prestamo.h"

struct rep_prestamo {
TFecha fechaRetiro;
TFecha fechaDevolución;
TSocio socio;
TLibro libro; 
};

TPrestamo crearTPrestamo(TSocio socio, TLibro libro, TFecha fechaRetiro){
  TPrestamo nuevoPrestamo = new rep_prestamo;
  nuevoPrestamo-> socio = socio;
  nuevoPrestamo-> libro = libro;
  nuevoPrestamo-> fechaRetiro = fechaRetiro;
  nuevoPrestamo->fechaDevolución = NULL;
  return nuevoPrestamo;
}
 
void imprimirTPrestamo(TPrestamo prestamo){
  printf("Préstamo de libro %s a %s %s.\n", tituloTLibro(prestamo->libro), nombreTSocio(prestamo->socio), apellidoTSocio(prestamo->socio));
  imprimirTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevolución == NULL)
    printf("No retornado\n");
  else
  imprimirTFecha(prestamo->fechaDevolución);
}

void liberarTPrestamo(TPrestamo &prestamo){
if (prestamo != NULL){
  liberarTFecha(prestamo->fechaRetiro);
  liberarTFecha(prestamo->fechaDevolución);
  liberarTSocio(prestamo->socio);
  liberarTLibro(prestamo->libro);
  delete prestamo;
  prestamo = NULL;
}
}

TSocio socioTPrestamo(TPrestamo prestamo){
  return prestamo->socio;
}
 
TFecha fechaRetiroTPrestamo(TPrestamo prestamo){
  return prestamo->fechaRetiro;
}

TFecha fechaDevolucionTPrestamo(TPrestamo prestamo){
  return prestamo->fechaDevolución;
}

TLibro libroTPrestamo(TPrestamo prestamo){
  return prestamo->libro;
}

bool fueRetornadoTPrestamo(TPrestamo prestamo){
  return (prestamo->fechaDevolución != NULL);
}

void actualizarFechaDevolucionTPrestamo(TPrestamo prestamo, TFecha fechaDevolucion){
if (fueRetornadoTPrestamo(prestamo))
liberarTFecha(prestamo->fechaDevolución);

prestamo->fechaDevolución = fechaDevolucion;
}

TPrestamo copiarTPrestamo(TPrestamo prestamo){
   TPrestamo copiaPrestamo = new rep_prestamo;
  copiaPrestamo-> socio = copiarTSocio(prestamo->socio);
  copiaPrestamo-> libro = copiarTLibro(prestamo->libro);
  copiaPrestamo-> fechaRetiro = copiarTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevolución != NULL)
    copiaPrestamo-> fechaDevolución = copiarTFecha(prestamo->fechaDevolución);
  else
    copiaPrestamo-> fechaDevolución = NULL;
  return copiaPrestamo;
}

/* ********** FUNCIONES NUEVAS TAREA 3 ********** */
// Libera la memoria asignada para un préstamo y sus fechas asociadas.
// IMPORTANTE: Esta función NO libera la memoria del socio ni del libro apuntados por el préstamo,
// evitando así problemas de doble liberación.
// PRE: prestamo != NULL
/* Requisitos específicos de la implementación solicitada: */
// La función es O(1) en el peor caso.
void liberarTPrestamoSoloEstructura(TPrestamo &prestamo){
  liberarTFecha(prestamo->fechaRetiro);
  liberarTFecha(prestamo->fechaDevolución);
  delete prestamo;
  prestamo = NULL;
}