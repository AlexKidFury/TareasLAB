#include "../include/fecha.h"

struct rep_fecha {
    nat dia, mes, anio;
    /************ Parte 2.1 ************/
    /*Escriba el código a continuación */


    /****** Fin de parte Parte 2.1 *****/
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
     TFecha nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    /************ Parte 3.1 ************/
    /*Escriba el código a continuación */

    /****** Fin de parte Parte 3.1 *****/
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    /************ Parte 3.3 ************/
    /*Escriba el código a continuación */
         delete fecha;
         fecha = NULL;
    /****** Fin de parte Parte 3.3 *****/
}
void imprimirTFecha(TFecha fecha) {
    /************ Parte 3.5 ************/
    /*Escriba el código a continuación */

printf("%u/%u/%u\n", fecha->dia, fecha->mes, fecha->anio);
    /****** Fin de parte Parte 3.5 *****/
}

TFecha copiarTFecha(TFecha fecha) {
    /************ Parte 3.9 ************/
    /*Escriba el código a continuación */
    /*Recuerde que las funciones auxiliares
     deben declararse antes de ser utilizadas*/
 
 TFecha copia = new rep_fecha;

 copia->dia = fecha->dia;
 copia->mes = fecha->mes;
 copia->anio = fecha->anio;
    return copia;
    /****** Fin de parte Parte 3.9 *****/
}

static nat diasMes(nat mes, nat anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            // Año bisiesto
            if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
                return 29;
            else
                return 28;
        default:
            return 0; // mes inválido
    }
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */

    // Función para aumentar una fecha en una cantidad dada de días
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
            fecha->dia -= diasMes(fecha->mes, fecha->anio);
            fecha->mes++;
            if (fecha->mes > 12) {
                fecha->mes = 1;
                fecha->anio++;
                }
            }

        }

// Función auxiliar para obtener la cantidad de días de un mes y año dado



    /****** Fin de parte Parte 3.10 *****/


int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    if((fecha1->anio < fecha2->anio) || (fecha1->anio == fecha2->anio && fecha1->mes < fecha2->mes) || (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia < fecha2->dia ) ) {
        res = -1;
    } else if ((fecha1->anio > fecha2->anio) || (fecha1->anio == fecha2->anio && fecha1->mes > fecha2->mes) || (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia ) ) {
        res = 1; 
    }
      
    /************ Parte 3.11 ************/
    /*Escriba el código a continuación */


    /****** Fin de parte Parte 3.11 *****/
    return res;
}
