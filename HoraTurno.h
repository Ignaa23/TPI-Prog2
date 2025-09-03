#pragma once
#include<ctime>
#include<iomanip>

class HoraTurno
{
private:
    int _hora;
    int _minutos;

public:
    HoraTurno();
    HoraTurno(int hora, int minutos);

    void setHora(int hora);
    void setMinutos(int minutos);

    int getHora();
    int getMinutos();

    void mostrar();
    bool esIgualA(HoraTurno otra);
    bool operator == (HoraTurno otra);
    static HoraTurno obtenerHoraActual();
    bool esHoraValida(HoraTurno horaTurno);
    bool operator < (HoraTurno otra);

    std::string toString();

};
