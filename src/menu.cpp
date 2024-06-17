#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <exception>

#include <limits>
#include <stdexcept>
#include "banco.hpp"
#include "db.hpp"
#include "menu.hpp"

using namespace std;

Menu::Menu(){
    showMainMenu();
}
int Menu::getOption(){
    int option;
    system("cowsay -f tux 'Bienvenido al sistema bancario'"); //system("cowsay -f tux 'Bienvenido al sistema bancario'
    cout << "\nPor favor indique cual es el motivo de su visita\n";
    while( (cout << "1. Atencion\n2. Consulta\n3. Salir\n" && !(cin >> option)) || option < ATENCION|| option > SALIRMENU){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcion invalida, intente de nuevo\n";
    }
    return option;
}
int Menu::showMainMenu(){
    int option; 
    Banco banco;
    crearDB(); // Crear la base de datos
    

    do {
        system("clear");
        option = getOption();
        switch (option){
            case ATENCION:
                cout << "Atencion\n";
                banco.newSession();                
                
                break;
            case CONSULTA:
                cout << "Consulta\n";
                break;
            case SALIRMENU:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }
    } while (option != SALIRMENU);

    return 0;


}
