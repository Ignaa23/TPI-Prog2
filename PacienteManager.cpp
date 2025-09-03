#include <iostream>
#include "PacienteManager.h"

using namespace std;

bool PacienteManager::dniExiste(int dni)
{
    int cantidad;
    Paciente pac;

    cantidad = _archivoPac.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);

        if(pac.getDni() == dni && pac.getEstado() == true)
        {
            return true;
        }
    }
    return false;
}



void PacienteManager::agregarPaciente()
{
    Paciente pac;
    int dni;
    int dia, mes, anio;
    string nombre, apellido, telefono, mail, obraSocial;
    int cantidadRegistros;
    int nuevoID = 1;

    cantidadRegistros = _archivoPac.getCantidadRegistros();

    for(int i = 0; i < cantidadRegistros; i++)
    {
        pac = _archivoPac.leer(i);

        if (pac.getIDPaciente() >= nuevoID)
        {
            nuevoID = pac.getIDPaciente() +1;
        }
    }

    cout<<"DNI: ";
    cin>>dni;

    if(dniExiste(dni) == true)
    {
        cout<<"Ya existe un paciente con ese DNI"<<endl;
        return;
    }

    cout<<"Apellido: ";
    cin.ignore();
    getline(cin, apellido);
    cout<<"Nombre: ";
    cin>>nombre;
    cout<<"Telefono: ";
    cin>>telefono;
    cout<<"Mail: ";
    cin>>mail;
    cout<<"Fecha de nacimiento (DD, MM, AAAA)" << endl;
    cout<<"Dia: ";
    cin>>dia;
    cout<<"Mes: ";
    cin>>mes;
    cout<<"Anio: ";
    cin>>anio;
    cout<<"Obra Social: ";
    cin.ignore();
    getline(cin, obraSocial);

    pac = Paciente(nuevoID, dni, apellido,nombre,telefono,mail, Fecha(dia,mes,anio),obraSocial);

    if(_archivoPac.guardarPaciente(pac))
    {
        cout<<endl<<endl;
        cout<<"Paciente agregado correctamente"<<endl;
    }
    else
    {
        cout<<"No se pudo agregar el paciente"<<endl;
    }


}

void PacienteManager::eliminarPaciente()
{
    int id;
    int cantidad;
    Paciente pac;

    cout<<"Ingrese el ID del paciente que desea eliminar: ";
    cin>>id;

    cantidad = _archivoPac.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);

        if(pac.getIDPaciente() == id && pac.getEstado() == true)
        {
            pac.mostrar();
            cout << endl<<"Esta seguro que desea eliminar este paciente? S / N " << endl;
            char op;
            cin >> op;
            if (op=='S' ||op=='s')
            {
                pac.setEstado(false);
                _archivoPac.grabar(pac, i);
                std::cout<<"Paciente eliminado correctamente"<<std::endl;
            }
            else cout << "No se elimino el paciente"<<endl;
            return;
        }
    }
    std::cout<<"Paciente no encontrado."<<std::endl;

}

void PacienteManager::reactivarPaciente()
{
    int id;
    Paciente pac;
    bool hayInactivos = false;
    int cantidad = _archivoPac.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);
        if(pac.getEstado() == false)
        {
            hayInactivos = true;
            break;
        }
    }

    if(hayInactivos == false)
    {
        cout<<"No hay pacientes inactivos para reactivar"<<endl<<endl;
        return;
    }

    cout<<"Ingrese el ID del pacientea reactivar: ";
    cin>>id;

    bool encontrado = false;

    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);

        if(pac.getIDPaciente() == id)
        {
            encontrado = true;
            if(pac.getEstado() == true)
            {
                cout<<"El paciente ya esta activo"<<endl;
            }
            else
            {
                pac.setEstado(true);
                if(_archivoPac.grabar(pac, i) == true)
                {
                    cout<<"Paciente reactivado exitosamente"<<endl;
                }
                else
                {
                    cout<<"Error al intentar guardar los cambios"<<endl;
                }
            }
            break;
        }
    }

    if(encontrado == false)
    {
        cout << "No se encontro ningun paciente con ese ID." << endl;
    }
}

void PacienteManager::modificarPaciente()
{
    int idPac,cantidad;
    Paciente pac;

    cout<<"Ingrese el ID del paciente que desea modificar: ";
    cin>>idPac;

    cantidad = _archivoPac.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);

        if(pac.getIDPaciente() == idPac && pac.getEstado() == true)
        {
            std::cout<<"Paciente encontrado"<<std::endl;
            pac.mostrar();

            std::cout<<"\nIngrese nuevos datos para el paciente:"<<std::endl;
            int dni,dia,mes,anio;
            string apellido,nombre,telefono,mail,obraSocial;


            cout<<"DNI: ";
            cin>>dni;
            cout<<"Apellido: ";
            cin.ignore();
            getline(cin, apellido);
            cout<<"Nombre: ";
            cin>>nombre;
            cout<<"Telefono: ";
            cin>>telefono;
            cout<<"Mail: ";
            cin>>mail;
            cout<<"Fecha de nacimiento (DD, MM, AAAA)"<<endl;
            cout<<"Dia: ";
            cin>>dia;
            cout<<"Mes: ";
            cin>>mes;
            cout<<"Anio: ";
            cin>>anio;
            cout<<"Obra Social: ";
            cin.ignore();
            getline(cin, obraSocial);

            pac.setDni(dni);
            pac.setApellido(apellido);
            pac.setNombre(nombre);
            pac.setTelefono(telefono);
            pac.setMail(mail);
            pac.setFechaNacimiento(Fecha(dia,mes,anio));
            pac.setObraSocial(obraSocial);


            _archivoPac.grabar(pac,i);

            std::cout<<"Paciente modificado correctamente"<<std::endl;
            return;
        }
    }
    std::cout<<"Paciente no encontrado"<<std::endl;
}

void PacienteManager::listarPacientes()
{
    int cantidad;
    Paciente pac;
    bool hayPacientes = false;

    cantidad = _archivoPac.getCantidadRegistros();

    cout<<"LISTADO DE PACIENTES"<<endl<<endl;
    pac.mostrarCabecera();
    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);

        if(pac.getEstado() == true)
        {
            pac.mostrarListado();
            std::cout<<std::endl;
            hayPacientes = true;
        }
    }

    if(hayPacientes == false)
    {
        std::cout<<"No hay registros de pacientes"<<std::endl;
    }
}

void PacienteManager::buscarPaciente()
{
    int cantidad;
    Paciente pac;
    int id;
    cantidad = _archivoPac.getCantidadRegistros();

    cout<< "Ingrese el ID del paciente:";
    cin>>id;

    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);

        if(pac.getIDPaciente() == id)
        {
            pac.mostrar();
            return;
        }
    }
    cout << "No existe paciente"<<endl;
    return;
}

void PacienteManager::listarAlfabeticamente()
{
    int cantidad = _archivoPac.getCantidadRegistros();
    Paciente *vPacientes = new Paciente[cantidad];
    if(vPacientes==nullptr)
    {
        cout<<"Error de memoria"<<endl;
        return;
    }

    _archivoPac.Leer(cantidad,vPacientes);


    for (int i = 0; i < cantidad ; i++)
    {
        for (int j = i + 1; j < cantidad; j++)
        {
            if (vPacientes[i].getApellido() > vPacientes[j].getApellido() || vPacientes[i].getApellido() == vPacientes[j].getApellido()&&vPacientes[i].getNombre()>vPacientes[j].getNombre() )
            {
                Paciente aux = vPacientes[i];
                vPacientes[i] = vPacientes[j];
                vPacientes[j] = aux;
            }

        }
    }
    Paciente pac;
    pac.mostrarCabecera();
    for (int i = 0; i < cantidad ; i++)
    {
        vPacientes[i].mostrarListado();
        cout << endl;
    }

    delete[]vPacientes;
}


void PacienteManager::exportarListado()
{
    int cantReg = _archivoPac.getCantidadRegistros();
    Paciente registro;


    for(int i = 0; i < cantReg; i++)
    {
        registro = _archivoPac.leer(i);
        cout << registro.toCSV() << endl;
    }
}


