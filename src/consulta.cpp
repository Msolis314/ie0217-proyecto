#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>
#include "consulta.hpp"

/// @brief Muestra el menú principal de consulta
void Consulta::mostrarMenuConsulta() {
    int opcion;

    do {
        system("clear");
        std::cout << "Seleccione el tipo de consulta:" << std::endl;
        std::cout << "1. Préstamos Hipotecarios" << std::endl;
        std::cout << "2. Préstamos Prendarios" << std::endl;
        std::cout << "3. Préstamos Personales" << std::endl;
        std::cout << "4. Préstamo Personalizado" << std::endl;
        std::cout << "5. Salir" << std::endl;

        if (!obtenerEntradaNumerica(opcion, "Ingrese una opción: ")) {
            continue;
        }

        switch (static_cast<TipoPrestamo>(opcion)) {
            case TipoPrestamo::Hipotecario:
                seleccionarTipoPrestamo(TipoPrestamo::Hipotecario);
                break;
            case TipoPrestamo::Prendario:
                seleccionarTipoPrestamo(TipoPrestamo::Prendario);
                break;
            case TipoPrestamo::Personal:
                seleccionarTipoPrestamo(TipoPrestamo::Personal);
                break;
            case TipoPrestamo::Personalizado:
                seleccionarTipoPrestamo(TipoPrestamo::Personalizado);
                break;
            case TipoPrestamo::Salir:
                std::cout << "Saliendo del menú de consultas..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
        }
    } while (static_cast<TipoPrestamo>(opcion) != TipoPrestamo::Salir);
}

/// @brief Selecciona el tipo de préstamo y obtiene la tasa de interés anual
/// @param tipoPrestamo Tipo de préstamo seleccionado
void Consulta::seleccionarTipoPrestamo(TipoPrestamo tipoPrestamo) {
    std::cout << "Seleccione la moneda del préstamo:" << std::endl;
    std::cout << "1. Colones" << std::endl;
    std::cout << "2. Dólares" << std::endl;

    int opcionMoneda;
    if (!obtenerEntradaNumerica(opcionMoneda, "Ingrese una opción: ")) {
        return;
    }

    Moneda moneda = static_cast<Moneda>(opcionMoneda);
    if (moneda != Moneda::Colones && moneda != Moneda::Dolares) {
        std::cout << "Opción no válida. Volviendo al menú principal..." << std::endl;
        return;
    }

    float tasaInteresAnual;
    switch (tipoPrestamo) {
        case TipoPrestamo::Hipotecario:
            tasaInteresAnual = (moneda == Moneda::Colones) ? 8.5 : 7.5;
            break;
        case TipoPrestamo::Prendario:
            tasaInteresAnual = (moneda == Moneda::Colones) ? 11.5 : 6.5;
            break;
        case TipoPrestamo::Personal:
            tasaInteresAnual = 15.0;
            break;
        case TipoPrestamo::Personalizado:
            generarTablaPagosPersonalizado();
            return;
        default:
            std::cout << "Opción no válida. Volviendo al menú principal..." << std::endl;
            return;
    }

    generarTablaPagos(tasaInteresAnual);
}

/// @brief Genera la tabla de pagos para un préstamo con una tasa de interés anual específica
/// @param tasaInteresAnual Tasa de interés anual del préstamo
void Consulta::generarTablaPagos(float tasaInteresAnual) {
    float monto;
    int cuotas;

    if (!obtenerEntradaNumerica(monto, "Ingrese el monto del préstamo: ") ||
        !obtenerEntradaNumerica(cuotas, "Ingrese el plazo en meses: ")) {
        return;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Generando tabla de pagos:" << std::endl;
    std::cout << "Monto del préstamo: $" << monto << std::endl;
    std::cout << "Duración en meses: " << cuotas << std::endl;
    std::cout << "Tasa de interés anual: " << tasaInteresAnual << "%" << std::endl;

    // Calcular el pago mensual basado en la fórmula de cuota fija
    float tasaInteresMensual = tasaInteresAnual / 12 / 100; // Tasa de interés mensual
    float factor = pow(1 + tasaInteresMensual, cuotas);
    float cuota = monto * (tasaInteresMensual * factor) / (factor - 1);

    // Mostrar tabla de pagos
    std::cout << "Tabla de pagos:" << std::endl;
    std::cout << std::setw(10) << "Mes" << std::setw(15) << "Pago Mensual" << std::endl;
    for (int mes = 1; mes <= cuotas; ++mes) {
        std::cout << std::setw(10) << mes << std::setw(15) << cuota << std::endl;
    }

    // Pausa para que el usuario vea la tabla (esperar a que presione Enter)
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/// @brief Genera la tabla de pagos personalizada permitiendo al usuario ingresar la tasa de interés anual
void Consulta::generarTablaPagosPersonalizado() {
    float monto;
    int cuotas;
    float tasaInteres;

    if (!obtenerEntradaNumerica(monto, "Ingrese el monto del préstamo: ") ||
        !obtenerEntradaNumerica(cuotas, "Ingrese el plazo en meses: ") ||
        !obtenerEntradaNumerica(tasaInteres, "Ingrese la tasa de interés anual (%): ")) {
        return;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Generando tabla de pagos personalizada:" << std::endl;
    std::cout << "Monto del préstamo: $" << monto << std::endl;
    std::cout << "Duración en meses: " << cuotas << std::endl;
    std::cout << "Tasa de interés anual: " << tasaInteres << "%" << std::endl;

    // Calcular el pago mensual basado en la fórmula de cuota fija
    float tasaInteresMensual = tasaInteres / 12 / 100; // Tasa de interés mensual
    float factor = pow(1 + tasaInteresMensual, cuotas);
    float cuota = monto * (tasaInteresMensual * factor) / (factor - 1);

    // Mostrar tabla de pagos
    std::cout << "Tabla de pagos:" << std::endl;
    std::cout << std::setw(10) << "Mes" << std::setw(15) << "Pago Mensual" << std::endl;
    for (int mes = 1; mes <= cuotas; ++mes) {
        std::cout << std::setw(10) << mes << std::setw(15) << cuota << std::endl;
    }

    // Pausa para que el usuario vea la tabla (esperar a que presione Enter)
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/// @brief Convierte el tipo de préstamo a string
/// @param tipoPrestamo Tipo de préstamo
/// @return Cadena que representa el tipo de préstamo
std::string Consulta::tipoPrestamoToString(TipoPrestamo tipoPrestamo) {
    switch (tipoPrestamo) {
        case TipoPrestamo::Hipotecario:
            return "Préstamo Hipotecario";
        case TipoPrestamo::Prendario:
            return "Préstamo Prendario";
        case TipoPrestamo::Personal:
            return "Préstamo Personal";
        case TipoPrestamo::Personalizado:
            return "Préstamo Personalizado";
        default:
            return "Desconocido";
    }
}

/// @brief Convierte la moneda a string
/// @param moneda Moneda
/// @return Cadena que representa la moneda
std::string Consulta::monedaToString(Moneda moneda) {
    switch (moneda) {
        case Moneda::Colones:
            return "Colones";
        case Moneda::Dolares:
            return "Dólares";
        default:
            return "Desconocida";
    }
}

/// @brief Obtiene una entrada numérica flotante del usuario
/// @param valor Referencia al valor flotante a obtener
/// @param mensaje Mensaje a mostrar al usuario
/// @return true si la entrada es válida, false en caso contrario
bool Consulta::obtenerEntradaNumerica(float &valor, const std::string &mensaje) {
    std::string entrada;
    std::cout << mensaje;
    std::getline(std::cin, entrada);

    // Intentar convertir la entrada a float
    try {
        valor = std::stof(entrada);
        return true;
    } catch (const std::invalid_argument &ex) {
        std::cerr << "Entrada no válida. Intente de nuevo." << std::endl;
        return false;
    } catch (const std::out_of_range &ex) {
        std::cerr << "Número fuera de rango. Intente con un valor más pequeño." << std::endl;
        return false;
    }
}

/// @brief Obtiene una entrada numérica entera del usuario
/// @param valor Referencia al valor entero a obtener
/// @param mensaje Mensaje a mostrar al usuario
/// @return true si la entrada es válida, false en caso contrario
bool Consulta::obtenerEntradaNumerica(int &valor, const std::string &mensaje) {
    std::string entrada;
    std::cout << mensaje;
    std::getline(std::cin, entrada);

    // Intentar convertir la entrada a int
    try {
        valor = std::stoi(entrada);
        return true;
    } catch (const std::invalid_argument &ex) {
        std::cerr << "Entrada no válida. Intente de nuevo." << std::endl;
        return false;
    } catch (const std::out_of_range &ex) {
        std::cerr << "Número fuera de rango. Intente con un valor más pequeño." << std::endl;
        return false;
    }
}