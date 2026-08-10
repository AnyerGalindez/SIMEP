#include "programa.h"
#include "elementovisitor.h"
Programa::Programa() {}

void Programa:: agregar(ComponenteProyecto* c) {
    hijos.push_back(c);
}

int Programa:: obtenerBeneficiarios(){
    int total=0;
    for(int i=0 ; i<hijos.size();i++){

        total+=hijos[i]->obtenerBeneficiarios();

    }
    return total;
}

void Programa::aceptar(ElementoVisitor *v){
    v->visitarPrograma(this);

}

//Setters
void Programa::setNombreProyecto(QString nombre) { nombreProyecto = nombre; }
void Programa::setEmpresaDesarrolladora(QString empresa) { empresaDesarrolladora = empresa; }
void Programa::setFechaInicio(QString fecha) { fechaInicio = fecha; }
void Programa::setTiempoEjecucion(QString tiempo) { tiempoEjecucion = tiempo; }
void Programa::setEventoAsociado(Desastre evento) { eventoAsociado = evento; }
void Programa::setOrganizacionAsociada(Organizacion org) { organizacionAsociada = org; }
//getters:
QString Programa::getNombreProyecto() const { return nombreProyecto; }
QString Programa::getEmpresaDesarrolladora() const { return empresaDesarrolladora; }
QString Programa::getFechaInicio() const { return fechaInicio; }
QString Programa::getTiempoEjecucion() const { return tiempoEjecucion; }
Desastre Programa::getEventoAsociado() const { return eventoAsociado; }
Organizacion Programa::getOrganizacionAsociada() const { return organizacionAsociada; }
Programa::~Programa(){
    for(int i=0; i<hijos.size();i++){
        delete hijos[i];
    }
    hijos.clear();
}