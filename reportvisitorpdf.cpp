#include "reportvisitorpdf.h"
#include "programa.h"
#include "actividad.h"
#include "desastre.h"
#include "organizacion.h"

#include <QTextDocument>
#include <QPrinter>
#include <QPageSize>
#include <QDebug>

ReportVisitorPDF::ReportVisitorPDF()
    : m_damnificados(0), m_familiasTotales(0), m_comerciosTotales(0) {}

void ReportVisitorPDF::setDatosGenerales(const QString &nombre, const QString &empresa,
                                         const QString &coordenadas, int damnificados,
                                         int familias, int comercios) {
    m_nombreProyecto = nombre;
    m_empresa = empresa;
    m_coordenadas = coordenadas;
    m_damnificados = damnificados;
    m_familiasTotales = familias;
    m_comerciosTotales = comercios;
}

void ReportVisitorPDF::visitarPrograma(Programa *programa) {
    Q_UNUSED(programa);
    m_detallesEstructura += "<li><b>Nodo Programa:</b> Coordinación General Registrada</li>";
}

void ReportVisitorPDF::visitarActividad(Actividad *actividad) {
    Q_UNUSED(actividad);
    m_detallesEstructura += "<li><b>Nodo Actividad:</b> Distribución de insumos y soporte operativo</li>";
}

void ReportVisitorPDF::visitarDesastre(Desastre *desastre) {
    Q_UNUSED(desastre);
    m_detallesEstructura += "<li><b>Nodo Desastre:</b> Registro de evaluación de daños</li>";
}

void ReportVisitorPDF::visitarOrganizacion(Organizacion *organizacion) {
    Q_UNUSED(organizacion);
    m_detallesEstructura += "<li><b>Nodo Organización:</b> Entidad participante asignada</li>";
}

bool ReportVisitorPDF::exportarPDF(const QString &rutaArchivo) {
    QTextDocument doc;

    // CSS ajustado con unidades 'pt' y porcentajes para renderizado dinámico en QPrinter
    QString html = QString(R"(
        <!DOCTYPE html>
        <html>
        <head>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    color: #1e293b;
                    margin: 10pt;
                }
                .header {
                    border-bottom: 2pt solid #2563eb;
                    padding-bottom: 8pt;
                    margin-bottom: 15pt;
                }
                .header h1 {
                    color: #0f172a;
                    font-size: 18pt;
                    margin: 0;
                }
                .header p {
                    color: #64748b;
                    font-size: 10pt;
                    margin: 4pt 0 0 0;
                }
                .card {
                    background-color: #f8fafc;
                    border: 1pt solid #cbd5e1;
                    border-radius: 4pt;
                    padding: 12pt;
                    margin-bottom: 15pt;
                }
                .card h3 {
                    margin: 0 0 8pt 0;
                    color: #1e40af;
                    font-size: 12pt;
                    border-bottom: 1pt solid #e2e8f0;
                    padding-bottom: 4pt;
                }
                table {
                    width: 100%;
                    border-collapse: collapse;
                }
                th, td {
                    text-align: left;
                    padding: 6pt 8pt;
                    border-bottom: 1pt solid #e2e8f0;
                    font-size: 10pt;
                }
                th {
                    background-color: #eff6ff;
                    color: #1e3a8a;
                    width: 35%;
                }
                ul {
                    margin: 6pt 0;
                    padding-left: 15pt;
                    font-size: 10pt;
                    color: #334155;
                }
                li {
                    margin-bottom: 4pt;
                }
                .footer {
                    text-align: center;
                    margin-top: 25pt;
                    color: #94a3b8;
                    font-size: 8pt;
                    border-top: 1pt solid #e2e8f0;
                    padding-top: 8pt;
                }
            </style>
        </head>
        <body>
            <div class="header">
                <h1>SIMEP - Informe de Evaluación Humanitaria</h1>
                <p>Sistema de Monitoreo y Evaluación de Proyectos | UNEXPO Barquisimeto</p>
            </div>

            <div class="card">
                <h3>Información General del Proyecto y Desastre</h3>
                <table>
                    <tr><th>Nombre del Proyecto:</th><td><b>  %1</b></td></tr>
                    <tr><th>Organización Responsable:</th><td>  %2</td></tr>
                    <tr><th>Coordenadas Geográficas:</th><td>  %3</td></tr>
                    <tr><th>Damnificados Estimados:</th><td>  %4 personas</td></tr>
                </table>
            </div>

            <div class="card">
                <h3>Resumen de Impacto y Beneficiarios</h3>
                <table>
                    <tr><th>Familias Atendidas:</th><td><b>  %5</b> familias</td></tr>
                    <tr><th>Comercios Recuperados:</th><td><b>  %6</b> comercios</td></tr>
                </table>
            </div>

            <div class="card">
                <h3>Trazabilidad de la Estructura</h3>
                <ul>
                    %7
                </ul>
            </div>

            <div class="footer">
                Documento generado automáticamente por SIMEP • Todos los derechos reservados.
            </div>
        </body>
        </html>
    )")
                       .arg(m_nombreProyecto.isEmpty() ? "No especificado" : m_nombreProyecto)
                       .arg(m_empresa.isEmpty() ? "No especificada" : m_empresa)
                       .arg(m_coordenadas.isEmpty() ? "Sin datos" : m_coordenadas)
                       .arg(m_damnificados)
                       .arg(m_familiasTotales)
                       .arg(m_comerciosTotales)
                       .arg(m_detallesEstructura.isEmpty() ? "<li>Sin nodos registrados en la estructura.</li>" : m_detallesEstructura);

    doc.setHtml(html);

    // Configuración del printer sin usar HighResolution para evitar encogimiento del HTML
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(rutaArchivo);
    printer.setPageSize(QPageSize(QPageSize::A4));

    doc.print(&printer);
    return true;
}