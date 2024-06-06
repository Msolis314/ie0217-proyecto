#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sqlite3.h>
#include <stdexcept>
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
}

void EntidadBancaria::setTipoCambio(){
    //Consultar la base de datos para obtener el tipo de cambio
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    const char* sql = "SELECT TIPO_CAMBIO FROM BANKINFO";
    rc = sqlite3_exec(db, sql, returnValue, fecha, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Tipo de cambio obtenido con exito" << std::endl;
    }

    sqlite3_close(db);


}

template <typename T>
bool EntidadBancaria::validarDatos(T dato){
    try {
        if (dato < 0){
            throw std::invalid_argument("El dato no puede ser negativo");
        }
    } catch (const std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        return false;
    }
}

float EntidadBancaria::getTipoCambio(){
    return *tipoCambio;
}
void EntidadBancaria::convertirMoneda(float monto, Monedas moneda){
    if (moneda == DOLAR){
        monto = monto * getTipoCambio();
    }else{
        monto = monto / getTipoCambio();
    }
}

