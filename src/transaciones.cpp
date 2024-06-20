#include <iostream>
#include <string>
#include <sqlite3.h>
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "db.hpp"
#include "cliente.hpp"
#include "transaciones.hpp"


Operaciones:: Operaciones(std::string nombre,std::string apellido,int id):cliente(nombre,apellido,id){
    Cliente cliente(nombre,apellido,id);
}

void Operaciones::depositar(Monedas cambio,float monto){
    int opcion;
    float saldo;
    int rightChoice;
    sqlite3* db;
    char* error;
    std::string sql;
    int rc;
    do {
        do {
            std::cout << "Seleccione el tipo de moneda de la cuenta" << std::endl;
            std::cout << "1.Colones" << std::endl;
            std::cout << "2.Dolares" << std::endl;
        } while (!(std::cin >> opcion) || opcion < COLON || opcion > DOLAR);

        switch (opcion)
        {
        case COLON:
            if (cliente.idCuentaC == 0){
            
                rightChoice = cliente.returnMain("No se ha generado una cuenta colones");
                if (rightChoice == RETURN){
                    return;
                }
                else {
                    break;
                
                }
            }
            cliente.convertirMoneda(monto, cambio);
            saldo = consultarSaldo(cliente.idCuentaC);
            saldo += monto;

            
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
            rightChoice = cliente.returnMain("Deposito exitoso");
            monto = 0;
            //Cerrar la base de datos
            sqlite3_close(db);
            break;
        case DOLAR:
            if (cliente.idCuentaD == 0){
                rightChoice = cliente.returnMain("No se ha generado una cuenta dolares");
                if (rightChoice == RETURN){
                    return;
                } else {
                    break;
                }
            }
            cliente.convertirMoneda(monto, cambio);
            saldo = consultarSaldo(cliente.idCuentaD);
            saldo += monto;

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
            rightChoice = cliente.returnMain("Deposito exitoso");
            monto = 0;
            //Cerrar la base de datos
            sqlite3_close(db);
            break;
        default:
            break;
        }
    } while (rightChoice != RETURN);
}


void Operaciones::retirar(Monedas cambio,float monto){
    int opcion;
    float saldo;
    int rightChoice;
    sqlite3* db;
    char* error;
    std::string sql;
    int rc;
    do {
    
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
                        break;
                    }
                }
                
                cliente.convertirMoneda(monto, cambio);
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
                sqlite3_close(db);
                break;
            case DOLAR:
                if (cliente.idCuentaD == 0){
                    rightChoice = cliente.returnMain("No se ha generado una cuenta dolares");
                    if (rightChoice == RETURN){
                        return;
                    }
                    else {
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
                        break;
                    }
                }
                cliente.convertirMoneda(monto, cambio);
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
    return saldo;
}

int callback(void* data, int argc, char** argv, char** azColName){
    if (argc > 0){
        float* saldo = static_cast<float*>(data);
        *saldo = std::stof(argv[0]);
    }
    return 0;
}