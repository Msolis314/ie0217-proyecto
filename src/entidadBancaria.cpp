#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sqlite3.h>
#include <stdexcept>
#include <sstream>
#include "entidadBancaria.hpp"
#include "db.hpp"

EntidadBancaria::EntidadBancaria(){
    setFecha();
    setTipoCambio();
}
void EntidadBancaria::setFecha(){
    time_t now = time(0);
    char *dt = ctime(&now);
    fecha = dt;

    //Establecer la fecha en la base de datos
    //mes/dia/año

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

    std::string sql = "UPDATE BANKINFO SET FECHA = '" + yearMonth + "'";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

}

void EntidadBancaria::setTipoCambio(){
    //Consultar la base de datos para obtener el tipo de cambio.
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "...." << std::endl;
    }

    const char* sql = "SELECT TIPO_CAMBIO FROM BANKINFO";
    rc = sqlite3_exec(db, sql, floatCallback, this->tipoCambio, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    

    sqlite3_close(db);


}


int EntidadBancaria::returnMain(std::string mensaje){
    std::cout << mensaje << std::endl;
    std::cout << "Que desea hacer?" << std::endl;
    int opcion;
    do{
        std::cout << "1. Intentar de nuevo" << std::endl;
        std::cout << "2. Salir al menu anterior" << std::endl;
    
    }while(!(std::cin >> opcion) || opcion < 1 || opcion > 2);

    return opcion;


}
bool EntidadBancaria::validarDatos(std::string dato, float* monto){

    try {
        std::istringstream stream(dato);

        if (!(stream >> *monto) || !stream.eof()){
            throw std::invalid_argument("El dato ingresado no es un numero");
        }
        else if (*monto < 0){
            throw std::invalid_argument("El monto no puede ser negativo");
        }
        return true;
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return false;
    }
}

float EntidadBancaria::getTipoCambio(){
    return *tipoCambio;
}
void EntidadBancaria::convertirMoneda(float &monto, Monedas moneda){
    int tipoMonedaMonto;

    do {
        std::cout << "Seleccione el tipo de moneda del monto" << std::endl;
        std::cout << "1.Colones" << std::endl;
        std::cout << "2.Dolares" << std::endl;
    } while (!(std::cin >> tipoMonedaMonto) || tipoMonedaMonto < COLON || tipoMonedaMonto > DOLAR);
    if (tipoMonedaMonto == moneda){
        monto = monto;
        return;
    }
    if (tipoMonedaMonto== DOLAR){
        monto = monto * getTipoCambio();
    }else{
        monto = monto / getTipoCambio();
    }
}


bool EntidadBancaria::validarEntrada(std::string dato, int* valor){
    try {
        std::istringstream stream(dato);

        if (!(stream >> *valor) || !stream.eof()){
            throw std::invalid_argument("El dato ingresado no es un numero");
        }
        else if (*valor < 0){
            throw std::invalid_argument("El monto no puede ser negativo");
        }
        return true;
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return false;
    }
}