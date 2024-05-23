#include "Persona.h"
#include <iostream>
#include <sstream>

// Implementación del  Constructor de la clase persona
Persona::Persona(std::string nombre, int tipoMasaje, int numHabitacion, bool atendido)
    : nombre(nombre), tipoMasaje(tipoMasaje), numHabitacion(numHabitacion), atendido(atendido) {}

// Implementación del método to_string() 
std::string Persona::to_string()
{
    std::stringstream ss;
    std::string masaje;

    //Convierto la variable int tipoMasaje en un string, para que al momento de mostrar la lista
    //Enseñe el tipo de masaje que eligió el usuario :)
    if (tipoMasaje == 1)
    {
        masaje = "Masaje de Chocolate";
    }
    if (tipoMasaje == 2)
    {
        masaje = "Masaje de Piedras Volcanicas";
    }
    if (tipoMasaje == 3)
    {
        masaje = " Masaje de Sales";
    }
    if (tipoMasaje == 4)
    {
        masaje = "  Masaje de Minerales";
    }

     //Construyo el string con los datos del cliente
    ss << "Nombre: " << nombre << ", Numero de habitacion: " << numHabitacion << ", Tipo de masaje: " << masaje;
    return ss.str();
}