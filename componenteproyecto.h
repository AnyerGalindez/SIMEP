#ifndef COMPONENTEPROYECTO_H
#define COMPONENTEPROYECTO_H
#include <QString>

class ElementoVisitor;
class ComponenteProyecto
{
protected:
    QString nombre,codigo;
public:
    ComponenteProyecto();
    virtual ~ComponenteProyecto() {};
    virtual int obtenerBeneficiarios()=0;
    virtual void aceptar(ElementoVisitor* v)=0;

};

#endif // COMPONENTEPROYECTO_H
