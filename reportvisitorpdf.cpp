#include "reportvisitorpdf.h"
#include "actividad.h"
#include "programa.h"
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QDebug>

ReportVisitorPDF::ReportVisitorPDF() {
    reporteContext = "=== REPORTE OFICIAL DEL PROYECTO SIMEP ===\n\n";
}

void ReportVisitorPDF::visitarActividad(Actividad* a) {
    reporteContext += "-> Se inspecciono una Actividad. Beneficiarios directos: " + QString::number(a->obtenerBeneficiarios()) + "\n";
}

void ReportVisitorPDF::visitarPrograma(Programa* p) {
    reporteContext += "\n[+] Se inspecciono un Programa Completo. Total acumulado: " + QString::number(p->obtenerBeneficiarios()) + "\n";
}

void ReportVisitorPDF::exportarPDF() {
    QPdfWriter writer("Reporte_SIMEP.pdf");
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter(&writer);
    painter.setFont(QFont("Arial", 12));

    painter.drawText(100, 100, 2000, 3000, Qt::AlignLeft | Qt::TextWordWrap, reporteContext);

    painter.end();

    qDebug() << "Backend: Reporte PDF exportado exitosamente.";
}