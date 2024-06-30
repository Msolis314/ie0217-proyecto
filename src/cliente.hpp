/*! @file cliente.hpp
 @brief Header file de la clase Cliente
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
#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <iostream>
#include <string>
#include <vector>
#include "entidadBancaria.hpp"



/**
 * @brief Mostrar en el menu de opciones para el cliente.
 * @return opcion seleccionada por el cliente.
 */
int menu_cliente();
/**
 * @enum MenuOptionsC
 * @brief opciones que puede seleccionar el cliente.
 */
enum MenuOptionsC{
/**
 * 
 * @brief opcion generar id cuenta.
 */
    GEN_ID_CUENTA = 1,
/**
 * 
 * @brief opcion transaccion.
 */
    TRANS = 2,
/**
 * 
 * @brief salir.
 */
    SALIRMENUC = 3
};


/**
 * @class Cliente
 * @brief es un cliente de una entidad bancaria.
 */
class Cliente: public EntidadBancaria{
    private:
        std::string nombre;
        std::string apellido;
        int id =0;
        int idCuentaC = 0;
        int idCuentaD = 0;
        std::vector<int> prestamos;

    public:
        //Declarar la clase operaciones como amiga de la clase cliente
        friend class Operaciones;
        friend class Prestamos; 
        friend class CDP;
            /**
         * @brief constructor de la clase cliente.
         * @param nombre nombre del cliente.
         * @param apellido Apellido del cliente.
         * @param id ID del cliente.
         */
        Cliente(std::string nombre, std::string apellido, int id);

        /**
         * @brief Agrega una cuenta al cliente en colones.
         * @param idCuentaC ID de la cuenta agregar.
         */
        void agregarCuentaC(int idCuentaC);
        /**
         * @brief Agrega una cuenta al cliente en dolares.
         * @param idCuentaC ID de la cuenta agregar.
         */
        void agregarCuentaD(int idCuentaD);
       

        /**
         * @brief Consulta las cuentas del cliente.
         */
        void consultarCuentas();
        
         /**
         * @brief Genera un  ID para una cuenta en colones.
         * @return El ID generado para la cuenta.
         */
         int generarIDCuentaC();
         /**
         * @brief Genera un  ID para una cuenta en dolares.
         * @return El ID generado para la cuenta.
         */
        int generarIDCuentaD();
        /**
         * @brief verifica si un ID de cuenta existe.
         * @param idCuenta ID a verificar.
         * @param moneda tipo de moneda de la cuenta.
         * @return true si el ID de la cuenta existe, false en caso contrario
         */
        bool checkIDCuentaExists(int idCuenta, Monedas moneda);
       

        /// @brief  Metodo para obtener el IDs de la cuenta.
        /// @param moneda 
        /// @return 
        int getIDCuenta(Monedas moneda);

        
        
        void mostrarMenuC();
        // void transaccion(float monto, Monedas moneda);
        // void operarPrestamo(float monto, Monedas moneda);

        /// @brief Desplegar el menu de transacciones
        void transaccion();


        /// @brief Metodo para consultar el saldo de las cuentas
        /// @details Consultar el saldo de las cuentas en colones , dolares o ambos
         void consultarSaldo();

         

        

};
#endif 