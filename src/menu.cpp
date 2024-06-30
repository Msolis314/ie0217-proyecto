/*! @file menu.cpp
 @brief Implementacion de la clase Menu
MIT License

Copyright (c) 2024 Msolis314

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <exception>

#include <limits>
#include <stdexcept>
#include "banco.hpp"
#include "db.hpp"
#include "consulta.hpp"
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
    updateFecha(); // Actualizar la fecha
    
    // Crear una instancia de Consulta
    Consulta consulta;
    

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
                consulta.mostrarMenuConsulta();
                
                break;
            case SALIRMENU:
                system("cowsay -f dragon 'Saliendo...'");
                
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }
    } while (option != SALIRMENU);
    cleanBankInfo();
    return 0;


}
