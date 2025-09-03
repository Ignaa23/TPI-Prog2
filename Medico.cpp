#include<iostream>
#include<cstring>
#include "Medico.h"

using namespace std;

Medico::Medico()
:Persona(),_fechaInicioActiv(1,1,2000){
    _especialidad[0]={};
    _fechaInicioActiv=Fecha();
}

Medico::Medico(int IDMed,int dni, std::string apellido, std::string nombre, std::string telefono, std::string mail, Fecha fecha, std::string especialidad,HoraTurno hi,HoraTurno hf,std::string diaAtencion, bool estado)
:Persona(dni, nombre, apellido, telefono, mail){
    setIDMedico(IDMed);
    setEspecialidad(especialidad);
    setFechaInicioActiv(fecha);
    setHoraInicioAtencion(hi);
    setHoraFinAtencion(hf);
    setEstado(estado);
    setDiaAtencion(diaAtencion);
}

void Medico::setIDMedico(int IDMed){
    _IDMedico = IDMed;
}

void Medico::setEspecialidad(const std::string &especialidad){
    if(especialidad.size() < 30){
        strcpy(_especialidad,especialidad.c_str());
    }
}

void Medico::setFechaInicioActiv(const Fecha &fecha){
    _fechaInicioActiv=fecha;
}

void Medico::setEstado(bool estado){
    _estado = estado;
}

void Medico::setHoraInicioAtencion(HoraTurno h) {
    _horaInicioAtencion = h;
}

void Medico::setHoraFinAtencion(HoraTurno h) {
    _horaFinAtencion = h;
}

void Medico::setDiaAtencion(const std::string& diaAtencion){
    if(diaAtencion.size() < 15){
        strcpy(_diaAtencion,diaAtencion.c_str());
    }
}


Fecha Medico::getFechaInicioActiv(){
    return _fechaInicioActiv;
}

std::string Medico::getEspecialidad()const{
    return _especialidad;
}

int Medico::getIDMedico(){
    return _IDMedico;
}

bool Medico::getEstado(){
    return _estado;
}

HoraTurno Medico::getHoraInicioAtencion()const {
    return _horaInicioAtencion;
}

HoraTurno Medico::getHoraFinAtencion()const {
    return _horaFinAtencion;
}

std::string Medico::getDiaAtencion()const{
    return _diaAtencion;
}


void Medico::mostrar(){
    cout<<"ID: "<<_IDMedico<<endl;
    cout<<"DNI: "<< _dni<<endl;
    cout<<"Nombre: "<<_nombre<<endl;
    cout<<"Apellido: "<<_apellido<<endl;
    cout<<"Telefono: "<<_telefono<<endl;
    cout<<"Mail: "<<_mail<<endl;
    cout<<"Fecha de inicio de actividades: "; _fechaInicioActiv.mostrar();
    cout<<"Especialidad: "<<_especialidad<<endl;
    cout<<"Dia y horario de atencion: "<<_diaAtencion;
    cout<<" (";
    _horaInicioAtencion.mostrar();
    cout << " - ";
    _horaFinAtencion.mostrar();
    cout << ")" << endl;
    cout<<endl;
}

void Medico::mostrarCabecera() {
    std::cout << std::left
              << std::setw(3) << "ID"
              << std::setw(10) << "DNI"
              << std::setw(15) << "Apellido"
              << std::setw(15) << "Nombre"
              << std::setw(12) << "Telefono"
              << std::setw(15) << "Mail"
              << std::setw(14) << "Fecha Inicio."
              << std::setw(15) << "Especialidad"
              << std::setw(12) << "Dia Atenc."
              << std::setw(12) << "Horario"
              << std::endl;

    std::cout << std::string(120, '-') << std::endl;
}

void Medico::mostrarListado(){
    std::cout << std::left
    << std::setw(3) << _IDMedico
    << std::setw(10) << _dni
    << std::setw(15) << _apellido
    << std::setw(15) << _nombre
    << std::setw(12) << _telefono
    << std::setw(15) << _mail
    << std::setw(14) << _fechaInicioActiv.toString()
    << std::setw(15) << _especialidad
    << std::setw(12) << _diaAtencion
    << std::setw(4)  << _horaInicioAtencion.toString()<< "-"
    << std::setw(4)  << _horaFinAtencion.toString()
    << std::endl;
}

Medico Medico::cargar(){
    Medico med;
    int nuevoID , dni;
    int dia, mes, anio,h,m;
    HoraTurno horaInicio, horaFin;

    string nombre, apellido, telefono, mail, especialidad,horaTexto,diaTexto;

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
    cout<<"Fecha de inicio de actividades: "<<endl;
    cout<<"Dia: ";
    cin>>dia;
    cout<<"Mes: ";
    cin>>mes;
    cout<<"Anio: ";
    cin>>anio;
    cout<<"Especialidad: ";
    cin.ignore();
    getline(cin, especialidad);
    cout<<"Dia de atencion: " ;
    cin>>diaTexto;

    cout << "Hora de inicio de atencion (formato HH:MM): ";
    cin >> horaTexto;
    if (sscanf(horaTexto.c_str(), "%d:%d", &h, &m) == 2){
        horaInicio.setHora(h);
        horaInicio.setMinutos(m);
    }
    else{
        cout << "Formato inválido. Intente de nuevo." << endl;
    }
    cout << "Hora de finalizacion (formato HH:MM):  ";
    cin >> horaTexto;
    if (sscanf(horaTexto.c_str(), "%d:%d", &h, &m) == 2){
        if (h > horaInicio.getHora()){
            horaFin.setHora(h);
            horaFin.setMinutos(m);
        }
        else{
            cout << "La hora de fin debe ser posterior a la de inicio." << endl;
            return Medico();
        }
    }
    else{
        cout << "Formato inválido. Intente de nuevo." << endl;
    }

    med = Medico(nuevoID, dni, apellido,nombre,telefono,mail, Fecha(dia,mes,anio),especialidad, horaInicio,horaFin,diaTexto);

    return med;
}

std::string Medico::toCSV(){
    std::string str = std::to_string(_IDMedico) + "," + std::to_string(_dni) + "," + _apellido + "," + _nombre + "," + _telefono + "," + _mail + ","  + _fechaInicioActiv.toString() + "," + _especialidad + "," + _horaInicioAtencion.toString() + "," + _horaFinAtencion.toString() + "," + _diaAtencion + "," + std::to_string(_estado);
    return str;
}
