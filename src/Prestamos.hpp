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


/// @brief Enumeracion de los tipos de prestamos
//// @details Enumeracion de los tipos de prestamos que se pueden solicitar.
enum TipoPretamo {
    PERSONAL = 1,
    HIPOTECARIO = 2,
    PRENDARIO = 3
};

/// @brief Enumeracion de los tipos de interes
//// @details Enumeracion de los tipos de interes que se pueden solicitar.
enum MonedaPrestamo {
    COLONES_PRESTAMO = 1,
    DOLARES_PRESTAMO = 2
};


/// @brief Clase que realiza las operaciones de prestamos.
/// @details Esta clase realiza las operaciones de prestamos como pagar cuota, calcular cuota, actualizar plazo, actualizar intereses, modificar capital, desplegar informe, solicitar prestamo, ingresar prestamo personal, ingresar prestamo hipotecario, ingresar prestamo prendario, generar id prestamo, ingresar tipo interes, set actual id prestamos, check id prestamo, agregar id lista, set tasa bank, consultar prestamos, callback consulta prestamos, get tipo interes, set tipo interes, get tasa actual, set tasa actual, get plazo, set plazo, get intereses abonados, set intereses abonados, get capital, set capital, get plazo actual, set plazo actual, calcular cuota variable, actualizar cuotas, abonar cuota, realizar abono, realizar abono2, obtener id prestamo sesion, restar monto cuenta cliente, consultar saldo cliente, consultar tipo moneda prestamo, consultar cuota, obtener tipo cambio.
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

    /// @brief Constructor de la clase Prestamos
    /// @param entidadBancaria Entidad bancaria
    /// @param nombre Nombre del cliente
    /// @param apellido Apellido del cliente
    /// @param idCliente ID del cliente
    Prestamos(EntidadBancaria* entidadBancaria, std::string nombre, std::string apellido, int idCliente);;

    // Métodos

    
    /// @brief Metodo para solicitar prestamo
    void solicitarPrestamo();

    /// @brief  Metodo para solcitar un prestamo personal
    void ingresar_prestamoPersonal();

    /// @brief Metodo para solicitar un prestamo hipotecario
    void ingresar_prestamoHipotecario();

    /// @brief Metodo para solicitar un prestamo prendario
    void ingresar_prestamoPrendario();

    /// @brief Metodo para generar un id de prestamo
    /// @return id de prestamo
    int generar_id_prestamo();

    /// @brief Metodo para ingresar el tipo de interes
    /// @return tipo de interes
    std::string ingresarTipoInteres();

    /// @brief Callback para los prestamos
    /// @param data  Puntero a los datos
    /// @param argc  Numero de columnas
    /// @param argv  Argumentos
    /// @param azColName  Nombre de las columnas
    /// @return  0
    static int callbackPrestamos(void *data, int argc, char **argv, char **azColName);

    /// @brief Metodo para setear el id de prestamos
    void setActualIDPrestamos();

    /// @brief Metodo para chequear el id de prestamo
    /// @param id  ID de prestamo
    /// @return  true si el id de prestamo existe, false en caso contrario
    bool checkID_PRESTAMO(int id);
    void agregarID_lista(int id);
    
    /// @brief Metodo para consultar los prestamos
    void consultarPrestamos();
    int callbackConsultaPrestamos(void *data, int argc, char **argv, char **azColName);

   
    
   
    /// @brief   Metodo    para calcular la cuota de un prestamo variable
    float calcularCuotaVariable(float tasaInteres, float indiceReferencia, float capital, int plazo);

    
    /// @brief Metodo para abonar en la base de datos
    void abonarCuota(int idPrestamo, float abono, bool esAbonoExtraordinario, MonedaPrestamo tipoMoneda);
    
    /// @brief Metodo para realizar un abono
    void realizarAbono2();

    /// @brief  Metodo para obtener el id de prestamo de la sesion deun cliente
    /// @return  id de prestamo
    int obtenerIdPrestamoSesion();

    /// @brief Metodo para restar el monto de la cuenta del cliente
    /// @param moneda  Moneda del prestamo
    /// @param monto  Monto a restar
    void restarMontoCuentaCliente(MonedaPrestamo moneda, float monto);

    /// @brief  Metodo para consultar el saldo del cliente
    /// @param tipoMoneda  Tipo de moneda
    /// @return  Saldo del cliente
    float consultarSaldoCliente(MonedaPrestamo tipoMoneda);

    /// @brief Metodo para consultar el tipo de moneda del prestamo
    /// @param idPrestamo  ID del prestamo
    /// @return  Tipo de moneda del prestamo
    MonedaPrestamo consultarTipoMonedaPrestamo(int idPrestamo);

    /// @brief Metodo para consultar la cuota de un prestamo
    /// @param idPrestamo  ID del prestamo
    /// @return  Cuota del prestamo
    double consultarCuota(int idPrestamo);

};


#endif ///PRESTAMOS_HPP