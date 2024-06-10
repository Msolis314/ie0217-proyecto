// Librerias
#include "db.hpp"
#include "banco.hpp"
#include <iostream>

int main(){
    // llamada de funciones
    crearDB();                            
    Banco banco;
    banco.login();
    // agregando clientes 
    banco.agregarCliente("Juan", "Perez");
    return 0;
}
