#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QObject>
#include <QTimer>
#include "indicadornumerico.h"

class Simulador : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double valorIndicador READ obtenerValorIndicador NOTIFY valorCambiado)

public:
    explicit Simulador(QObject *parent = nullptr);
    ~Simulador();

    double obtenerValorIndicador() const;

public slots:
    void iniciarSimulacion();
    void detenerSimulacion();

signals:
    void valorCambiado();

private:
    QTimer *timer;
    IndicadorNumerico *indicador;
};

#endif // SIMULADOR_H