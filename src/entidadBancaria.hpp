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
    TRANSFERENCIA
};

class EntidadBancaria{
    private:
        char* fecha;
        float* tipoCambio;
    public:
        EntidadBancaria();
        time_t getFecha();
        float getTipoCambio();
        void setFecha();
        void setTipoCambio();
        void escribirEnHistorial(int tipoTransaccion, int ID_CLIENTE,int ID_CUENTA, int ID_PRESTAMO = 0, int ID_CUENTA_DESTINO);
        template <typename T> bool validarDatos(T dato);
        void convertirMoneda(float monto, Monedas moneda);
        virtual void transaccion(float monto, Monedas moneda);

};
#endif // ENTIDAD_BANCARIA_HPP 