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

    Q_INVOKABLE void iniciarSimulacion();
    Q_INVOKABLE void detenerSimulacion();
    Q_INVOKABLE void reiniciarSimulacion(); // <-- Nuevo método

signals:
    void valorCambiado();

private:
    IndicadorNumerico *indicador;
    QTimer *timer;
};

#endif // SIMULADOR_H