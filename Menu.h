#ifndef MENU_H
#define MENU_H

#include <windows.h> // Incluye la biblioteca Windows API para utilizar SetConsoleOutputCP
#include "Hash.h"

void setupConsole(); // Declaración de la función setupConsole()
void menu(HashTable &hashTable);

#endif // MENU_H
