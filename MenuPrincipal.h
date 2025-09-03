#pragma once

#include "MenuMedico.h"
#include "MenuPaciente.h"
#include "MenuTurnos.h"
#include "MenuReportes.h"

class MenuPrincipal
{
private:
    MenuMedico _medicoMenu;
    MenuPaciente _pacienteMenu;
    MenuTurnos _turnosMenu;
    MenuReportes _reportesMenu;

public:
    void mostrarMenu();
};
