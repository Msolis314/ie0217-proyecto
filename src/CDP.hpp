
/*! @file CDP.hpp
 @brief Header file de la clase CDP y sus clases derivadas.
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
#ifndef CDP_HPP
#define CDP_HPP
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "db.hpp"
#include "transaciones.hpp"
#include "cliente.hpp"


/// @brief Enumeracion de las operaciones de un CDP.
enum OPERACIONES_CDP{
    AGREGAR_CDP=1,
    RETIRAR_CDP,
    DESPLEGAR_CDP,
    ELIMINAR_CDP,
    SALIR_CDP
};

/// @brief Enumeracion de las tasas de un CDP.
enum TASAS{
    FIJA,
    VARIABLE
};


/// @brief Enumeracion de las combinaciones de modalidades de interes de un CDP.
///@details SIMPLE = 1, COMPUESTO = 2, SIMPLE_VARIABLE = 3, COMPUESTO_VARIABLE = 4
enum TIPOS_INTERES{
    SIMPLE =1,
    COMPUESTO,
    SIMPLE_VARIABLE,
    COMPUESTO_VARIABLE,

};

/// @brief Enumeracion de los periodos de pago de un CDP.
/// @details MENSUAL = 0, TRIMESTRAL = 1, SEMESTRAL = 2, ANUAL = 3, FIN_PLAZO = 4, ERROR = -1
enum PERIODOS_PAGO{
    MENSUAL= 0,
    TRIMESTRAL,
    SEMESTRAL,
    ANUAL, 
    FIN_PLAZO,
    ERROR = -1
};


/// @brief Estructura que contiene los datos de un CDP.
/// @details Contiene los intereses, impuestos, montos minimos, plazos minimos y maximos de un CDP.
struct CDPData
{
    float Interes_Colones = 0.125; // 12.5%
    float Interes_Dolares = 0.05; // 5%
    float Impuestos = 0.15; // 15%
    

    float Monto_Minimo_Colones = 100000;
    float Monto_Minimo_Dolares = 100;

    int Plazo_Minimo = 1; // 1 mes
    int Plazo_Maximo = 60; // 5 años
} typedef CDPData;


/// @brief Clase que representa un Certificado de Depósito a Plazo.
/// @details Esta clase tiene como objetivo representar un CDP y realizar operaciones sobre el mismo.
/// @details Esta clase hereda de la clase EntidadBancaria.
/// @details Esta clase tiene como atributos un cliente, un nombre, un apellido, un id, una fecha de creacion, una fecha de vencimiento, un CDPData, un monto, un periodo de pago, un interes, una moneda, un tipo de interes, un plazo y un periodo.
class CDP: public EntidadBancaria{
    private:

        Cliente cliente;   ///< Cliente que posee el CDP.
        std::string nombre; ///< Nombre del Cliente que posee el CDP.
        std::string apellido;   ///< Apellido del Cliente que posee el CDP.
        int idCliente;  ///< ID del cliente que posee el CDP.
        std::string fechaCreacion;  ///< Fecha de creacion del CDP.
        std::string fechaVencimiento;   ///< Fecha de vencimiento del CDP.
        CDPData data;   ///< Datos del CDP.
        float monto;    ///< Monto del CDP.
        std::string periodoPago; ///< Periodo de pago del CDP.
        float interes;  ///< Interes del CDP.
        int moneda; ///< Moneda del CDP.
        std::string tipoInteres; ///< Tipo de interes del CDP.
        int plazo; ///< Plazo del CDP en meses.
        PERIODOS_PAGO periodo; ///< Periodo de pago del CDP.
    public:
        /// @brief Constructor de la clase CDP
        /// @param nombre Nombre del cliente.
        /// @param apellido Apellido del cliente.
        /// @param id ID del cliente.
        CDP(std::string nombre, std::string apellido, int id);

        /// @brief Metodo para agregar un CDP a la base de datos.
        void agregarCDP();

        /// @brief Metodo para desplegar la informacion de un CDP.
        void desplegarCDP();

        


        /// @brief Metodo para retirar un CDP.
        void retirarCDP();

        /// @brief Metodo para desplegar las opciones de un CDP.
        void displayMenuCDP();


        /// @brief Metodo para elegir una cuenta.
        /// @return int Retorna la cuenta elegida. COLONES = 1, DOLARES = 2
        int elegirCuenta();


        /// @brief Metodo para elegir uno de los periodos de pago de un CDP.
        /// @param opcion  Opcion elegida por el usuario.
        /// @return  PERIODOS_PAGO Retorna el periodo de pago elegido.
        PERIODOS_PAGO displayMenuPeriodosPago(int &opcion);

        /// @brief Metodo para desplegar las opciones de un CDP.
        void displayMenuOptions();

        /// @brief Metodo para generar un ID de un CDP.
        /// @return  int Retorna el ID generado.
        int generarID();

        
        /// @brief Metodo para calcular la fecha de vencimiento de un CDP.
        /// @param plazo plazo en meses del CDP.
        /// @return  std::string Retorna la fecha de vencimiento del CDP.
        std::string calcularFechaVencimiento(int plazo);

        /// @brief Metodo para depositar en la cuenta de un cliente los intereses de un CDP.

        void depositarIntereses();

        /// @brief Metodo para obtener el interes de un CDP.
        /// @return  float Retorna el interes de un CDP.
        float getInteres(int idCDP);

        /// @brief Metodo para combrobar que la fecha corresponda al periodo de pago de un CDP.
        /// @param fecha  Fecha a comprobar.
        /// @return  bool Retorna true si la fecha corresponde al periodo de pago de un CDP.
        bool comprobarFecha(std::string fecha,int idCDP);

        /// @brief Metodo para obtener el plazo de un CDP.
        /// @return  int Retorna el plazo de un CDP.
        int getPlazo(int idCDP);

        /// @brief Metodo para obtener el periodo de pago de un CDP.
        /// @return  PERIODOS_PAGO Retorna el periodo de pago de un CDP.
        std::string getPeriodoPago(int idCDP);

        /// @brief Metodo para mostrar los id, la moneda y el monto de los CDP de un cliente.
        void mostrarCDP();

        /// @brief Metodo para obtener el id_deposito de un CDP.
        /// @return  int Retorna el id_deposito de un CDP.
        int getIDDeposito(int idCDP);

        /// @brief Metodo para comprobar si un CDP existe.
        /// @param idCDP  ID del CDP a comprobar.
        /// @return  bool Retorna true si el CDP existe.
        bool checkIDCDPExists(int idCDP);

        std::string getMoneda(int idCDP);

        ~CDP() = default;


};

/// @brief Clase que representa los intereses de un Certificado de Depósito a Plazo.
/// @details Esta clase es abstracta y tiene como objetivo calcular los intereses de un CDP.
/// @details Esta clase tiene como atributos un CDPData, un plazo, un capital, una moneda y un periodo.
class CDPintereses{
    protected:
        CDPData data;
        int plazo;
        float capital;
        int moneda;
        PERIODOS_PAGO periodo;
    public: 

        /// @brief  Constructor de la clase CDPintereses.
        /// @param plazo  plazo en meses del CDP.
        /// @param periodo  periodo de pago del CDP.
        /// @param moneda  COLONES = 1, DOLARES = 2
        /// @param capital  capital invertido en  el CDP.
        CDPintereses(int plazo, PERIODOS_PAGO periodo,int moneda, float capital);

        /// @brief Metodo para calcular los intereses de un CDP.
        /// @return  float Retorna los intereses de un CDP.
        virtual float calcularInteres() = 0;

        /// @brief Metodo para obtener el plazo de un CDP.
        /// @return  int Retorna el plazo de un CDP.
        int getMeses() ;
        ~CDPintereses() = default;

};

/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses fijos y calculados de forma simple.
/// @details Formula  Interes = Monto * Tasa * Plazo
class CDPfijaSimple: public CDPintereses{
    public:

        /// @brief Constructor de la clase CDPfijaSimple.
        /// @param plazo plazo en meses del CDP.
        /// @param periodo periodo de pago del CDP.
        /// @param moneda moneda del CDP.
        /// @param capital  monton invertido en el CDP.
        CDPfijaSimple(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);

        /// @brief Metodo para calcular los intereses de un CDP.
        /// @return  float Retorna los intereses de un CDP.
        /// @details funcion sobrecargada de la clase CDPintereses.
        float calcularInteres() override;

        /// @brief Destructor de la clase CDPfijaSimple.
        ~CDPfijaSimple() = default;
};


/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses fijos y calculados de forma compuesta.
/// @details Formula  Interes = Monto * (1 + Tasa)^Plazo - Monto
class CDPfijaCompuesto: public CDPintereses{
    public:

        /// @brief Constructor de la clase CDPfijaCompuesto.
        /// @param plazo  plazo en meses del CDP.
        /// @param periodo  periodo de pago del CDP.
        /// @param moneda  moneda del CDP.
        /// @param capital  capital invertido en el CDP.
        CDPfijaCompuesto(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);

        /// @brief Metodo para calcular los intereses de un CDP.
        /// @return  float Retorna los intereses de un CDP.
        /// @details funcion sobrecargada de la clase CDPintereses.

        float calcularInteres() override;

        /// @brief Destructor de la clase CDPfijaCompuesto.
        ~CDPfijaCompuesto() = default;
};

/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses variables y calculados de forma simple.
/// @details Formula  Interes = Monto * Tasa * Plazo
class CDPvariableSimple: public CDPintereses{
    public:

        /// @brief Constructor de la clase CDPvariableSimple.
        CDPvariableSimple(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);

        /// @brief Metodo para calcular los intereses de un CDP.
        float calcularInteres() override;
        ~CDPvariableSimple() = default;
};

/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses variables y calculados de forma compuesta.
/// @details Formula  Interes = Monto * (1 + Tasa)^Plazo - Monto
class CDPvariableCompuesto: public CDPintereses{
    public:

        /// @brief Constructor de la clase CDPvariableCompuesto.
        CDPvariableCompuesto(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);

        /// @brief Metodo para calcular los intereses de un CDP.
        float calcularInteres() override;

        ~CDPvariableCompuesto() = default;
};

/// @brief Metodo para imprimir los CDP de un cliente.
/// @param NotUsed  No se utiliza.
/// @param argc  Numero de columnas.
/// @param argv  Valores de las columnas.
/// @param azColName  Nombres de las columnas.
/// @return int Retorna 0 si la operacion fue exitosa.
int callbackgetCDP(void *NotUsed, int argc, char **argv, char **azColName);



#endif // CDP_HPP