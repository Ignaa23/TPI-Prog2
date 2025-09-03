#include <iostream>
#include "ArchivoPaciente.h"

using namespace std;

ArchivoPaciente::ArchivoPaciente(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoPaciente::guardarPaciente(Paciente reg){
    bool escribio;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "ab");
    if(pFile==nullptr){
        return false;
    }

    escribio = fwrite(&reg, sizeof(Paciente), 1, pFile);

    fclose(pFile);
    return escribio;
}

int ArchivoPaciente::getCantidadRegistros(){
    int cantidad;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if(pFile==nullptr){
        return 0;
    }

    fseek(pFile,0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Paciente);

    fclose(pFile);
    return cantidad;
}

Paciente ArchivoPaciente::leer(int posicion){
    Paciente registro;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if(pFile == nullptr){
        return Paciente();
    }

    fseek(pFile, sizeof(Paciente)*posicion, SEEK_SET);
    fread(&registro, sizeof(Paciente), 1, pFile);

    fclose(pFile);
    return registro;
}

Paciente ArchivoPaciente::buscarPaciente(int idPac){
    Paciente obj;

    FILE *pFile;
    pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return obj;
    }

    int pos=0;
    while(fread(&obj, sizeof(Paciente), 1, pFile) == 1){
        if(obj.getIDPaciente() == idPac){
            return obj;
        }
        pos++;
    }
    fclose(pFile);
}

bool ArchivoPaciente::grabar(Paciente reg, int pos){
    bool modifico;

    FILE *pFile;
    pFile=fopen(_nombreArchivo.c_str(), "rb+");
    if(pFile==nullptr){
        cout<<"NO SE PUDO ABRIR EL ARCHIVO "<<endl;
        return false;
    }

    fseek(pFile, pos * sizeof(Paciente), SEEK_SET); //El puntero se ubica al principio del registro a modificar
    modifico = fwrite(&reg, sizeof(Paciente), 1, pFile);

    fclose(pFile);
    return modifico;
}

void ArchivoPaciente::Leer(int cantidadRegistros, Paciente *pacientes){
    FILE *pFile= fopen(_nombreArchivo.c_str(), "rb");
    if(pFile== NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&pacientes[i], sizeof(Paciente), 1, pFile);
    }
    fclose(pFile);
}
