#include <iostream>

// Definición de códigos ANSI para colores
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m" //"\033[40m\033[34m"

//Función para mostrar el menú con sus respectivos colores :D
void mostrarMenu()
{
    std::cout << YELLOW << "\n\nSPA Charly Garcia" << RESET << std::endl;
    std::cout << BLUE << "1- Elegir Turno" << RESET << std::endl;
    std::cout << BLUE << "2- Retirar Turno" << RESET << std::endl;
    std::cout << BLUE << "3- Mostrar Lista de Turnos" << RESET << std::endl;
    std::cout << BLUE << "4- Atender Persona\n"
              << RESET << std::endl;
    std::cout << RED << "5- Salir\n"
              << RESET << std::endl;
}

//Función para obtener la opción que eligió el usuario
int obtenerOpcion()
{
    char opcion;
    std::cout << GREEN << "Ingrese la opción: " << RESET;
    std::cin >> opcion;
    std::cout << RESET;

    // validar un numero entre 1 y 5
    if (opcion >= 49 && opcion <= 53)
    {                       //[0]=49 y [5]=53 en ascii
        return opcion - 48; // para tener un numero desde 1, 48 es el 0 en Ascci
    }
    return 0; // Si no esta en el rango devuelve 0
}
