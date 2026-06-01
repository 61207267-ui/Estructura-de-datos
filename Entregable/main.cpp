#include <iostream>
#include <string>
#include "validaciones.h" // Solo para leerEntero y leerPrioridad

using namespace std;

// ========================================================
// 1. ESTRUCTURAS DE DATOS DINÁMICAS (CON CONSTRUCTORES)
// ========================================================

struct NodoLista {
    int id;
    string nombre;
    int prioridad;
    NodoLista* siguiente;

    NodoLista(int _id, string _nombre, int _prioridad) {
        id = _id;
        nombre = _nombre;
        prioridad = _prioridad;
        siguiente = NULL;
    }
};

struct NodoCola {
    int id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;

    NodoCola(int _id, string _nombre, int _prioridad) {
        id = _id;
        nombre = _nombre;
        prioridad = _prioridad;
        siguiente = NULL;
    }
};

struct NodoPila {
    int idProceso;
    int bloqueMemoria; 
    NodoPila* siguiente;

    NodoPila(int _idProceso, int _bloqueMemoria) {
        idProceso = _idProceso;
        bloqueMemoria = _bloqueMemoria;
        siguiente = NULL;
    }
};

// ========================================================
// 2. FUNCIONES AUXILIARES DE CONTEO (Con bucles while)
// ========================================================
int contarElementosLista(NodoLista* inicio) {
    int c = 0;
    NodoLista* aux = inicio;
    while (aux != NULL) {
        c++;
        aux = aux->siguiente;
    }
    return c;
}

int contarElementosCola(NodoCola* frente) {
    int c = 0;
    NodoCola* aux = frente;
    while (aux != NULL) {
        c++;
        aux = aux->siguiente;
    }
    return c;
}

int contarElementosPila(NodoPila* tope) {
    int c = 0;
    NodoPila* aux = tope;
    while (aux != NULL) {
        c++;
        aux = aux->siguiente;
    }
    return c;
}

// ========================================================
// 3. VALIDACIÓN DE ID ÚNICO (Con bucle while)
// ========================================================
bool idExiste(NodoLista* inicio, int id) {
    NodoLista* aux = inicio;
    while (aux != NULL) {
        if (aux->id == id) {
            return true; 
        }
        aux = aux->siguiente;
    }
    return false; 
}

// ========================================================
// 4. OPERACIONES DEL GESTOR DE PROCESOS (LISTA ENLAZADA)
// ========================================================

void insertarProcesoFinal(NodoLista*& inicio, int id, string nombre, int prioridad) {
    NodoLista* nuevo = new NodoLista(id, nombre, prioridad);
    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        NodoLista* aux = inicio;
        while (aux->siguiente != NULL) { // Recorrido logico con while
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
    cout << "-> Proceso [" << nombre << "] registrado con exito.\n";
}

// ÚNICAMENTE PARA IMPRIMIR VALORES SE USA FOR
void mostrarLista(NodoLista* inicio) {
    int limite = contarElementosLista(inicio);
    if (limite == 0) {
        cout << "El registro global de procesos esta vacio.\n";
        return;
    }
    cout << "\n=== REGISTRO GLOBAL DE PROCESOS ===\n";
    NodoLista* aux = inicio;
    for (int i = 0; i < limite; i++) { // For exclusivo para imprimir
        cout << "Proceso " << (i + 1) << " -> ID: " << aux->id << " | Nombre: " << aux->nombre << " | Prioridad: " << aux->prioridad << "\n";
        aux = aux->siguiente;
    }
    cout << "===================================\n";
}

void buscarProceso(NodoLista* inicio, int id) {
    NodoLista* aux = inicio;
    while (aux != NULL) { // Logica de busqueda con while
        if (aux->id == id) {
            cout << "-> Proceso Encontrado: ID: " << aux->id << " | Nombre: " << aux->nombre << " | Prioridad: " << aux->prioridad << "\n";
            return;
        }
        aux = aux->siguiente;
    }
    cout << "-> [ERROR] Proceso con ID " << id << " no encontrado.\n";
}

void modificarPrioridad(NodoLista* inicio, int id, int nuevaPrioridad) {
    NodoLista* aux = inicio;
    while (aux != NULL) { // Logica de modificacion con while
        if (aux->id == id) {
            aux->prioridad = nuevaPrioridad;
            cout << "-> Prioridad actualizada correctamente para el proceso ID " << id << ".\n";
            return;
        }
        aux = aux->siguiente;
    }
    cout << "-> [ERROR] No se pudo modificar. ID no encontrado.\n";
}

void eliminarProceso(NodoLista*& inicio, int id) {
    if (inicio == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }
    NodoLista* anterior = NULL;
    NodoLista* aux = inicio;
    while (aux != NULL && aux->id != id) { // Logica de eliminacion con while
        anterior = aux;
        aux = aux->siguiente;
    }
    if (aux == NULL) {
        cout << "-> [ERROR] El proceso con ID " << id << " no existe.\n";
        return;
    }
    if (anterior == NULL) {
        inicio = inicio->siguiente;
    } else {
        anterior->siguiente = aux->siguiente;
    }
    delete aux;
    cout << "-> Proceso ID " << id << " eliminado permanentemente.\n";
}

// ========================================================
// 5. OPERACIONES DEL PLANIFICADOR DE CPU (COLA DE PRIORIDAD)
// ========================================================
void encolarProcesoConPrioridad(NodoCola*& frente, NodoCola*& final, int id, string nombre, int prioridad) {
    NodoCola* nuevo = new NodoCola(id, nombre, prioridad);
    if (frente == NULL) { 
        frente = final = nuevo;
    } else if (prioridad > frente->prioridad) { 
        nuevo->siguiente = frente;
        frente = nuevo;
    } else { 
        NodoCola* ant = NULL;
        NodoCola* act = frente;
        while (act != NULL && act->prioridad >= prioridad) { // Logica de ordenamiento con while
            ant = act;
            act = act->siguiente;
        }
        nuevo->siguiente = act;
        ant->siguiente = nuevo;
        if (act == NULL) { 
            final = nuevo;
        }
    }
    cout << "-> Proceso [" << nombre << "] encolado en CPU (Prioridad: " << prioridad << ").\n";
}

void desencolarProceso(NodoCola*& frente, NodoCola*& final) {
    if (frente == NULL) {
        cout << "-> [AVISO] No hay procesos pendientes en el Planificador.\n";
        return;
    }
    NodoCola* aux = frente;
    cout << "-> [CPU] Ejecutando y despachando Proceso ID: " << aux->id << " | Nombre: " << aux->nombre << "\n";
    frente = frente->siguiente;
    if (frente == NULL) {
        final = NULL;
    }
    delete aux;
}

// ÚNICAMENTE PARA IMPRIMIR VALORES SE USA FOR
void mostrarCola(NodoCola* frente) {
    int limite = contarElementosCola(frente);
    if (limite == 0) {
        cout << "Cola del Planificador de CPU vacia.\n";
        return;
    }
    cout << "\n--- COLA DE ESPERA DE CPU (Por Prioridad) ---\n";
    NodoCola* aux = frente;
    for (int i = 0; i < limite; i++) { // For exclusivo para imprimir
        cout << (i + 1) << ". ID: " << aux->id << " | Nombre: " << aux->nombre << " | Prioridad: " << aux->prioridad << "\n";
        aux = aux->siguiente;
    }
    cout << "---------------------------------------------\n";
}

// ========================================================
// 6. OPERACIONES DEL GESTOR DE MEMORIA (PILA DINÁMICA)
// ========================================================
bool pilaVacia(NodoPila* tope) {
    return (tope == NULL);
}

void pushMemoria(NodoPila*& tope, int idProceso, int bloqueMemoria) {
    NodoPila* nuevo = new NodoPila(idProceso, bloqueMemoria);
    nuevo->siguiente = tope;
    tope = nuevo;
    cout << "-> [MEMORIA] Bloque asignado de " << bloqueMemoria << " MB al Proceso ID: " << idProceso << ".\n";
}

void popMemoria(NodoPila*& tope) {
    if (pilaVacia(tope)) {
        cout << "-> [AVISO] El Stack de memoria RAM esta libre.\n";
        return;
    }
    NodoPila* aux = tope;
    cout << "-> [MEMORIA] Liberando " << aux->bloqueMemoria << " MB del Proceso ID: " << aux->idProceso << ".\n";
    tope = tope->siguiente;
    delete aux;
}

// ÚNICAMENTE PARA IMPRIMIR VALORES SE USA FOR
void mostrarPilaMemoria(NodoPila* tope) {
    int limite = contarElementosPila(tope);
    if (limite == 0) {
        cout << "La memoria RAM no registra bloques asignados.\n";
        return;
    }
    cout << "\n=== ESTADO DEL STACK DE MEMORIA (RAM) ===\n";
    NodoPila* aux = tope;
    for (int i = 0; i < limite; i++) { // For exclusivo para imprimir
        cout << "Nivel " << (i + 1) << " -> [ Bloque: " << aux->bloqueMemoria << " MB | Proceso ID: " << aux->idProceso << " ]\n";
        aux = aux->siguiente;
    }
    cout << "=========================================\n";
}

// ========================================================
// 7. SUBMENÚS CON PASO POR REFERENCIA ESTRICTO (&)
// ========================================================

void subMenuGestorProcesos(NodoLista*& registroGlobal) { 
    int opLista;
    do {
        cout << "\n--- SUBMENU: GESTOR DE PROCESOS ---\n";
        cout << "1. Registrar e Insertar Proceso al Final\n";
        cout << "2. Mostrar Historial Global de Procesos\n";
        cout << "3. Buscar Proceso por ID\n";
        cout << "4. Modificar Prioridad en Tiempo Real\n";
        cout << "5. Eliminar Registro de Proceso\n";
        cout << "6. Volver al Menu Principal\n";
        opLista = leerEntero("Ingrese una opcion (1-6): ");

        switch (opLista) {
            case 1: {
                int id;
                do {
                    id = leerEntero("Ingrese ID unico del proceso: ");
                    if (idExiste(registroGlobal, id)) { 
                        cout << "[ERROR] El ID " << id << " ya esta registrado. Ingrese uno diferente.\n";
                    }
                } while (idExiste(registroGlobal, id));

                string nombre;
                cout << "Ingrese Nombre del proceso: ";
                cin.ignore();
                getline(cin, nombre);
                int prio = leerPrioridad("Ingrese nivel de prioridad (1-10): ");
                insertarProcesoFinal(registroGlobal, id, nombre, prio);
                break;
            }
            case 2:
                mostrarLista(registroGlobal);
                break;
            case 3: {
                int id = leerEntero("ID del proceso a buscar: ");
                buscarProceso(registroGlobal, id);
                break;
            }
            case 4: {
                int id = leerEntero("ID del proceso a reconfigurar: ");
                int nuevaPrio = leerPrioridad("Ingrese nueva prioridad (1-10): ");
                modificarPrioridad(registroGlobal, id, nuevaPrio);
                break;
            }
            case 5: {
                int id = leerEntero("ID del proceso a dar de baja: ");
                eliminarProceso(registroGlobal, id);
                break;
            }
            case 6:
                cout << "Regresando al menu principal...\n";
                break;
            default:
                cout << "[ERROR] Opcion no valida.\n";
        }
    } while (opLista != 6);
}

void subMenuPlanificadorCPU(NodoCola*& frenteCPU, NodoCola*& finalCPU) { 
    int opCola;
    do {
        cout << "\n--- SUBMENU: PLANIFICADOR DE CPU ---\n";
        cout << "1. Encolar Proceso en Fila de Espera\n";
        cout << "2. Desencolar / Despachar Proceso (Ejecutar en CPU)\n";
        cout << "3. Ver Fila de Procesos Pendientes\n";
        cout << "4. Volver al Menu Principal\n";
        opCola = leerEntero("Ingrese una opcion (1-4): ");

        switch (opCola) {
            case 1: {
                int id = leerEntero("Ingrese ID del proceso para CPU: ");
                string nombre;
                cout << "Ingrese Nombre del proceso: ";
                cin.ignore();
                getline(cin, nombre);
                int prio = leerPrioridad("Ingrese prioridad de ejecucion (1-10): ");
                encolarProcesoConPrioridad(frenteCPU, finalCPU, id, nombre, prio);
                break;
            }
            case 2:
                desencolarProceso(frenteCPU, finalCPU);
                break;
            case 3:
                mostrarCola(frenteCPU);
                break;
            case 4:
                cout << "Regresando al menu principal...\n";
                break;
            default:
                cout << "[ERROR] Opcion no valida.\n";
        }
    } while (opCola != 4);
}

void subMenuGestorMemoria(NodoPila*& topMemoria) { 
    int opPila;
    do {
        cout << "\n--- SUBMENU: GESTOR DE MEMORIA RAM ---\n";
        cout << "1. Asignar Bloque de Memoria (Push)\n";
        cout << "2. Liberar Ultimo Bloque Asignado (Pop)\n";
        cout << "3. Verificar si el Stack de Memoria esta Vacio\n";
        cout << "4. Ver Mapa de Ocupacion de Memoria Actual\n";
        cout << "5. Volver al Menu Principal\n";
        opPila = leerEntero("Ingrese una opcion (1-5): ");

        switch (opPila) {
            case 1: {
                int id = leerEntero("ID del proceso solicitante: ");
                int tamano = leerEntero("Ingrese cantidad de memoria a reservar (MB): ");
                pushMemoria(topMemoria, id, tamano);
                break;
            }
            case 2:
                popMemoria(topMemoria);
                break;
            case 3:
                if (pilaVacia(topMemoria)) {
                    cout << "-> Confirmado: La Pila de Memoria esta 100% LIBRE.\n";
                } else {
                    cout << "-> Alerta: Hay bloques de memoria activos en ejecucion.\n";
                }
                break;
            case 4:
                mostrarPilaMemoria(topMemoria);
                break;
            case 5:
                cout << "Regresando al menu principal...\n";
                break;
            default:
                cout << "[ERROR] Opcion no valida.\n";
        }
    } while (opPila != 5);
}

// ========================================================
// 8. MENÚ PRINCIPAL DEL SISTEMA
// ========================================================
void menuPrincipal() {
    NodoLista* registroGlobal = NULL;
    NodoCola* frenteCPU = NULL;
    NodoCola* finalCPU = NULL;
    NodoPila* topMemoria = NULL;

    int opcionPrincipal;

    do {
        cout << "\n=======================================================\n";
        cout << "  BIENVENIDO AL SIMULADOR DE SISTEMA OPERATIVO\n";
        cout << "=======================================================\n";
        cout << "1. Gestor de Procesos (Lista Enlazada Simple)\n";
        cout << "2. Planificador de CPU (Cola de Prioridad)\n";
        cout << "3. Gestor de Memoria RAM (Pila Dinamica)\n";
        cout << "4. Salir del simulador\n";
        opcionPrincipal = leerEntero("Seleccione un modulo del sistema (1-4): ");

        switch (opcionPrincipal) {
            case 1:
                subMenuGestorProcesos(registroGlobal); 
                break;
            case 2:
                subMenuPlanificadorCPU(frenteCPU, finalCPU); 
                break;
            case 3:
                subMenuGestorMemoria(topMemoria); 
                break;
            case 4:
                cout << "\nSaliendo del simulador... Sistema Operativo Apagado Correctamente.\n";
                break;
            default:
                cout << "[ERROR] Opcion incorrecta. Elija un numero entre 1 y 4.\n";
        }
    } while (opcionPrincipal != 4);
}

int main() {
    menuPrincipal();
    return 0;
}