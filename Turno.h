#pragma once
#include<iomanip>

#include "Paciente.h"
#include "Medico.h"
#include "Fecha.h"
#include "HoraTurno.h"

class Turno
{
private:
    int _IDTurno;
    int _IDPaciente;
    int _IDMedico;
    Fecha _fechaAtencion;
    HoraTurno _horaAtencion;
    float _importeConsulta;
    bool _estado;
    char _obraSocial [30];
    bool _asistio;

public:
    Turno();
    Turno(int IDTurno,int IDPac, int IDMed, Fecha fecha, HoraTurno horaConsulta, float importe,std::string obraSocial, bool estado = true, bool asistio = false);

    void setIDPaciente(int IDPac);
    void setIDMedico(int IDMed);
    void setFechaAtencion(const Fecha &fecha);
    void setHoraAtencion (const HoraTurno &horaAtencion);
    void setImporteConsulta(float importe);
    void setEstado(bool estado);
    void setIDTurno(int idTurno);
    void setObraSocial(std::string obraSocial);
    void setAsistio(bool asistio);

    int getIDPaciente();
    int getIDMedico();
    Fecha getFechaAtencion();
    HoraTurno getHoraAtencion();
    float getImporteConsulta();
    bool getEstado();
    int getIDTurno();
    std::string getObraSocial();
    bool getAsistio();

    std::string toCSV();

    void mostrar();
    void mostrarListado();
    void mostrarCabecera();
};
