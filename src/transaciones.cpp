/*! @file transaciones.cpp
 @brief Implementación de la clase Operaciones
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

#include <iostream>
#include <string>
#include <sqlite3.h>
#include "entidadBancaria.hpp"
#include "banco.hpp"
#include "menu.hpp"
#include "db.hpp"
#include "cliente.hpp"
#include "transaciones.hpp"


// Función para obtener la fecha y hora actual en formato string
std::string Operaciones::obtenerFechaHoraActual() {
    std::time_t tiempoActual = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&tiempoActual));
    return std::string(buffer);
}

// Función para registrar una transacción en la base de datos
// Función para registrar una transacción en la base de datos
void Operaciones::registrarTransaccion(int idCliente, const std::string& tipoTransaccion, int idCuenta, int idCuentaDestino, float monto, const std::string& moneda) {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string fechaHora = obtenerFechaHoraActual();
    std::string sql = "INSERT INTO HISTORIAL_TRANSACCIONES (ID_CLIENTE, TIPO_TRANSACCION, ID_CUENTA, ID_CUENTA_DESTINO, MONTO, MONEDA, FECHA) "
                      "VALUES (" + std::to_string(idCliente) + ", '" + tipoTransaccion + "', " + 
                      (idCuenta == 0 ? "NULL" : std::to_string(idCuenta)) + ", " + 
                      (idCuentaDestino == 0 ? "NULL" : std::to_string(idCuentaDestino)) + ", " + 
                      std::to_string(monto) + ", '" + moneda + "', '" + fechaHora + "');";

    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
}

// Método para imprimir el historial del usuario
void Operaciones::imprimirHistorialTransacciones(int idCliente) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string sql = "SELECT * FROM HISTORIAL_TRANSACCIONES WHERE ID_CLIENTE = " + std::to_string(idCliente);

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::cout << "Historial de Transacciones:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idTransaccion = sqlite3_column_int(stmt, 0);
        std::string tipoTransaccion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int idCuenta = sqlite3_column_int(stmt, 3);
        int idCuentaDestino = sqlite3_column_int(stmt, 4);
        float monto = static_cast<float>(sqlite3_column_double(stmt, 5));
        std::string moneda = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)); // Nueva columna
        std::string fecha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

        std::cout << "ID Transaccion: " << idTransaccion << ", Tipo: " << tipoTransaccion << ", ID Cuenta: " << idCuenta
                  << ", ID Cuenta Destino: " << idCuentaDestino << ", Monto: " << monto << ", Moneda: " << moneda
                  << ", Fecha: " << fecha << std::endl; // Imprime la moneda
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

Operaciones:: Operaciones(std::string nombre,std::string apellido,int id):cliente(nombre,apellido,id){
    Cliente cliente(nombre,apellido,id);
}
void Operaciones::depositar(Monedas cambio,float monto){
    functionVars vars;
    float saldo;
    vars.monto = monto;
    vars.tries = 0;
    float montoDeposito;
    std::string montoDepositoStr;
    std::string moneda; // Variable para almacenar el tipo de moneda


    //Desplegar el menu de opciones

    do {
        if (vars.tries > 0){
            std::cout << "Monto a depositar: " << std::endl;
            std::cin >> vars.dato;

            //Validar el monto ingresado
            try{
                if(!cliente.validarDatos(vars.dato, &vars.monto)){
                    throw std::invalid_argument("El monto ingresado no es valido");
                }
            }   
            catch (std::invalid_argument &e){
                std::cout << e.what() << std::endl;
                vars.rightChoice = cliente.returnMain("Desea intentar de nuevo?");
                if (vars.rightChoice == RETURN){
                    return;
                }
                else {
                    vars.tries++;
                    continue;
                }
            }
        }
        do {
            //Seleccionar el tipo de moneda
            std::cout << "Seleccione el tipo de moneda de la cuenta" << std::endl;
            std::cout << "1.Colones" << std::endl;
            std::cout << "2.Dolares" << std::endl;
            std::cin >> vars.dato;
            try {
                if (!cliente.validarEntrada(vars.dato, &vars.opcion)){
                    throw std::invalid_argument("La opcion ingresada no es valida");
                }
                if (vars.opcion < COLON || vars.opcion > DOLAR){
                    throw std::invalid_argument("La opcion ingresada no es valida");
                }
                break;

            }
            catch (std::invalid_argument &e){
                std::cout << e.what() << std::endl;
                vars.rightChoice = cliente.returnMain("Desea intentar de nuevo?");
                if (vars.rightChoice == RETURN){
                    return;
                }
                else {
                    vars.tries++;
                    continue;
                }
            }
        } while (true);

        switch (vars.opcion)
        {
        case COLON:
            if (cliente.idCuentaC == 0){
                vars.rightChoice = cliente.returnMain("No se ha generado una cuenta colones");
                if (vars.rightChoice == RETURN){
                    return;
                }
                else {
                    vars.tries++;
                    break;
                }
            }

            //Convertir el monto a colones
            cliente.convertirMoneda(vars.monto, COLON);

            //Consultar el saldo de la cuenta
            saldo = consultarSaldo(cliente.idCuentaC);
            //Actualizar el saldo de la cuenta
            saldo += vars.monto;

            
            vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);

            if (vars.rc){
                std::cerr << "No se pudo abrir la base de datos" << std::endl;
            }
            else{
                std::cout << "...." << std::endl;
            }

            vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaC);
            vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

            if (vars.rc != SQLITE_OK) {
                    std::cerr << "SQL ERROR: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                } else {
                    moneda = "colones"; // Se establece la moneda como colones
                    registrarTransaccion(cliente.id, "Deposito", cliente.idCuentaC, 0, vars.monto, moneda); // Registro de deposito
                }

            vars.rightChoice = cliente.returnMain("Deposito exitoso");
            vars.monto = 0;
            vars.tries++;
            //Cerrar la base de datos
            sqlite3_close(vars.db);
            break;

        case DOLAR:
        //Parte de la cuenta en dolares
            if (cliente.idCuentaD == 0){
                
                vars.rightChoice = cliente.returnMain("No se ha generado una cuenta dolares");
                if (vars.rightChoice == RETURN){
                    return;
                } else {
                    break;
                }
            }

            //Convertir el monto a dolares
            cliente.convertirMoneda(vars.monto, DOLAR);

            //Consultar el saldo de la cuenta
            saldo = consultarSaldo(cliente.idCuentaD);
            saldo += vars.monto;

            vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);

            if (vars.rc){
                std::cerr << "No se pudo abrir la base de datos" << std::endl;
            }
            else{
                std::cout << "...." << std::endl;
            }

            vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaD);
            vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

            if (vars.rc != SQLITE_OK) {
                    std::cerr << "SQL ERROR: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                } else {
                    moneda = "dolares"; // Se establece la moneda como dolares
                    registrarTransaccion(cliente.id, "Deposito", cliente.idCuentaD, 0, vars.monto, moneda); // Regsitro de deposito
                }
            vars.rightChoice = cliente.returnMain("Deposito exitoso");
            vars.monto = 0;
            vars.tries++;
            //Cerrar la base de datos
            sqlite3_close(vars.db);
            break;
        default:
            break;
        }
    } while (vars.rightChoice != RETURN);

}


/// @note Se ha modificado la función para que el monto sea un parámetro de entrada
/// @details Función para retirar dinero de la cuenta, monto tambien se modifica adentro
void Operaciones::retirar(Monedas cambio,float monto){
    int opcion;
    float saldo;
    int tries = 0;
    int rightChoice;
    sqlite3* db;
    char* error;
    std::string sql;
    int rc;
    std::string moneda;
    do {

        // EN caso que este sea un segundo intento
        if (tries > 0){
            std::cout << "Monto a retirar: " << std::endl;
            std::cin >> monto;
            try{
                if(!cliente.validarDatos(std::to_string(monto), &monto)){
                    throw std::invalid_argument("El monto ingresado no es valido");
                }
            }   
            catch (std::invalid_argument &e){
                std::cout << e.what() << std::endl;
                rightChoice = cliente.returnMain("Desea intentar de nuevo?");
                if (rightChoice == RETURN){
                    return;
                }
                else {
                    tries++;
                    continue;
                }
            }
        }

        //Seleccionar el tipo de moneda
        do {
            std::cout << "Seleccione el tipo de moneda de la cuenta" << std::endl;
            std::cout << "1.Colones" << std::endl;
            std::cout << "2.Dolares" << std::endl;
        } while (!(std::cin >> opcion) || opcion < COLON || opcion > DOLAR);

        switch (opcion) {
            //Colones
            case COLON:
            //Verificar si el cliente tiene una cuenta en colones
                if (cliente.idCuentaC == 0){
                    rightChoice = cliente.returnMain("No se ha generado una cuenta colones");
                    if (rightChoice == RETURN){
                        return;
                    }
                    else {
                        tries++;
                        break;
                    }
                }
                //Consultar el saldo de la cuenta
                saldo = consultarSaldo(cliente.idCuentaC);
                //Verificar si el saldo es suficiente
                if (saldo < monto){
                    rightChoice = cliente.returnMain("No tiene suficiente saldo en la cuenta");
                    if (rightChoice == RETURN){
                        return;
                    }
                    else {
                        tries++;
                        break;
                    }
                }
                
                cliente.convertirMoneda(monto, COLON);
                saldo -= monto;

                rc = sqlite3_open("SistemaBancario.db", &db);

                if (rc){
                    std::cerr << "No se pudo abrir la base de datos" << std::endl;
                }
                else{
                    std::cout << "...." << std::endl;
                }

                sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaC);
                rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

                if (rc != SQLITE_OK) {
                    std::cerr << "SQL ERROR: " << error << std::endl;
                    sqlite3_free(error);
                } else {
                    moneda = "colones"; // Se establece la moneda como colones
                    registrarTransaccion(cliente.id, "Retiro", cliente.idCuentaC, 0, monto, moneda); // Regsitro de retiro
                }

                rightChoice = cliente.returnMain("Retiro exitoso");
                tries++;
                sqlite3_close(db);
                break;
            case DOLAR:
                if (cliente.idCuentaD == 0){
                    rightChoice = cliente.returnMain("No se ha generado una cuenta dolares");
                    if (rightChoice == RETURN){
                        return;
                    }
                    else {
                        tries++;
                        break;
                    }
                }
                saldo = consultarSaldo(cliente.idCuentaD);
                if (saldo < monto){
                    rightChoice = cliente.returnMain("No tiene suficiente saldo en la cuenta");
                    if (rightChoice == RETURN){
                        return;
                    }
                    else {
                        tries++;
                        break;
                    }
                }
                cliente.convertirMoneda(monto, DOLAR);
                saldo -= monto;

                rc = sqlite3_open("SistemaBancario.db", &db);

                if (rc){
                    std::cerr << "No se pudo abrir la base de datos" << std::endl;
                }
                else{
                    std::cout << "...." << std::endl;
                }

                sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaD);
                rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

                if (rc != SQLITE_OK) {
                    std::cerr << "SQL ERROR: " << error << std::endl;
                    sqlite3_free(error);
                } else {
                    moneda = "dolares"; // Se establece la moneda como dolares
                    registrarTransaccion(cliente.id, "Retiro", cliente.idCuentaD, 0, monto, moneda); // Registro de retiro
                }

                //Cerrar la base de datos
                sqlite3_close(db);
                rightChoice = cliente.returnMain("Retiro exitoso");
                tries++;
                break;
            default:
                break;
        }
        
    } while (rightChoice != RETURN);
}


/// @details Función para consultar el saldo de la cuenta, se utilza en depositar y retirar
float Operaciones::consultarSaldo(int idCuenta){
    sqlite3* db;
    char* error;
    int rc;
    float saldo;

    //Abrir la base de datos
    rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc){
        std::cerr << "No se pudo abrir la base de datos" << std::endl;
    }
    else{
        std::cout << "...." << std::endl;
    }

    std::string sql = "SELECT AHORROS FROM CUENTA_BANCARIA WHERE ID_CUENTA = " + std::to_string(idCuenta);
    rc = sqlite3_exec(db, sql.c_str(), callback, &saldo, &error);
    if (rc != SQLITE_OK){
        std::cerr << "SQL ERROR: " << error << std::endl;
        sqlite3_free(error);
    }

    sqlite3_close(db);
    //Si la cuenta no existe
    if (!cliente.checkIDCuentaExists(idCuenta, COLON) && !cliente.checkIDCuentaExists(idCuenta, DOLAR)){
        return 0;
    }
    return saldo;
}

int callback(void* data, int argc, char** argv, char** azColName){
    if (argc > 0){
        float* saldo = static_cast<float*>(data);
        *saldo = std::stof(argv[0]);
    }
    return 0;
}
int Operaciones::checkAcountCurrency(int cuenta){
    //Consultar la base de datos para obtener el tipo de moneda de la cuenta
    sqlite3* db;

    char* error;
    int rc;
    std::string moneda;
    rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc){
        std::cerr << "No se pudo abrir la base de datos" << std::endl;
    }
    else{
        std::cout << "...." << std::endl;
    }
    //Se selecciona la moneda de la cuenta
    std::string sql = "SELECT TIPO_MONEDA FROM CUENTA_BANCARIA WHERE ID_CUENTA = " + std::to_string(cuenta);
    rc = sqlite3_exec(db, sql.c_str(), stringCallback, &moneda, &error);
    if (rc != SQLITE_OK){
        std::cerr << "SQL ERROR: " << error << std::endl;
        sqlite3_free(error);
    }

    sqlite3_close(db);
    if (moneda == "colones"){
        return COLON;
    }
    else if (moneda == "dolares"){
        return DOLAR;
    }

}

int Operaciones::pedirMonto(float &monto){
    functionVars vars;
    try {
        std::cout << "Ingrese el monto" << std::endl;
        std::cin >> vars.dato;
        if (!cliente.validarDatos(vars.dato, &monto)){
            throw std::invalid_argument("El monto ingresado no es valido");
        }
    } catch (std::invalid_argument &e){
        
        vars.rightChoice = cliente.returnMain(e.what());
        if (vars.rightChoice == RETURN){
            return RETURN;
        }
    }
    return 0;
}
void Operaciones::transferir() {
    // Transferir dinero de una cuenta a otra
    functionVars vars;
    
    // Variables locales
    float saldo;
    float saldoDestino; 
    int idCuentaDestino;
    std::string monedaOrigen;
    std::string monedaDestino;
    Monedas tipoMonedaDestino;

    // Inicialmente se pide el monto a transferir
    do {
        vars.rightChoice = pedirMonto(vars.monto);
        if (vars.rightChoice == RETURN) {
            return;
        } else {
            break;
        }
    } while (vars.rightChoice != RETURN);

    do {
        // Si ha habido más de un intento se repite el proceso
        if (vars.tries > 0) {
            vars.rightChoice = pedirMonto(vars.monto);
        }

        do {
            // Pedir el ID de la cuenta destino
            std::cout << "Ingrese el ID de la cuenta destino:" << std::endl;
            while (!(std::cin >> idCuentaDestino) || idCuentaDestino < 0) {
                std::cout << "Ingrese un ID válido" << std::endl;
                std::cin.clear();
                std::cin.ignore(12300000000, '\n');
            }

            // Verificar si la cuenta destino es la misma que la del cliente
            if (idCuentaDestino == cliente.idCuentaC || idCuentaDestino == cliente.idCuentaD) {
                vars.rightChoice = cliente.returnMain("No puede transferir a su propia cuenta");
                if (vars.rightChoice == RETURN) {
                    return;
                } else {
                    continue;
                }
            } 

            // Verificar si la cuenta destino existe
            if (!cliente.checkIDCuentaExists(idCuentaDestino, COLON) && !cliente.checkIDCuentaExists(idCuentaDestino, DOLAR)) {
                vars.rightChoice = cliente.returnMain("La cuenta destino no existe");
                if (vars.rightChoice == RETURN) {
                    return;
                } else {
                    continue;
                }
            }
            break;
        } while (vars.rightChoice != RETURN);
        
        do {
            std::cout << "Seleccione el tipo de moneda de la cuenta de donde desea transferir" << std::endl;
            std::cout << "1. Colones" << std::endl;
            std::cout << "2. Dolares" << std::endl;
        } while (!(std::cin >> vars.opcion) || vars.opcion < COLON || vars.opcion > DOLAR);

        switch (vars.opcion) {
            case COLON:
                // Verificar si el cliente tiene una cuenta en colones
                if (cliente.idCuentaC == 0) {
                    vars.rightChoice = cliente.returnMain("No se ha generado una cuenta en colones");
                    if (vars.rightChoice == RETURN) {
                        return;
                    } else {
                        vars.tries++;
                        break;
                    }
                }

                // Convertir la moneda del monto si es necesario
                cliente.convertirMoneda(vars.monto, COLON);

                // Consultar el saldo de la cuenta
                saldo = consultarSaldo(cliente.idCuentaC);
                if (saldo < vars.monto) {
                    // Verificar si el saldo es suficiente
                    vars.rightChoice = cliente.returnMain("No tiene suficiente saldo en la cuenta");
                    if (vars.rightChoice == RETURN) {
                        return;
                    } else {
                        vars.tries++;
                        break;
                    }
                }

                // Actualizar el saldo de la cuenta
                saldo -= vars.monto;

                // Abrir la base de datos
                vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);
                if (vars.rc) {
                    std::cerr << "No se pudo abrir la base de datos" << std::endl;
                } else {
                    std::cout << "Conexión establecida con la base de datos" << std::endl;
                }

                // Actualizar saldo en la tabla CUENTA_BANCARIA para la cuenta de origen
                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaC);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);
                if (vars.rc != SQLITE_OK) {
                    std::cerr << "Error SQL: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }

                // Consultar el tipo de moneda de la cuenta destino
                tipoMonedaDestino = static_cast<Monedas>(checkAcountCurrency(idCuentaDestino));

                // Actualizar saldo de la cuenta destino según el tipo de moneda
                if (tipoMonedaDestino == COLON) {
                    saldoDestino = consultarSaldo(idCuentaDestino);
                    saldoDestino += vars.monto;
                } else {
                    cliente.convertirMoneda(vars.monto, DOLAR);
                    saldoDestino = consultarSaldo(idCuentaDestino);
                    saldoDestino += vars.monto;
                }

                // Actualizar saldo en la tabla CUENTA_BANCARIA para la cuenta destino
                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldoDestino) + " WHERE ID_CUENTA = " + std::to_string(idCuentaDestino);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);
                if (vars.rc != SQLITE_OK) {
                    std::cerr << "Error SQL: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }

                // Cerrar la base de datos
                sqlite3_close(vars.db);

                // Registrar la transferencia
                monedaOrigen = "colones";
                monedaDestino = (tipoMonedaDestino == COLON) ? "colones" : "dolares";
                registrarTransaccion(cliente.id, "Transferencia", cliente.idCuentaC, idCuentaDestino, vars.monto, monedaDestino);

                vars.rightChoice = cliente.returnMain("Transferencia exitosa");
                vars.tries++;
                break;

            case DOLAR:
                // Verificar si el cliente tiene una cuenta en dólares
                if (cliente.idCuentaD == 0) {
                    vars.rightChoice = cliente.returnMain("No se ha generado una cuenta en dólares");
                    if (vars.rightChoice == RETURN) {
                        return;
                    } else {
                        vars.tries++;
                        break;
                    }
                }

                // Consultar el saldo de la cuenta
                saldo = consultarSaldo(cliente.idCuentaD);
                if (saldo < vars.monto) {
                    vars.rightChoice = cliente.returnMain("No tiene suficiente saldo en la cuenta");
                    if (vars.rightChoice == RETURN) {
                        return;
                    } else {
                        vars.tries++;
                        break;
                    }
                }

                // Convertir la moneda del monto si es necesario
                cliente.convertirMoneda(vars.monto, DOLAR);
                saldo -= vars.monto;

                // Abrir la base de datos
                vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);
                if (vars.rc) {
                    std::cerr << "No se pudo abrir la base de datos" << std::endl;
                } else {
                    std::cout << "Conexión establecida con la base de datos" << std::endl;
                }

                // Actualizar saldo en la tabla CUENTA_BANCARIA para la cuenta de origen
                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaD);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);
                if (vars.rc != SQLITE_OK) {
                    std::cerr << "Error SQL: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }

                // Consultar el tipo de moneda de la cuenta destino
                tipoMonedaDestino = static_cast<Monedas>(checkAcountCurrency(idCuentaDestino));

                // Actualizar saldo de la cuenta destino según el tipo de moneda
                if (tipoMonedaDestino == DOLAR) {
                    saldoDestino = consultarSaldo(idCuentaDestino);
                    saldoDestino += vars.monto;
                } else {
                    cliente.convertirMoneda(vars.monto, COLON);
                    saldoDestino = consultarSaldo(idCuentaDestino);
                    saldoDestino += vars.monto;
                }

                // Actualizar saldo en la tabla CUENTA_BANCARIA para la cuenta destino
                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldoDestino) + " WHERE ID_CUENTA = " + std::to_string(idCuentaDestino);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);
                if (vars.rc != SQLITE_OK) {
                    std::cerr << "Error SQL: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }

                // Cerrar la base de datos
                sqlite3_close(vars.db);

                // Registrar la transferencia
                monedaOrigen = "dolares";
                monedaDestino = (tipoMonedaDestino == DOLAR) ? "dolares" : "colones";
                registrarTransaccion(cliente.id, "Transferencia", cliente.idCuentaD, idCuentaDestino, vars.monto, monedaDestino);

                vars.rightChoice = cliente.returnMain("Transferencia exitosa");
                vars.tries++;
                break;

            default:
                break;
        }

    } while (vars.rightChoice != RETURN);
}
