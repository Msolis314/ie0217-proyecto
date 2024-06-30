
/*! @file banco.hpp
 @brief Header de la clase Banco
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

#ifndef BANCO_HPP
#define BANCO_HPP

#include <iostream>
#include <string>
#include <vector>
#include "entidadBancaria.hpp"

enum LoginMenu{
    LOGIN = 1,
    REGISTRO,
    SALIR
};

/**
 * @brief Clase que representa un banco.
 */
class Banco: public EntidadBancaria{
    protected:
        /**
         * @brief lista o vector de los IDs actual
         */
        std::vector<int> actualIDs;         
        /**
         * @brief lista o vector de los IDs prestamos actuales
         */
        std::vector<int> actualIDPrestamos; 
        /**
         * @brief lista o vector de los IDs cuentas actuale
         */
        std::vector<int> actualIDCuentas; 

        // Datos del cliente actual

        int idCliente;
        std::string nombreCliente;
        std::string apellidoCliente;
    public:
        /**
         * @brief constructor
         */  
        Banco(); 
        /**
         * @brief Método para establecer los IDs actuales
         */
        void setActualIDs();
        /**
         * @brief callback
         */
        static int callbackIDs(void *data, int argc, char **argv, char **azColName);     
        /**
         * @brief Callback  consultando a prestamos
         */      

        static int callbackPrestamos(void *data, int argc, char **argv, char **azColName);  
        /**
         * @brief Callback  consultando a cuentas
         */      

        static int callbackCuentas(void *data, int argc, char **argv, char **azColName);    
        /**
         * @brief Callback  consultando a clientes
         */ 
        static int callbackClientes(void *data, int argc, char **argv, char **azColName);  
        /**
         * @brief Metodo para los IDs de préstamos actuales 
         */ 
        void setActualIDPrestamos(); 
        /**
         * @brief Metodo para los IDs de cuentas actuales 
         */                                                               
        void setActualIDCuentas();                                                          
        /**
         * @brief Metodo para agregar cliente
         * @param nombre Nombre del cliente
         * @param apellido Apellido del cliente
         */
        void agregarCliente(std::string nombre, std::string apellido,std::string password);                     
        /**
         * @brief Metodo para generar los id de los clientes
         */
        int generarID();            
         /**
         * @brief Metodo para verificar los ids
         * @param id ID a verificar
         * @return verdad si el ID existe, falso si no existe en la tabla de customers
         */                                                              
        bool checkIDExists(int id); 

        /// @brief  Metodo para verificar si un cliente con esos nombres y apellidos ya existe con ese ID
        /// @param nombre nombre del cliente
        /// @param apellido  apellido del cliente
        /// @param id id del cliente
        /// @return verdadero si el cliente ya existe, falso si no existe
        bool checkID(std::string nombre, std::string apellido,int id);

        /// @brief Método para agregar un ID a la lista de IDs actuales
        void agregarID(int id);

        /// @brief Metodo para validar si la ID es válida
        /// @param id entrada de la ID
        /// @return  verdadero si la ID es válida, falso si no lo es
        bool validarID(std::string id);
        
         /**
         * @brief Metodo login

         */                                                 
        void login();
        /**
         * @brief Metodo para consultar clientes de la base de datos
         * @param nombre Nombre del cliente
         * @param apellido Apellido del cliente
         */
        bool consultarClientes(std::string nombre, std::string apellido);
        /**
         * @brief Metodo para realizar un deposito entre cuentas
         * @param idCuentaD id de la cuenta de destino
         * @param idCuentaC id de la cuenta de origen
         * @param monto Monto a depositar
         */
        void depositoEntreCuentas(int idCuentaD, int idCuentaC, float monto);

        /// @brief Método para validar el string del nombre o apellido
        /// @param nombre Nombre o apellido a validar
        /// @return true si el nombre o apellido es válido, false si no lo es
        bool validarNombre(std::string nombre);

        /// @brief Método para validar la contraseña
        /// @param contrasena Contraseña a validar
        /// @return true si la contraseña es válida, false si no lo es
        bool validarContrasena(std::string contrasena);

        /// @brief Método para verificar si un cliente existe
        /// @param nombre Nombre del cliente
        /// @param apellido Apellido del cliente
        /// @return true si el cliente existe, false si no existe
        bool checkifClienteExists(std::string nombre, std::string apellido, std::string id);

        /// @brief Nueva sesión de la clase Banco
        void newSession();


        /// @brief  Metodo para registrar un nuevo cliente
        void signUp();

};

#endif // BANCO_HPP