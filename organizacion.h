#ifndef ORGANIZACION_H
#define ORGANIZACION_H
#include <QString>
class Organizacion
{
private:
    QString tipo,cobertura;
    double capacidad;
public:
    Organizacion(QString t="",double cap=0.0,QString cob="");
    //getters:
    QString getTipo() const;
    double getCapacidad() const;
    QString getCobertura() const;
    // setters:
    void setTipo(QString t);
    void setCapacidad(double cap);
    void setCobertura(QString cob);
};
#endif // ORGANIZACION_H
