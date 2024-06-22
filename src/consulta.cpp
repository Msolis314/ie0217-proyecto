#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>
#include "consulta.hpp"

void Consulta::mostrarMenuConsulta() {
    int opcion;

    do {
        system("clear");
        std::cout << "Seleccione el tipo de consulta:" << std::endl;
        std::cout << "1. Personalizado (Ingrese monto, cuotas y tasa)" << std::endl;
        std::cout << "2. Préstamos Hipotecarios" << std::endl;
        std::cout << "3. Préstamos Prendarios" << std::endl;
        std::cout << "4. Préstamos Personales" << std::endl;
        std::cout << "5. Salir" << std::endl;

        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                generarTablaPagosPersonalizado();
                break;
            case 2:
                seleccionarTipoPrestamo(TipoPrestamo::HipotecarioColones);
                break;
            case 3:
                seleccionarTipoPrestamo(TipoPrestamo::PrendarioColones);
                break;
            case 4:
                seleccionarTipoPrestamo(TipoPrestamo::Personal);
                break;
            case 5:
                std::cout << "Saliendo del menú de consultas..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
        }
    } while (opcion != 5);
}

void Consulta::seleccionarTipoPrestamo(TipoPrestamo tipoPrestamo) {
    std::cout << "Seleccione la moneda del préstamo:" << std::endl;
    std::cout << "1. Colones" << std::endl;
    std::cout << "2. Dólares" << std::endl;

    int moneda;
    std::cin >> moneda;

    switch (moneda) {
        case 1:
            if (tipoPrestamo == TipoPrestamo::HipotecarioColones)
                generarTablaPagos(TipoPrestamo::HipotecarioColones, 8.5, 3, 10.09);
            else if (tipoPrestamo == TipoPrestamo::PrendarioColones)
                generarTablaPagos(TipoPrestamo::PrendarioColones, 11.5, 2, 16.34);
            else if (tipoPrestamo == TipoPrestamo::Personal)
                generarTablaPagosPersonalizado(); // Cambio aquí
            break;
        case 2:
            if (tipoPrestamo == TipoPrestamo::HipotecarioColones)
                generarTablaPagos(TipoPrestamo::HipotecarioDolares, 7.5, 7, 8.39);
            else if (tipoPrestamo == TipoPrestamo::PrendarioColones)
                generarTablaPagos(TipoPrestamo::PrendarioDolares, 6.5, 2, 11.08);
            else if (tipoPrestamo == TipoPrestamo::Personal)
                generarTablaPagosPersonalizado(); // Cambio aquí
            break;
        default:
            std::cout << "Opción no válida. Volviendo al menú principal..." << std::endl;
            return;
    }
}

void Consulta::generarTablaPagos(TipoPrestamo tipoPrestamo, float tasaInteresAnual, int duracionAnios, float tasaInteresTotalAnual) {
    float monto;
    int cuotas;

    std::cout << "Ingrese el monto del préstamo: ";
    std::cin >> monto;

    // Calcular la cantidad de cuotas basada en el tipo de préstamo
    if (tipoPrestamo == TipoPrestamo::HipotecarioColones || tipoPrestamo == TipoPrestamo::HipotecarioDolares)
        cuotas = duracionAnios * 12; // Se asume pago mensual para hipotecarios
    else if (tipoPrestamo == TipoPrestamo::PrendarioColones || tipoPrestamo == TipoPrestamo::PrendarioDolares)
        cuotas = duracionAnios * 6; // Se asume pago semestral para prendarios
    else
        cuotas = duracionAnios; // Para préstamos personales

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Generando tabla de pagos para el préstamo " << tipoPrestamoToString(tipoPrestamo) << ":" << std::endl;
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

void Consulta::generarTablaPagosPersonalizado() {
    float monto;
    int cuotas;
    float tasaInteres;

    std::cout << "Ingrese el monto del préstamo: ";
    std::cin >> monto;
    std::cout << "Ingrese la cantidad de cuotas: ";
    std::cin >> cuotas;
    std::cout << "Ingrese la tasa de interés (%): ";
    std::cin >> tasaInteres;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Generando tabla de pagos personalizada:" << std::endl;
    std::cout << "Monto del préstamo: $" << monto << std::endl;
    std::cout << "Cantidad de cuotas: " << cuotas << std::endl;
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

std::string Consulta::tipoPrestamoToString(TipoPrestamo tipoPrestamo) {
    switch (tipoPrestamo) {
        case TipoPrestamo::HipotecarioColones:
            return "Hipotecario en colones";
        case TipoPrestamo::HipotecarioDolares:
            return "Hipotecario en dólares";
        case TipoPrestamo::PrendarioColones:
            return "Prendario en colones";
        case TipoPrestamo::PrendarioDolares:
            return "Prendario en dólares";
        case TipoPrestamo::Personal:
            return "Personal";
        default:
            return "Desconocido";
    }
}
