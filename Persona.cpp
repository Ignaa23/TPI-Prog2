#include "Persona.h"
#include <cstring>

Persona::Persona(){
    _dni=0;
    _nombre[0]={};
    _apellido[0]={};
    _telefono[0]={};
    _mail[0]= {};
}
Persona::Persona(int dni, std::string nombre, std::string apellido, std::string telefono, std::string mail ){
    setDni(dni);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setMail(mail);
}
///seters
void Persona::setDni(int numero){
    _dni=numero;
}

void Persona::setNombre(const std::string &nombre){
    if(nombre.size() < 40){
        strcpy(_nombre, nombre.c_str());
    }
}

void Persona::setApellido(const std::string &apellido){
    if(apellido.size() < 40){
        strcpy(_apellido, apellido.c_str());
    }
}

void Persona::setTelefono (const std::string &tel){
    if(tel.size() < 20){
        strcpy(_telefono, tel.c_str());
    }
}
void Persona::setMail (const std::string &mail){
    if(mail.size() < 30){
        strcpy(_mail, mail.c_str());
    }
}



///geters
int Persona::getDni()const{
    return _dni;
}

std::string Persona::getNombre() const{
    return _nombre;
}

std::string Persona::getApellido()const{
    return _apellido;
}

std::string Persona::getTelefono()const{
    return _telefono;
}
std::string Persona::getMail()const{
    return _mail;
}
