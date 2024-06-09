#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sqlite3.h>
#include "entidadBancaria.hpp"
#include "banco.hpp"
#include "db.hpp"
#include "cliente.hpp"

Banco::Banco(){
    setActualIDs();
    setActualIDPrestamos();
    setActualIDCuentas();
}
void Banco::setActualIDs(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    const char* sql = "SELECT ID FROM CUSTOMERS";
    rc = sqlite3_exec(db, sql, callback, this, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "IDs obtenidos con exito" << std::endl;
    }

    
};

void Banco::setActualIDCuentas(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    const char* sql = "SELECT ID_CUENTA FROM CUSTOMERS";
    rc = sqlite3_exec(db, sql, callbackCuentas, this, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "IDs de cuentas obtenidos con exito" << std::endl;
    }

    
};  
int Banco::callback(void *data, int argc, char **argv, char **azColName){
    int i;
    Banco* banco = static_cast<Banco*>(data);
    for(i = 0;i <argc; i++){
        banco->actualIDs.push_back(std::stoi(argv[i]));

    }
}

int Banco::callbackPrestamos(void *data, int argc, char **argv, char **azColName){
    int i;
    Banco* banco = static_cast<Banco*>(data);
    for(i = 0;i <argc; i++){
        banco->actualIDPrestamos.push_back(std::stoi(argv[i]));

    }
}

int Banco::callbackCuentas(void *data, int argc, char **argv, char **azColName){
    int i;
    Banco* banco = static_cast<Banco*>(data);
    for(i = 0;i <argc; i++){
        banco->actualIDCuentas.push_back(std::stoi(argv[i]));

    }
}

int Banco::callbackClientes(void *data, int argc, char **argv, char **azColName){
    int i;
    Banco* banco = static_cast<Banco*>(data);
    if (argc == 0){
        std::cout << "No se encontraron clientes con esos datos" << std::endl;
        return 1;
    } else {
        return 0;
    }
}



void Banco::setActualIDPrestamos(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    const char* sql = "SELECT ID_PRESTAMO_C FROM CUSTOMERS";
    rc = sqlite3_exec(db, sql, callbackPrestamos, this, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "IDs de prestamos obtenidos con exito" << std::endl;
    }

    
};

int Banco::generarID(){
    int id = 0;
    while (true){
        if (!checkIDExists(id)){
            return id;
        }
        id++;
    }
}

bool Banco::checkIDExists(int id){
    std:: vector<int>:: iterator it;
    for (it = actualIDs.begin(); it != actualIDs.end(); it++){
        if (*it == id){
            return true;
        }
    }
    return false;
}
void Banco::agregarCliente(std::string nombre, std::string apellido){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    int id = generarID();
    std::string sql = "INSERT INTO CUSTOMERS (ID, NOMBRE, APELLIDO) VALUES (" + std::to_string(id) + ", '" + nombre + "', '" + apellido + "');";
    const char* data = sql.c_str();
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Cliente agregado con exito" << std::endl;
    }


    sqlite3_close(db);
    this->actualIDs.push_back(id);
}

void Banco::consultarClientes(std::string nombre, std::string apellido){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    std::string sql = "SELECT * FROM CUSTOMERS WHERE NOMBRE = '" + nombre + "' AND APELLIDO = '" + apellido + "';";
    const char* data = sql.c_str();
    rc = sqlite3_exec(db, data, callbackClientes, this, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "No se encontraron clientes con esos datos " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else {
        std::cout << "Consulta realizada con exito" << std::endl;
    }
    

}

void Banco::login(){
    std::string nombre;
    std::string apellido;
    std::cout << "Ingrese su nombre: ";
    std::cin >> nombre;
    std::cout << "Ingrese su apellido: ";
    std::cin >> apellido;
    consultarClientes(nombre, apellido);
}