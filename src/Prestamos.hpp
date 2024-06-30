/*! @file Prestamos.hpp
 @brief Header file de la clase Prestamos
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


#ifndef PRESTAMOS_HPP
#define PRESTAMOS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility> // Para std::pair
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "cliente.hpp"
#include "db.hpp"

enum TipoPretamo {
    PERSONAL = 1,
    HIPOTECARIO = 2,
    PRENDARIO = 3
};

enum MonedaPrestamo {
    COLONES_PRESTAMO = 1,
    DOLARES_PRESTAMO = 2
};

class Prestamos {
private:
    Cliente cliente;
    std::string nombreCliente;
    std::string apellidoCliente;
    int idCliente;
    std::string tipoInteres;
    float tasaActual;
    int plazo;
    double interesesAbonados;
    float capital;
    float tasaBanco;
    std::vector<int> actualIDPrestamos; 
    std::string TipoPrestamo;
    std::vector<std::pair<int, float>> tasaVariable; // Vector para almacenar las tasas variables
    EntidadBancaria* entidadBancaria; // Añadir referencia a EntidadBancaria
    int tipoAbono;
public:
    Prestamos(EntidadBancaria* entidadBancaria, std::string nombre, std::string apellido, int idCliente);;

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
    std::string ingresarTipoInteres();

    static int callbackPrestamos(void *data, int argc, char **argv, char **azColName);
    void setActualIDPrestamos();
    bool checkID_PRESTAMO(int id);
    void agregarID_lista(int id);
    
    // @brief establecer tasa de cambio del banco
    void setTasaBank();
    void consultarPrestamos();
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

    float calcularCuotaVariable(float tasaInteres, float indiceReferencia, float capital, int plazo);

    void actualizarCuotas();

    void abonarCuota(int idPrestamo, float abono, bool esAbonoExtraordinario, MonedaPrestamo tipoMoneda);
    void realizarAbono();
    void realizarAbono2();
    int obtenerIdPrestamoSesion();
    void restarMontoCuentaCliente(MonedaPrestamo moneda, float monto);
    float consultarSaldoCliente(MonedaPrestamo tipoMoneda);

    MonedaPrestamo consultarTipoMonedaPrestamo(int idPrestamo);

    double consultarCuota(int idPrestamo);

    float obtenerTipoCambio(MonedaPrestamo monedaPrestamo, MonedaPrestamo monedaCuenta);
};

#endif