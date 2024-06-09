#ifndef BANCO_HPP
#define BANCO_HPP

#include <iostream>
#include <string>
#include <vector>
#include "entidadBancaria.hpp"


class Banco: public EntidadBancaria{
    protected:
        std::vector<int> actualIDs;
        std::vector<int> actualIDPrestamos;
        std::vector<int> actualIDCuentas;
    public:
        Banco();
        void setActualIDs();
        static int callback(void *data, int argc, char **argv, char **azColName);

        static int callbackPrestamos(void *data, int argc, char **argv, char **azColName);
        static int callbackCuentas(void *data, int argc, char **argv, char **azColName);
        static int callbackClientes(void *data, int argc, char **argv, char **azColName);
        
        void setActualIDPrestamos();
        void setActualIDCuentas();
        void agregarCliente(std::string nombre, std::string apellido);
        int generarID();
        bool checkIDExists(int id);
        void login();
        
        void consultarClientes(std::string nombre, std::string apellido);
        void depositoEntreCuentas(int idCuentaD, int idCuentaC, float monto);

};

#endif // BANCO_HPP