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


Cliente::Cliente(std::string nombre, std::string apellido, int id) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->id = id;
    
}

// Generando menu

void Cliente::mostrarMenuC() {
    int opc;
    do {
        std::cout << "------ Menú del Cliente ------" << std::endl;
        std::cout << "1. Agregar Cuenta" << std::endl;
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
                        std::cout << "1. Cuenta en colones" << std::endl;
                        std::cout << "2. Cuenta en dólares" << std::endl;

                        std::cout << "Elija una opción: ";
                        std::cin >> opcionTipoCuenta;

                        if (opcionTipoCuenta == DOLAR) {
                            int id_newD = generarIDCuentaD();
                            agregarCuentaD(id_newD);
                            std::cout << "Cuenta exitosamente agregada en dólares." << std::endl;

                        } else if (opcionTipoCuenta == COLON) {
                            int id_newC = generarIDCuentaC();
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
    return;
}







// IMplementacion del metodo para agregar un numero de cuenta.
void Cliente::agregarCuentaC(int idCuentaC) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cout << "...." << std::endl;
        return;
    }

    // Generar un nuevo ID de cuenta
    int id_cuentaC = generarIDCuentaC();

    // Preparar la consulta SQL para insertar el ID de cuenta en colones
    std::string sql= "UPDATE CUSTOMERS SET ID_CUENTA_C = " + std::to_string(id_cuentaC) + " WHERE ID = " + std::to_string(id) + ";";
    const char* data = sql.c_str();

    // Ejecutar la consulta SQL
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al insertar el ID de cuenta en colones: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "ID de cuenta en colones agregado exitosamente." << std::endl;
    }

    //Insertar id en la tabla de cuentas
    sql = "INSERT INTO CUENTA_BANCARIA(ID_CUENTA,TIPO_MONEDA,AHORROS,ID_CLIENTE) VALUES (" + std::to_string(id_cuentaC) + ",'colones',0," + std::to_string(id) + ");";
    data = sql.c_str();

    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al insertar el ID de cuenta en la tabla de cuentas: " << zErrMsg << std::endl;
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
    int id_cuentaD = generarIDCuentaD();

    // Preparar la consulta SQL para insertar el ID de cuenta en dólares
    std::string sql= "UPDATE CUSTOMERS SET ID_CUENTA_D = " + std::to_string(id_cuentaD) + " WHERE ID = " + std::to_string(id) + ";";
    const char* data = sql.c_str();

    // Ejecutar la consulta SQL 
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al insertar el ID de cuenta en dólares: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "ID de cuenta en dólares agregado exitosamente." << std::endl;
    }

    //Insertar id en la tabla de cuentas
    sql = "INSERT INTO CUENTA_BANCARIA(ID_CUENTA,TIPO_MONEDA,AHORROS,ID_CLIENTE) VALUES (" + std::to_string(id_cuentaD) + ",'dolares',0," + std::to_string(id) + ");";
    data = sql.c_str();

    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al insertar el ID de cuenta en la tabla de cuentas: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "ID de cuenta en dólares agregado exitosamente." << std::endl;
    }

    sqlite3_close(db);
}




int Cliente::generarIDCuentaC() {
// definiendo un rango
    long int minDigits = 1000000000000000; // si queremos que contenga al menos 16 digitos 
    long int maxDigits = 9999999999999999;  

    int idnum = minDigits + rand() % (maxDigits - minDigits + 1); // generamos un numero aleatorio y tomamos el resto del modulo entero

    // Verificar si el ID generado ya existe en la base de datos
    while (checkIDCuentaExists(idnum,COLON)) {
        // Si el ID ya existe, generamos otro número aleatorio y lo volvemos a probar
        idnum = minDigits + rand() % (maxDigits - minDigits + 1);
    }
    return idnum;
}

int Cliente::generarIDCuentaD() {
    // definiendo un rango
    long int minDigits = 10000; // si queremos que contenga al menos 5 digitos                                          
    long int maxDigits = 99999;  

    int idnum = minDigits + rand() % (maxDigits - minDigits + 1); // generamos un numero aleatorio y tomamos el resto del modulo entero

    // Verificar si el ID generado ya existe en la base de datos
    while (checkIDCuentaExists(idnum,DOLAR)) {
        // Si el ID ya existe, generamos otro número aleatorio y lo volvemos a probar
        idnum = minDigits + rand() % (maxDigits - minDigits + 1);
    }
    return idnum;
}


bool Cliente::checkIDCuentaExists(int idCuenta,Monedas moneda) {
    sqlite3 *db;
    int rc;                                           // verificador de que la todo funciona
    char* zErrMsg = 0;                                // Manejo de errores
    bool found = false;                             // generar una variable que me indique si se encontro en la base de datos
    std::string sql;                                  // variable para la consulta SQL
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return false;
    } else {
        std::cout << "...." << std::endl;
    }

    if (moneda == DOLAR) {
        sql = "SELECT COUNT(*) FROM CUSTOMERS WHERE ID_CUENTA_D = " + std::to_string(idCuenta); // se va buscar en el parametro que se le pase
    } else {
        sql = "SELECT COUNT(*) FROM CUSTOMERS WHERE ID_CUENTA_C = " + std::to_string(idCuenta); // se va buscar en el parametro que se le pase
    }

    
    rc = sqlite3_exec(db, sql.c_str(), [](void* foundPtr, int argc, char** argv, char** azColName) -> int {
        bool* found = static_cast<bool*>(foundPtr);                                                             // 
        *found = (argc > 0 && std::stoi(argv[0]) > 0); // Verifica si se encontró alguna fila y si el valor de COUNT(*) es mayor que 0
        return 0;                                      // si todo bien, retorna cero
    }, &found, &zErrMsg);                              

    if (rc != SQLITE_OK) {                                                                 
        std::cerr << "Error en la consulta SQL: " << zErrMsg << std::endl; // mensaje de error
        sqlite3_free(zErrMsg);                          // liberar memoria            
    }

    return found;                                      // devuelve true si se encontro en la base de datos, fase si no.
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