#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Estructura para almacenar cada palabra
struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

// Función para cargar las palabras desde el archivo
void cargarDiccionario(vector<Palabra>& palabras) {
    ifstream archivo("diccionario.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo diccionario.txt.\n";
        return;
    }

    string linea;
    Palabra p;
    while (getline(archivo, linea)) {
        if (linea.find("Palabra: ") == 0) {
            p.palabra = linea.substr(9);
        } else if (linea.find("Traduccion: ") == 0) {
            p.traduccion = linea.substr(12);
        } else if (linea.find("Funcionalidad: ") == 0) {
            p.funcionalidad = linea.substr(15);
        } else if (linea == "---") {
            palabras.push_back(p);
            p = Palabra(); // Reseteamos para la siguiente palabra
        }
    }
    archivo.close();
}

// Función para guardar las palabras en el archivo
void guardarDiccionario(const vector<Palabra>& palabras) {
    ofstream archivo("diccionario.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    for (const auto& p : palabras) {
        archivo << "Palabra: " << p.palabra << "\n";
        archivo << "Traduccion: " << p.traduccion << "\n";
        archivo << "Funcionalidad: " << p.funcionalidad << "\n";
        archivo << "---\n";
    }
    archivo.close();
}

// Función para agregar una nueva palabra
void agregarPalabra(vector<Palabra>& palabras) {
    Palabra nueva;
    cin.ignore(); // Limpiar el buffer de entrada

    cout << "Ingrese Palabra: ";
    getline(cin, nueva.palabra);
    cout << "Ingrese Traduccion: ";
    getline(cin, nueva.traduccion);
    cout << "Ingrese Funcionalidad: ";
    getline(cin, nueva.funcionalidad);

    palabras.push_back(nueva);
    guardarDiccionario(palabras);

    cout << "Palabra agregada exitosamente.\n";
}

// Función para mostrar todas las palabras
void mostrarPalabras(const vector<Palabra>& palabras) {
    cout << "\n=== Listado de Palabras ===\n";
    for (size_t i = 0; i < palabras.size(); ++i) {
        cout << i + 1 << ". " << palabras[i].palabra << " - " << palabras[i].traduccion << endl;
        cout << "   Funcionalidad: " << palabras[i].funcionalidad << endl;
    }
}

// Función para actualizar una palabra
void actualizarPalabra(vector<Palabra>& palabras) {
    mostrarPalabras(palabras);

    int indice;
    cout << "Ingrese el numero de la palabra que desea actualizar: ";
    cin >> indice;
    cin.ignore(); // Limpiar el buffer de entrada

    if (indice < 1 || indice > palabras.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    Palabra& p = palabras[indice - 1];

    cout << "Actualizando: " << p.palabra << "\n";

    cout << "Nueva Palabra (enter para mantener): ";
    string entrada;
    getline(cin, entrada);
    if (!entrada.empty()) p.palabra = entrada;

    cout << "Nueva Traduccion (enter para mantener): ";
    getline(cin, entrada);
    if (!entrada.empty()) p.traduccion = entrada;

    cout << "Nueva Funcionalidad (enter para mantener): ";
    getline(cin, entrada);
    if (!entrada.empty()) p.funcionalidad = entrada;

    guardarDiccionario(palabras);
    cout << "Palabra actualizada exitosamente.\n";
}

// Función para eliminar una palabra
void eliminarPalabra(vector<Palabra>& palabras) {
    mostrarPalabras(palabras);

    int indice;
    cout << "Ingrese el numero de la palabra que desea eliminar: ";
    cin >> indice;

    if (indice < 1 || indice > palabras.size()) {
        cout << "Indice invalido.\n";
        return;
    }

    palabras.erase(palabras.begin() + (indice - 1));
    guardarDiccionario(palabras);

    cout << "Palabra eliminada exitosamente.\n";
}

// Función principal
int main() {
    vector<Palabra> palabras;
    cargarDiccionario(palabras);

    int opcion;

    do {
        cout << "\n=== MENU DICCIONARIO ===\n";
        cout << "1. Agregar Palabra\n";
        cout << "2. Mostrar Palabras\n";
        cout << "3. Actualizar Palabra\n";
        cout << "4. Eliminar Palabra\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarPalabra(palabras);
                break;
            case 2:
                mostrarPalabras(palabras);
                break;
            case 3:
                actualizarPalabra(palabras);
                break;
            case 4:
                eliminarPalabra(palabras);
                break;
            case 5:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }

    } while (opcion != 5);

    return 0;
}
