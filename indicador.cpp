#include "indicador.h"

Indicador::Indicador() {
    valor=0.0;
}

Indicador::~Indicador(){}
double Indicador::obtenerValor(){
    return valor;
}