#include <iostream>
#include "MenuMedico.h"

using namespace std;

void MenuMedico::mostrar(){
    int opcion;
    while(true){
        system("cls");
        cout << "-----MENU MEDICO-----"<< endl;
        cout << "1- REGISTRAR MEDICO"<< endl;
        cout << "2- MODIFICAR MEDICO"<< endl;
        cout << "3- LISTAR MEDICOS"<< endl;
        cout << "4- ELIMINAR MEDICO"<< endl;
        cout << "5- REACTIVAR MEDICO"<< endl;
        cout << "6- BUSCAR MEDICO"<< endl;
        cout << "0- VOLVER AL MENU PRINCIPAL"<< endl << endl;
        cout << "SELECCIONAR OPCION: ";

        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1:
                _managerMed.agregarMedico();
                break;
            case 2:
                _managerMed.modificarMedico();
                break;
            case 3:
                _managerMed.listarMedicos();
                break;
            case 4:
                _managerMed.eliminarMedico();
                break;
            case 5:
                _managerMed.reactivarMedico();
                break;
            case 6:
                _managerMed.buscarMedico();
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
