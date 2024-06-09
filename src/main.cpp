#include "db.hpp"
#include "banco.hpp"
#include <iostream>

int main(){
    crearDB();
    Banco banco;
    banco.login();
    banco.agregarCliente("Juan", "Perez");
    return 0;
}
