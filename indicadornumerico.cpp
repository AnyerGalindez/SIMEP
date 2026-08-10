#include "indicadornumerico.h"

IndicadorNumerico::IndicadorNumerico(QString n) {
    nombre=n;
    valor=00;
}
void IndicadorNumerico::actualizarValor(double nuevoValor){
    valor=nuevoValor;
}
