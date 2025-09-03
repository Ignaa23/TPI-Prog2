#include<iostream>
#include "MenuTurnos.h"

using namespace std;

void MenuTurnos::mostrar(){
    int opcion;
    while(true){
        system("cls");
        cout << "-----MENU TURNOS-----"<< endl;
        cout << "1- NUEVO TURNO"<< endl;
        cout << "2- REPROGRAMAR TURNO"<< endl;
        cout << "3- LISTAR TURNOS"<< endl;
        cout << "4- CANCELAR TURNO"<< endl;
        cout << "5- CONFIRMACION DE ASISTENCIA"<< endl;
        cout << "0- VOLVER AL MENU PRINCIPAL"<< endl<<endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;

        system("cls");
        switch(opcion){
        case 1:
            _managTurnos.nuevoTurno();
            break;
        case 2:
            _managTurnos.reprogramarTurno();
            break;
        case 3:
            _managTurnos.listarTurnos();
            break;
        case 4:
            _managTurnos.cancelarTurno();
            break;
        case 5:
            _managTurnos.confirmacionAsistencia();
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
