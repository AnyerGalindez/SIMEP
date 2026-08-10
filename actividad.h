#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H
#include "componenteproyecto.h"
class Actividad : public ComponenteProyecto
{
private:
    int familias,comercios;
public:

    Actividad();
    int obtenerBeneficiarios() override;
    void aceptar(ElementoVisitor* v) override;

};

#endif // ACTIVIDAD_H
