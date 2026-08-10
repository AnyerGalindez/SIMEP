#ifndef PROGRAMA_H
#define PROGRAMA_H
#include "organizacion.h"
#include "desastre.h"
#include <vector>
#include "componenteproyecto.h"
class Programa : public ComponenteProyecto
{
private:
    std::vector<ComponenteProyecto*> hijos;
    QString nombreProyecto;
    QString empresaDesarrolladora;
    QString fechaInicio;
    QString tiempoEjecucion;

    Desastre eventoAsociado;
    Organizacion organizacionAsociada;
public:
    Programa();
    void agregar(ComponenteProyecto* c) ;
    //Heredados:
    int obtenerBeneficiarios() override;
    void aceptar(ElementoVisitor* v) override;

    // Nuevos Setters
    void setNombreProyecto(QString nombre);
    void setEmpresaDesarrolladora(QString empresa);
    void setFechaInicio(QString fecha);
    void setTiempoEjecucion(QString tiempo);
    void setEventoAsociado(Desastre evento);
    void setOrganizacionAsociada(Organizacion org);

    // Getters
    QString getNombreProyecto() const;
    QString getEmpresaDesarrolladora() const;
    QString getFechaInicio() const;
    QString getTiempoEjecucion() const;
    Desastre getEventoAsociado() const;
    Organizacion getOrganizacionAsociada() const;
    ~Programa();
};

#endif // PROGRAMA_H
