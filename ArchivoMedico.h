#pragma once
#include "Medico.h"

class ArchivoMedico{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoMedico(std::string nombreArchivo = "Medico.dat");
        bool guardarMedico(Medico reg);
        int getCantidadRegistros();
        Medico buscarMedico(int idMed);
        Medico leer(int pos);
        bool grabar(Medico reg, int pos);
};
