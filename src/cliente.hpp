/**
 * @file archivo de encabezado cliente.hpp
 * @brief Atributos y metodos para la clase Cliente
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
        int id;
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
         * @brief Agrega un prestamo al cliente.
         * @param idPrestamo ID del prestamo a agregar.
         */
        void agregarPrestamo(int idPrestamo);

        /**
         * @brief Consulta las cuentas del cliente.
         */
        void consultarCuentas();
        /**
         * @brief Consultar los prestamos del cliente.
         */
        void consultarPrestamos();
         /**
         * @brief Genera un  ID para una cuenta en colones.
         * @return El ID generado para la cuenta.
         */
        unsigned long int generarIDCuentaC();
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
        /**
         * @brief muestra menu para el cliente.
         */

        bool checkIDPrestamoExists(int idPrestamo);

        /// @brief  Metodo para obtener el IDs de la cuenta.
        /// @param moneda 
        /// @return 
        int getIDCuenta(Monedas moneda);

        /// @brief  Metodo para obtener el IDs de los prestamos.
        /// @return
        void getIDPrestamos();
        
        void mostrarMenuC();
        // void transaccion(float monto, Monedas moneda);
        // void operarPrestamo(float monto, Monedas moneda);

        /// @brief Desplegar el menu de transacciones
        void transaccion();


        /// @brief Metodo para consultar el saldo de las cuentas
        /// @details Consultar el saldo de las cuentas en colones , dolares o ambos
         void consultarSaldo();

         /// @brief  Metodo para transferir dinero entre cuentas
         void transferir();

        

};
#endif 