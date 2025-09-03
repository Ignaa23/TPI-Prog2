#pragma once
#include<iomanip>
#include "ArchivoTurnos.h"
#include "PacienteManager.h"
#include "MedicoManager.h"
#include "Fecha.h"
#include "HoraTurno.h"
#include "FuncionesAux.h"

class TurnosManager{
    private:
        ArchivoTurnos _archivoTur;
        ArchivoPaciente _archivoPac;
        ArchivoMedico _archivoMed;
        HoraTurno _horaActual;
        Fecha _hoy;

    public:
        bool existePaciente(int idPaciente);
        bool existeMedico(int idMedico);
        void nuevoTurno();
        void cancelarTurno();
        void reprogramarTurno();
        void listarTurnos();
        void mostrarTodos();
        void listarTurnosPorPaciente(int id);
        void listarTurnosPorMedico(int id);
        bool esTurnoDisponible(int idMed,Fecha nuevaFecha, HoraTurno nuevaHora);
        HoraTurno* generarHorariosDisponibles(int idMedico, Fecha& fecha,int intervaloMinutos,int& cantidadDisponibles);
        void obtenerFechasDisponibles(int diaAtencionMedico,Fecha fechasDisponibles[], int& cantidadFechas);
        void mostrarHorariosDisponibles(HoraTurno* disponibles, int cantidad);
        void mostrarFechasDisponibles(Fecha* fechasDisponibles, int& cantidadFechas);
        void confirmacionAsistencia();
        bool ponerEstadoEnCero(Fecha fechaTurno);

        void historialDeTurnosPorPaciente();
        void cantidadDeTurnosPorMedico();
        void cantidadDeTurnosPorObraSocial();
        void listarPacientesConTurnoDelMes();
        void listarMedicosConTurnoDelMes();
        void medicoQueMasRecaudoEnUnMes();

        void exportarListado();
};
