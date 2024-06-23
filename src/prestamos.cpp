#include <iostream>
#include <string>
#include <sqlite3.h>
#include "entidadBancaria.hpp"
#include "menu.hpp"
#include "db.hpp"
#include "cliente.hpp"
#include "transaciones.hpp"
#include "Prestamos.hpp"
#include <cmath> 
#include"consulta.hpp"

using namespace std;

Prestamos::Prestamos(std::string tipoInteres, float tasaActual, std::string plazo, double capital, std::string TipoPrestamo)
    : tipoInteres(tipoInteres), tasaActual(tasaActual), plazo(plazo), capital(capital), TipoPrestamo(TipoPrestamo), interesesAbonados(0.0) {
    // datos cliente falta
    }

void Prestamos::solicitarPrestamo() {
    int opcion;
    cout << "Seleccione el tipo de préstamo:" << endl;
    cout << "1. Préstamo personal" << endl;
    cout << "2. Préstamo hipotecario" << endl;
    cout << "3. Préstamo prendario" << endl;
    cout << "Opción: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            ingresar_prestamoPersonal();
            break;
        case 2:
            ingresar_prestamoHipotecario();
            break;
        case 3:
            ingresar_prestamoPrendario();
            break;
        default:
            cout << "Opción no válida. Seleccione una opción válida." << endl;
            break;
    }
}

void Prestamos::ingresar_prestamoPersonal() {
    int seleccion;
    string tipoCambio;
    Cliente cliente; 

    do {
        cout << "Seleccione el tipo de cambio:\n";
        cout << "1. Colón\n";
        cout << "2. Dólar\n";
        cout << "Ingrese su opción: ";
        cin >> seleccion;

        if (seleccion < 1 || seleccion > 2) {
            cout << "Opción inválida. Inténtelo de nuevo.\n";
        }
    } while (seleccion < 1 || seleccion > 2);

    tipoCambio = (seleccion == 1) ? "Colones" : "DOlares";

    cout << "Solicitud de Préstamo Personal:" << endl;
    cout << "Ingrese el monto del préstamo: ";
    cin >> capital;

    cout << "Ingrese el plazo en meses: ";
    cin >> plazo;

    cout << "Ingrese el tipo de interés (fijo/variable): ";
    cin >> tipoInteres;

    cout << "Ingrese la tasa de interés (%): ";
    cin >> tasaActual;

    // Calcular el pago mensual basado en la fórmula de cuota fija
    float tasaInteresMensual = stof(tasaActual) / 12 / 100; // Tasa de interés mensual
    float factor = pow(1 + tasaInteresMensual, stoi(plazo));
    float cuota = capital * (tasaInteresMensual * factor) / (factor - 1);

    cout << "Detalles del préstamo:" << endl;
    cout << "Tipo de interés: " << tipoInteres << endl;
    cout << "Tasa de interés anual (%): " << tasaActual << endl;
    cout << "Plazo en meses: " << plazo << endl;
    cout << "Monto del préstamo: " << capital << " " << tipoCambio << endl;
    cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << endl;

    // Guardar en la base de datos
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc) {
        cout << "No se pudo abrir la base de datos" << endl;
        return;
    } else {
        cout << "Base de datos abierta" << endl;
    }

    // Construir la consulta SQL para insertar los datos del préstamo
    string sqlInsert = "INSERT INTO PRESTAMO (ID_CLIENTE, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL) VALUES (" +
                       to_string(cliente.idCliente) + ", '" + tipoCambio + "', '" + tipoInteres + "', " + to_string(cuota) + ", " + plazo + ", " + tasaActual + ", " + to_string(capital) + ", " + to_string(capital) + ");";

    rc = sqlite3_exec(db, sqlInsert.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    } else {
        cout << "Datos del préstamo guardados exitosamente." << endl;
    }

    // Cerrar la base de datos
    sqlite3_close(db);
}




void Prestamos::ingresar_prestamoHipotecario() {
    int seleccion;
    std::string tipoCambio;
    float tasaActual;

    do {
        std::cout << "Seleccione el tipo de cambio:" << std::endl;
        std::cout << "1. Colón" << std::endl;
        std::cout << "2. Dólar" << std::endl;
        std::cout << "Ingrese su opción: ";
        std::cin >> seleccion;

        if (seleccion < 1 || seleccion > 2) {
            std::cout << "Opción inválida. Inténtelo de nuevo." << std::endl;
        }
    } while (seleccion < 1 || seleccion > 2);

    switch (seleccion) {
        case 1:
            tipoCambio = "Colones";
            tasaActual = 10.09; // Tasa para Colones
            break;
        case 2:
            tipoCambio = "Dólares";
            tasaActual = 8.39; 
            break;
        default:
            
            return;
    }

    std::cout << "Solicitud de Préstamo Hipotecario:" << std::endl;
    std::cout << "Ingrese el monto del préstamo: ";
    std::cin >> capital;
    std::string tipoInteres = "fijo"; // Asignación de tipoInteres
    std::string plazo = "12"; 

    // Calcular el pago mensual basado en la fórmula de cuota fija
    float tasaInteresMensual = tasaActual / 12 / 100; // Tasa de interés mensual
    float factor = pow(1 + tasaInteresMensual, std::stoi(plazo));
    float cuota = capital * (tasaInteresMensual * factor) / (factor - 1);

    std::cout << "Detalles del préstamo:" << std::endl;
    std::cout << "Tipo de interés: " << tipoInteres << std::endl;
    std::cout << "Tasa de interés anual (%): " << tasaActual << std::endl;
    std::cout << "Plazo en meses: " << plazo << std::endl;
    std::cout << "Monto del préstamo: " << capital << " " << tipoCambio << std::endl;
    std::cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << std::endl;

    // Guardar en la base de datos 
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return;
    } else {
        std::cout << "Base de datos abierta" << std::endl;
    }

    // Construir la consulta SQL para insertar los datos del préstamo
    std::string sqlInsert = "INSERT INTO PRESTAMO (ID_CLIENTE, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL) VALUES (" +
                            std::to_string(cliente.idCliente) + ", '" + tipoCambio + "', '" + tipoInteres + "', " + std::to_string(cuota) + ", " + plazo + ", " + std::to_string(tasaActual) + ", " + std::to_string(capital) + ", " + std::to_string(capital) + ");";

    rc = sqlite3_exec(db, sqlInsert.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Datos del préstamo guardados exitosamente." << std::endl;
    }

    // Cerrar la base de datos
    sqlite3_close(db);
}






void Prestamos::ingresar_prestamoPrendario() {
    int seleccion;
    std::string tipoCambio;
    float tasaActual;

    do {
        std::cout << "Seleccione el tipo de cambio:" << std::endl;
        std::cout << "1. Colón" << std::endl;
        std::cout << "2. Dólar" << std::endl;
        std::cout << "Ingrese su opción: ";
        std::cin >> seleccion;

        if (seleccion < 1 || seleccion > 2) {
            std::cout << "Opción inválida. Inténtelo de nuevo." << std::endl;
        }
    } while (seleccion < 1 || seleccion > 2);

    switch (seleccion) {
        case 1:
            tipoCambio = "Colones";
            tasaActual = 16.34;
            break;
        case 2:
            tipoCambio = "Dólares";
            tasaActual = 11.08; 
            break;
        default:
            
            return;
    }

    std::cout << "Solicitud de Préstamo Prendario:" << std::endl;
    std::cout << "Ingrese el monto del préstamo: ";
    std::cin >> capital;
    std::string tipoInteres = "fijo"; // Asignación de tipoInteres
    std::string plazo = "6"; 

    // Calcular el pago mensual basado en la fórmula de cuota fija
    float tasaInteresMensual = tasaActual / 12 / 100; // Tasa de interés mensual
    float factor = pow(1 + tasaInteresMensual, std::stoi(plazo));
    float cuota = capital * (tasaInteresMensual * factor) / (factor - 1);

    std::cout << "Detalles del préstamo:" << std::endl;
    std::cout << "Tipo de interés: " << tipoInteres << std::endl;
    std::cout << "Tasa de interés anual (%): " << tasaActual << std::endl;
    std::cout << "Plazo en meses: " << plazo << std::endl;
    std::cout << "Monto del préstamo: " << capital << " " << tipoCambio << std::endl;
    std::cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << std::endl;

    // Guardar en la base de datos 
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return;
    } else {
        std::cout << "Base de datos abierta" << std::endl;
    }

    // Construir la consulta SQL para insertar los datos 
    std::string sqlInsert = "INSERT INTO PRESTAMO (ID_CLIENTE, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL) VALUES (" +
                            std::to_string(cliente.idCliente) + ", '" + tipoCambio + "', '" + tipoInteres + "', " + std::to_string(cuota) + ", " + plazo + ", " + std::to_string(tasaActual) + ", " + std::to_string(capital) + ", " + std::to_string(capital) + ");";

    rc = sqlite3_exec(db, sqlInsert.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Datos del préstamo guardados exitosamente." << std::endl;
    }

    // Cerrar la base de datos
    sqlite3_close(db);
}
