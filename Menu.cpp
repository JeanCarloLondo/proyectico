
#include <iostream>
#include <string>
#include <limits> // Para utilizar std::numeric_limits
#include "menu.h"

void setupConsole()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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

void menu(HashTable &hashTable)
{
    int opcion;
    int roomNum;
    int id;
    std::string name;

    while (true)
    {
        std::cout << "\nMenú:\n";
        std::cout << "1. Agregar Inquilino\n";
        std::cout << "2. Eliminar Inquilino\n";
        std::cout << "3. Mostrar Habitaciones\n";
        std::cout << "4. Buscar Inquilino\n";
        std::cout << "5. Salir\n";

        opcion = obtenerOpcionValida(); // Obtener una opción válida del usuario

        if (opcion == 0)
        {
            continue; // Si la opción es inválida, pedir otra opción
        }

        switch (opcion)
        {
        case 1:
        {
            std::cout << "Ingrese Cédula del inquilino: ";
            std::cin >> id;

            if (hashTable.searchItem(id))
            {
                std::cerr << "Error: La cédula ingresada ya existe en la lista." << std::endl;
                break;
            }

            std::cout << "Ingrese nombre del inquilino: ";
            std::cin.ignore();            // Limpiar el buffer de entrada antes de leer la línea
            std::getline(std::cin, name); // Leer el nombre completo incluyendo espacios
            std::cout << "Ingrese NumHab del inquilino: ";
            std::cin >> roomNum;
            Dato dato(name, roomNum, id); // Crear una variable temporal Dato
            hashTable.insertItem(dato);   // Pasar la variable a la función
            break;
        }
        case 2:
            std::cout << "Ingrese Cédula del inquilino a eliminar: ";
            std::cin >> id;
            hashTable.removeItem(id);
            break;
        case 3:
            hashTable.printTable();
            break;

        case 4:
            cout << "Ingrese la cédula del inquilino que desea buscar: " << endl;
            cin >> id;
            hashTable.searchItem(id);

            break;

        case 5:
            std::cout << "Saliendo del programa..." << std::endl;
            return; // Salir de la función y terminar el programa
        default:
            std::cerr << "Error: Opción no reconocida." << std::endl;
        }
    }
}
