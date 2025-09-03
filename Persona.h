#pragma once
#include <string>

class Persona
{
protected:
    int _dni;
    char _nombre[40];
    char _apellido[40];
    char _telefono[20];
    char _mail[30];

public:
    Persona();
    Persona(int dni, std::string nombre, std::string apellido, std::string telefono, std::string mail );

    void setDni(int numero);
    void setNombre(const std::string &nombre);
    void setApellido(const std::string &apellido);
    void setTelefono (const std::string &tel);
    void setMail (const std::string &mail);

    int getDni()const;
    std::string getNombre() const;
    std::string getApellido()const;
    std::string getTelefono()const;
    std::string getMail()const;
};

//#endif // PERSONA_H_INCLUDED
