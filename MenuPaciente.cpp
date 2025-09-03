#include <iostream>
#include "MenuPaciente.h"

using namespace std;

void MenuPaciente::mostrar(){
    int opcion;
    while(true){
        system("cls");
        cout << "-----MENU PACIENTE-----"<< endl;
        cout << "1- REGISTRAR PACIENTE"<< endl;
        cout << "2- MODIFICAR PACIENTE"<< endl;
        cout << "3- LISTAR PACIENTES"<< endl;
        cout << "4- ELIMINAR PACIENTE"<< endl;
        cout << "5- BUSCAR PACIENTE"<< endl;
        cout << "6- LISTAR ALFABETICAMENTE"<< endl;
        cout << "7- REACTIVAR PACIENTE"<< endl;
        cout << "0- VOLVER AL MENU PRINCIPAL"<< endl << endl;
        cout<<"SELECCIONAR OPCION: ";

        cin >> opcion;
        system("cls");
        switch(opcion){
        case 1:
            _managerPac.agregarPaciente();
            break;
        case 2:
            _managerPac.modificarPaciente();
            break;
        case 3:
            _managerPac.listarPacientes();
            break;
        case 4:
            _managerPac.eliminarPaciente();
            break;
        case 5:
            _managerPac.buscarPaciente();
            break;
        case 6:
            _managerPac.listarAlfabeticamente();
            break;
        case 7:
            _managerPac.reactivarPaciente();
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
