#include <iostream>

#include "MenuReportes.h"

using namespace std;

void MenuReportes::mostrar(){
    int opcion;
    while(true){
        system("cls");
        cout << "-----MENU REPORTES-----"<< endl<<endl;
        cout << "1- CANTIDAD DE TURNOS POR MEDICO EN UN MES"<< endl;
        cout << "2- LISTAR MEDICO INACTIVOS"<< endl;
        cout << "3- LISTAR PACIENTES CON TURNOS EN UN MES"<< endl;
        cout << "4- LISTAR MEDICOS CON TURNOS EN UN MES" << endl;
        cout << "5- MEDICO QUE MAS DINERO RECAUDO EN UN MES" << endl;
        cout << "6- CANTIDAD DE TURNOS POR OBRA SOCIAL" << endl;
        cout << "7- LISTADO DE TURNOS FUTUROS POR PACIENTE" << endl;
        cout << "0- VOLVER AL MENU PRINCIPAL"<< endl<<endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;

        system("cls");
        switch(opcion){
         case 1:
            _archTurno.cantidadDeTurnosPorMedico();
            break;
        case 2:
            _archMedico.listarMedicosInactivos();
            break;
        case 3:
            _archTurno.listarPacientesConTurnoDelMes();
            break;
        case 4:
            _archTurno.listarMedicosConTurnoDelMes();
            break;
        case 5:
           _archTurno.medicoQueMasRecaudoEnUnMes();
            break;
        case 6:
            _archTurno.cantidadDeTurnosPorObraSocial();
            break;
        case 7:
            _archTurno.historialDeTurnosPorPaciente();
            break;
        case 0:
            return;
            break;
        default:
            cout<<"OPCION INVALIDA"<<endl;
            break;
        }
        system("pause");
    }
}

void MenuReportes::exportar(){
    int opcion;
    while(true){
        system("cls");
        cout << "-----EXPORTAR LISTADOS-----"<< endl;
        cout << "1- EXPORTAR LISTADOS DE PACIENTES"<< endl;
        cout << "2- EXPORTAR LISTADOS DE MEDICOS"<< endl;
        cout << "3- EXPORTAR LISTADOS DE TURNOS"<< endl;
        cout << "0- VOLVER AL MENU PRINCIPAL"<< endl<<endl;
        cout << "SELECCIONE UNA OPCION: ";

        cin >> opcion;

        system("cls");
        switch(opcion){
        case 1:
            _archPac.exportarListado();
            cout<<endl<<endl;
            break;
        case 2:
            _archMedico.exportarListado();
            cout<<endl<<endl;
            break;
        case 3:
            _archTurno.exportarListado();
            cout<<endl<<endl;
            break;
        case 0:
            return;
            break;
        default:
            cout<<"OPCION INVALIDA"<<endl;
            break;
        }
        system("pause");
    }
}

