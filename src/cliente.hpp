#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <iostream>
#include <string>
#include <vector>
#include "entidadBancaria.hpp"




int menu_cliente();
enum MenuOptionsC{
    GEN_ID_CUENTA = 1,
    TRANS = 2,
    SALIRMENUC = 3
};



class Cliente: public EntidadBancaria{
    private:
        std::string nombre;
        std::string apellido;
        int id;
        std::vector<int> cuentas;
        std::vector<int> prestamos;
    public:
        Cliente(std::string nombre, std::string apellido);
        void agregarCuentaC(int idCuentaC);
        void agregarCuentaD(int idCuentaD);
        void agregarPrestamo(int idPrestamo);
        void consultarCuentas();
        void consultarPrestamos();
        int generarIDCuenta();
        bool checkIDCuentaExists(int idCuenta); 
        void mostrarMenuC();
        // void transaccion(float monto, Monedas moneda);.
        // void operarPrestamo(float monto, Monedas moneda);

};
#endif // CLIENTE_HPP