#include<iostream>
#include<iomanip>
#include "HoraTurno.h"

using namespace std;

HoraTurno::HoraTurno()
{
    _hora = 0;
    _minutos = 0;
}

HoraTurno::HoraTurno(int hora, int minutos)
{
    setHora(hora);
    setMinutos(minutos);
}

void HoraTurno::setHora(int hora)
{
    if(hora>=0 && hora<=23)
    {
        _hora = hora;
    }
    else _hora = -1;
}
void HoraTurno::setMinutos(int minutos)
{
    if(minutos>=0 && minutos<=59)
    {
        _minutos = minutos;
    }
    else _minutos = -1;
}

int HoraTurno::getHora(){
    return _hora;
}

int HoraTurno::getMinutos()
{
    return _minutos;
}

void HoraTurno::mostrar(){
    cout << std::setw(2) << std::setfill('0') << _hora << ":"<< std::setw(2) << std::setfill(' ') << _minutos;
}

bool HoraTurno::esIgualA(HoraTurno otra)
{
    if(_hora == otra.getHora() && _minutos == otra.getMinutos())
    {
        return true;
    }
}

bool HoraTurno::operator == (HoraTurno otra)
{
    if(_hora == otra.getHora() && _minutos == otra.getMinutos())
    {
        return true;
    }
}

bool HoraTurno::operator<(HoraTurno otra)
{
    if (_hora < otra.getHora()) return true;
    if (_hora == otra.getHora() && _minutos < otra.getMinutos()) return true;
    return false;
}

HoraTurno HoraTurno::obtenerHoraActual()
{
    time_t t = time(nullptr);
    tm* horaLocal = localtime(&t);

    int hora = horaLocal->tm_hour;
    int minuto = horaLocal->tm_min;

    return HoraTurno(hora,minuto);
}

bool HoraTurno::esHoraValida(HoraTurno horaTurno)
{
    HoraTurno horaActual = HoraTurno::obtenerHoraActual();

    if(horaTurno.getHora() < horaActual.getHora())
    {
        return false;
    }

    if(horaTurno.getHora() == horaActual.getHora() && horaTurno.getMinutos() <= horaActual.getMinutos())
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::string HoraTurno::toString(){
    char buffer[6];
    sprintf(buffer, "%02d:%02d", _hora, _minutos);
    return std::string(buffer);
}
