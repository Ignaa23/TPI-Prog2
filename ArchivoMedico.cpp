#include <iostream>
#include "ArchivoMedico.h"

using namespace std;

ArchivoMedico::ArchivoMedico(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoMedico::guardarMedico(Medico reg){
    bool escribio;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "ab");
    if (pFile==nullptr){
        return false;
    }

    escribio = fwrite(&reg, sizeof(Medico), 1, pFile);

    fclose(pFile);
    return escribio;
}

int ArchivoMedico::getCantidadRegistros(){
    int cantidad;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile==nullptr){
        return 0;
    }

    fseek(pFile,0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Medico);

    fclose(pFile);
    return cantidad;
}

Medico ArchivoMedico::leer(int posicion){
    Medico registro;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr){
        return Medico();
    }

    fseek(pFile, sizeof(Medico)*posicion, SEEK_SET);
    fread(&registro, sizeof(Medico), 1, pFile);

    fclose(pFile);
    return registro;
}

bool ArchivoMedico::grabar(Medico reg, int pos){
    bool modifico;

    FILE *pFile;
    pFile=fopen(_nombreArchivo.c_str(), "rb+");
    if(pFile==nullptr){
        cout<<"NO SE PUDO ABRIR EL ARCHIVO "<<endl;
        return false;
    }

    fseek(pFile, pos * sizeof(Medico), SEEK_SET); //El puntero se ubica al principio del registro a modificar
    modifico = fwrite(&reg, sizeof(Medico), 1, pFile);

    fclose(pFile);
    return modifico;
}


Medico ArchivoMedico::buscarMedico(int idMed){
    Medico obj;

    FILE *pFile;
    pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return obj;
    }

    int pos=0;
    while(fread(&obj, sizeof(Medico), 1, pFile) == 1){
        if(obj.getIDMedico() == idMed){
            return obj;
        }
        pos++;
    }

    fclose(pFile);
}

