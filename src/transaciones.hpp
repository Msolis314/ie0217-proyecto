#ifndef TRANSACCIONES_HPP //TRANSACCIONES_HPP
#define TRANSACCIONES_HPP

#include <iostream>
#include <string>
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "cliente.hpp"

class Operaciones {
    private:
        std::string tipo;
        std::string fecha;
        std::string hora;
        float monto;
        Cliente cliente;
        int idCuentaDestino;
    public:
        Operaciones(std::string nombre,std::string apellido,int id);

        // Depositar dinero en la cuenta.
        void depositar(Monedas cambio, float monto);
        void retirar(Monedas cambio, float monto);
        void transferir();
        void pagarPrestamo();
        void solicitarPrestamo();
        float consultarSaldo(int idCuenta);
        void escribirHistorial();
        void consultarMovimientos();
        void consultarPrestamos();


};
#endif //TRANSACCIONES_HPP