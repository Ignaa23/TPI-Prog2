#include<iostream>
#include "Fecha.h"

using namespace std;

Fecha::Fecha(){
    _dia = 1;
    _mes = 1;
    _anio = 1900;
}

Fecha::Fecha(int dia, int mes, int anio){
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

void Fecha::setDia(int dia){
    if(dia >= 1 && dia <= 31){
        _dia = dia;
    }
    else{
        _dia = -1;
    }
}

void Fecha::setMes(int mes){
    if (mes>=1 && mes<=12){
        _mes=mes;
    }
    else _mes = -1;
}

void Fecha::setAnio(int anio){
    if(anio>=1900){
        _anio=anio;
    }
    else _anio = -1;
}

int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
    return _anio;
}

void Fecha::mostrar(){
    cout<<_dia<<"/";
    cout<<_mes<<"/";
    cout<<_anio<<endl;
}

bool Fecha::esIgualA(Fecha otra){
    if(_dia == otra.getDia() && _mes == otra.getMes() && _anio == otra.getAnio()){
        return true;
    }
}

bool Fecha::operator == (Fecha otra){
    if(_dia == otra.getDia() && _mes == otra.getMes() && _anio == otra.getAnio()){
        return true;
    }
}

bool Fecha::operator >= (Fecha otra){
    if(_dia >= otra.getDia() && _mes >= otra.getMes() && _anio >= otra.getAnio()){
        return true;
    }
}

bool Fecha::operator >(Fecha otra){
    if (_anio != otra.getAnio()) return _anio > otra.getAnio();
    if (_mes != otra.getMes()) return _mes > otra.getMes();
    return _dia > otra.getDia();
}

bool Fecha::operator <(Fecha otra){
    if (_anio != otra.getAnio()) return _anio < otra.getAnio();
    if (_mes != otra.getMes()) return _mes < otra.getMes();
    return _dia < otra.getDia();
}

Fecha Fecha::obtenerFechaActual(){
    time_t t = time(nullptr);
    tm* fechaLocal = localtime(&t);

    int dia = fechaLocal->tm_mday;
    int mes = fechaLocal->tm_mon + 1;
    int anio = fechaLocal->tm_year + 1900;

    return Fecha(dia, mes, anio);
}

bool Fecha::esFechaValida(Fecha fechaTurno){

    Fecha hoy = Fecha::obtenerFechaActual();

    if(fechaTurno.getAnio() < hoy.getAnio()){
        return false;
    }
    if(fechaTurno.getAnio() == hoy.getAnio() && fechaTurno.getMes() < hoy.getMes()){
        return false;
    }
    if(fechaTurno.getAnio() == hoy.getAnio() && fechaTurno.getMes() == hoy.getMes() && fechaTurno.getDia() < hoy.getDia()){
        return false;
    }
    else{
        return true;
    }
}

int Fecha::getDiaSemana(int dia, int mes, int anio){
    if (mes < 3){
        mes += 12;
        anio -- ;
    }

    int k = anio % 100;
    int j = anio / 100;

    int h = (dia + 13*(mes + 1)/5 + k + k/4 + j/4 + 5*j) % 7;

    return  h;
}

bool Fecha::esAnioBisiesto(int anio){
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int Fecha::diasEnMes(int mes, int anio){
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (mes == 2 && esAnioBisiesto(anio)) return 29;
    return diasMes[mes - 1];
}

void Fecha::incrementarDia(){
    _dia++;
    if(_dia > diasEnMes(_mes, _anio)){
        _dia = 1;
        _mes++;
        if (_mes > 12) {
            _mes = 1;
            _anio++;
        }
    }
}

Fecha Fecha::sumarUnDia(Fecha fecha){
    Fecha nuevaFecha = fecha;
    nuevaFecha.incrementarDia();

    return nuevaFecha;
}

std::string Fecha::toString(){
    return std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
}
