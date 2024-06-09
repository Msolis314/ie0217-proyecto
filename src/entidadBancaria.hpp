#ifndef ENTIDAD_BANCARIA_HPP
#define ENTIDAD_BANCARIA_HPP
#include <string>
#include <vector>
#include <iostream>
#include <ctime>

enum Monedas{
    DOLAR,
    COLON
};

enum TipoTransaccion{
    DEPOSITO,
    RETIRO,
    PAGOCAPITAL,
    PAGOINTERES,
    TRANSFERENCIA,
    PAGOCAPITALAJENO,
    PAGOINTERESAJENO
};

/// @brief Clase padre del sistema bancario
class EntidadBancaria{
    private:
        char* fecha;
        float* tipoCambio;
    public:

        EntidadBancaria();
        std::string getFecha();
        float getTipoCambio();
        void setFecha();
        void setTipoCambio();
        void escribirEnHistorial();
        bool validarDatos(std::string dato,float* monto);
        void convertirMoneda(float monto, Monedas moneda);
        void transaccion(float monto, Monedas moneda);
        static int callback(void *data, int argc, char **argv, char **azColName);

};
#endif // ENTIDAD_BANCARIA_HPP 