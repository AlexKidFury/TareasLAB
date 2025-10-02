
#include "../include/reserva.h"

struct rep_reserva {
  TSocio socio;
  TLibro libro; 
};

TReserva crearTReserva(TSocio socio, TLibro libro){
  TReserva reserva = new rep_reserva;
  reserva->socio = socio;
  reserva->libro = libro;
  return reserva;
}

void imprimirTReserva(TReserva reserva){
printf("Reserva de libro %s por %s %s.\n", tituloTLibro(reserva->libro), nombreTSocio(reserva->socio), apellidoTSocio(reserva->socio));
}


void liberarTReserva(TReserva &reserva){
if (reserva != NULL){
  liberarTSocio(reserva->socio);
  liberarTLibro(reserva->libro);
  delete reserva;
  reserva = NULL;
}
}

TSocio socioTReserva(TReserva reserva){
  return reserva->socio;
}

TLibro libroTReserva(TReserva reserva){
  return reserva->libro;
}

TReserva copiarTReserva(TReserva reserva){
  TReserva copia = new rep_reserva;
  copia->socio = copiarTSocio(reserva->socio);
  copia->libro = copiarTLibro(reserva->libro);
  return copia;
}

// Función que libera únicamente la estructura de la reserva, pero NO libera la memoria
// del socio ni del libro a los que apunta.
// Debe ejecutar en O(1) peor caso
void liberarTReservaSoloEstructura(TReserva &reserva) {
delete reserva;
reserva = NULL;
}
