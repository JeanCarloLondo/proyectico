#ifndef PERSONA_H
#define PERSONA_H
#include <string>

// Declaro la clase persona
class Persona
{
public:
    std::string nombre; // Nombre del cliente
    int tipoMasaje; // Tipo de masaje que quiera el cliente
    int numHabitacion; // num de habitacion del cliente
    bool atendido; // Me va a indicar si el cliente ya fue atendido o no

    // Constructor de la clase persona
    Persona(std::string nombre, int tipoMasaje, int numHabitacion, bool atendido);

// Método para comparar el número de habitación de la persona
    // con otro número de habitación y verificar si son iguales lo que me permitirá retirar 
    bool compararNum(int numHabitacion)
    {
        return numHabitacion == numHabitacion;
    }
    
// Método para obtener una representación de cadena de la persona
    std::string to_string();
};

#endif // PERSONA_H