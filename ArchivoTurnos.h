#pragma once
#include "Turno.h"

class ArchivoTurnos
{
private:
    std::string _nombreArchivo;

public:
    ArchivoTurnos(std::string nombreArchivo = "turnos.dat");
    bool guardarTurno(Turno regTurno);
    int getCantidadRegistros();
    Turno leer(int pos);
    bool leermuchos(Turno *vTurnos, int cant);
    bool guardarTurnoModificado(Turno reg, int pos);

    int getNuevoID();
};
