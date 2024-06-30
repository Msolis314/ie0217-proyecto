#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>

/// @brief Enumeración de los tipos de préstamos
enum class TipoPrestamo {
    Hipotecario = 1,
    Prendario,
    Personal,
    Personalizado,
    Salir
};

/// @brief Enumeración de las monedas
enum class Moneda {
    Colones = 1,
    Dolares
};

/// @brief Clase para realizar consultas de préstamos
class Consulta {
public:
    /// @brief Muestra el menú principal de consulta
    void mostrarMenuConsulta();

    /// @brief Selecciona el tipo de préstamo
    /// @param tipoPrestamo Tipo de préstamo seleccionado
    void seleccionarTipoPrestamo(TipoPrestamo tipoPrestamo);

    /// @brief Genera la tabla de pagos para un préstamo
    /// @param tasaInteresAnual Tasa de interés anual del préstamo
    void generarTablaPagos(float tasaInteresAnual);

    /// @brief Genera la tabla de pagos personalizada
    void generarTablaPagosPersonalizado();

    /// @brief Convierte el tipo de préstamo a string
    /// @param tipoPrestamo Tipo de préstamo
    /// @return Cadena que representa el tipo de préstamo
    std::string tipoPrestamoToString(TipoPrestamo tipoPrestamo);

    /// @brief Convierte la moneda a string
    /// @param moneda Moneda
    /// @return Cadena que representa la moneda
    std::string monedaToString(Moneda moneda);

    /// @brief Obtiene una entrada numérica flotante del usuario
    /// @param valor Referencia al valor flotante a obtener
    /// @param mensaje Mensaje a mostrar al usuario
    /// @return true si la entrada es válida, false en caso contrario
    bool obtenerEntradaNumerica(float &valor, const std::string &mensaje);

    /// @brief Obtiene una entrada numérica entera del usuario
    /// @param valor Referencia al valor entero a obtener
    /// @param mensaje Mensaje a mostrar al usuario
    /// @return true si la entrada es válida, false en caso contrario
    bool obtenerEntradaNumerica(int &valor, const std::string &mensaje);
};

#endif // CONSULTA_HPP
