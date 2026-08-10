#ifndef INDICADORNUMERICO_H
#define INDICADORNUMERICO_H
#include "indicador.h"

#include <QString>
class IndicadorNumerico: public Indicador
{
public:
    IndicadorNumerico(QString n);
    void actualizarValor(double nuevoValor) override;
};

#endif // INDICADORNUMERICO_H
