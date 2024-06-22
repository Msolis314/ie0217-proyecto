#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>

enum class TipoPrestamo {
    HipotecarioColones,
    HipotecarioDolares,
    PrendarioColones,
    PrendarioDolares,
    Personal,
    Personalizado
};

class Consulta {
public:
    void mostrarMenuConsulta();
    void seleccionarTipoPrestamo(TipoPrestamo tipoPrestamo);
    void generarTablaPagos(TipoPrestamo tipoPrestamo, float tasaInteresAnual, int duracionAnios, float tasaInteresTotalAnual);
    void generarTablaPagosPersonalizado();
    std::string tipoPrestamoToString(TipoPrestamo tipoPrestamo);

private:
    void mostrarOpcionesMoneda();
};

#endif // CONSULTA_HPP