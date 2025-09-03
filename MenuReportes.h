#pragma once

#include "TurnosManager.h"
#include "MedicoManager.h"
#include "PacienteManager.h"

class MenuReportes{
private:
    MedicoManager _archMedico;
    TurnosManager _archTurno;
    PacienteManager _archPac;

public:
    void mostrar();
    void exportar();


};
