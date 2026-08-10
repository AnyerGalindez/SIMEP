#ifndef DESASTRE_H
#define DESASTRE_H
#include <QString>
class Desastre
{
private:
    QString fecha,coordenadas;
    double intensidad;
    int damnificados;
public:
    Desastre(QString f="",QString c="", double i=0, int d=0);
    //getters
    QString getFecha() const;
    QString getCoordenadas() const;
    double getIntensidad() const;
    int getDamnificados() const;
    //setters:
    void setFecha(QString f);
    void setCoordenadas(QString c);
    void  setIntensidad(double i);
    void  setDamnificados(int d );
};

#endif // DESASTRE_H
