#pragma once
#include<iomanip>

#include "Fecha.h"
#include "Persona.h"

class Paciente: public Persona
{
private:
    int _IDPaciente;
    char _obraSocial[30];
    Fecha _fechaNacimiento;
    bool _estado;

public:
    Paciente();
    Paciente(int IDPac,int dni, std::string apellido, std::string nombre, std::string telefono, std::string mail, Fecha fecha, std::string obraSoc, bool estado = true);

    void setIDPaciente (int IDPac);
    void setObraSocial(const std::string &obraSoc);
    void setFechaNacimiento(const Fecha &fecha);
    void setEstado(bool estado);

    int getIDPaciente();
    std::string getObraSocial()const;
    Fecha getFechaNacimiento();
    bool getEstado();

    Paciente cargar();
    void mostrar();
    void mostrarCabecera();
    void mostrarListado() ;

    std::string toCSV();

};

//#endif // PACIENTE_H_INCLUDED
