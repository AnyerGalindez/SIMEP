#ifndef REPORTVISITORPDF_H
#define REPORTVISITORPDF_H

#include <QString>
#include "elementovisitor.h"

// Forward declarations de las clases que existen en ElementoVisitor
class Programa;
class Actividad;
class Desastre;
class Organizacion;

class ReportVisitorPDF : public ElementoVisitor {
private:
    QString m_nombreProyecto;
    QString m_empresa;
    QString m_coordenadas;
    int m_damnificados;
    int m_familiasTotales;
    int m_comerciosTotales;
    QString m_detallesEstructura;

public:
    ReportVisitorPDF();

    void setDatosGenerales(const QString &nombre, const QString &empresa,
                           const QString &coordenadas, int damnificados,
                           int familias, int comercios);

    // MÉTODOS EXACTOS QUE HEREDA DE ELEMENTOVISITOR
    void visitarPrograma(Programa *programa) override;
    void visitarActividad(Actividad *actividad) override;
    void visitarDesastre(Desastre *desastre) override;
    void visitarOrganizacion(Organizacion *organizacion) override;

    bool exportarPDF(const QString &rutaArchivo);
};

#endif // REPORTVISITORPDF_H