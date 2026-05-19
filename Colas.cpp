#include <iostream>
#include <string>

using namespace std;


struct Descarga {
    string nombreArchivo;
    Descarga* siguiente;

    Descarga(string nombre) {
        nombreArchivo = nombre;
        siguiente = NULL;
    }
};


void encolarDescarga(Descarga*& frente, Descarga*& final, string nombre) {
    Descarga* nuevaDescarga = new Descarga(nombre);

    if (frente == NULL) {
    } else {
        final->siguiente = nuevaDescarga;
    }
    
    final = nuevaDescarga;
    cout << "Archivo '" << nombre << "' agregado a la cola de espera." << endl;
}

void procesarDescarga(Descarga*& frente, Descarga*& final) {
    if (frente == NULL) {
        cout << "No hay descargas pendientes." << endl;
        return;
    }

    Descarga* temp = frente;
    cout << "\n>>> Descargando ahora: " << temp->nombreArchivo << " <<<" << endl;

    frente = frente->siguiente;

    if (frente == NULL) {
        final = NULL;
    }

    delete temp; 
    cout << "Descarga finalizada con exito." << endl;
}

void verCola(Descarga* frente) {
    Descarga* temp = frente;
    cout << "\nESTADO ACTUAL DE LA COLA: ";
    if (temp == NULL) cout << "(Vacia)";
    
    while (temp != NULL) {
        cout << "[" << temp->nombreArchivo << "]";
        if (temp->siguiente != NULL) cout << " -> ";
        temp = temp->siguiente;
    }
    cout << endl;
}

int main() {
    Descarga* frente = NULL;
    Descarga* final = NULL;

    encolarDescarga(frente, final, "Python_Installer.exe");
    encolarDescarga(frente, final, "Java_Tutorial.pdf");
    encolarDescarga(frente, final, "Video_Clase_C++.mp4");

    verCola(frente);

    procesarDescarga(frente, final);
    
    verCola(frente); 

    encolarDescarga(frente, final, "Manual_CSharp.zip");

    verCola(frente);

    return 0;
}