#pragma once
#include<cstdio>
#include "Fecha.h"
#include "HoraTurno.h"
#include "Persona.h"
#include "FuncionesAux.h"


class Medico : public Persona{
    private:
        int _IDMedico;
        char _especialidad[30];
        Fecha _fechaInicioActiv;
        bool _estado;
        HoraTurno _horaInicioAtencion;
        HoraTurno _horaFinAtencion;
        char _diaAtencion[15];

    public:
        Medico();
        Medico(int IDMed,int dni, std::string nombre, std::string apellido,
            std::string telefono, std::string mail, Fecha fecha, std::string especialidad,
            HoraTurno hi,HoraTurno hf,std::string diaAtencion, bool estado=true);
        void setIDMedico(int IDMed);
        void setEspecialidad(const std::string &especialidad);
        void setFechaInicioActiv(const Fecha &fecha);
        void setEstado(bool estado);
        void setHoraInicioAtencion(HoraTurno h);
        void setHoraFinAtencion(HoraTurno h);
        void setDiaAtencion(const std::string &diaAtencion);


        int getIDMedico();
        Fecha getFechaInicioActiv();
        std::string getEspecialidad()const;
        bool getEstado();
        HoraTurno getHoraInicioAtencion()const;
        HoraTurno getHoraFinAtencion()const;
        std::string getDiaAtencion()const;

        Medico cargar();
        void mostrar();
        void mostrarCabecera();
        void mostrarListado() ;

        std::string toCSV();
};

//#endif // MEDICO_H_INCLUDED
