#ifndef REPORTVISITORPDF_H
#define REPORTVISITORPDF_H
#include <QString>
#include "elementovisitor.h"
#include "actividad.h"
#include "programa.h"

class ReportVisitorPDF : public ElementoVisitor
{
private:
    QString reporteContext;
public:
    ReportVisitorPDF();
    void visitarActividad(Actividad* a) override;
    void visitarPrograma(Programa* p) override;
    void exportarPDF();
};

#endif // REPORTVISITORPDF_H
