// Incluyendo las librerias
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sqlite3.h>
#include "entidadBancaria.hpp"
#include "banco.hpp"
#include "db.hpp"
#include "cliente.hpp"


// IMplementacion del metodo para agregar un numero de cuenta.
void Cliente::agregarCuenta(int idCuenta){
    sqlite3 *db;                                                        // generando puntero.
    char *zErrMsg = 0;                                                  // mensaje de error.
    int rc;                                                             // inicializando variable de retorno.

    rc = sqlite3_open("SistemaBancario.db", &db);                       // abriendo la base de datos sistema bancario
    if (rc){                                                            // if para verificar que se abrio correctamente
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }
    
    int id = generarIDCuenta();            

   // Haciendo una consulta SQL para insertar una nueva cuenta bancaria
    std::string sql = "INSERT INTO  CUENTA_BANCARIA(ID_CUENTA) VALUES (" + std::to_string(idCuenta) + ");";
    const char* data = sql.c_str();                                     // Usando Sqlite
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);                     // Ejecutando la consulta
    if (rc != SQLITE_OK){                                               // si todo se ejecuta bien en el if, el cliente se agrega con exito, sino msj error
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Id cuenta agregada exitosamente" << std::endl;    // Numero de cuenta agregado.
    }

}







// generando el numero de cuenta del cliente.
int Cliente::generarIDCuenta(){
    // Generar un número aleatorio que funcione como un id unico
    int idCuenta = rand() * (RAND_MAX + 1) + rand();

    // Verificar si el ID generado ya existe en la base de datos
    while (checkIDCuentaExists(idCuenta)) {
        // Si el ID ya existe, generamos otro número aleatorio y lo volvemos a probar
        idCuenta = rand() * (RAND_MAX + 1) + rand();
    }

    return idCuenta;
}




bool Cliente::checkIDCuentaExists(int idCuenta) {
    std::vector<int>::iterator it;
    // Recorre la lista de IDs de cuentas y verifica si alguno coincide con el ID proporcionado.
    for (it = .begin(); it != actualIDCuentas.end(); it++) {                                  // FALTA DEFINIR COSAS
        if (*it == idCuenta) {
            return true; // Si encuentra un ID igual, devuelve true.
        }
    }
    return false; // Si no se encuentra ningún ID igual, devuelve false.
}

