#ifndef PRESTAMOS_HPP//TRANSACCIONES_HPP
#define PRESTAMOS_HPP


#include <iostream>
#include <string>
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "cliente.hpp"
#include "db.hpp"



enum TipoPretamo{
    PERSONAL = 1,
    HIPOTECARIO = 2,
    PRENDARIO = 3
};


class Prestamos : public EntidadBancaria{
private:
    std::string tipoInteres;
    float tasaActual;
    int plazo;
    double interesesAbonados;
    float capital;
    Cliente cliente;
    float tasaBanco;
    std::vector<int> actualIDPrestamos; 

    std::string nombre;
    std::string apellido;
    int idCliente;  
    std::string TipoPrestamo;
public:
    Prestamos(std::string tipoInteres, float tasaActual, std::string plazo, float capital,std::string TipoPrestamo,float tasaBanco);

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
    int generar_id_prestamo();
    string ingresarTipoInteres();

    static int callbackPrestamos(void *data, int argc, char **argv, char **azColName);
    void setActualIDPrestamos();
    bool checkID_PRESTAMO(int id);
    void agregarID_lista(int id);
    
    // @brief establecer el tipo de cambio
    void setTipoCambioBank();
    float consultarPrestamo(int id_P);
    int callbackConsultaPrestamos(void *data, int argc, char **argv, char **azColName);

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

