
/*#include <iostream>
#include <string>
#include <limits> // Para utilizar std::numeric_limits
#include "Hash.h"
#include "Dato.h"

// Función para obtener una opción válida del menú
int obtenerOpcionValida()
{
    int opcion;
    std::cout << "Seleccione una opción: ";
    std::cin >> opcion;

    // Verificar si la entrada es válida
    if (std::cin.fail())
    {
        std::cin.clear();                                                   // Limpiar el estado de error del flujo de entrada
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada no válida
        std::cerr << "Error: Entrada no válida. Por favor, ingrese un número válido." << std::endl;
        return 0; // Devolver 0 para indicar una entrada inválida
    }

    // Verificar que la opción esté en el rango de 1 a 5
    if (opcion >= 1 && opcion <= 5)
    {
        return opcion; // Devolver la opción válida
    }
    else
    {
        std::cerr << "Error: Opción fuera de rango. Por favor, seleccione una opción válida." << std::endl;
        return 0; // Devolver 0 para indicar una opción inválida
    }
}

void menu(HashTable &HashTable)
{
    int opcion;
    int roomNum;
    std::string name;

    while (true)
    {
        std::cout << "\nMenú:\n";
        std::cout << "1. Agregar Inquilino\n";
        std::cout << "2. Eliminar Inquilino\n";
        std::cout << "3. Mostrar habitaciones\n";
        std::cout << "4. Salir\n";
    }

     opcion = obtenerOpcionValida(); // Obtener una opción válida del usuario

      switch (opcion){
        case 1:
            std::cout << "Ingrese Número de Habitación: ";
            std::cin >> roomNum;
            std::cout << "Ingrese nombre del inquilino: ";
            std::cin.ignore();              // Limpiar el buffer de entrada antes de leer la línea
            std::getline(std::cin,name); // Leer el nombre completo incluyendo espacios
            HashTable.insertItem(roomNum, Dato::dato->name);
            break;
      }
}
/**/