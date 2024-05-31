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

class EntidadBancaria{
    private:
        time_t fecha;
        float tipoCambio;
    public:
        EntidadBancaria();
        time_t getFecha();
        float getTipoCambio();
        void setFecha(time_t fecha);
        void setTipoCambio(float tipoCambio);
        void consultarHistorial();
        template <typename T> bool validarDatos(T dato);
        void convertirMoneda(float monto, Monedas moneda);
        virtual void transaccion(float monto, Monedas moneda);

};
#endif // ENTIDAD_BANCARIA_HPP