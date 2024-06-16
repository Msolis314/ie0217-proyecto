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


Cliente::Cliente(std::string nombre, std::string apellido) {
    this->nombre = nombre;
    this->apellido = apellido;
    
}

// Generando menu

void Cliente::mostrarMenuC() {
    int opc;
    do {
        std::cout << "------ Menú del Cliente ------" << std::endl;
        std::cout << "1. Generar ID de cuenta" << std::endl;
        std::cout << "2. Realizar transacciones" << std::endl;
        std::cout << "3. Salir del menú" << std::endl;
        std::cout << "Elija una opción: ";
        std::cin >> opc;

        switch (opc) {
           case 1:
                {
                    // Submenú para elegir el tipo de cuenta del usuario
                    int opcionTipoCuenta;
                    do {
                        std::cout << "Por favor, seleccione el tipo de cuenta que desea adquirir:" << std::endl;
                        std::cout << "1. Cuenta en dólares" << std::endl;
                        std::cout << "2. Cuenta en colones" << std::endl;
                        std::cout << "Elija una opción: ";
                        std::cin >> opcionTipoCuenta;

                        if (opcionTipoCuenta == 1) {
                            int id_newD;
                            agregarCuentaD(id_newD);
                            std::cout << "Cuenta exitosamente agregada en dólares." << std::endl;

                        } else if (opcionTipoCuenta == 2) {
                            int id_newC;
                            agregarCuentaC(id_newC);
                            std::cout << "Cuenta exitosamente agregada en colones." << std::endl;
                        } else {
                            std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                        }
                    } while (opcionTipoCuenta != 1 && opcionTipoCuenta != 2);
                }
                break;
            case TRANS:
                std::cout << "**********************************************" << std::endl;
                std::cout << "*** Bienvenida al sistema de transacciones.***" << std::endl;
                std::cout << "**********************************************" << std::endl;
                break;
            case SALIRMENUC:
                std::cout << "Saliendo del menú del cliente..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
        }
    } while (opc != SALIRMENUC);
}







// IMplementacion del metodo para agregar un numero de cuenta.
void Cliente::agregarCuentaC(int idCuentaC) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return;
    }

    // Generar un nuevo ID de cuenta
    int id_cuentaC = generarIDCuenta();

    // Preparar la consulta SQL para insertar el ID de cuenta en colones
    std::string sql = "INSERT INTO CUSTOMERS(ID_CUENTA_C) VALUES (" + std::to_string(id_cuentaC) + ");";
    const char* data = sql.c_str();

    // Ejecutar la consulta SQL
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al insertar el ID de cuenta en colones: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "ID de cuenta en colones agregado exitosamente." << std::endl;
    }

    sqlite3_close(db);
}


// IMplementacion del metodo para agregar un numero de cuenta.
void Cliente::agregarCuentaD(int idCuentaD) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return;
    }

    // Generar un nuevo ID de cuenta
    int id_cuentaD = generarIDCuenta();

    // Preparar la consulta SQL para insertar el ID de cuenta en colones
    std::string sql = "INSERT INTO CUSTOMERS(ID_CUENTA_D) VALUES (" + std::to_string(id_cuentaD) + ");";
    const char* data = sql.c_str();

    // Ejecutar la consulta SQL
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al insertar el ID de cuenta en dolares: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "ID de cuenta en dolares agregado exitosamente." << std::endl;
    }

    sqlite3_close(db);
}




int Cliente::generarIDCuenta() {
// definiendo un rango
    long int minDigits = 1000000000000000; // si queremos que contenga al menos 16 digitos 
    long int maxDigits = 9999999999999999;  

    int idnum = minDigits + rand() % (maxDigits - minDigits + 1); // generamos un numero aleatorio y tomamos el resto del modulo entero

    // Verificar si el ID generado ya existe en la base de datos
    while (checkIDCuentaExists(idnum)) {
        // Si el ID ya existe, generamos otro número aleatorio y lo volvemos a probar
        idnum = minDigits + rand() % (maxDigits - minDigits + 1);
    }
    return idnum;
}



bool Cliente::checkIDCuentaExists(int idCuenta) {
    sqlite3 *db;
    int rc;                                           // verificador de que la todo funciona
    char* zErrMsg = 0;                                // Manejo de errores
    bool found = false;                               // generar una variable que me indique si se encontro en la base de datos

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return false;
    } else {
        std::cout << "Base de datos abierta con exito" << std::endl;
    }
    
    std::string sql = "SELECT COUNT(*) FROM CUSTOMERS WHERE ID_CUENTA_C = " + std::to_string(idCuenta); // se va buscar en el parametro que se le pase

    rc = sqlite3_exec(db, sql.c_str(), [](void* foundPtr, int argc, char** argv, char** azColName) -> int {
        bool* found = static_cast<bool*>(foundPtr);                                                             // 
        *found = (argc > 0 && std::stoi(argv[0]) > 0); // Verifica si se encontró alguna fila y si el valor de COUNT(*) es mayor que 0
        return 0;                                      // si todo bien, retorna cero
    }, &found, &zErrMsg);                              

    if (rc != SQLITE_OK) {                                                                 
        std::cerr << "Error en la consulta SQL: " << zErrMsg << std::endl; // mensaje de error
        sqlite3_free(zErrMsg);                          // liberar memoria            
    }

    return found;                                      // devuelve true si se encontro en la base de datos, fase si no
}



void Cliente::agregarPrestamo(int idPrestamo) {
    // xxxx
}

void Cliente::consultarCuentas() {
    // xxxx
}

void Cliente::consultarPrestamos() {
    // xxxx
}