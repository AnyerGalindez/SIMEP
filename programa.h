#ifndef PROGRAMA_H
#define PROGRAMA_H
#include <vector>
#include "componenteproyecto.h"
class Programa : public ComponenteProyecto
{
private:
    std::vector<ComponenteProyecto*> hijos;
public:
    Programa();
    void agregar(ComponenteProyecto* c) ;
    //Heredados:
    int obtenerBeneficiarios() override;
    void aceptar(ElementoVisitor* v) override;
    ~Programa();
};

#endif // PROGRAMA_H
