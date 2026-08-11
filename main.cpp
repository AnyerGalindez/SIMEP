#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "simulador.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Instanciamos el simulador y lo exponemos a QML con el nombre "simulador"
    Simulador simulador;
    engine.rootContext()->setContextProperty("simulador", &simulador);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SIMEP", "Main");

    return QGuiApplication::exec();
}