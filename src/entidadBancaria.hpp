#ifndef ENTIDAD_BANCARIA_HPP
#define ENTIDAD_BANCARIA_HPP
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <type_traits>
#include <ctime>

/// @brief Enumeracion de las monedas
enum Monedas{
    DOLAR,
    COLON
};

/// @brief Enumeracion de los tipos de transacciones
enum TipoTransaccion{
    DEPOSITO,
    RETIRO,
    PAGOCAPITAL,
    PAGOINTERES,
    TRANSFERENCIA,
    PAGOCAPITALAJENO,
    PAGOINTERESAJENO
};

/// @brief Enumeracion de las respuestas para la funcion returnMain
enum Respuesta{
    RETRY =1,
    RETURN
};
/// @brief Clase padre del sistema bancario
/// @details Clase que contiene los metodos y atributos comunes a todas las entidades bancarias
class EntidadBancaria{
    private:
        char* fecha;
        float* tipoCambio;
    public:

        /// @brief Constructor de la clase
        /// @details Constructor de la clase que inicializa la fecha y el tipo de cambio
        EntidadBancaria();

        /// @brief obtener la fecha actual
        std::string getFecha();

        /// @brief obtener el tipo de cambio
        float getTipoCambio();

        /// @brief establecer la fecha actual
        void setFecha();

        /// @brief establecer el tipo de cambio
        void setTipoCambio();

        /// @brief escribir en el historial
        /// @details Metodo que escribe en el historial de transacciones
        /// @note Metodo abstracto, se debe implementar en las clases hijas
        void escribirEnHistorial();

        /// @brief retornar al menu principal desde algun error
        /// @details Metodo que retorna al menu principal en caso de algun error
        /// @param mensaje Mensaje a mostrar
        int returnMain(std::string mensaje);

        /// @brief validar los datos
        /// @details Metodo que valida los datos ingresados en caso de valores numericos
        /// @param dato Dato a validar
        /// @param monto Puntero al monto
        bool validarDatos(std::string dato,float* monto);

        /// @brief convertir moneda
        /// @details Metodo que convierte un monto de una moneda a otra
        /// @param monto Monto a convertir
        /// @param moneda Moneda a la que se va a convertir
        void convertirMoneda(float monto, Monedas moneda);

        /// @brief transaccion
        /// @details Metodo que realiza una transaccion
        /// @param monto Monto de la transaccion
        /// @param moneda Moneda de la transaccion
        /// @note Metodo abstracto, se debe implementar en las clases hijas
        void transaccion(float monto, Monedas moneda);
        static int callback(void *data, int argc, char **argv, char **azColName);

        /// @brief Funcion para validar la entrada de datos
        
        bool validarEntrada(std::string dato, int* valor);

};
#endif // ENTIDAD_BANCARIA_HPP 