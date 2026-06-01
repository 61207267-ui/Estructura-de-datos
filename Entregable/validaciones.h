#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
#include <string>

using namespace std;

// 1. Validacion clasica para leer solo numeros enteros sin usar <limits>
inline int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            break;
        } else {
            cout << "[ERROR] Entrada invalida. Por favor, ingrese un numero entero.\n";
            cin.clear();           // Restablece el estado de cin
            cin.ignore(1000, '\n'); // Limpia hasta 1000 caracteres del bufer hasta el enter
        }
    }
    return valor;
}

// 2. Validacion para el rango de prioridad (1-10)
inline int leerPrioridad(string mensaje) {
    int valor;
    while (true) {
        valor = leerEntero(mensaje);
        if (valor >= 1 && valor <= 10) {
            break;
        } else {
            cout << "ERROR La prioridad debe estar en el rango de 1 (Baja) a 10 (Alta).\n";
        }
    }
    return valor;
}

#endif