#include<iostream>
#include<cstring>
#include "Fecha.h"
#include "Paciente.h"

using namespace std;

Paciente::Paciente()
    :Persona(),_fechaNacimiento(1,1,2000){
    _obraSocial[0]= {0};
    _fechaNacimiento = Fecha();
}

Paciente::Paciente(int IDPac,int dni, std::string apellido, std::string nombre, std::string telefono, std::string mail, Fecha fecha, std::string obraSoc,bool estado)
    :Persona(dni, nombre, apellido, telefono, mail){
    setIDPaciente(IDPac);
    setObraSocial(obraSoc);
    setFechaNacimiento(fecha);
    setEstado(estado);
}

void Paciente::setIDPaciente(int IDPac){
    _IDPaciente = IDPac;
}

void Paciente::setObraSocial(const std::string &obraSoc){
    if(obraSoc.size() < 30){
        strcpy(_obraSocial,obraSoc.c_str());
    }
}

void Paciente::setFechaNacimiento(const Fecha &fecha){
    _fechaNacimiento = fecha;
}

void Paciente::setEstado(bool estado){
    _estado = estado;
}

Fecha Paciente::getFechaNacimiento(){
    return _fechaNacimiento;
}

std::string Paciente::getObraSocial()const{
    return _obraSocial;
}

int Paciente::getIDPaciente(){
    return _IDPaciente;
}

bool Paciente::getEstado(){
    return _estado;
}

void Paciente::mostrar(){
    cout<<"ID: "<<_IDPaciente<<endl;
    cout<<"DNI: "<< _dni<<endl;
    cout<<"Apellido: "<<_apellido<<endl;
    cout<<"Nombre: "<<_nombre<<endl;
    cout<<"Telefono: "<<_telefono<<endl;
    cout<<"Mail: "<<_mail<<endl;
    cout<<"Fecha de nacimiento: "; _fechaNacimiento.mostrar();
    cout<<"Obra Social: "<<_obraSocial;
    cout<<endl<<endl;
}

void Paciente::mostrarCabecera() {
    std::cout << std::left
              << std::setw(10) << "IDPac"
              << std::setw(15) << "DNI"
              << std::setw(15) << "Apellido"
              << std::setw(15) << "Nombre"
              << std::setw(12) << "Telefono"
              << std::setw(15) << "Mail"
              << std::setw(18) << "Fecha Nac."
              << std::setw(12)  << "Obra social"
              << std::endl;

    std::cout << std::string(115, '-') << std::endl;
}

void Paciente::mostrarListado()
{
    std::cout << std::left
    << std::setw(10) << _IDPaciente
    << std::setw(15) << _dni
    << std::setw(15) << _apellido
    << std::setw(15) << _nombre
    << std::setw(12) << _telefono
    << std::setw(17) << _mail
    << std::setw(18) << _fechaNacimiento.toString()
    << std::setw(12)  << _obraSocial
    << std::endl;
}

Paciente Paciente::cargar(){
    Paciente pac;
    int nuevoID = 1, dni;
    int dia, mes, anio;
    string nombre, apellido, telefono, mail, obraSocial;

    cout<<"DNI: ";
    cin>>dni;
    cout<<"Apellido: ";
    cin.ignore();
    getline(cin, apellido);
    cout<<"Nombre: ";
    cin>>nombre;
    cout<<"Telefono: ";
    cin>>telefono;
    cout<<"Mail: ";
    cin>>mail;
    cout<<"Fecha de nacimiento (DD, MM, AAAA)"<<endl;
    cout<<"Dia: ";
    cin>>dia;
    cout<<"Mes: ";
    cin>>mes;
    cout<<"Anio: ";
    cin>>anio;
    cout<<"Obra Social: ";
    cin.ignore();
    getline(cin, obraSocial);

    pac = Paciente(nuevoID, dni, apellido,nombre,telefono,mail, Fecha(dia,mes,anio),obraSocial);

    return pac;
}

std::string Paciente::toCSV(){std::string str = std::to_string(_IDPaciente) + "," + std::to_string(_dni) + "," + _apellido + "," + _nombre + "," + _telefono + "," + _mail + ","  + _fechaNacimiento.toString() + "," + _obraSocial + "," + std::to_string(_estado);
    return str;
 }



