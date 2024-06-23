#ifndef PRESTAMOS_HPP//TRANSACCIONES_HPP
#define PRESTAMOS_HPP


#include <iostream>
#include <string>
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "cliente.hpp"



class Prestamos {
private:
    std::string tipoInteres;
    float tasaActual;
    int = plazo;
    double interesesAbonados;
    double capital;
    Cliente cliente;
    std::string TipoPrestamo;
public:
    Prestamos(std::string tipoInteres, float tasaActual, std::string plazo, double capital,std::string TipoPrestamo);

    // Métodos
    void pagarCuota(double monto);
    double calcularCuota() const;
    void actualizarPlazo(std::string nuevoPlazo);
    void actualizarIntereses(std::string nuevaTasa);
    void modificarCapital(double nuevoCapital);
    void desplegarInforme() const;
    void solicitarPrestamo();
    void ingresar_prestamoPersonal();
    void ingresar_prestamoHipotecario();
    void ingresar_prestamoPrendario();


    std::string getTipoInteres() const;
    void setTipoInteres(const std::string &tipoInteres);
    std::string getTasaActual() const;
    void setTasaActual(const std::string &tasaActual);
    std::string getPlazo() const;
    void setPlazo(const std::string &plazo);
    double getInteresesAbonados() const;
    void setInteresesAbonados(double interesesAbonados);
    double getCapital() const;
    void setCapital(double capital);
    
    std::string getPlazoActual() const;
    void setPlazoActual(const std::string &plazoActual);
};

#endif 

