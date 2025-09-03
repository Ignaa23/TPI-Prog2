#include<iostream>
#include "MenuPrincipal.h"

using namespace std;

void MenuPrincipal::mostrarMenu(){
    int opcion;
    while(true){
        system("cls");
        cout << "-----MENU PRINCIPAL-----"<< endl;
        cout << "1- MENU PACIENTES"<< endl;
        cout << "2- MENU MEDICOS"<< endl;
        cout << "3- TURNOS"<< endl;
        cout << "4- REPORTES"<< endl;
        cout << "5- EXPORTAR ARCHIVOS"<< endl;
        cout << "0- SALIR"<< endl<<endl;
        cout << "SELECCIONAR OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion){
        case 1:
            _pacienteMenu.mostrar();
            break;
        case 2:
            _medicoMenu.mostrar();
            break;
        case 3:
            _turnosMenu.mostrar();
            break;
        case 4:
            _reportesMenu.mostrar();
            break;
        case 5:
            _reportesMenu.exportar();
            break;
        case 0:
            cout<<"FIN DEL PROGRAMA"<<endl;
            return;
            break;
        default:
            cout<<"OPCION INVALIDA"<<endl;
            system("pause");
            break;
        }
    }
}
