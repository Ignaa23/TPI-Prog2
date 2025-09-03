#pragma once
#include<string>
#include<ctime>

class Fecha
{
private:
    int _dia;
    int _mes;
    int _anio;

public:
    Fecha ();
    Fecha (int dia, int mes, int anio);

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    int getDia();
    int getMes();
    int getAnio();

    void mostrar();
    bool esIgualA(Fecha otra);
    bool operator == (Fecha otra);
    bool operator >= (Fecha otra);
    bool operator > (Fecha otra);
    bool operator < (Fecha otra);
    static Fecha obtenerFechaActual();
    bool esFechaValida(Fecha fechaTurno);

    int getDiaSemana(int dia, int mes, int anio);
    int diaDeTextoAInt(std::string nombreDia);

    bool esAnioBisiesto(int anio);
    int diasEnMes(int mes, int anio);
    Fecha sumarUnDia(Fecha fecha);
    void incrementarDia();
    Fecha* obtenerFechasDisponibles(int diaAtencionMedico, int& cantidadFechas);
    void mostrarFechasDisponibles(int idMedico);

    std::string toString();


};

//#endif // FECHA_H_INCLUDED
