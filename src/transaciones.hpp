/*! @file transacciones.hpp
 @brief Header file de la clase Operaciones
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


        /// @brief Obtener fecha y hora.
        /// @return Fecha y hora en formato de cadena.
        std::string obtenerFechaHoraActual();


        /// @brief Registro de transacciones en base de datos.
        /// @param idCliente id del cliente en sesión.
        /// @param tipoTransaccion Clasificacion de la transacción.
        /// @param idCuenta ID de la cuenta del cliente en sesión.
        /// @param idCuentaDestino ID de la cuenta destino en caso de transferencia.
        /// @param monto Cantidad de dinero involucrado en la transacción.
        /// @param moneda Moneda de la transacción.
        void registrarTransaccion(int idCliente, const std::string& tipoTransaccion, int idCuenta, int idCuentaDestino, float monto, const std::string& moneda);


        /// @brief Imprimir historial de transacciones del usuario.
        /// @param idCliente id del cliente en sesión.
        void imprimirHistorialTransacciones(int IdCliente);

        /// @brief Imprimir historial de transferencias rebicidas por el usuario.
        /// @param idCliente id del cliente en sesión.
        void imprimirHistorialTransferenciasRecibidas(int idCliente);


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