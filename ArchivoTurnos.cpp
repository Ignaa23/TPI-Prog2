#include "ArchivoTurnos.h"

ArchivoTurnos::ArchivoTurnos(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoTurnos::guardarTurno(Turno regTurno){
    bool escribio;

    FILE* pFile;
    pFile = fopen(_nombreArchivo.c_str(), "ab");
    if(pFile == nullptr){
        return false;
    }

    escribio = fwrite(&regTurno, sizeof(Turno),1,pFile);

    fclose(pFile);
    return escribio;
}

int ArchivoTurnos::getCantidadRegistros(){
    int cantidad;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if(pFile==nullptr){
        return 0;
    }

    fseek(pFile,0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Turno);

    fclose(pFile);
    return cantidad;
}

Turno ArchivoTurnos::leer(int posicion){
    Turno registro;

    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if(pFile == nullptr){
        return Turno();
    }

    fseek(pFile, sizeof(Turno) * posicion, SEEK_SET);
    fread(&registro, sizeof(Turno), 1, pFile);

    fclose(pFile);
    return registro;
}

bool ArchivoTurnos::leermuchos(Turno *vTurnos, int cant){
    FILE *pFile;
    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if(pFile == nullptr){
        return false;
    }

    fread(vTurnos, sizeof(Turno),cant, pFile);

    fclose(pFile);
    return true;
}

bool ArchivoTurnos::guardarTurnoModificado( Turno turno, int pos) {
    FILE* pFile;
    pFile = fopen("turnos.dat","rb+");
    if (pFile == nullptr){
        return false  ;
    }

    fseek(pFile, sizeof(Turno) * pos, SEEK_SET);
    bool escribio = fwrite(&turno, sizeof(Turno), 1, pFile);

    fclose(pFile);
    return escribio;
}

int ArchivoTurnos::getNuevoID(){
    return getCantidadRegistros() +1;
}
