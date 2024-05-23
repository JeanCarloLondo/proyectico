#include <iostream>
#include <string>
#include <memory>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * Configura la consola en sistemas Windows para soportar caracteres UTF-8.
 * Esto es necesario para mostrar correctamente caracteres especiales como acentos o caracteres Unicode.
 */
void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

/**
 * Clase Persona: Modela una persona con atributos para nombre, edad y peso.
 * Los operadores '<' y '==' están sobrecargados para permitir comparaciones directas entre dos personas.
 */
class Persona {
public:
    std::string nombre;
    int edad;
    double peso;

    Persona(std::string nombre, int edad, double peso) : nombre(nombre), edad(edad), peso(peso) {}

    // Compara dos personas por edad y luego por nombre si las edades son iguales.
    bool operator<(const Persona& other) const {
        if (edad == other.edad) {
            return nombre < other.nombre;
        }
        return edad < other.edad;
    }

    // Comprueba si dos personas son iguales en términos de edad y nombre.
    bool operator==(const Persona& other) const {
        return (edad == other.edad) && (nombre == other.nombre);
    }
};

/**
 * Clase Nodo: Un nodo en el árbol binario que contiene un puntero a una persona y a los nodos hijos.
 */
class Nodo {
public:
    std::shared_ptr<Persona> dato; // Datos de la persona en el nodo.
    std::shared_ptr<Nodo> izq;     // Puntero al nodo hijo izquierdo.
    std::shared_ptr<Nodo> der;     // Puntero al nodo hijo derecho.

    Nodo(std::shared_ptr<Persona> dato) : dato(dato), izq(nullptr), der(nullptr) {}
};

/**
 * Clase Arbol: Representa un árbol binario de búsqueda que organiza las personas principalmente por edad y nombre.
 */
class Arbol {
public:
    std::shared_ptr<Nodo> raiz; // Raíz del árbol.

    Arbol() : raiz(nullptr) {}

    // Inserta una nueva persona en el árbol manteniendo el orden del árbol binario de búsqueda.
    void insertar(std::string nombre, int edad, double peso) {
        std::shared_ptr<Persona> item = std::make_shared<Persona>(nombre, edad, peso);
        raiz = insertarRecursivo(raiz, item);
    }

    // Intenta eliminar una persona del árbol por nombre y edad. Devuelve true si la operación fue exitosa.
    bool eliminar(std::string nombre, int edad) {
        Persona target(nombre, edad, 0); // El peso no es relevante para la eliminación.
        bool encontrado;
        std::tie(raiz, encontrado) = eliminarRecursivo(raiz, target);
        return encontrado;
    }

    // Imprime visualmente el árbol. Si el árbol está vacío, se muestra un mensaje indicativo.
    void imprimirArbol() {
        if (!raiz) {
            std::cout << "El árbol está vacío." << std::endl;
        } else {
            imprimirArbolRecursivo(raiz, "", true);
        }
    }

private:
    // Función recursiva para insertar nodos en el árbol.
    std::shared_ptr<Nodo> insertarRecursivo(std::shared_ptr<Nodo> nodo, std::shared_ptr<Persona> dato) {
        if (!nodo) {
            return std::make_shared<Nodo>(dato);
        } else if (*dato < *nodo->dato) {
            nodo->izq = insertarRecursivo(nodo->izq, dato);
        } else {
            nodo->der = insertarRecursivo(nodo->der, dato);
        }
        return nodo;
    }

    // Función recursiva para eliminar nodos del árbol.
    std::pair<std::shared_ptr<Nodo>, bool> eliminarRecursivo(std::shared_ptr<Nodo> nodo, const Persona& target) {
        if (!nodo) {
            return {nullptr, false};
        }
        if (target < *nodo->dato) {
            auto result = eliminarRecursivo(nodo->izq, target);
            nodo->izq = result.first;
            return {nodo, result.second};
        } else if (*nodo->dato < target) {
            auto result = eliminarRecursivo(nodo->der, target);
            nodo->der = result.first;
            return {nodo, result.second};
        } else {
            if (!nodo->izq) {
                return {nodo->der, true};
            } else if (!nodo->der) {
                return {nodo->izq, true};
            }
            auto minNode = minValorNodo(nodo->der);
            nodo->dato = minNode->dato;
            auto result = eliminarRecursivo(nodo->der, *minNode->dato);
            nodo->der = result.first;
            return {nodo, true};
        }
    }

    // Encuentra el nodo con el valor mínimo en el subárbol derecho, utilizado durante la eliminación.
    std::shared_ptr<Nodo> minValorNodo(std::shared_ptr<Nodo> nodo) {
        while (nodo && nodo->izq) {
            nodo = nodo->izq;
        }
        return nodo;
    }

    // Imprime el árbol en orden. Utiliza 'prefix' para manejar la indentación y 'isLeft' para ajustar la orientación de las líneas de conexión.
    void imprimirArbolRecursivo(std::shared_ptr<Nodo> nodo, const std::string &prefix, bool isLeft) {
        if (nodo->der) {
            imprimirArbolRecursivo(nodo->der, prefix + (isLeft ? "│   " : "    "), false);
        }

        std::cout << prefix << (isLeft ? "└── " : "┌── ") << nodo->dato->nombre << " (" << nodo->dato->edad << " años, " << nodo->dato->peso << " kg)" << std::endl;

        if (nodo->izq) {
            imprimirArbolRecursivo(nodo->izq, prefix + (isLeft ? "    " : "│   "), true);
        }
    }
};

/**
 * Menú interactivo para operaciones sobre el árbol binario de búsqueda.
 * Permite al usuario agregar, eliminar y visualizar las personas en el árbol.
 */
void menu(Arbol& arbol) {
    while (true) {
        std::cout << "\nMenú:\n";
        std::cout << "1. Agregar Persona\n";
        std::cout << "2. Eliminar Persona\n";
        std::cout << "3. Mostrar Árbol\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opción: ";
        int opcion;
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                std::string nombre;
                int edad;
                double peso;
                std::cout << "Ingrese nombre: ";
                std::getline(std::cin, nombre);
                std::cout << "Ingrese edad: ";
                std::cin >> edad;
                std::cout << "Ingrese peso: ";
                std::cin >> peso;
                arbol.insertar(nombre, edad, peso);
                break;
            }
            case 2: {
                std::string nombre;
                int edad;
                std::cout << "Ingrese nombre de la persona a eliminar: ";
                std::getline(std::cin, nombre);
                std::cout << "Ingrese edad de la persona a eliminar: ";
                std::cin >> edad;
                if (arbol.eliminar(nombre, edad)) {
                    std::cout << "Persona eliminada.\n";
                } else {
                    std::cout << "No se encontró a la persona.\n";
                }
                break;
            }
            case 3:
                arbol.imprimirArbol();
                break;
            case 4:
                return;
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    }
}

int main() {
    setupConsole();
    Arbol arbol;
    menu(arbol);
    return 0;
}