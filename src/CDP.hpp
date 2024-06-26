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

#include "cliente.hpp"

enum OPERACIONES_CDP{
    AGREGAR_CDP=1,
    RETIRAR_CDP,
    DESPLEGAR_CDP,
    SALIR_CDP
};
enum TASAS{
    FIJA,
    VARIABLE
};

enum TIPOS_INTERES{
    SIMPLE =1,
    COMPUESTO,
    SIMPLE_VARIABLE,
    COMPUESTO_VARIABLE,

};

enum PERIODOS_PAGO{
    MENSUAL= 0,
    TRIMESTRAL,
    SEMESTRAL,
    ANUAL, 
    FIN_PLAZO
};

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

        int elegirCuenta();

        PERIODOS_PAGO displayMenuPeriodosPago(int &opcion);

        void displayMenuOptions();

        

        std::string calcularFechaVencimiento(int plazo);
        ~CDP() = default;


};

/// @brief Clase que representa los intereses de un Certificado de Depósito a Plazo.
/// @details Esta clase es abstracta y tiene como objetivo calcular los intereses de un CDP.
class CDPintereses{
    protected:
        CDPData data;
        int plazo;
        float capital;
        int moneda;
        PERIODOS_PAGO periodo;
    public:
        CDPintereses(int plazo, PERIODOS_PAGO periodo,int moneda, float capital);
        virtual float calcularInteres() = 0;
        int getMeses() ;
        ~CDPintereses() = default;

};

/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses fijos y calculados de forma simple.
/// @details Formula  Interes = Monto * Tasa * Plazo
class CDPfijaSimple: public CDPintereses{
    public:
        CDPfijaSimple(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);
        float calcularInteres() override;
        ~CDPfijaSimple() = default;
};


/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses fijos y calculados de forma compuesta.
/// @details Formula  Interes = Monto * (1 + Tasa)^Plazo - Monto
class CDPfijaCompuesto: public CDPintereses{
    public:
        CDPfijaCompuesto(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);
        float calcularInteres() override;
        ~CDPfijaCompuesto() = default;
};

/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses variables y calculados de forma simple.
/// @details Formula  Interes = Monto * Tasa * Plazo
class CDPvariableSimple: public CDPintereses{
    public:
        CDPvariableSimple(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);
        float calcularInteres() override;
        ~CDPvariableSimple() = default;
};

/// @brief Clase que representa un Certificado de Depósito a Plazo con intereses variables y calculados de forma compuesta.
/// @details Formula  Interes = Monto * (1 + Tasa)^Plazo - Monto
class CDPvariableCompuesto: public CDPintereses{
    public:
        CDPvariableCompuesto(int plazo, PERIODOS_PAGO periodo,int moneda,float capital);
        float calcularInteres() override;
        ~CDPvariableCompuesto() = default;
};

int callbackgetCDP(void *NotUsed, int argc, char **argv, char **azColName);
#endif // CDP_HPP