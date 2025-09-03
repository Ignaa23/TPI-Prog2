#include <iostream>
#include "MedicoManager.h"

using namespace std;

bool MedicoManager::dniExiste(int dni)
{
    int cantidad;
    Medico med;

    cantidad = _archivoMed.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);

        if(med.getDni() == dni && med.getEstado() == true)
        {
            return true;
        }
    }
    return false; //El DNI todavia no existe
}

void MedicoManager::agregarMedico()
{
    Medico med;
    int dni;
    int dia, mes, anio;
    int h, m;
    string nombre, apellido, telefono, mail, especialidad,horaTexto, diaTexto;
    int cantidadRegistros;
    int nuevoID = 1;
    HoraTurno horaInicio, horaFin;

    cantidadRegistros = _archivoMed.getCantidadRegistros();

    for(int i = 0; i < cantidadRegistros; i++)
    {
        med = _archivoMed.leer(i);

        if (med.getIDMedico() >= nuevoID)
        {
            nuevoID = med.getIDMedico()+1;
        }
    }

    cout << "DNI: ";
    cin >> dni;

    if(dniExiste(dni) == true)
    {
        cout<<"Ya existe un medico con ese DNI"<<endl;
        return;
    }

    cout << "Apellido: ";
    cin.ignore();
    getline(cin, apellido);

    cout << "Nombre: ";
    cin >> nombre;

    cout << "Telefono: ";
    cin >> telefono;

    cout << "Mail: ";
    cin >> mail;

    cout << "Fecha de inicio de actividad (DD, MM, AAAA)" << endl;
    cout << "Dia: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;

    cout << "Especialidad: ";
    cin.ignore();
    getline(cin, especialidad);

    cout<<"Dia de atencion: " ;
    cin>>diaTexto;

    cout << "Hora de inicio de atencion (formato HH:MM): ";
    cin >> horaTexto;
    if (sscanf(horaTexto.c_str(), "%d:%d", &h, &m) == 2)
    {
        horaInicio.setHora(h);
        horaInicio.setMinutos(m);
    }
    else
    {
        cout << "Formato invalido. Intente de nuevo." << endl;
    }
    cout << "Hora de finalizacion (formato HH:MM):  ";
    cin >> horaTexto;
    if (sscanf(horaTexto.c_str(), "%d:%d", &h, &m) == 2)
    {
        if (h > horaInicio.getHora())
        {
            horaFin.setHora(h);
            horaFin.setMinutos(m);
        }
        else
        {
            cout << "La hora de fin debe ser posterior a la de inicio." << endl;
            return;
        }
    }
    else
    {
        cout << "Formato invalido. Intente de nuevo." << endl;
    }

    med = Medico(nuevoID, dni, apellido,nombre,telefono,mail, Fecha(dia,mes,anio),especialidad,horaInicio,horaFin,diaTexto);


    if(_archivoMed.guardarMedico(med))
    {
        cout<<endl<<endl<<"Medico agregado correctamente "<<endl;
    }
    else
    {
        cout<<"No se pudo agregar el Medico"<<endl;
    }
}

void MedicoManager::eliminarMedico()
{
    int id;
    int cantidad;
    Medico med;

    cout<<"Ingrese el ID del medico que desea eliminar: ";
    cin>>id;
    cout<< endl;
    cantidad = _archivoMed.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);

        if(med.getIDMedico() == id && med.getEstado() == true)
        {
            med.mostrar();
            cout << endl<<"Esta seguro que desea eliminar este medico? S / N " << endl;
            char op;
            cin >> op;
            if (op=='S' ||op=='s')
            {
                med.setEstado(false);
                _archivoMed.grabar(med, i);
                std::cout<<"Medico eliminado correctamente"<<std::endl;
                return;
            }
            else cout << "No se elimino el medico"<<endl;
            return;
        }
    }
    std::cout<<"Medico no encontrado."<<std::endl;
}

void MedicoManager::modificarMedico()
{
    int id;
    int cantidad;
    Medico med;

    cout<<"Ingrese el ID del medico que desea modificar: ";
    cin>>id;

    cantidad = _archivoMed.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);

        if(med.getIDMedico() == id && med.getEstado() == true)
        {
            std::cout<<"Medico encontrado"<<std::endl;
            med.mostrar();

            std::cout<<"\nIngrese nuevos datos para el medico:"<<std::endl;

            string nombre, apellido, especialidad,diaAtencion,horaTexto;
            HoraTurno  horaInicio, horaFin;
            int h,m;

            std::cout << "Nombre: ";
            std::cin >> nombre;
            std::cout << "Apellido: ";
            std::cin >> apellido;
            std::cout << "Especialidad: ";
            std::cin >> especialidad;
            std::cout << "Dia de atencion: ";
            std::cin >> diaAtencion;
            cout << "Hora de inicio de atencion (formato HH:MM): ";
            cin >> horaTexto;
            if (sscanf(horaTexto.c_str(), "%d:%d", &h, &m) == 2)
            {
                horaInicio.setHora(h);
                horaInicio.setMinutos(m);
            }
            else
            {
                cout << "Formato invalido. Intente de nuevo." << endl;
            }
            cout << "Hora de finalizacion (formato HH:MM):  ";
            cin >> horaTexto;
            if (sscanf(horaTexto.c_str(), "%d:%d", &h, &m) == 2)
            {
                if (h > horaInicio.getHora())
                {
                    horaFin.setHora(h);
                    horaFin.setMinutos(m);
                }
                else
                {
                    cout << "La hora de fin debe ser posterior a la de inicio." << endl;
                    return ;
                }
            }
            else
            {
                cout << "Formato invalido. Intente de nuevo." << endl;
            }

            med.setNombre(nombre);
            med.setApellido(apellido);
            med.setEspecialidad(especialidad);
            med.setDiaAtencion(diaAtencion);
            med.setHoraInicioAtencion(horaInicio);
            med.setHoraFinAtencion(horaFin);

            if( _archivoMed.grabar(med, i))
            {

                std::cout<<"Medico modificado correctamente"<<std::endl;
                return;
            }
            else cout<<"no se pudo modificar"<<endl;
        }

    }
    std::cout<<"Medico no encontrado"<<std::endl;
}

void MedicoManager::listarMedicos()
{

    int cantidad;
    Medico med;
    bool hayMedicos = false;

    cout<<"LISTADO DE MEDICOS"<<endl<<endl;
    cantidad = _archivoMed.getCantidadRegistros();
    med.mostrarCabecera();
    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);

        if(med.getEstado() == true)
        {
            med.mostrarListado();
            std::cout<<std::endl;
            hayMedicos = true;
        }
    }

    if(hayMedicos == false)
    {
        std::cout<<"No hay registros de medicos "<<std::endl;
    }

}

void MedicoManager::listarMedicosInactivos(){
    int cantidad;
    Medico med;
    bool hayMedicosInactivos = false;


    std::cout<<"Lista de medicos inactivos:"<<std::endl;
    std::cout<<std::endl;
    med.mostrarCabecera();
    cantidad = _archivoMed.getCantidadRegistros();
    for(int i = 0; i < cantidad; i++){
        med = _archivoMed.leer(i);

        if(med.getEstado() == false){
            med.mostrarListado();
            std::cout<<std::endl;
            hayMedicosInactivos = true;
        }
    }

    if(hayMedicosInactivos == false){
        std::cout<<"\nNo hay registros de medicos inactivos"<<std::endl;
        std::cout<<std::endl;
    }
}

void MedicoManager::buscarMedico()
{
    int cantidad;
    Medico med;
    int id;
    cantidad = _archivoMed.getCantidadRegistros();

    cout<< "Ingrese el ID del medico:";
    cin>>id;
    cout<<endl;
    for(int i = 0; i < cantidad; i++)
    {
        med= _archivoMed.leer(i);

        if(med.getIDMedico() == id)
        {
            med.mostrar();
            return;
        }
    }
    cout << "No existe medico"<<endl;
    return;
}


void MedicoManager::reactivarMedico()
{
    int id;
    Medico med;
    bool hayInactivos = false;
    int cantidad = _archivoMed.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);
        if(med.getEstado() == false)
        {
            hayInactivos = true;
            break;
        }
    }

    if(hayInactivos == false)
    {
        cout<<"No hay medicos inactivos para reactivar"<<endl;
        return;
    }

    cout<<"Ingrese el ID del medico a reactivar: ";
    cin>>id;

    bool encontrado = false;

    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);

        if(med.getIDMedico() == id)
        {
            encontrado = true;
            if(med.getEstado() == true)
            {
                cout<<"El medico ya esta activo"<<endl;
            }
            else
            {
                med.setEstado(true);
                if(_archivoMed.grabar(med, i) == true)
                {
                    cout<<"Medico reactivado exitosamente"<<endl;
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
        cout << "No se encontro ningun medico con ese ID." << endl;
    }
}

Medico MedicoManager::buscarMedico(int idMed)
{
    Medico med;
    int cantidad = _archivoMed.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);
        if (med.getIDMedico()== idMed)
        {
            return med;
        }
    }
}

void MedicoManager::exportarListado()
{
    int cantReg = _archivoMed.getCantidadRegistros();
    Medico registro;


    for(int i = 0; i < cantReg; i++)
    {
        registro = _archivoMed.leer(i);
        cout << registro.toCSV() << endl;
    }
}
