#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

vector<Palabra> cargarDiccionario(const string& nombreArchivo) {
    vector<Palabra> diccionario;
    ifstream archivo(nombreArchivo);
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra, traduccion, funcionalidad;
        getline(ss, palabra, '|');
        getline(ss, traduccion, '|');
        getline(ss, funcionalidad);
        diccionario.push_back({palabra, traduccion, funcionalidad});
    }
    return diccionario;
}

void guardarDiccionario(const vector<Palabra>& diccionario, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::trunc);
    for (const auto& p : diccionario) {
        archivo << p.palabra << "|" << p.traduccion << "|" << p.funcionalidad << endl;
    }
}

void agregarPalabra(vector<Palabra>& diccionario) {
    Palabra nueva;
    cout << "Ingrese Palabra: ";
    getline(cin, nueva.palabra);
    cout << "Ingrese Traduccion: ";
    getline(cin, nueva.traduccion);
    cout << "Ingrese Funcionalidad: ";
    getline(cin, nueva.funcionalidad);
    diccionario.push_back(nueva);
}

void mostrarDiccionario(const vector<Palabra>& diccionario) {
    cout << "Listado de Palabras:\n";
    for (const auto& p : diccionario) {
        cout << "Palabra: " << p.palabra << ", Traduccion: " << p.traduccion << ", Funcionalidad: " << p.funcionalidad << endl;
    }
}

void actualizarPalabra(vector<Palabra>& diccionario) {
    string buscar;
    cout << "Ingrese la palabra a actualizar: ";
    getline(cin, buscar);

    for (auto& p : diccionario) {
        if (p.palabra == buscar) {
            cout << "Nueva traduccion: ";
            getline(cin, p.traduccion);
            cout << "Nueva funcionalidad: ";
            getline(cin, p.funcionalidad);
            return;
        }
    }
    cout << "Palabra no encontrada.\n";
}

void borrarPalabra(vector<Palabra>& diccionario) {
    string buscar;
    cout << "Ingrese la palabra a eliminar: ";
    getline(cin, buscar);

    auto it = remove_if(diccionario.begin(), diccionario.end(), [&buscar](Palabra& p) {
        return p.palabra == buscar;
    });

    if (it != diccionario.end()) {
        diccionario.erase(it, diccionario.end());
        cout << "Palabra eliminada.\n";
    } else {
        cout << "Palabra no encontrada.\n";
    }
}

int main() {
    const string nombreArchivo = "diccionario.txt";
    vector<Palabra> diccionario = cargarDiccionario(nombreArchivo);

    int opcion;
    do {
        cout << "\nMENU CRUD Diccionario\n";
        cout << "1. Agregar Palabra\n";
        cout << "2. Mostrar Diccionario\n";
        cout << "3. Actualizar Palabra\n";
        cout << "4. Borrar Palabra\n";
        cout << "5. Salir\n";
        cout << "Ingrese opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1: agregarPalabra(diccionario); guardarDiccionario(diccionario, nombreArchivo); break;
            case 2: mostrarDiccionario(diccionario); break;
            case 3: actualizarPalabra(diccionario); guardarDiccionario(diccionario, nombreArchivo); break;
            case 4: borrarPalabra(diccionario); guardarDiccionario(diccionario, nombreArchivo); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 5);

    return 0;
}
