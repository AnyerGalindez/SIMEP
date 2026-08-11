#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QDebug>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>

#include "reportvisitorpdf.h"
#include "programa.h"
#include "actividad.h"
#include "simulador.h"

class GestorReportes : public QObject {
    Q_OBJECT
public:
    explicit GestorReportes(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE bool generarReportePDF(const QString &nombreArchivoBase,
                                       const QString &nombreProyecto,
                                       const QString &empresa,
                                       const QString &coordenadas,
                                       int damnificados,
                                       int familias,
                                       int comercios)
    {
        // 1. Obtener la carpeta del proyecto a partir de la ubicación de main.cpp
        QFileInfo fileInfo(__FILE__);
        QString rutaCarpetaProyecto = fileInfo.absolutePath();

        // 2. Definir la subcarpeta "reportes"
        QString rutaCarpetaReportes = rutaCarpetaProyecto + "/reportes";

        // 3. Crear la carpeta si no existe
        QDir dir(rutaCarpetaReportes);
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        // 4. Generar un nombre único basado en fecha y hora (Ej: Reporte_SIMEP_20260811_111525.pdf)
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        // Limpiamos la extensión si venía en el nombre base
        QString nombreBase = nombreArchivoBase;
        if (nombreBase.endsWith(".pdf", Qt::CaseInsensitive)) {
            nombreBase.chop(4);
        }

        QString nombreArchivoUnico = QString("%1_%2.pdf").arg(nombreBase, timestamp);
        QString rutaCompleta = rutaCarpetaReportes + "/" + nombreArchivoUnico;

        ReportVisitorPDF visitor;

        // Instanciamos componentes Composite
        Programa programaPrincipal;
        Actividad actividad1;

        // Aceptamos el visitor en los elementos
        programaPrincipal.aceptar(&visitor);
        actividad1.aceptar(&visitor);

        // Cargamos los datos recolectados de la interfaz
        visitor.setDatosGenerales(nombreProyecto, empresa, coordenadas, damnificados, familias, comercios);

        // Exportar a la ruta con el nombre único
        bool exito = visitor.exportarPDF(rutaCompleta);

        if (exito) {
            QDesktopServices::openUrl(QUrl::fromLocalFile(rutaCompleta));
        }

        return exito;
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Simulador simulador;
    GestorReportes gestorReportes;

    engine.rootContext()->setContextProperty("simulador", &simulador);
    engine.rootContext()->setContextProperty("gestorReportes", &gestorReportes);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("SIMEP", "Main");

    return app.exec();
}