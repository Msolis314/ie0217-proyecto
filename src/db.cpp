#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <sqlite3.h>
#include "db.hpp"

#define TIPO_CAMBIO 540

int crearDB(){
    sqlite3 *db;
    char *zErrMsg = 0;
    //const char * data = "SQLite 3";
    int rc;
    
    // Abrir la base de datos
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return 1;
    }else{
        std::cout << std::endl;
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
        std::cout  << std::endl;
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
        std::cout << "\n..." << std::endl;
    }

    

    // Crear tabla de Cuenta Bancaria
    sql = "CREATE TABLE IF NOT EXISTS CUENTA_BANCARIA(" \
        "ID_CUENTA INT PRIMARY KEY NOT NULL," \
        "TIPO_MONEDA TEXT NOT NULL," \
        "AHORROS INT NOT NULL," \
        "ID_CLIENTE INT NOT NULL," \
        "FOREIGN KEY (ID_CLIENTE) REFERENCES CUSTOMERS(ID));"; // se usa la clave foranea
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "....." << std::endl;
    }
    // Crear tabla de transacciones.
    sql = "CREATE TABLE IF NOT EXISTS TRANSACCIONES(" \
    "NUM_TRAN INT NOT NULL," \
    "ID_CLIENTE INT NOT NULL," \
    "ID_CUENTA_ORIGEN INT NOT NULL," \
    "FECHA DATETIME NOT NULL," \
    "FOREIGN KEY (ID_CLIENTE) REFERENCES CUSTOMERS(ID)," \
    "FOREIGN KEY (ID_CUENTA_ORIGEN) REFERENCES CUENTA_BANCARIA(ID_CUENTA));";


    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "......." << std::endl;
    }

    // Tabla de historial de transacciones
    sql = "CREATE TABLE IF NOT EXISTS HISTORIAL_TRANSACCIONES ("
    "ID_TRANSACCION INTEGER PRIMARY KEY AUTOINCREMENT,"
    "ID_CLIENTE INT NOT NULL,"
    "TIPO_TRANSACCION TEXT NOT NULL,"
    "ID_CUENTA INT,"
    "ID_CUENTA_DESTINO INT,"
    "MONTO REAL,"
    "FECHA DATETIME NOT NULL,"
    "FOREIGN KEY (ID_CLIENTE) REFERENCES CUSTOMERS(ID),"
    "FOREIGN KEY (ID_CUENTA) REFERENCES CUENTA_BANCARIA(ID_CUENTA),"
    "FOREIGN KEY (ID_CUENTA_DESTINO) REFERENCES CUENTA_BANCARIA(ID_CUENTA)"
    ");";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "........" << std::endl;
    }

    // Tabla de historial de prestamos
    sql = "CREATE TABLE IF NOT EXISTS HISTORIA_PRESTAMOS ("
    "ID_HISTORIA INTEGER PRIMARY KEY AUTOINCREMENT,"
    "ID_CLIENTE INT NOT NULL,"
    "ID_PRESTAMO INT NOT NULL,"
    "MONTO REAL,"
    "FECHA DATETIME NOT NULL,"
    "FOREIGN KEY (ID_CLIENTE) REFERENCES CUSTOMERS(ID),"
    "FOREIGN KEY (ID_PRESTAMO) REFERENCES PRESTAMO(ID_PRESTAMO)"
    ");";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "........" << std::endl;
    }

    // Crear tabla de Prestamos
    sql = "CREATE TABLE IF NOT EXISTS PRESTAMO(" \
    "ID_PRESTAMO INT PRIMARY KEY NOT NULL," \
    "ID_CLIENTE INT NOT NULL," \
    "TIPO_CAMBIO TEXT NOT NULL," \
    "TIPO_INTERES TEXT NOT NULL," \
    "CUOTA REAL NOT NULL," \
    "PLAZO INT NOT NULL," \
    "INTERESES_ABONADOS REAL NOT NULL," \
    "TASA_INTERES REAL NOT NULL," \
    "CAPITAL_OG REAL NOT NULL," \
    "CAPITAL_ACTUAL REAL NOT NULL," \
    "FOREIGN KEY (ID_CLIENTE) REFERENCES CUSTOMERS(ID));";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "..........." << std::endl;
    }

    // Crear tabla para guardar las contraseñas
    sql = "CREATE TABLE IF NOT EXISTS PASSWORDS(" \
    "ID_CLIENTE INT PRIMARY KEY NOT NULL," \
    "PASSWORD TEXT NOT NULL," \
    "SALT TEXT NOT NULL," \
    "FOREIGN KEY (ID_CLIENTE) REFERENCES CUSTOMERS(ID));";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "............." << std::endl;
    }

    //Crear tabla de depositos a plazo
    sql = "CREATE TABLE IF NOT EXISTS DEPOSITO_PLAZO(" \
    "ID_DEPOSITO INT PRIMARY KEY NOT NULL," \
    "ID_CLIENTE INT NOT NULL," \
    "MONTO REAL NOT NULL," \
    "PLAZO INT NOT NULL," \
    "FECHA_INICIO DATETIME NOT NULL," \
    "FECHA_FIN DATETIME NOT NULL," \
    "FOREIGN KEY (ID_CLIENTE) REFERENCES CUSTOMERS(ID)," \
    "FOREIGN KEY (ID_DEPOSITO) REFERENCES CUENTA_BANCARIA(ID_CUENTA));";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "............" << std::endl;
    }
    

    sqlite3_close(db);
    system("clear");


    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

/*
int stringCallback(void *data, int argc, char **argv, char **azColName){
    std::string *str = (std::string*)data;
    *str = argv[0];
    return 0;

}


int intCallback(void *data, int argc, char **argv, char **azColName){
    int *value = (int*)data;
    if (argv[0]){
        *value = atoi(argv[0]);
    }
    return 0;
}
*/
std::string getFecha(){
    time_t now = time(0);
    char *dt = ctime(&now);
    return dt;
}


int updateFecha(){
    std::string fecha;
    time_t t = time(nullptr);
    std::tm* date = std::localtime(&t);
    int year = date->tm_year + 1900;
    int month = date->tm_mon + 1; 
    int day = date->tm_mday;
    std::string  yearMonth = std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "...." << std::endl;
    }

    std::string sql = "INSERT INTO BANKINFO (FECHA, TIPO_CAMBIO, TASA_BANCO_CENTRAL) VALUES ('" + yearMonth + "', " + std::to_string(TIPO_CAMBIO) + ", 0.05);";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return 0;
}


int cleanBankInfo(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "...." << std::endl;
    }

    std::string sql = "DELETE FROM BANKINFO";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return 0;
}