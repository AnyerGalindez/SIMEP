#include "organizacion.h"

Organizacion::Organizacion(QString t,double cap, QString cob) {
    tipo=t;
    capacidad=cap;
    cobertura=cob;
}

QString Organizacion::getTipo() const {return tipo;}
double Organizacion::getCapacidad() const {return capacidad;}
QString Organizacion::getCobertura() const { return cobertura;}

void Organizacion::setTipo(QString t) {tipo=t;}
void Organizacion::setCapacidad(double cap){capacidad=cap;}
void Organizacion::setCobertura(QString cob){cobertura=cob;}