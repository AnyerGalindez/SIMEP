#include "programa.h"

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

}

Programa::~Programa(){
    for(int i=0; i<hijos.size();i++){
        delete hijos[i];
    }
    hijos.clear();
}