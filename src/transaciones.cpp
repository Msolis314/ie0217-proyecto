#include <iostream>
#include <string>
#include <sqlite3.h>
#include "entidadBancaria.hpp"
#include "banco.hpp"
#include "menu.hpp"
#include "db.hpp"
#include "cliente.hpp"
#include "transaciones.hpp"


Operaciones:: Operaciones(std::string nombre,std::string apellido,int id):cliente(nombre,apellido,id){
    Cliente cliente(nombre,apellido,id);
}
void Operaciones::depositar(Monedas cambio,float monto){
    functionVars vars;
    float saldo;

    //Desplegar el menu de opciones

    do {
        if (vars.tries > 0){
            std::cout << "Monto a depositar: " << std::endl;
            std::cin >> vars.dato;
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
            std::cout << "Seleccione el tipo de moneda de la cuenta" << std::endl;
            std::cout << "1.Colones" << std::endl;
            std::cout << "2.Dolares" << std::endl;
        } while (!(std::cin >> vars.opcion) || vars.opcion < COLON || vars.opcion > DOLAR);

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
            cliente.convertirMoneda(vars.monto, COLON);
            saldo = consultarSaldo(cliente.idCuentaC);
            saldo += vars.monto;

            
            vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);

            if (vars.rc){
                std::cout << "No se pudo abrir la base de datos" << std::endl;
            }
            else{
                std::cout << "...." << std::endl;
            }

            vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaC);
            vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

            if (vars.rc != SQLITE_OK){
                std::cout << "SQL ERROR: " << vars.zErrMsg << std::endl;
                sqlite3_free(vars.zErrMsg);
            }
            vars.rightChoice = cliente.returnMain("Deposito exitoso");
            vars.monto = 0;
            vars.tries++;
            //Cerrar la base de datos
            sqlite3_close(vars.db);
            break;
        case DOLAR:
            if (cliente.idCuentaD == 0){
            
                vars.rightChoice = cliente.returnMain("No se ha generado una cuenta dolares");
                if (vars.rightChoice == RETURN){
                    return;
                } else {
                    break;
                }
            }
            cliente.convertirMoneda(vars.monto, DOLAR);
            saldo = consultarSaldo(cliente.idCuentaD);
            saldo += vars.monto;

            vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);

            if (vars.rc){
                std::cout << "No se pudo abrir la base de datos" << std::endl;
            }
            else{
                std::cout << "...." << std::endl;
            }

            vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaD);
            vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

            if (vars.rc != SQLITE_OK){
                std::cout << "SQL ERROR: " << vars.zErrMsg << std::endl;
                sqlite3_free(vars.zErrMsg);
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



void Operaciones::retirar(Monedas cambio,float monto){
    int opcion;
    float saldo;
    int tries = 0;
    int rightChoice;
    sqlite3* db;
    char* error;
    std::string sql;
    int rc;
    do {
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
                    std::cout << "No se pudo abrir la base de datos" << std::endl;
                }
                else{
                    std::cout << "...." << std::endl;
                }

                sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaC);
                rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

                if (rc != SQLITE_OK){
                    std::cout << "SQL ERROR: " << error << std::endl;
                    sqlite3_free(error);
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
                    std::cout << "No se pudo abrir la base de datos" << std::endl;
                }
                else{
                    std::cout << "...." << std::endl;
                }

                sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaD);
                rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

                if (rc != SQLITE_OK){
                    std::cout << "SQL ERROR: " << error << std::endl;
                    sqlite3_free(error);
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

float Operaciones::consultarSaldo(int idCuenta){
    sqlite3* db;
    char* error;
    int rc;
    float saldo;
    rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }
    else{
        std::cout << "...." << std::endl;
    }

    std::string sql = "SELECT AHORROS FROM CUENTA_BANCARIA WHERE ID_CUENTA = " + std::to_string(idCuenta);
    rc = sqlite3_exec(db, sql.c_str(), callback, &saldo, &error);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << error << std::endl;
        sqlite3_free(error);
    }

    sqlite3_close(db);
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
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }
    else{
        std::cout << "...." << std::endl;
    }
    //Se selecciona la moneda de la cuenta
    std::string sql = "SELECT MONEDA FROM CUENTA_BANCARIA WHERE ID_CUENTA = " + std::to_string(cuenta);
    rc = sqlite3_exec(db, sql.c_str(), floatCallback, &moneda, &error);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << error << std::endl;
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
void Operaciones::transferir(){
    // Transferir dinero de una cuenta a otra
    functionVars vars;
    
    //Variables
    float saldo;
    float saldoDestino; 
    int idCuentaDestino;

    //Inicialmente se pide el monto a transferir
    try {
        std::cout << "Ingrese el monto a transferir" << std::endl;
        std::cin >> vars.dato;
        if (!cliente.validarDatos(vars.dato, &vars.monto)){
            throw std::invalid_argument("El monto ingresado no es valido");
        }
    } catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        vars.rightChoice = cliente.returnMain("Desea intentar de nuevo?");
        if (vars.rightChoice == RETURN){
            return;
        }
    }
    do {
        //Si ha habido mas de un intneto se repite el proceso
        if (vars.tries > 0){
            std::cout << "Monto a transferir: " << std::endl;
            std::cin >> vars.dato;
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
            //Pedir el ID de la cuenta destino
            std::cout << "Ingrese el ID de la cuenta destino" << std::endl;
            std::cin >> idCuentaDestino;
            //Verificar si la cuenta destino es la misma que la del cliente
            if (idCuentaDestino == cliente.idCuentaC || idCuentaDestino == cliente.idCuentaD){
                vars.rightChoice = cliente.returnMain("No puede transferir a su propia cuenta");
                if (vars.rightChoice == RETURN){
                    return;

                }
                else {
                        vars.tries++;
                        break;
                }
            } else if (!cliente.checkIDCuentaExists(idCuentaDestino, COLON) && !cliente.checkIDCuentaExists(idCuentaDestino, DOLAR)){
                    vars.rightChoice = cliente.returnMain("La cuenta destino no existe"); //La cuenta destino no existe
                    if (vars.rightChoice == RETURN){
                        return;
                    }
                    else {
                        vars.tries++;
                        break;
                    }
            }
            
        } while (vars.rightChoice != RETURN);
        
        do {
            std::cout << "Seleccione el tipo de moneda de la cuenta de donde desea transferir" << std::endl;
            std::cout << "1.Colones" << std::endl;
            std::cout << "2.Dolares" << std::endl;
        } while (!(std::cin >> vars.opcion) || vars.opcion < COLON || vars.opcion > DOLAR);

        switch (vars.opcion) {
            case COLON:
            //Verificar si el cliente tiene una cuenta en colones
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
                
                //Consultar el saldo de la cuenta
                saldo = consultarSaldo(cliente.idCuentaC);
                if (saldo < vars.monto){
                    //Verificar si el saldo es suficiente
                    vars.rightChoice = cliente.returnMain("No tiene suficiente saldo en la cuenta");
                    if (vars.rightChoice == RETURN){
                        return;
                    }
                    else {
                        vars.tries++;
                        break;
                    }
                }
                
                //Convertir la moneda del monton si es necesario
                cliente.convertirMoneda(vars.monto, COLON);
                //Actualizar el saldo de la cuenta
                saldo -= vars.monto;


                vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);

                if (vars.rc){
                    std::cout << "No se pudo abrir la base de datos" << std::endl;
                }
                else{
                    std::cout << "...." << std::endl;
                }

                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaC);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

                if (vars.rc != SQLITE_OK){
                    std::cout << "SQL ERROR: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }

                //Consultar el saldo de la cuenta destino
                saldoDestino = consultarSaldo(idCuentaDestino);
                //Actualizar el saldo de la cuenta destino
                saldoDestino += vars.monto;

                //Actualizar el saldo de la cuenta destino
                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldoDestino) + " WHERE ID_CUENTA = " + std::to_string(idCuentaDestino);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

                if (vars.rc != SQLITE_OK){
                    std::cout << "SQL ERROR: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }
                //Cerrar la base de datos
                sqlite3_close(vars.db);
                vars.rightChoice = cliente.returnMain("Transferencia exitosa");
                vars.tries++;
                break;
            case DOLAR:

                if (cliente.idCuentaD == 0){
                    vars.rightChoice = cliente.returnMain("No se ha generado una cuenta dolares");
                    if (vars.rightChoice == RETURN){
                        return;
                    }
                    else {
                        vars.tries++;
                        break;
                    }
                }
                saldo = consultarSaldo(cliente.idCuentaD);
                if (saldo < vars.monto){
                    vars.rightChoice = cliente.returnMain("No tiene suficiente saldo en la cuenta");
                    if (vars.rightChoice == RETURN){
                        return;
                    }
                    else {
                        vars.tries++;
                        break;
                    }
                }
                cliente.convertirMoneda(vars.monto, DOLAR);
                saldo -= vars.monto;

                vars.rc = sqlite3_open("SistemaBancario.db", &vars.db);

                if (vars.rc){
                    std::cout << "No se pudo abrir la base de datos" << std::endl;
                }
                else{
                    std::cout << "...." << std::endl;
                }

                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldo) + " WHERE ID_CUENTA = " + std::to_string(cliente.idCuentaD);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

                if (vars.rc != SQLITE_OK){
                    std::cout << "SQL ERROR: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }

                saldoDestino = consultarSaldo(idCuentaDestino);
                saldoDestino += vars.monto;

                vars.sql = "UPDATE CUENTA_BANCARIA SET AHORROS = " + std::to_string(saldoDestino) + " WHERE ID_CUENTA = " + std::to_string(idCuentaDestino);
                vars.rc = sqlite3_exec(vars.db, vars.sql.c_str(), NULL, 0, &vars.zErrMsg);

                if (vars.rc != SQLITE_OK){
                    std::cout << "SQL ERROR: " << vars.zErrMsg << std::endl;
                    sqlite3_free(vars.zErrMsg);
                }
                sqlite3_close(vars.db);
                vars.rightChoice = cliente.returnMain("Transferencia exitosa");
                vars.tries++;
                break;
            default:
                break;
        }

    } while (vars.rightChoice != RETURN);
}



            