#ifndef BANCO_HPP
#define BANCO_HPP

#include <iostream>
#include <string>
#include <vector>
#include "entidadBancaria.hpp"

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
        static int callback(void *data, int argc, char **argv, char **azColName);     
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
        void agregarCliente(std::string nombre, std::string apellido);                     
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
        
         /**
         * @brief Metodo login

         */                                                 
        void login();
        /**
         * @brief Metodo para consultar clientes de la base de datos
         * @param nombre Nombre del cliente
         * @param apellido Apellido del cliente
         */
        void consultarClientes(std::string nombre, std::string apellido);
        /**
         * @brief Metodo para realizar un deposito entre cuentas
         * @param idCuentaD id de la cuenta de destino
         * @param idCuentaC id de la cuenta de origen
         * @param monto Monto a depositar
         */
        void depositoEntreCuentas(int idCuentaD, int idCuentaC, float monto);

};

#endif // BANCO_HPP