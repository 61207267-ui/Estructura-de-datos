#include <iostream>
#include <string>

using namespace std;


struct Nodo {
    string tarea;      
    Nodo* siguiente;   

    
    Nodo(string textoTarea) {
        tarea = textoTarea;
        siguiente = NULL;
    }
};
  
Nodo* inicio = NULL; 

void registrarTarea() {
    string texto;
    cout << "Escribe la nueva tarea: ";
    getline(cin, texto);


    Nodo* nuevo = new Nodo(texto);

    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        Nodo* temporal = inicio;
        while (temporal->siguiente != NULL) {
            temporal = temporal->siguiente;
        }
        temporal->siguiente = nuevo; 
    }
    cout << "-> Tarea agregada con exito.\n";
}

void buscarTarea() {
    string texto;
    cout << "Que tarea deseas buscar?: ";
    getline(cin, texto);

    Nodo* temporal = inicio;
    bool encontrado = false;
    
    while (temporal != NULL) {
        if (temporal->tarea == texto) {
            encontrado = true;
            break;
        }
        temporal = temporal->siguiente;
    }
    if (encontrado) cout << "-> ¡Si existe en la lista!\n";
    else cout << "-> No se encontro esa tarea.\n";
}

void modificarTarea() {
    string texto, textoNuevo;
    cout << "Que tarea deseas modificar?: ";
    getline(cin, texto);
    cout << "Escribe el nuevo nombre: ";
    getline(cin, textoNuevo);

    Nodo* temporal = inicio;
    bool modificado = false;

    while (temporal != NULL) {
        if (temporal->tarea == texto) {
            temporal->tarea = textoNuevo;
            modificado = true;
            break;
        }
        temporal = temporal->siguiente;
    }
    if (modificado) cout << "-> Tarea actualizada correctamente.\n";
    else cout << "-> No se encontro la tarea para modificar.\n";
}

void verUltimaTarea() {
    if (inicio == NULL) {
        cout << "-> La lista esta vacia.\n";
    } else {
        Nodo* temporal = inicio;
        while (temporal->siguiente != NULL) {
            temporal = temporal->siguiente;
        }
        cout << "-> Ultima tarea en la lista: " << temporal->tarea << "\n";
    }
}

void verPrimeraTarea() {
    if (inicio == NULL) {
        cout << "-> La lista esta vacia.\n";
    } else {
        cout << "-> Primera tarea en la lista: " << inicio->tarea << "\n";
    }
}

void verDireccionInicial() {
    if (inicio == NULL) {
        cout << "-> La lista esta vacia. No hay direccion inicial.\n";
    } else {
        cout << "-> El inicio de la lista esta en la direccion: " << inicio << "\n";
    }
}

void mostrarTodasTareas() {
    if (inicio == NULL) {
        cout << "-> No hay tareas pendientes.\n";
    } else {
        cout << "\n--- VISTA HORIZONTAL DE LA LISTA ---\n";
        Nodo* temporal = inicio;
        
        while (temporal != NULL) {
            cout << "[" << temporal->tarea << "]";
            
            if (temporal->siguiente != NULL) {
                cout << " -> ";
            } else {
                cout << " -> NULL"; 
            }
            
            temporal = temporal->siguiente;
        }
        cout << "\n"; 
    }
}

int main() {
    int opcion;

    do {
        cout << "MENU - LISTA DE TAREAS\n";
        cout << "1. Registrar Tarea (Ingreso)\n";
        cout << "2. Buscar Tarea\n";
        cout << "3. Modificar Tarea (Actualizacion)\n";
        cout << "4. Ver Ultima Tarea Registrada\n";
        cout << "5. Ver Primera Tarea Registrada\n";
        cout << "6. Ver Direccion Inicial (Memoria)\n";
        cout << "7. Mostrar Todas las Tareas\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1: registrarTarea(); 
            break;
            case 2: buscarTarea(); 
            break;
            case 3: modificarTarea(); 
            break;
            case 4: verUltimaTarea(); 
            break;
            case 5: verPrimeraTarea(); 
            break;
            case 6: verDireccionInicial(); 
            break;
            case 7: mostrarTodasTareas(); 
            break;
            case 8: cout << "Programa finalizado.\n"; 
            break;
            default: cout << "Opcion no valida. Intente de nuevo.\n"; 
            break;
        }

    } while (opcion != 8);

    return 0;
}