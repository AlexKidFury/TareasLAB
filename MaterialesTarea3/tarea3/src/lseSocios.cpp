
#include "../include/lseSocios.h"

struct rep_lseSocios {
	TSocio socio;
	rep_lseSocios* sig;
};

TLSESocios crearTLSESociosVacia(){
    return NULL;
}

bool esVaciaTLSESocios(TLSESocios lseSocios){
	return (lseSocios == NULL);
}

void imprimirTLSESocios(TLSESocios lseSocios){
	printf("Lista de Socios:\n");
	while (lseSocios != NULL){
		imprimirTSocio(lseSocios->socio);
		lseSocios = lseSocios->sig;
	}
}

void liberarTLSESocios(TLSESocios &lseSocios){
		TLSESocios aux;
    while (lseSocios != NULL){
        liberarTSocio(lseSocios->socio); 
        aux = lseSocios;                 
        lseSocios = lseSocios->sig;      
        delete aux;     
	}
}

void insertarTLSESocios(TLSESocios &lseSocios, TSocio socio){
    TLSESocios nuevo = new rep_lseSocios;
    nuevo->socio = socio;
    nuevo->sig = NULL;

    if (lseSocios == NULL || compararTFechas(fechaAltaTSocio(socio), fechaAltaTSocio(lseSocios->socio)) < 0) {
        nuevo->sig = lseSocios;
        lseSocios = nuevo;
    } else {
        TLSESocios actual = lseSocios;
        while (actual->sig != NULL && compararTFechas(fechaAltaTSocio(socio), fechaAltaTSocio(actual->sig->socio)) >= 0) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }
}

bool existeSocioTLSESocios(TLSESocios lseSocios, int ci){
    while (lseSocios != NULL && ciTSocio(lseSocios->socio)!= ci){
		lseSocios = lseSocios->sig;
	}
	return lseSocios != NULL;
}

TSocio obtenerSocioTLSESocios(TLSESocios lseSocios, int ci){
    while (lseSocios != NULL && ciTSocio(lseSocios->socio)!= ci){
		lseSocios = lseSocios->sig;
	}
	return lseSocios->socio;
}

TSocio obtenerNesimoTLSESocios(TLSESocios lseSocios, int n){
    while (lseSocios != NULL && n > 1){
		lseSocios = lseSocios->sig;
        n--;
	}
    return lseSocios->socio;
}

nat cantidadTLSESocios(TLSESocios lseSocios){
    nat cont = 0;
    while (lseSocios != NULL){
		lseSocios = lseSocios->sig;
        cont++;
	}
	return cont;
}

/*void removerSocioTLSESocios(TLSESocios &lseSocios, int ci){
     while (lseSocios != NULL && ciTSocio(lseSocios->socio)!= ci){
		lseSocios = lseSocios->sig;
	}
    liberarTSocio(lseSocios->socio);
} */

void removerSocioTLSESocios(TLSESocios &lseSocios, int ci){
    if (ciTSocio(lseSocios->socio) == ci){
    TLSESocios aux = lseSocios;
    lseSocios=lseSocios->sig;
    liberarTSocio(aux->socio);
    delete aux;
    return;
    }
    
    TLSESocios actual = lseSocios;
    while(ciTSocio(actual->sig->socio) != ci)
    actual=actual->sig;
    
    TLSESocios aux = actual->sig;
    actual->sig = aux->sig;
    liberarTSocio(aux->socio);
    delete aux;}