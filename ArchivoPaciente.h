#pragma once
#include "Paciente.h"

class ArchivoPaciente{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoPaciente(std::string nombreArchivo = "Paciente.dat");
        bool guardarPaciente(Paciente reg);
        int getCantidadRegistros();
        Paciente leer(int pos);
        Paciente buscarPaciente(int idPac);
        bool grabar(Paciente reg, int pos);
        void Leer(int cantidadRegistros, Paciente *pacientes);
};
