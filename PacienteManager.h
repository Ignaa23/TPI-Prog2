#pragma once
#include "ArchivoPaciente.h"

class PacienteManager
{
private:
    ArchivoPaciente _archivoPac;

public:
    bool dniExiste(int dni);
    bool existePaciente(int idPaciente);
    void agregarPaciente();
    void eliminarPaciente();
    void modificarPaciente();
    void listarPacientes();
    void listarAlfabeticamente();
    void buscarPaciente();
    void reactivarPaciente() ;

    void exportarListado();
};
