#ifndef INDICADOR_H
#define INDICADOR_H
#include <QString>
class Indicador
{
protected:
    QString nombre;
    double valor;

public:
    Indicador();
    virtual void actualizarValor(double nuevoValor)=0;
    double obtenerValor();
    virtual ~Indicador();
};

#endif // INDICADOR_H
