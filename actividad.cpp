#include "actividad.h"
#include "elementovisitor.h"
Actividad::Actividad() {
    familias=0;
    comercios=0;
}

int Actividad:: obtenerBeneficiarios(){
    return familias+comercios;
}
void Actividad ::aceptar(ElementoVisitor *v){
    v->visitarActividad(this);

}
