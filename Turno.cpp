#include<iostream>
#include<cstring>
#include "Turno.h"

using namespace std;

Turno::Turno(){
    _IDPaciente = 0;
    _IDMedico = 0;
    _fechaAtencion = Fecha();
    _horaAtencion = HoraTurno();
    _importeConsulta = 0;
    _estado = true;
    _IDTurno = 0;
    _obraSocial [0]= {};
    _asistio = false;
}

Turno::Turno(int IDTurno,int IDPac, int IDMed, Fecha fecha, HoraTurno horaAtencion, float importe,std::string obraSocial, bool estado, bool asistio){
    setIDTurno(IDTurno);
    setIDPaciente(IDPac);
    setIDMedico(IDMed);
    setFechaAtencion(fecha);
    setHoraAtencion(horaAtencion);
    setImporteConsulta(importe);
    setObraSocial(obraSocial);
    setEstado(estado);
    setAsistio(asistio);
}
///seters
void Turno::setIDPaciente(int IDPac){
    _IDPaciente = IDPac;
}

void Turno::setIDMedico(int IDMed){
    _IDMedico = IDMed;
}

void Turno::setFechaAtencion(const Fecha &fecha){
    _fechaAtencion = fecha;
}

void Turno::setHoraAtencion (const HoraTurno &horaAtencion){
    _horaAtencion = horaAtencion;
}

void Turno::setImporteConsulta(float importe){
    _importeConsulta = importe;
}

void Turno::setEstado(bool estado){
    _estado = estado;
}

void Turno::setIDTurno(int idturno){
    _IDTurno = idturno;
}

void Turno::setObraSocial(std::string obraSocia){
    if(obraSocia.size()<30){
        strcpy(_obraSocial, obraSocia.c_str());
    }
}

void Turno::setAsistio(bool asistio){
    _asistio = asistio;
}

///geters
int Turno::getIDPaciente(){
    return _IDPaciente;
}

int Turno::getIDMedico(){
    return _IDMedico;
}

Fecha Turno::getFechaAtencion(){
    return _fechaAtencion;
}

HoraTurno Turno::getHoraAtencion(){
    return _horaAtencion;
}

float Turno::getImporteConsulta(){
    return _importeConsulta;
}

bool Turno::getEstado(){
    return _estado;
}

int Turno::getIDTurno(){
    return _IDTurno;
}

bool Turno::getAsistio(){
    return _asistio;
}

void Turno::mostrar(){
    Fecha hoy;
    hoy = hoy.obtenerFechaActual();
    cout << "ID Turno: "<< _IDTurno<<endl;
    cout << "ID paciente: "<< _IDPaciente<<endl;
    cout << "ID medico: "<< _IDMedico << endl;
    cout << "Fecha del turno: ";
    _fechaAtencion.mostrar();
    cout << "Hora del turno: ";
    _horaAtencion.mostrar();
    cout << endl;
    cout << "Importe de consulta: $"<< _importeConsulta<< endl;
    cout << "Obra Social: " << _obraSocial << endl;
    /*
    if(_fechaAtencion < hoy){
        cout << "Asistio: " << _asistio << endl;
    }
    */
}

void Turno::mostrarCabecera(){
    std::cout << std::left
              << std::setw(10) << "IDTurno"
              << std::setw(12) << "IDPaciente"
              << std::setw(10) << "IDMedico"
              << std::setw(15) << "Fecha"
              << std::setw(10) << "Hora"
              << std::setw(12) << "Importe"
              << std::setw(15) << "Obra Social"
              << std::setw(8)  << "Estado"
              << std::setw(8)  << "Asistio"
              << std::endl;
    std::cout << std::string(100, '-') << std::endl;
}

void Turno::mostrarListado(){
    std::cout << std::left
              << std::setw(10) << _IDTurno
              << std::setw(12) << _IDPaciente
              << std::setw(10) << _IDMedico
              << std::setw(15) << _fechaAtencion.toString()
              << std::setw(10) << _horaAtencion.toString()
              << std::setw(12) << std::fixed << std::setprecision(2) << _importeConsulta
              << std::setw(15) << _obraSocial
              << std::setw(8)  << _estado
              << std::setw(8)  << _asistio
              << std::endl;
}

std::string Turno::toCSV(){
    std::string str = std::to_string(_IDTurno) + "," + std::to_string(_IDPaciente) + "," + std::to_string(_IDMedico)+ "," + _fechaAtencion.toString() + "," + _horaAtencion.toString() + "," + std::to_string((int) _importeConsulta)+ ","  + _obraSocial + "," + std::to_string(_estado);
    return str;
}
