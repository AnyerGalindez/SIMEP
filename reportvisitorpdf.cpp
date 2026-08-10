#include "reportvisitorpdf.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QRect>
#include <QDebug>

// Constructor obligatorio
ReportVisitorPDF::ReportVisitorPDF() {
}

// Métodos obligatorios para recorrer el árbol
void ReportVisitorPDF::visitarActividad(Actividad* a) {
}

void ReportVisitorPDF::visitarPrograma(Programa* p) {
    // 1. Extraemos los datos usando los getters que creaste
    reporteContext = "DATOS DEL PROYECTO:\n";
    reporteContext += "Nombre: " + p->getNombreProyecto() + "\n";
    reporteContext += "Empresa: " + p->getEmpresaDesarrolladora() + "\n";
    reporteContext += "Fecha de Inicio: " + p->getFechaInicio() + "\n\n";

    reporteContext += "EVENTO DE DESASTRE ASOCIADO:\n";
    reporteContext += "Ubicación: " + p->getEventoAsociado().getCoordenadas() + "\n";
    // Convertimos los números a texto con QString::number()
    reporteContext += "Intensidad: " + QString::number(p->getEventoAsociado().getIntensidad()) + "\n";
    reporteContext += "Damnificados: " + QString::number(p->getEventoAsociado().getDamnificados()) + "\n\n";

    reporteContext += "ORGANIZACIÓN RESPONSABLE:\n";
    reporteContext += "Tipo: " + p->getOrganizacionAsociada().getTipo() + "\n";
    reporteContext += "Cobertura: " + p->getOrganizacionAsociada().getCobertura() + "\n";
}

// La función que crea el documento físico
void ReportVisitorPDF::exportarPDF() {
    QString rutaArchivo = QDir::currentPath() + "/Reporte_SIMEP.pdf";

    QPdfWriter writer(rutaArchivo);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter(&writer);

    // Aseguramos que la tinta sea negra
    painter.setPen(Qt::black);

    // Pintamos el título
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(200, 400, "REPORTE OFICIAL DEL PROYECTO");

    // Pintamos todo el texto recolectado dentro de un área específica
    painter.setFont(QFont("Arial", 12));
    painter.drawText(QRect(200, 800, 2000, 2500), Qt::AlignLeft | Qt::TextWordWrap, reporteContext);

    painter.end();

    qDebug() << "PDF generado exitosamente en:" << rutaArchivo;
    QDesktopServices::openUrl(QUrl::fromLocalFile(rutaArchivo));
}