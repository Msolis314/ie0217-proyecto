// Incluyendo las librerias
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sqlite3.h>
#include <stdexcept>
#include <sstream>
#include <type_traits>
#include "entidadBancaria.hpp"
#include "banco.hpp"
#include "db.hpp"
#include "cliente.hpp"
#include "transaciones.hpp"


Cliente::Cliente(std::string nombre, std::string apellido, int id) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->id = id;
    this ->  idCuentaC= getIDCuenta(COLON);
    this ->  idCuentaD= getIDCuenta(DOLAR);

    
}

// Generando menu

void Cliente::mostrarMenuC() {
    int opc;
    do {
        std::cout << "\n------ Menú del Cliente ------" << std::endl;
        std::cout << "1. Agregar Cuenta" << std::endl;
        std::cout << "2. Realizar transacciones" << std::endl;
        std::cout << "3. Salir del menú" << std::endl;
        std::cout << "Elija una opción: ";
        do {
            std::cin >> opc;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
            }
        } while (std::cin.fail());

        switch (opc) {
           case 1:
                {
                    // Submenú para elegir el tipo de cuenta del usuario
                    int opcionTipoCuenta;
                    do {
                        std::cout << "\nPor favor, seleccione el tipo de cuenta a adquirir:" << std::endl;
                        std::cout << "1. Cuenta en colones" << std::endl;
                        std::cout << "2. Cuenta en dólares" << std::endl;

                        std::cout << "Elija una opción: ";
                        std::cin >> opcionTipoCuenta;

                        if (opcionTipoCuenta == DOLAR) {
                            int id_newD = generarIDCuentaD();
                            agregarCuentaD(id_newD);
                            

                        } else if (opcionTipoCuenta == COLON) {
                            int id_newC = generarIDCuentaC();
                            agregarCuentaC(id_newC);
                            
                        } else {
                            std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                        }
                    } while (opcionTipoCuenta != 1 && opcionTipoCuenta != 2);
                }
                break;
            case TRANS:
                std::cout << "\n**********************************************" << std::endl;
                std::cout << "*** Bienvenido al sistema de transacciones.***" << std::endl;
                std::cout << "**********************************************" << std::endl;
                transaccion();
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

    //No puede haber mas de una cuenta en colones
    if (this->idCuentaC != 0) {
        std::cout << "El cliente ya tiene una cuenta en colones." << std::endl;
        return;
    }
    
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

    this->idCuentaC = id_cuentaC;
    sqlite3_close(db);
}


// IMplementacion del metodo para agregar un numero de cuenta.
void Cliente::agregarCuentaD(int idCuentaD) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    //No puede haber mas de una cuenta en dolares
    if (this->idCuentaD != 0) {
        std::cout << "El cliente ya tiene una cuenta en dólares." << std::endl;
        return;
    }

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

    this->idCuentaD = id_cuentaD;

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


int Cliente::getIDCuenta(Monedas moneda){
    sqlite3 *db;
    int rc;
    char* zErrMsg = 0;
    int idCuenta = 0; // Initialize idCuenta to 0
    std::string sql;

    //Abriendo la base de datos
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return 0;
    } else {
        std::cout << "...." << std::endl;
    }

    //Obteniendo el ID de la cuenta en la moneda especificada
    if (moneda == DOLAR) {
        sql = "SELECT ID_CUENTA_D FROM CUSTOMERS WHERE ID = " + std::to_string(id);
    } else {
        sql = "SELECT ID_CUENTA_C FROM CUSTOMERS WHERE ID = " + std::to_string(id);
    }

    rc = sqlite3_exec(db, sql.c_str(), [](void* idCuentaPtr, int argc, char** argv, char** azColName) -> int {
        int* idCuenta = static_cast<int*>(idCuentaPtr);
        if (argc > 0 && argv[0] != nullptr) {
            *idCuenta = std::stoi(argv[0]);
        } else {
            *idCuenta = 0; // Set idCuenta to 0 if no result is found
        }
        return *idCuenta;
    }, &idCuenta, &zErrMsg);

    
    
    sqlite3_close(db);
    return idCuenta; // Return idCuenta
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

void Cliente::transaccion(){
    int opc;
    std::string monto;
    float montoF;
    Operaciones op(this->nombre, this->apellido, this->id);

    do {
        std::cout << "\n------ Menú de Transacciones ------" << std::endl;
        std::cout << "1. Depositar dinero" << std::endl;
        std::cout << "2. Retirar dinero" << std::endl;
        std::cout << "3. Transferir dinero" << std::endl;
        std::cout << "4. Pagar préstamo" << std::endl;
        std::cout << "5. Solicitar préstamo" << std::endl;
        std::cout << "6. Consultar saldo" << std::endl;
        std::cout << "7. Consultar movimientos" << std::endl;
        std::cout << "8. Consultar préstamos" << std::endl;
        std::cout << "9. Salir del menú" << std::endl;
        std::cout << "Elija una opción: ";

        do {
            std::cin >> opc;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
            }
        } while (std::cin.fail());

        switch (opc)
        {
        case DEPOSITO :
            try{
                std::cout << "Ingrese el monto a depositar:";
                std::cin >> monto;
                if (this->validarDatos(monto, &montoF)) {
                    op.depositar(COLON, montoF);
                }
                throw std::invalid_argument("Monto inválido");
            } catch (std::invalid_argument &e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        case RETIRO:
            
            try{
                std::cout << "Ingrese el monto a retirar:";
                std::cin >> monto;
                if (this->validarDatos(monto, &montoF)) {
                    op.retirar(COLON, montoF);
                }
                throw std::invalid_argument("Monto inválido");
            } catch (std::invalid_argument &e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        case TRANSFERENCIA:                    
            // xxxx
            break;
        case PAGOPRESTAMO:
            // xxxx
            break;
        case SOLICITUDPRESTAMO:
            // xxxx
            break;
        case CONSULTARSALDO:
            // xxxx
            break;
        case CONSULTARMOVIMIENTOS:
            // xxxx
            break;
        case CONSULTARPRESTAMOS:
            // xxxx
            break;
        case SALIRMENUT:
            std::cout << "Saliendo del menú de transacciones..." << std::endl;
            break;
        default:
            break;
        }
    } while ( opc != SALIRMENUT);
    return;

    
}

