// nodo.h
#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <string>
#include "Persona.h"

// Definición de la clase Nodo
class Nodo
{
public:
    Persona persona; // Objeto Persona como dato del Nodo

    // Constructor de la clase Nodo
    Nodo(Persona persona) : persona(persona) {}
};

#endif // NODO_H