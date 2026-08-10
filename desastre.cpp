#include "desastre.h"

Desastre::Desastre(QString f,QString c, double i, int d) {
    fecha=f;
    coordenadas=c;
    intensidad=i;
    damnificados=d;
}
QString Desastre::getFecha() const{
    return fecha;
}
QString Desastre::getCoordenadas() const {
    return coordenadas;
}
double Desastre::getIntensidad() const {
    return intensidad;
}
int Desastre::getDamnificados() const {
    return damnificados;
}
void Desastre::setFecha(QString f){ fecha=f;}
void Desastre::setCoordenadas(QString c){coordenadas=c;}
void Desastre::setIntensidad(double i){intensidad=i;}
void Desastre::setDamnificados(int d){damnificados=d;}