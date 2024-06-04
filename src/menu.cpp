#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <limits>
#include <stdexcept>

#include "menu.hpp"

using namespace std;



int menu(){
    int option;

    while( (cout << "1. Atencion\n2. Consulta\n3. Salir\n" && !(cin >> option)) || option < ATENCION|| option > SALIR){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcion invalida, intente de nuevo\n";
    }

    do {
        switch (option){
            case ATENCION:
                cout << "Atencion\n";
                break;
            case CONSULTA:
                cout << "Consulta\n";
                break;
            case SALIR:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }
    } while (option != SALIR);


}
