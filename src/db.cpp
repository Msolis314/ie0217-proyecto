#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sqlite3.h>
#include "db.hpp"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int crearDB(){
    sqlite3 *db;
    char *zErrMsg = 0;
    const char * data = "SQLite 3";
    int rc;
    
    // Abrir la base de datos
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return 1;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }
    // Crear tabla de Clientes

    const char* sql = "CREATE TABLE IF NOT EXISTS CUSTOMERS(" \
        "ID INT PRIMARY KEY    NOT NULL," \
        "NOMBRE           TEXT    NOT NULL," \
        "APELLIDO       TEXT    NOT NULL," \
        "ID_PRESTAMO_C   INT ," \
        "ID_CUENTA_C    INT ," \
        "ID_PRESTAMO_D   INT ," \
        "ID_CUENTA_D    INT     );";
    
    /* sqlite3_exec() ejecuta una sentencia SQL
    * db: la base de datos
    * sql: la sentencia SQL
    * callback: la funcion que se llama para cada fila del resultado
    * 0: el primer argumento de la funcion de callback
    * &zErrMsg: mensaje de error
    * 
    */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Tabla de clientes creada con exito" << std::endl;
    }

    // Crear tabla de informacion Bancaria
    sql = "CREATE TABLE IF NOT EXISTS BANKINFO(" \
        "FECHA           TEXT    NOT NULL," \
        "TIPO_CAMBIO    REAL    NOT NULL," \
        " TASA_BANCO_CENTRAL NOT NULL);";
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Tabla de informacion bancaria creada con exito" << std::endl;
    }

    return 0;
}