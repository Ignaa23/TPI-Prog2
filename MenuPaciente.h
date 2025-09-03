#pragma once

#include "PacienteManager.h"

class MenuPaciente
{
private:
    PacienteManager _managerPac;
    ArchivoPaciente _archivoPac;

public:
    void mostrar();
};
