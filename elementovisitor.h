#ifndef ELEMENTOVISITOR_H
#define ELEMENTOVISITOR_H
class Actividad;
class Programa;

class ElementoVisitor
{
public:
    ElementoVisitor(){};
    virtual ~ElementoVisitor() {};
    virtual void visitarActividad(Actividad* a)=0;
    virtual void visitarPrograma(Programa* p)=0;
};

#endif // ELEMENTOVISITOR_H
