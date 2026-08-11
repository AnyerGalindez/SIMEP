#ifndef ELEMENTOVISITOR_H
#define ELEMENTOVISITOR_H

// Declaraciones adelantadas (Forward declarations)
class Programa;
class Desastre;
class Organizacion;
class Actividad;

class ElementoVisitor {
public:
    virtual ~ElementoVisitor() = default;

    virtual void visitarPrograma(Programa* programa) = 0;
    virtual void visitarDesastre(Desastre* desastre) = 0;
    virtual void visitarOrganizacion(Organizacion* organizacion) = 0;
    virtual void visitarActividad(Actividad* actividad) = 0;
};

#endif // ELEMENTOVISITOR_H