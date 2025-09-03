#include <iostream>
#include "TurnosManager.h"

using namespace std;

bool TurnosManager::existePaciente(int idPaciente){
    int cantidad;
    Paciente pac;

    cantidad = _archivoPac.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        pac = _archivoPac.leer(i);

        if (pac.getIDPaciente() == idPaciente && pac.getEstado() == true)
        {
            return true;
        }
    }
    return false;
}

bool TurnosManager::existeMedico(int idMedico){
    Medico med;
    int cantidad;

    cantidad = _archivoMed.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        med = _archivoMed.leer(i);

        if(med.getIDMedico() == idMedico && med.getEstado() == true)
        {
            return true;
        }
    }
    return false;
}

void TurnosManager::nuevoTurno(){
    Turno turno;
    int IDPac, IDMed, cantDisponibles, opcionTurno, cantFechas, opcionFecha;
    //int dia, mes, anio;

    float importe;
    char confirmar;
    std::string obraSocial;
    HoraTurno seleccion ;

    Fecha fechasDisponibles[30]={};
    Fecha fechaConsulta;
    HoraTurno horaConsulta;

    int nuevoID = _archivoTur.getNuevoID();

    cout << "ID paciente: ";
    cin >> IDPac;

    if(existePaciente(IDPac) == false){
        cout << "Error: No existe paciente con ID " << IDPac << endl;
        return;
    }

    cout << "ID medico: ";
    cin >> IDMed;

    if(existeMedico(IDMed) == false){
        cout << "Error: No existe medico con ID " << IDMed << endl;
        return;
    }

    Medico med = _archivoMed.buscarMedico(IDMed);
    int numeroDia = diaTextoAEntero(med.getDiaAtencion()) ;

    obtenerFechasDisponibles(numeroDia,fechasDisponibles, cantFechas);
    mostrarFechasDisponibles(fechasDisponibles, cantFechas);

    cout<< "Seleccione una fecha: ";
    cin >> opcionFecha;
    if (opcionFecha >= 1 && opcionFecha <= cantFechas){
        fechaConsulta = fechasDisponibles[opcionFecha - 1];
    }
    /*
    cout<<"Ingrese una fecha: "<<endl;
    cout<<"Dia: ";
    cin>>dia;
    cout<<"Mes: ";
    cin>>mes;
    cout<<"Anio: ";
    cin>>anio;

    fechaConsulta = Fecha(dia,mes,anio);
    */

    HoraTurno *disponibles= generarHorariosDisponibles(IDMed,fechaConsulta,20,cantDisponibles);

    if (cantDisponibles == 0 || disponibles == nullptr){
        std::cout << "No hay horarios disponibles para ese medico en esa fecha.\n";
        return;
    }

    mostrarHorariosDisponibles(disponibles,cantDisponibles);

    cout<< "Seleccione un horario: ";
    cin >> opcionTurno;

    if (opcionTurno >= 1 && opcionTurno <= cantDisponibles){
        seleccion = disponibles[opcionTurno - 1];

    }

    cout << "Importe de consulta: $";
    cin >> importe;


    if(importe<0){
        cout << "Error: Importe invalido"<<endl;
        return;
    }

    cout << endl << endl;
    Paciente reg = _archivoPac.buscarPaciente(IDPac);
    obraSocial = reg.getObraSocial();
    turno = Turno(nuevoID, IDPac, IDMed, fechaConsulta,seleccion, importe,obraSocial);

    turno.mostrar();
    cout << endl ;
    cout<<"confirmar el turno? (S / N)";
    cin>>confirmar;
    cout<<endl<<endl;

    if(confirmar == 's' || confirmar == 'S'){
        if(_archivoTur.guardarTurno(turno)==true){
            cout<<"Turno guardado correctamente"<<endl;
            cout<<"Conserve su numero de turno, sera necesario en caso de cambio o cancelacion"<<endl<<endl;
        }
    }
}

void TurnosManager::cancelarTurno(){
    int idTurno, cantidad;
    Turno registro;
    cantidad = _archivoTur.getCantidadRegistros();

    cout<<"Ingrese el numero de turno que desea cancelar: ";
    cin>>idTurno;


    for(int i=0; i<cantidad; i++)
    {
        registro = _archivoTur.leer(i);
        if(registro.getIDTurno() == idTurno && registro.getEstado() == true)
        {
            registro.mostrar();
            cout << endl<<"¿Esta seguro que desea canccelar este turno? S / N " << endl;
            char op;
            cin >> op;
            if (op=='S' ||op=='s')
            {
                registro.setEstado(false);
                _archivoTur.guardarTurnoModificado(registro,i);
                cout << "Turno cancelado"<<endl<<endl;
                return;
            }
            else cout << "Turno NO cancelado"<<endl;
            return;
        }
    }
    cout << "ID Turno inexistente"<<endl;
    return;
}

void TurnosManager::confirmacionAsistencia(){
    int idTurno;
    Turno reg;
    bool encontrado = false;
    int cantidad = _archivoTur.getCantidadRegistros();

    cout<<"Ingrese el ID de turno que desea confirmar la asistencia: ";
    cin>>idTurno;
    cout<<endl;

    for(int i=0; i<cantidad; i++){
        reg = _archivoTur.leer(i);
        if(reg.getIDTurno() == idTurno && reg.getEstado() == true){
            reg.setAsistio(true);
            reg.setEstado(false);
            _archivoTur.guardarTurnoModificado(reg, i);
            encontrado = true;
            break;
        }
    }
    if(encontrado == true){
        cout<<"Asistencia confirmada exitosamente"<<endl;
    }
    else{
        cout << "No se encontró un turno activo con ese ID." << endl;
    }
}

void TurnosManager::reprogramarTurno(){

    int idTurno, cantidad, opcionFecha,opcionHora,cantFechas,cantDisp;
    char confirmar;
    Turno registro;
    Fecha nuevaFecha;
    Fecha fechasDisponibles[30];
    HoraTurno nuevaHora;
    bool encontrado = false;

    cout<<"Ingrese el numero de turno que desea reprogramar: ";
    cin>>idTurno;
    cantidad = _archivoTur.getCantidadRegistros();

    for(int i=0; i<cantidad; i++){
        registro = _archivoTur.leer(i);
        if(registro.getIDTurno() == idTurno && registro.getEstado() == true){
            Medico med = _archivoMed.buscarMedico(registro.getIDMedico());
            int numeroDia = diaTextoAEntero(med.getDiaAtencion()) ;
            encontrado = true;

            obtenerFechasDisponibles(numeroDia,fechasDisponibles, cantFechas);
            mostrarFechasDisponibles(fechasDisponibles, cantFechas);

            cout<< "Seleccione una fecha: ";
            cin >> opcionFecha;

            if (opcionFecha >= 1 && opcionFecha <= cantFechas)
            {
                nuevaFecha = fechasDisponibles[opcionFecha - 1];
            }

            HoraTurno *disponibles=generarHorariosDisponibles(registro.getIDMedico(),nuevaFecha,20,cantDisp);

            if (cantDisp == 0 || disponibles == nullptr)
            {
                std::cout << "No hay horarios disponibles para ese médico en esa fecha.\n";
                return;
            }

            mostrarHorariosDisponibles(disponibles,cantDisp);

            cout<< "Seleccione un horario: ";
            cin >> opcionHora;
            cout<< endl;
            if (opcionHora>= 1 && opcionHora<= cantDisp)
            {
                nuevaHora = disponibles[opcionHora- 1];

            }

            registro.setFechaAtencion(nuevaFecha);
            registro.setHoraAtencion(nuevaHora);


            registro.mostrar();

            cout << "confirmar el turno? (S / N)" ;
            cin >> confirmar;

            if(confirmar == 's' || confirmar == 'S')
            {
                _archivoTur.guardarTurnoModificado(registro,i);

                cout << "Turno reprogramado correctamente"<<endl<<endl;
            }
            else return;
        }
    }
    if (encontrado == false)cout<< "Turno no encontrado o con fecha expirada"<< endl<<endl;
}

void TurnosManager::listarTurnos(){
    system("cls");
    int opcion;
    cout << "--- Mostrar Turnos ---\n";
    cout << "1 - Ver todos los turnos\n";
    cout << "2 - Ver turnos por medico\n";
    cout << "3 - Ver turnos por paciente\n";
    cout << "0 - Volver\n";
    cout << "Opcion: ";
    cin >> opcion;
    system("cls");
    switch(opcion){
        case 1:{
            mostrarTodos();
            break;
        }
        case 2:{
            int idmed;
            cout << "Ingrese el ID del medico: ";
            cin >> idmed;
            cout << endl << endl;
            listarTurnosPorMedico(idmed);
            break;
        }
        case 3:{
            int idpac;
            cout << "Ingrese el ID del paciente: ";
            cin >> idpac;
            cout << endl << endl;
            listarTurnosPorPaciente(idpac);
            break;
        }
        case 0:
            return;
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
    }
}

void TurnosManager::mostrarTodos(){
    Turno turno;
    bool hayturnos = false;

    int cantidad = _archivoTur.getCantidadRegistros();

    std::cout<<"Lista de todos los turnos:"<<std::endl;
    std::cout<<std::endl;
    turno.mostrarCabecera();
    for(int i = 0; i < cantidad; i++){
        turno = _archivoTur.leer(i);
        if (ponerEstadoEnCero(turno.getFechaAtencion())){
            turno.setEstado(false);
            _archivoTur.guardarTurnoModificado(turno, i);
        }
        turno.mostrarListado();
        std::cout<<std::endl;
        hayturnos= true;
    }

    if(hayturnos == false){
        std::cout<<"Aun no hay turnos asignados "<<std::endl;
    }
}

void TurnosManager::listarTurnosPorPaciente(int idPaciente){
    Turno turno;
    bool hayturnos = false;

    int cantidad = _archivoTur.getCantidadRegistros();

    std::cout<<"Lista de turnos para el paciente con ID "<<idPaciente<<":"<<std::endl;
    std::cout<<std::endl;
    turno.mostrarCabecera();
    for(int i = 0; i < cantidad; i++){
        turno = _archivoTur.leer(i);

        if(turno.getIDPaciente() == idPaciente){
            if (ponerEstadoEnCero(turno.getFechaAtencion())){
                turno.setEstado(false);
                _archivoTur.guardarTurnoModificado(turno, i);
            }
            turno.mostrarListado();
            std::cout<<std::endl<<endl;;
            hayturnos= true;
        }
    }

    if(hayturnos == false){
        std::cout<<"Aun no hay turnos asignados para el paciente con ID "<<idPaciente<<std::endl;
        std::cout<<std::endl;
    }
}

void TurnosManager::listarTurnosPorMedico(int id){
    Turno turno;
    bool hayturnos = false;

    int cantidad = _archivoTur.getCantidadRegistros();

    std::cout<<"Lista de turnos para el medico con ID "<<id<<":"<<std::endl;
    std::cout<<std::endl;
    turno.mostrarCabecera();
    for(int i = 0; i < cantidad; i++){
        turno = _archivoTur.leer(i);

        if(turno.getIDMedico() == id){
            turno.mostrarListado();
            std::cout<<std::endl;
            hayturnos= true;
        }
    }

    if(hayturnos == false){
        std::cout<<"Aun no hay turnos asignados para el medico con ID "<<id<<std::endl;
        std::cout<<std::endl;
    }
}

bool TurnosManager::esTurnoDisponible(int idMed,Fecha nuevaFecha, HoraTurno nuevaHora){
    Turno turno;
    int cantidad = _archivoTur.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        turno= _archivoTur.leer(i);

        if(turno.getEstado() == true &&
                turno.getIDMedico() == idMed &&
                turno.getFechaAtencion()== nuevaFecha &&
                turno.getHoraAtencion() == nuevaHora)
        {
            return false;
        }

    }

    return true;
}

void TurnosManager::cantidadDeTurnosPorMedico(){
    int cantDeTurnos = 0;
    int idMed, mes, anio;
    Turno reg;
    Medico med;
    int totalTurnos = _archivoTur.getCantidadRegistros();
    int totalMedicos = _archivoMed.getCantidadRegistros();

    cout<<"Ingrese el ID del medico: ";
    cin>>idMed;

    if(idMed < 1 || idMed > totalMedicos){
        cout<<"\nID invalido, no existe ese medico."<<endl<<endl;
        return;
    }

    cout<<"Ingrese el mes: ";
    cin>>mes;

    if(mes < 1 || mes > 12){
        cout<<"\nMes invalido, debe estar entre 1 y 12."<<endl<<endl;
        return;
    }

    cout<<"Ingrese el anio: ";
    cin>>anio;

    if(anio < 2010 || anio > 2030){
        cout<<"\nAnio invalido, debe estar entre 2010 y 2030."<<endl<<endl;
        return;
    }

    for(int i = 0; i < totalTurnos; i++){
        reg = _archivoTur.leer(i);
        if (reg.getIDMedico() == idMed && reg.getFechaAtencion().getMes() == mes && reg.getFechaAtencion().getAnio() == anio){
            cantDeTurnos++;
        }
    }

    if(cantDeTurnos!=0){
        cout<< "\nEl medico con ID " << idMed << " tuvo " << cantDeTurnos << " turno/s en el mes " << mes << " del anio "<< anio <<endl<<endl;
        std::cout<<"Lista de todos los turnos que tiene el medico "<<idMed<<" en el mes "<<mes<< " del anio "<<anio<<":"<<std::endl;
        std::cout<<std::endl;
        reg.mostrarCabecera();

        for(int i = 0; i < totalTurnos; i++){
            reg = _archivoTur.leer(i);
            if (reg.getIDMedico() == idMed && reg.getFechaAtencion().getMes() == mes && reg.getFechaAtencion().getAnio() == anio){
                if (ponerEstadoEnCero(reg.getFechaAtencion())){
                    reg.setEstado(false);
                    _archivoTur.guardarTurnoModificado(reg, i);
                }
                reg.mostrarListado();
            }
        }
        cout<<endl<<endl;
    }
    else{
        cout << "\nEl medico "<< idMed << " no tuvo turnos en el mes " << mes << " del anio "<< anio << endl<<endl;
    }
}

HoraTurno* TurnosManager::generarHorariosDisponibles(int idMedico, Fecha& fecha,int intervaloMinutos,int& cantidadDisponibles){
    Medico obj=_archivoMed.buscarMedico(idMedico);
    HoraTurno inicio = obj.getHoraInicioAtencion();
    HoraTurno fin = obj.getHoraFinAtencion();
    HoraTurno horaActual = _horaActual.obtenerHoraActual();


    int totalMinutosInicio = inicio.getHora() * 60 + inicio.getMinutos();
    int totalMinutosFin = fin.getHora() * 60 + fin.getMinutos();
    int maxPosibles = (totalMinutosFin - totalMinutosInicio) / intervaloMinutos;

    HoraTurno* disponibles = new HoraTurno[maxPosibles];
    cantidadDisponibles = 0;

    int totalMinutosActual = horaActual.getHora() * 60 + horaActual.getMinutos();

    Fecha fechaActual = _hoy.obtenerFechaActual();

    bool esHoy = (fecha == fechaActual);

    for (int t = totalMinutosInicio; t < totalMinutosFin; t += intervaloMinutos)
    {
        HoraTurno posibleHorario(t / 60, t % 60);
        bool esHorarioPasado = esHoy && t <= totalMinutosActual;

        if (!esHorarioPasado && esTurnoDisponible(idMedico, fecha, posibleHorario))
        {
            disponibles[cantidadDisponibles] = posibleHorario;
            cantidadDisponibles++;
        }
    }


    return disponibles;

}

void TurnosManager::mostrarHorariosDisponibles(HoraTurno* disponibles, int cantidad){
    if(cantidad == 0){
        std::cout << "No hay horarios disponibles.\n";
        return;
    }

    std::cout << "Horarios disponibles:\n";
    for(int i = 0; i < cantidad; i++){
        std::cout << (i + 1) << ") "
                  << std::setw(2) << std::setfill('0') << to_string (disponibles[i].getHora())
                  << ":"
                  << std::setw(2) << std::setfill('0') << to_string (disponibles[i].getMinutos())
                  << "\n";
    }
}

void TurnosManager::obtenerFechasDisponibles(int diaAtencionMedico,Fecha fechasDisponibles[], int& cantFechas){
    Fecha hoy = _hoy.obtenerFechaActual();
    Fecha fechaIterada = hoy;

    cantFechas = 0;

    for(int i = 0; i < 30; i++){
        int diaSemana = _hoy.getDiaSemana(fechaIterada.getDia(),fechaIterada.getMes(),fechaIterada.getAnio());

        if (diaSemana == diaAtencionMedico){
            fechasDisponibles[cantFechas] = fechaIterada;
            cantFechas++;
        }

        fechaIterada = _hoy.sumarUnDia(fechaIterada);
    }
}

void TurnosManager::mostrarFechasDisponibles(Fecha* fechasPosibles, int& cantFechas){
    if (cantFechas == 0){
        std::cout << "No hay dias disponibles.\n";
        return;
    }

    cout << "Fechas disponibles "<<endl;
    for (int i = 0; i < cantFechas; ++i){
        cout << i+1 << ") " ;
        fechasPosibles[i].mostrar();
    }
}

void TurnosManager::exportarListado(){
    int cantReg = _archivoTur.getCantidadRegistros();
    Turno registro;


    for(int i = 0; i < cantReg; i++)
    {
        registro = _archivoTur.leer(i);
        cout << registro.toCSV() << endl;
    }
}

void TurnosManager::historialDeTurnosPorPaciente(){
    int idPaciente;
    Fecha hoy = Fecha::obtenerFechaActual();
    Turno reg;
    ArchivoTurnos archivo;
    int cantidad = archivo.getCantidadRegistros();
    Turno* turnos = new Turno[cantidad];
    if(turnos == nullptr)return;
    int contador = 0;

    cout << "Ingrese el ID del paciente: ";
    cin >> idPaciente;
    cout << endl;

    for(int i = 0; i < cantidad; i++){
        reg = archivo.leer(i);

        if(reg.getEstado() == true && reg.getIDPaciente() == idPaciente && reg.getFechaAtencion() > hoy){
            turnos[contador] = reg;
            contador++;
        }
    }

    if(contador == 0){
        cout << "El paciente no tiene turnos futuros registrados" << endl;
        return;
    }

    for(int i = 0; i < contador ; i++){
        for(int j = i+1; j < contador ; j++){
            if(turnos[i].getFechaAtencion() > turnos[j].getFechaAtencion()){
                Turno aux = turnos[i];
                turnos[i] = turnos[j];
                turnos[j] = aux;
            }
        }
    }

    reg.mostrarCabecera();
    for(int i = 0; i < contador; i++){
        turnos[i].mostrarListado();
        cout<<endl;
    }

    delete[]turnos;
}

void TurnosManager::cantidadDeTurnosPorObraSocial(){
    int cantidadTurnos = _archivoTur.getCantidadRegistros();

    string* obras = new string [cantidadTurnos];
    if(obras == nullptr)return;
    int* turnos = new int [cantidadTurnos];
    if(turnos == nullptr)return;
    int totalObras = 0;


    for(int i = 0; i < cantidadTurnos; i++){
        Turno tur = _archivoTur.leer(i);
        int idPaciente = tur.getIDPaciente();
        Paciente pac = _archivoPac.buscarPaciente(idPaciente);

        if(pac.getEstado() == true){
            string obra = pac.getObraSocial();
            bool encontrada = false;
            for(int j = 0; j < totalObras; j++){
                if(obras[j] == obra){
                    turnos[j]++;
                    encontrada = true;
                    break;
                }
            }

            if(encontrada == false ){
                obras[totalObras] = obra;
                turnos[totalObras] = 1;
                totalObras++;
            }
        }
    }

    cout << "Cantidad de turnos por obra social:\n\n";
    for(int i = 0; i < totalObras; i++){
        cout << obras[i] << ": " << turnos[i] << " turnos" << endl;
    }
    cout<<endl;

    delete []obras ;
    delete []turnos;
}

void TurnosManager::listarPacientesConTurnoDelMes(){
    int mes, anio;
    Paciente pac;

    do {
        cout << "Ingrese el mes (1-12): ";
        cin >> mes;

        if(mes < 1 || mes > 12){
            cout << "Mes invalido. Debe estar entre 1 y 12." << endl;
            return;
        }
    } while(mes < 1 || mes > 12);

    do {
        cout << "Ingrese el anio: ";
        cin >> anio;

        if(anio < 2021 || anio > 2030){
            cout << "Anio invalido" << endl;
            return;
        }
    } while(anio < 2021 || anio > 2030);
    cout<<endl<<endl;
    int cantidadPacientes = _archivoPac.getCantidadRegistros();
    int cantidadTurnos = _archivoTur.getCantidadRegistros();

    bool seMostroAlMenosUno = false;
    pac.mostrarCabecera();

    for(int i = 0; i < cantidadPacientes; i++){
        pac = _archivoPac.leer(i);

        if(pac.getEstado() == true){
            bool tieneTurno = false;

            for(int j = 0; j < cantidadTurnos; j++){
                Turno tur = _archivoTur.leer(j);
                Fecha fec = tur.getFechaAtencion();

                if(tur.getIDPaciente() == pac.getIDPaciente() && fec.getAnio() == anio && fec.getMes() == mes){
                    tieneTurno = true;
                    break;
                }
            }

            if(tieneTurno == true){
                pac.mostrarListado();
                seMostroAlMenosUno = true;
            }
        }
    }
    if(seMostroAlMenosUno == false){
        cout << "No existen pacientes con turnos en ese mes" << endl;
    }
    cout<<endl<<endl;
}


void TurnosManager::listarMedicosConTurnoDelMes(){
    int mes, anio;
    Medico med;

    do {
        cout << "Ingrese el mes (1-12): ";
        cin >> mes;

        if(mes < 1 || mes > 12){
            cout << "Mes invalido. Debe estar entre 1 y 12." << endl;
            return;
        }
    } while(mes < 1 || mes > 12);

    do {
        cout << "Ingrese el anio: ";
        cin >> anio;

        if(anio < 2021 || anio > 2030){
            cout << "Anio invalido" << endl;
            return;
        }
    } while(anio < 2021 || anio > 2030);
    cout<<endl<<endl;
    int cantidadMedicos = _archivoMed.getCantidadRegistros();
    int cantidadTurnos = _archivoTur.getCantidadRegistros();

    bool seMostroAlMenosUno = false;
    med.mostrarCabecera();

    for(int i = 0; i < cantidadMedicos; i++){
        med = _archivoMed.leer(i);

        if(med.getEstado() == true){
            bool tieneTurno = false;

            for(int j = 0; j < cantidadTurnos; j++){
                Turno tur = _archivoTur.leer(j);
                Fecha fec = tur.getFechaAtencion();

                if(tur.getIDMedico() == med.getIDMedico() && fec.getAnio() == anio && fec.getMes() == mes){
                    tieneTurno = true;
                    break;
                }
            }

            if(tieneTurno == true){
                med.mostrarListado();
                seMostroAlMenosUno = true;
            }
        }
    }

    if(seMostroAlMenosUno == false){
        cout << "No existen medicos con turnos en ese mes" << endl;
    }
    cout<<endl<<endl;
}

void TurnosManager::medicoQueMasRecaudoEnUnMes(){
    int mes,anio;
    Fecha fec, hoy;
    hoy = fec.obtenerFechaActual();

    do{
        cout<<"Ingrese el anio: ";
        cin>>anio;
        if(anio < 2021 || anio > 2030){
            cout<<"anio invalido. Debe estar entre 2021 y 2030"<<endl;
            return;
        }
    }while(anio < 2021 || anio > 2030);

    do{
        cout<<"Ingrese el mes (1-12): ";
        cin>>mes;
        if(anio == hoy.getAnio() && mes > hoy.getMes()){
            cout<<"Mes invalido. El mes debe ser menor al mes actual"<<endl;
            return;
        }
        else{
            if(mes < 1 || mes > 12){
            cout<<"Mes invalido. Debe estar entre 1 y 12"<<endl;
            return;
            }
        }
    }while(mes < 1 || mes > 12);
    cout<<endl<<endl;

    int cantidadReg = _archivoTur.getCantidadRegistros();
    int* ids = new int [cantidadReg];
    if (ids == nullptr) return;
    float* totales = new float [cantidadReg];
    if (totales == nullptr) return;


    int totalMedicos = 0;

    for(int i = 0; i < cantidadReg; i++){
        Turno tur = _archivoTur.leer(i);
        Fecha fec = tur.getFechaAtencion();

        if(fec.getMes() == mes && fec.getAnio() == anio){
            int idMedico = tur.getIDMedico();
            float importe = tur.getImporteConsulta();

            bool encontrado = false;
            for(int j = 0; j < totalMedicos; j++){
                if(ids[j] == idMedico){
                    totales[j] += importe;
                    encontrado = true;
                    break;
                }
            }

            if(encontrado==false){
                ids[totalMedicos] = idMedico;
                totales[totalMedicos] = importe;
                totalMedicos++;
            }
        }
    }

    if(totalMedicos == 0){
        cout << "No hubo turnos en ese mes." << endl;
        return;
    }
    cout<<endl<<endl;
    int posMax = 0;
    for(int i = 1; i < totalMedicos; i++){
        if(totales[i] > totales[posMax]){
            posMax = i;
        }
    }

    cout << "El medico que mas recaudo fue:\n";
    cout<<endl;
    Medico archiMed;
    archiMed.mostrarCabecera();
    cout<<endl;
    Medico m = _archivoMed.buscarMedico(ids[posMax]);
    m.mostrarListado();
    cout<<endl;
    cout << "Total recaudado: $" << totales[posMax] << endl<<endl;

    delete[]ids;
    delete[]totales;
}

bool TurnosManager::ponerEstadoEnCero(Fecha fechaTurno){
    Fecha hoy = Fecha::obtenerFechaActual();

    return(fechaTurno < hoy);
}


