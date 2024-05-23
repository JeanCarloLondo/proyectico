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
    // Parámetros:
    // - nombre: nombre de la persona a insertar.
    // - edad: edad de la persona a insertar.
    // - peso: peso de la persona a insertar.
    void insertar(std::string nombre, int edad, double peso) {
        // Crear un objeto Persona con los datos proporcionados.
        std::shared_ptr<Persona> item = std::make_shared<Persona>(nombre, edad, peso);
        // Llamar a la función insertarRecursivo para insertar el nuevo nodo en el árbol.
        raiz = insertarRecursivo(raiz, item);
    }
    
    // Método recursivo para recorrer el árbol en orden y mostrar los datos de las personas.
    // Parámetros:
    // - nodo: puntero al nodo actual en el recorrido.
    void recorrerEnOrden(std::shared_ptr<Nodo> nodo) {
        if (nodo != nullptr) {
            // Recorrer el subárbol izquierdo
            recorrerEnOrden(nodo->izq);
            // Mostrar los datos de la persona en el nodo actual
            std::cout << nodo->dato->nombre << " (" << nodo->dato->edad << ")" << std::endl;
            // Recorrer el subárbol derecho
            recorrerEnOrden(nodo->der);
        }
    }

    // Método público para imprimir los datos de las personas en orden.
    void imprimir() {
        // Iniciar el recorrido en orden desde la raíz del árbol.
        recorrerEnOrden(raiz);
    }

private:
    // Método privado recursivo para insertar un nuevo nodo en el árbol.
    // Parámetros:
    // - nodo: puntero al nodo actual en el recorrido.
    // - dato: puntero al objeto Persona a insertar.
    // Retorno: puntero al nodo modificado.
    std::shared_ptr<Nodo> insertarRecursivo(std::shared_ptr<Nodo> nodo, std::shared_ptr<Persona> dato) {
        if (nodo == nullptr) {  // Si el árbol está vacío
            // Crear un nuevo nodo con el dato proporcionado.
            nodo = std::make_shared<Nodo>(dato);
        } else if (dato->edad < nodo->dato->edad) {  // Si la edad del dato es menor que la del nodo actual
            // Insertar recursivamente en el subárbol izquierdo.
            nodo->izq = insertarRecursivo(nodo->izq, dato);
        } else if (dato->edad >= nodo->dato->edad) {  // Si la edad del dato es mayor o igual que la del nodo actual
            // Insertar recursivamente en el subárbol derecho.
            nodo->der = insertarRecursivo(nodo->der, dato);
        }
        return nodo;  // Retornar el nodo modificado.
    }
};

// Función principal
int main() {
    Arbol arbol; // Crear un objeto Arbol

    // Insertar algunas personas en el árbol
    arbol.insertar("Edi", 51, 90.0);
    arbol.insertar("Juan", 14, 90.0);
    arbol.insertar("Isa", 61, 90.0);

    // Imprimir los datos de las personas en orden
    arbol.imprimir();

    return 0;
}
