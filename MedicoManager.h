#pragma once
#include<cstdio>
#include "ArchivoMedico.h"

class MedicoManager
{
private:
    ArchivoMedico _archivoMed;

public:
    bool dniExiste(int dni);
    bool existeMedico(int idMedico);
    void agregarMedico();
    void eliminarMedico();
    void modificarMedico();
    void listarMedicos();
    void listarMedicosInactivos();
    void buscarMedico();
    Medico buscarMedico(int idMed);
    void reactivarMedico();
    void exportarListado();
};
