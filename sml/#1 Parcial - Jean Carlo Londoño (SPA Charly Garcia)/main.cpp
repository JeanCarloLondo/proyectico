#include <Windows.h>

#include <iostream>
#include "Nodo.h"
#include "Persona.h"
#include "Menu.cpp"

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"

// Vamos a definir algunas variables, como es una lista finita ya sé de antemano el maximo de turnos

const int MAX_TURNOS = 16;
Nodo *SPA[MAX_TURNOS];
int turnosOcupados = 0;

// Funcion para crear un nuevo turno
Persona crearTurno()
{
    // Solicitando datos al usuario
    std::string nombre;
    int tipoMasaje;
    int numHabitacion;
    bool atendido;

    std::cout << "Por favor, digite su nombre (TEXTO Y PEGADO) ";
    std::cin >> nombre;

    std::cout << "Por favor, digite su numero de habitacion(Entero):  ";
    std::cin >> numHabitacion;

    std::cout << "Que tipo de masaje desea? (Seleccioné un número que equivalga a la opción deseada)" << endl;

    bool valid = true;
    do
    {
        std::cout << "(1) - Masaje Chocolate" << endl;
        std::cout << "(2) - Masaje Piedras Volcánicas" << endl;
        std::cout << "(3) - Masaje de Sales" << endl;
        std::cout << "(4) - Masaje de Minerales" << endl;
        cin >> tipoMasaje;
        if (tipoMasaje < 1 || tipoMasaje > 4)
        {
            cout << "Por favor digite una opción válida" << endl;
            valid = false;
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    // Devuelvo el objeto Persona con los datos proporcionados por el usuario
    return Persona(nombre, tipoMasaje, numHabitacion, atendido);
}

// Función para agregar un nuevo turno a la lista
void agregarTurno(Persona item)
{
    boolean libre = false;
    int i = 0;

    // busquede de turno libre
    while (!libre && i < MAX_TURNOS)
    {
        if (SPA[i] == nullptr)
        {
            libre = true;
        }
        else
        {
            i = i + 1;
        }
    }

    if (i >= MAX_TURNOS)
    {
        // controla si se supera el tope de turnos
        std::cout << "No hay más turnos disponibles.." << std::endl;
    }
    else
    {
        boolean inf = false;

        while (inf == false)
        {

            int turno = 0;
            cout << " Por favor elija el turno que desee: \n1, 8:00-8:30\n2, 8:30-9:00\n3, 9:00-9:30\n4, 9:30-10:00\n5, 10:00-10:30\n6, 10:30-11:00\n7, 11:00-11:30\n8, 11:30-12:00\n9, 12:00-12:30\n10, 12:30-1:00\n11, 1:00-1:30\n12, 1:30-2:00\n13, 2:00-2:30\n14, 2:30-3:00\n15, 3:00-3:30\n16, 3:30-4:00  -> ";
            cin >> turno;
            if (turno >= 0 && turno <= 16)
            {
                if (SPA[turno] != nullptr)
                {
                    cout << "Lo sentimos, ese turno está ocupado, elija otro o intentelo más tarde" << endl;
                    inf = false;
                }
                else
                {
                    SPA[turno] = new Nodo(item);
                    cout << " Buena elección, tu turno ha sido generado..." << endl;
                    turnosOcupados = turnosOcupados + 1;
                    inf = true;
                    break;
                }
            }
            else
            {
                cout << " Por favor seleccione una opción valida" << endl;
                inf = false;
            }
        }
    }
}

// Función para retirar un turno de la lista
void retirarTurno()
{
    int numHabitacion;
    std::cout << "Ingrese el num de habitacion de la persona a la cual desea retirar el turno : (Número) ";
    cin >> numHabitacion;

    int indice = 0;
    while (indice < MAX_TURNOS)
    {
        if (SPA[indice] != nullptr)
        {
            if (SPA[indice]->persona.numHabitacion == numHabitacion)
            {
                std::cout << "Retirar turno...." << std::endl;
                Persona *item = &SPA[indice]->persona;
                SPA[indice] = nullptr; // libera la plaza
                turnosOcupados = turnosOcupados - 1;
                return;
            }
        }
        indice = indice + 1;
    }
    std::cout << "No se encuentra el número" << numHabitacion << " En la lista " << std::endl;
}

// Función para mostrar la lista de turnos
void mostrarLista()
{
    std::cout << "    Turnos Totales: " << std::to_string(MAX_TURNOS) << std::endl;
    std::cout << "     Turnos ocupados: " << std::to_string(turnosOcupados) << std::endl;
    std::cout << std::endl
              << " DETALLE" << std::endl;

    for (int i = 0; i < MAX_TURNOS; ++i)
    {
        Nodo *item = SPA[i];
        if (item != nullptr)
        {
            std::cout << "     [" << std::to_string(i) << "] "
                      << "Turno: " << SPA[i]->persona.to_string() << std::endl;
        }
        else
        {
            std::cout << "     [" << std::to_string(i) << "] " << RED << "Libre" << RESET << std::endl;
        }
    }
}

// Función para atender a la siguiente persona en la lista de turnos
void atenderPersona()
{

    cout << "La siguiente persona en ser atendida es: " << endl;
    bool encontrado = false;
    for (int i = 0; i < MAX_TURNOS; ++i)
    {
        if (SPA[i] != nullptr && SPA[i]->persona.atendido != true)
        {
            bool atendido = false;
            cout << SPA[i]->persona.nombre;
            encontrado = true;
            int elec = 0;
            cout << " ->  Deseas atender a :" << SPA[i]->persona.nombre << " Ahora mismo ?  (1)-SI  (2)-NO " << endl;
            cin >> elec;
            if (elec >= 1 && elec <= 2)
            {
                if (elec == 1)
                {
                    cout << SPA[i]->persona.nombre << " ha sido atendido." << endl;
                    SPA[i]->persona.atendido = true;
                    Persona *item = &SPA[i]->persona;
                    SPA[i] = nullptr;
                    cout << " La siguiente persona en ser atendida es: ";

                    if (elec == 2)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << " Por favor seleccione una opción valida";
                break;
            }
        }
    }

    if (!encontrado)
    {
        cout << "No hay personas en la lista de turnos ocupados.";
    }
}

// Función para atender la opción seleccionada en el menú
void atenderMenu(int opcion)
{
    Persona *item = nullptr;
    switch (opcion)
    {
    case 1:
    {
        if (turnosOcupados >= MAX_TURNOS)
        {
            std::cout << "No puedes agendar más turnos, elimina uno o intentalo mas tarde" << std::endl;
            break;
        }

        std::cout << "Elegir turno\n";
        agregarTurno(crearTurno());
        break;
    }

    case 2:
    {
        std::cout << "Retirar turno\n";
        retirarTurno();
        break;
    }

    case 3:
    {
        std::cout << "\n VER TURNOS DEL SPA\n";
        mostrarLista();
        break;
    }

    case 4:
    {
        std::cout << "\n Atender Persona\n";
        atenderPersona();
        break;
    }

    default:
    {
        std::cout << "Opcion no valida\n";
        break;
    }
    }
}

int main()
{

    SetConsoleOutputCP(CP_UTF8); // para ver las tildes en el terminal
    int opcion;
    bool terminar = false;

    // Inicializar espacios
    for (int i = 0; i < MAX_TURNOS; ++i)
    {
        SPA[i] = nullptr;
    }

    while (!terminar)
    {
        mostrarMenu();            // Llama a la función del archivo externo para mostrar el menú
        opcion = obtenerOpcion(); // Llama a la función para obtener la opción

        if (opcion == 5)
        {
            terminar = true;
        }
        else
        {
            atenderMenu(opcion); // Llama a la función para atender la opción seleccionada
        }
    }

    return 0;
}
