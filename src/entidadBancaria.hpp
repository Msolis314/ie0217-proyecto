#ifndef ENTIDAD_BANCARIA_HPP
#define ENTIDAD_BANCARIA_HPP
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <type_traits>
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

        /// @brief Funcion para validar la entrada de datos
        template <typename T>
        bool validarEntrada(std::string dato, T* valor){
            try {
                std::istringstream ss(dato);
                if(!( ss >> *valor)|| !ss.eof()){
                    throw std::invalid_argument("No se pudo convertir el dato");
                }
                return true;
            } 
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return false;
            }

        }

};
#endif // ENTIDAD_BANCARIA_HPP 