#ifndef TRANSACCIONES_HPP //TRANSACCIONES_HPP
#define TRANSACCIONES_HPP

#include <iostream>
#include <string>
#include <sqlite3.h>
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "cliente.hpp"

struct functionVars{
    int opcion;
    float monto;
    std::string dato;
    int tries;
    int rightChoice;
    sqlite3 *db;
    std::string sql;
    char *zErrMsg = 0;
    int rc;

} typedef functionVars;

/// @brief Clase que realiza las operaciones bancarias.
/// @details Esta clase realiza las operaciones bancarias como depositar, retirar, transferir, pagar prestamo, solicitar prestamo, consultar saldo, escribir historial, consultar movimientos y consultar prestamos.
//// @note Esta clase es amiga de la clase Cliente y esta hecha para interactuar con ella.
class Operaciones {
    private:
        std::string tipo;
        std::string fecha;
        std::string hora;
        float monto;
        Cliente cliente;
        int idCuentaDestino;
    public:
        /// @brief Constructor de la clase Operaciones.
        /// @param nombre Nombre del cliente.
        /// @param apellido Apellido del cliente.
        /// @param id ID del cliente.
        Operaciones(std::string nombre,std::string apellido,int id);

        /// @brief Depositar dinero en la cuenta.
        /// @param cambio Monedas de cambio DOLAR o COLON.
        /// @param monto Monto a depositar.
        void depositar(Monedas cambio, float monto);

        /// @brief Retirar dinero de la cuenta.
        /// @param cambio Monedas de cambio DOLAR o COLON.
        /// @param monto Monto a retirar.
        void retirar(Monedas cambio, float monto);
        void transferir();
        void pagarPrestamo();
        void solicitarPrestamo();

        /// @brief Consultar el saldo de la cuenta.
        /// @param idCuenta ID de la cuenta.
        /// @return Saldo de la cuenta.
        float consultarSaldo(int idCuenta);

        /// @brief Escribir el historial de las transacciones.
        void escribirHistorial();

        /// @brief  Verificar si la cuenta tiene la moneda correcta.
        /// @param idCuenta 
        /// @return  1 si la cuenta es de la moneda correcta, 0 si no lo es.
        int checkAcountCurrency(int idCuenta);

        void consultarMovimientos();
        void consultarPrestamos();

        /// @brief  Pedir el monto de la transaccion.
        /// @param monto 
        /// @return  1 si el monto es valido, 0 si no lo es.
        int pedirMonto(float &monto);


};
#endif //TRANSACCIONES_HPP