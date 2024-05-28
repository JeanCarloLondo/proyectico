#include <iostream>
#include <string>
#include <memory>
#include "HashTable.h"
#include "menu.h"

int main()
{
    setupConsole(); // Configurar la consola

    HashTable hashTable; // Crear una tabla hash con un número de habitaciones

    menu(hashTable); // Ejecutar el menú

    return 0;
}