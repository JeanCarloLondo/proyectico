#include <iostream>
#include <string>
#include <memory> // Biblioteca para los shared ptrs
using namespace std;

// Crear el objeto que sera la data del nodo en la estructura

class Persona
{
public:
    string nombre;
    int edad;
    double peso;
    Persona(string nombre, int edad, double peso) : nombre(nombre), edad(edad), peso(peso){}; // Constructor y su inici
};

class Nodo
{
public:
    std::shared_ptr<Persona> dato; // Apuntador que apunta a clase persona(objeto)
    std::shared_ptr<Nodo> izq;     // Apuntador a la izq
    std::shared_ptr<Nodo> der;     // Apuntador a la der

    // Constructor de la clase nodito
    Nodo(std::shared_ptr<Persona> dato) : dato(dato), izq(nullptr), der(nullptr) {}
};

class Arbol
{
public:
    shared_ptr<Nodo> raiz; // Pointer de nodo a la raiz que en este momento es null

    Arbol() : raiz(nullptr){}; // Constructor de la clase arbol, que es la lista basicamente, se inciializa la raiz

    void Insertar(string nombre, int edad, double peso)
    {
        shared_ptr<Persona> dato = make_shared<Persona>(nombre, edad, peso);
        raiz = insertarRecursivo(raiz, dato);
    }

    void Imprimir()
    {
        mostrarOrden(raiz);
    }

    void Eliminar(int edad) // Por ahora solo eliminemos con la edad
    {
        raiz = eliminarRecursivo(raiz, edad);
    }

private:
    shared_ptr<Nodo> insertarRecursivo(std::shared_ptr<Nodo> nodo, std::shared_ptr<Persona> dato)
    {
        if (nodo == nullptr)
        {
            nodo = make_shared<Nodo>(dato);
        } // En caso de que la lista este vacia

        else
        {
            if (dato->edad < nodo->dato->edad)
            {
                nodo->izq = insertarRecursivo(nodo->izq, dato);
            }
            if (dato->edad > nodo->dato->edad)
            {
                nodo->der = insertarRecursivo(nodo->der, dato);
            }
        }
        return nodo;
    }

    shared_ptr<Nodo> eliminarRecursivo(shared_ptr<Nodo> nodo, int edad)
    {
        if (nodo == nullptr)
        { // Lista vacia
            return nodo;
        }

        if (edad < nodo->dato->edad)
        {
            nodo->izq = eliminarRecursivo(nodo->izq, edad); // encuentra el ult val a la izq
        }
        if (edad > nodo->dato->edad)
        {
            nodo->der = eliminarRecursivo(nodo->der, edad); // encuentra ultimo val a la der
        }

        else
        {
            if (nodo->izq == nullptr)
            {
                return nodo->der;
            } // si al llegar a la ult comp el izq esta null return der
            if (nodo->der == nullptr)
            {
                return nodo->izq;
            }
        }

        // Despues de q lo encuentra
        shared_ptr<Nodo> temp = minValor(nodo->der);
        nodo->dato = temp->dato;
        nodo->der = eliminarRecursivo(nodo->der, temp->dato->edad);

        return nodo;
    }

    shared_ptr<Nodo> minValor(shared_ptr<Nodo> nodo) // metodo q elimina
    {
        shared_ptr<Nodo> current = nodo;
        while(current && current->izq !=nullptr){
            current = current->izq;
        }
        return current;
    }

    void mostrarOrden(shared_ptr<Nodo> raiz)
    {
        if (raiz != nullptr)
        { // pq si no esta vacia la lista
            mostrarOrden(raiz->der);
            std::cout << raiz->dato->nombre << " (" << raiz->dato->edad << " annos, " << raiz->dato->peso << " kg)" << std::endl;
            mostrarOrden(raiz->izq);
        }
    }
};

int main()
{
    Arbol arbol;

    arbol.Insertar("Pepe", 18, 72);
    arbol.Insertar("Juan", 23, 90);

    arbol.Imprimir();

    arbol.Eliminar(18);
    arbol.Imprimir();

    return 0;
}