#include <iostream>
#include<string>
using namespace std;

#define MAX 5

struct Libro{

    int codigo;
    string nombre;
    string autor;
};

Libro pila[MAX];

int tope = -1;

// INSERTAR LIBRO
void insertar(Libro dato){

    if(tope == MAX - 1){

        cout << "La pila esta llena." << endl;

    }else{

        tope++;

        pila[tope] = dato;

        cout << "Libro insertado correctamente." << endl;
    }
}

// ELIMINAR LIBRO
void eliminar(){

    if(tope == -1){

        cout << "La pila esta vacia." << endl;

    }else{

        cout << "Libro eliminado: " << pila[tope].nombre << endl;

        tope--;
    }
}

// VER LIBRO SUPERIOR
void cima(){

    if(tope == -1){

        cout << "La pila esta vacia." << endl;

    }else{

        cout << "\nLIBRO SUPERIOR" << endl;
        cout << "Codigo: " << pila[tope].codigo << endl;
        cout << "Nombre: " << pila[tope].nombre << endl;
        cout << "Autor: " << pila[tope].autor << endl;
    }
}

// VERIFICAR VACIA
bool estaVacia(){

    return tope == -1;
}

// MOSTRAR LIBROS
void imprimir(){

    if(estaVacia()){

        cout << "La pila esta vacia." << endl;

    }else{

        cout << "\nLIBROS EN LA PILA" << endl;

        for(int i = tope; i >= 0; i--){

            cout << "\nCodigo: " << pila[i].codigo << endl;
            cout << "Nombre: " << pila[i].nombre << endl;
            cout << "Autor: " << pila[i].autor << endl;
        }
    }
}

int main(){

    int opcion;

    Libro dato;

    do{

        cout << "\n====== PILA DE LIBROS ======" << endl;
        cout << "1. Insertar libro" << endl;
        cout << "2. Eliminar libro" << endl;
        cout << "3. Ver libro superior" << endl;
        cout << "4. Verificar si esta vacia" << endl;
        cout << "5. Mostrar libros" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch(opcion){

            case 1:

                cout << "Ingrese codigo: ";
                cin >> dato.codigo;

                cin.ignore();

                cout << "Ingrese nombre: ";
                getline(cin, dato.nombre);

                cout << "Ingrese autor: ";
                getline(cin, dato.autor);

                insertar(dato);

                break;

            case 2:

                eliminar();

                break;

            case 3:

                cima();

                break;

            case 4:

                if(estaVacia()){

                    cout << "La pila esta vacia." << endl;

                }else{

                    cout << "La pila NO esta vacia." << endl;
                }

                break;

            case 5:

                imprimir();

                break;

            case 6:

                cout << "Programa finalizado." << endl;

                break;

            default:

                cout << "Opcion invalida." << endl;
        }

    }while(opcion != 6);

    return 0;
}