#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <iostream>
#include <string>
#include <vector>
#include "entidadBancaria.hpp"

class Cliente: public EntidadBancaria{
    private:
        std::string nombre;
        std::string apellido;
        int id;
        std::vector<int> cuentas;
        std::vector<int> prestamos;
    public:
        Cliente(std::string nombre, std::string apellido);
        void agregarCuenta(int idCuenta);
        void agregarPrestamo(int idPrestamo);
        void consultarCuentas();
        void consultarPrestamos();
        int generarIDCuenta();
        bool checkIDCuentaExists(int idCuenta); 
        // void transaccion(float monto, Monedas moneda);
        // void operarPrestamo(float monto, Monedas moneda);

};
#endif // CLIENTE_HPP