#include<iostream>

#include "FuncionesAux.h"

int diaTextoAEntero(std::string nombreDia) {
    if (nombreDia == "Domingo" || nombreDia == "domingo") return 1;
    if (nombreDia == "Lunes" || nombreDia == "lunes") return 2;
    if (nombreDia == "Martes" || nombreDia == "martes") return 3;
    if (nombreDia == "Miercoles" || nombreDia == "miercoles") return 4;
    if (nombreDia == "Jueves" || nombreDia == "jueves") return 5;
    if (nombreDia == "Viernes" || nombreDia == "viernes") return 6;
    if (nombreDia == "Sabado" || nombreDia == "sabado") return 0;
    return -1;
}
