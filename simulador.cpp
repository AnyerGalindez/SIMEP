#include "simulador.h"
#include <QDebug>

Simulador::Simulador(QObject *parent) : QObject(parent)
{
    indicador = new IndicadorNumerico("Simulacion de Familias Atendidas");
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=]() {
        double valorActual = indicador->obtenerValor();
        indicador->actualizarValor(valorActual + 5.0);

        qDebug() << "Simulacion - Nuevo valor:" << indicador->obtenerValor();

        emit valorCambiado();
    });
}

Simulador::~Simulador() {
    delete indicador;
}

double Simulador::obtenerValorIndicador() const {
    return indicador->obtenerValor();
}

void Simulador::iniciarSimulacion() {
    timer->start(1000);
    qDebug() << "--- Simulacion Iniciada ---";
}

void Simulador::detenerSimulacion() {
    timer->stop();
    qDebug() << "--- Simulacion Detenida ---";
}