/*! @file entidadBancaria.hpp
 @brief Clase padre del sistema bancario
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
    DOLAR = 2,
    COLON = 1
};

/// @brief Enumeracion de los tipos de transacciones
enum TipoTransaccion{
    DEPOSITO =1,
    RETIRO,
    TRANSFERENCIA,
    PAGOPRESTAMO,
    SOLICITUDPRESTAMO,
    CONSULTARSALDO,
    CONSULTARMOVIMIENTOS,
    CONSULTARPRESTAMOS,
    OPERACIONESCDP,
    SALIRMENUT

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
        char* fecha = new char[80];
        std::string fechaActual;
        float* tipoCambio = new float(0);
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
        void convertirMoneda(float &monto, Monedas moneda);

        void convertirMonedaPrestamo(float &monto, int moneda, int monedaPrestamo);

        /// @brief transaccion
        /// @details Metodo que realiza una transaccion
        /// @param monto Monto de la transaccion
        /// @param moneda Moneda de la transaccion
        /// @note Metodo abstracto, se debe implementar en las clases hijas
        void transaccion(float monto, Monedas moneda);

        /// @brief Funcion callback para los queries
        /// @param data  Puntero a los datos
        /// @param argc  Numero de columnas
        /// @param argv  Argumentos
        /// @param azColName  Nombre de las columnas
        /// @return  0
        static int callback(void *data, int argc, char **argv, char **azColName);

        /// @brief Funcion para validar la entrada de datos
        
        bool validarEntrada(std::string dato, int* valor);

        

};
#endif // ENTIDAD_BANCARIA_HPP 