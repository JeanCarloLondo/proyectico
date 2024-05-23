#include <iostream>
#include <string>
#include <memory>

// Definición de la clase Persona, que representa a una persona con nombre, edad y peso.
class Persona {
public:
    std::string nombre;
    int edad;
    double peso;

    // Constructor de Persona que inicializa sus atributos.
    Persona(std::string nombre, int edad, double peso) : nombre(nombre), edad(edad), peso(peso) {}
};

// Definición de la clase Nodo, que representa un nodo en un árbol binario.
class Nodo {
public:
    std::shared_ptr<Persona> dato; // Puntero a un objeto Persona
    std::shared_ptr<Nodo> izq;     // Puntero al hijo izquierdo
    std::shared_ptr<Nodo> der;     // Puntero al hijo derecho

    // Constructor de Nodo que inicializa sus punteros.
    Nodo(std::shared_ptr<Persona> dato) : dato(dato), izq(nullptr), der(nullptr) {}
};

// Definición de la clase Arbol, que representa un árbol binario.
class Arbol {
public:
    std::shared_ptr<Nodo> raiz; // Puntero a la raíz del árbol

    // Constructor de Arbol que inicializa la raíz como nulo.
    Arbol() : raiz(nullptr) {}

    // Método para insertar un nuevo nodo en el árbol.
    void insertar(std::string nombre, int edad, double peso) {
        std::shared_ptr<Persona> item = std::make_shared<Persona>(nombre, edad, peso);
        raiz = insertarRecursivo(raiz, item);
    }

    // Método para eliminar un nodo del árbol por la edad.
    void eliminar(int edad) {
        
    }

    // Método público para imprimir los datos de las personas en orden.
    void imprimir() {
        recorrerEnOrden(raiz);
    }

private:
    // Método privado recursivo para insertar un nuevo nodo en el árbol.
    std::shared_ptr<Nodo> insertarRecursivo(std::shared_ptr<Nodo> nodo, std::shared_ptr<Persona> dato) {
        if (nodo == nullptr) {
            nodo = std::make_shared<Nodo>(dato);
        } else if (dato->edad < nodo->dato->edad) {
            nodo->izq = insertarRecursivo(nodo->izq, dato);
        } else {
            nodo->der = insertarRecursivo(nodo->der, dato);
        }
        return nodo;
    }

    // Método privado recursivo para eliminar un nodo en el árbol.
    std::shared_ptr<Nodo> eliminarRecursivo(std::shared_ptr<Nodo> nodo, int edad) {
        if (nodo == nullptr) {
            return nodo;
        }

        if (edad < nodo->dato->edad) {
            nodo->izq = eliminarRecursivo(nodo->izq, edad);
        } else if (edad > nodo->dato->edad) {
            nodo->der = eliminarRecursivo(nodo->der, edad);
        } else {
            if (nodo->izq == nullptr) {
                return nodo->der;
            } else if (nodo->der == nullptr) {
                return nodo->izq;
            }

          // Despues de q lo encuentra y tiene 2 hijos
            std::shared_ptr<Nodo> temp = minValorNodo(nodo->der); //valor minimo del subarbol derecho
            nodo->dato = temp->dato; //iguala el nodo que queremos eliminar con el minimo encontrado
            nodo->der = eliminarRecursivo(nodo->der, temp->dato->edad); //en lugar de eliminar el nodo actualizado
            // eliminamos recursivamente el nodo minimo del subarbol derecho
        }
        return nodo;
    }

    // Función auxiliar para encontrar el nodo con el valor mínimo en un subárbol.
    std::shared_ptr<Nodo> minValorNodo(std::shared_ptr<Nodo> nodo) {
        std::shared_ptr<Nodo> current = nodo;
        while (current && current->izq != nullptr) {
            current = current->izq;
        }
        return current;
    }

    // Método recursivo para recorrer el árbol en orden y mostrar los datos.
    void recorrerEnOrden(std::shared_ptr<Nodo> nodo) {
        if (nodo != nullptr) {
            recorrerEnOrden(nodo->izq);
            std::cout << nodo->dato->nombre << " (" << nodo->dato->edad << " annos, " << nodo->dato->peso << " kg)" << std::endl;
            recorrerEnOrden(nodo->der);
        }
    }
};

// Función principal
int main() {
    Arbol arbol;

    // Insertar algunas personas en el árbol
    arbol.insertar("Edi", 51, 90.0);
    arbol.insertar("Juan", 14, 50.0);
    arbol.insertar("Isa", 61, 55.0);
    arbol.insertar("Pepe", 34, 75.0);

    // Imprimir los datos de las personas en orden
    std::cout << "Datos iniciales del árbol:\n";
    arbol.imprimir();

    // Eliminar a "Juan" del árbol y mostrar el resultado
    std::cout << "Eliminar a Juan...\n";
    arbol.eliminar(34);
    arbol.imprimir();

    return 0;
}
