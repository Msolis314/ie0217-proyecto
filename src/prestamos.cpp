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

// Constructor de la clase Prestamos
Prestamos::Prestamos(std::string tipoInteres, float tasaActual, std::string plazo, float capital,std::string TipoPrestamo):cliente("","",0) {
    this->tipoInteres = tipoInteres;
    this->tasaActual = tasaActual;
    this->plazo = std::stoi(plazo);
    this-> cliente  = Cliente(nombre, apellido, idCliente);
    this->capital = capital;
    this->TipoPrestamo = TipoPrestamo;
}

// Metodo para solicitar un prestamo
void Prestamos::solicitarPrestamo() {
    int opcion;
    // Presenta al usuario las opciones de tipos de prestamos disponibles
    cout << "****Seleccione el tipo de prestamo****" << endl;
    cout << "1. Prestamo personal" << endl;
    cout << "2. Prestamo hipotecario" << endl;
    cout << "3. Prestamo prendario" << endl;
    cout << "Opcion: ";
    // Lee la opcion seleccionada por el usuario
    cin >> opcion;

    // Dependiendo de la opcion seleccionada, llama a la funcion correspondiente
    switch (opcion) {
        case 1:
            // Llamando a la funcion para ingresar un prestamo personal
            ingresar_prestamoPersonal();
            break;
        case 2:
            // Llamando a la función para ingresar un prestamo hipotecario
            ingresar_prestamoHipotecario();
            break;
        case 3:
            // Llamando a la función para ingresar un prestamo prendario
            ingresar_prestamoPrendario();
            break;
        default:
            // msj de error
            cout << "Opción no valida. Seleccione una opcion valida." << endl;
            break;
    }
}






/*****************************************************
 * *****Metodo para ingresar prestamo Personal********
******************************************************/
void Prestamos::ingresar_prestamoPersonal() {
    int seleccion;
    string tipoCambio;
    int rightChoice;
   //  Clase Cliente para el atributo idcliente.
    
    // Ingrear la moneda y la con la opcion correcta.
    do {
        cout << "Seleccione el tipo de cambio:\n";
        cout << "1. Colon\n";
        cout << "2. Dolar\n";
        cout << "Ingrese su opción: ";
        cin >> seleccion;

        // Verificando que sea valido
        if (seleccion < 1 || seleccion > 2) {
            cout << "Opción inválida. Inténtelo de nuevo.\n";
        }
    } while (seleccion < 1 || seleccion > 2 || !cin.good());

    // Asigna el tipo de cambio segun la selecciin
    tipoCambio = (seleccion == 1) ? "Colones" : "Dólares";

    // Solicita al usuario los detalles del prestamo personal
    cout << "****Solicitud de Prestamo Personal****" << endl;
    string capitalStr;
    int tryCount = 0;
    do {
        cout << "Ingrese el monto del préstamo: ";
        cin >> capital;
        if (tryCount > 0) {
            cliente.returnMain("Por favor ingrese un monto válido");
        }
    }while (!validarDatos(capitalStr, &capital));

    
    
    do {
        cout << "Ingrese el plazo en meses: ";
        cin >> plazo;
        if (plazo < 1) {
            cout << "El plazo debe ser mayor a 0. Inténtelo de nuevo.\n";
        }
    } while (plazo < 1 || !cin.good());
    
    
    cout << "Ingrese el tipo de interés (fijo/variable): ";
    cin >> tipoInteres;

    cout << "Ingrese la tasa de interés (%): ";
    cin >> tasaActual;
    
    // Calcula el pago mensual basado en la formula de cuota fija
    float tasaInteresMensual = tasaActual / 12 / 100; // Convirtiendo la tasaActual a tasa mensual
    float factor = pow(1 + tasaInteresMensual, plazo); // Calculando el factor para la formula de cuota fija
    float cuota = capital * (tasaInteresMensual * factor) / (factor - 1); // Calcula la cuota mensual

    // Muestra los detalles generales del prestamo calculado
    cout << "****Detalles del prestamo****" << endl;
    cout << "Tipo de interes: " << tipoInteres << endl;
    cout << "Tasa de interes anual (%): " << tasaActual << endl;
    cout << "Plazo en meses: " << plazo << endl;
    cout << "Monto del prestamo: " << capital << " " << tipoCambio << endl;
    cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << endl;

    // Abriedno la base de datos
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    // Verificando si la base de datos se abrió correctamente
    if (rc) {
        cout << "No se pudo abrir la base de datos" << endl;
        return;
    } else {
        cout << "Base de datos abierta" << endl;
    }
    // consulta SQL para insertar los datos del prestamo a la tabla prestamo
    string sqlInsert = "INSERT INTO PRESTAMO (ID_CLIENTE, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL) VALUES (" +
                       to_string(this->cliente.id) + ", '" + tipoCambio + "', '" + tipoInteres + "', " + to_string(cuota) + ", " + to_string(plazo) + ", " + to_string(tasaActual) + ", " + to_string(capital) + ", " + to_string(capital) + ");";

    // Ejecuta la consulta SQL y verifica si hubo errores
    rc = sqlite3_exec(db, sqlInsert.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    } else {
        cout << "Datos del prestamo guardados exitosamente." << endl;
    }

    // Cerrando la base de datos
    sqlite3_close(db);
}







/*****************************************************
 * *****Metodo para ingresar prestamo hipotecario*****
******************************************************/

void Prestamos::ingresar_prestamoHipotecario() {
    int seleccion;
    std::string tipoCambio;
    float tasaActual;

    // Seleccion del tipo de moneda
    do {
        std::cout << "Seleccione el tipo de cambio:" << std::endl;
        std::cout << "1. Colón" << std::endl;
        std::cout << "2. Dólar" << std::endl;
        std::cout << "Ingrese su opción: ";
        std::cin >> seleccion;

        // Verificando si la selección es valida
        if (seleccion < 1 || seleccion > 2) {
            std::cout << "Opción inválida. Inténtelo de nuevo." << std::endl;
        }
    } while (seleccion < 1 || seleccion > 2);

    // Asignando el tipo de cambio y la tasa de interes segun la selección
    switch (seleccion) {
        case 1:
            tipoCambio = "Colones";
            tasaActual = 10.09; // Tasa para Colones
            break;
        case 2:
            tipoCambio = "Dólares";
            tasaActual = 8.39; // Tasa para Dolares
            break;
        default:
            return;
    }

    // Solicitando al usuario los detalles del prestamo
    std::cout << "****Solicitud de Prestamo Hipotecario****" << std::endl;
    std::cout << "Ingrese el monto del préstamo: ";
    std::cin >> capital;

    // Asignanbdo el tipo de interes como fijo y el plazo como 12 meses
    std::string tipoInteres = "fijo"; // Asignacion de tipoInteres
    std::string plazo = "12"; // Plazo en meses

    // Calcula el pago mensual basado en la fórmula de cuota fija
    float tasaInteresMensual = tasaActual / 12 / 100; // Tasa de interés mensual
    float factor = pow(1 + tasaInteresMensual, std::stoi(plazo)); // Calcula el factor para la formula de cuota fija
    float cuota = capital * (tasaInteresMensual * factor) / (factor - 1); // Calcula la cuota mensual

    // Mostrando los detalles del préstamo calculado
    std::cout << "****Detalles del prestamo****" << std::endl;
    std::cout << "Tipo de interés: " << tipoInteres << std::endl;
    std::cout << "Tasa de interés anual (%): " << tasaActual << std::endl;
    std::cout << "Plazo en meses: " << plazo << std::endl;
    std::cout << "Monto del préstamo: " << capital << " " << tipoCambio << std::endl;
    std::cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << std::endl;

    // Abriendo la base de datos 
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    // Verifica si la base de datos se abri correctamente
    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return;
    } else {
        std::cout << "Base de datos abierta" << std::endl;
    }

    // Construye la consulta para insertar los datos del prestamo
    std::string sqlInsert = "INSERT INTO PRESTAMO (ID_CLIENTE, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL) VALUES (" +
                            std::to_string(cliente.id) + ", '" + tipoCambio + "', '" + tipoInteres + "', " + std::to_string(cuota) + ", " + plazo + ", " + std::to_string(tasaActual) + ", " + std::to_string(capital) + ", " + std::to_string(capital) + ");";

    // Ejecuta la consulta SQL y verifica errores
    rc = sqlite3_exec(db, sqlInsert.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Datos del prestamo guardados exitosamente." << std::endl;
    }

    // Cierra la base de datos
    sqlite3_close(db);
}












/*****************************************************
 * *****Metodo para ingresar prestamo Prendario*******
******************************************************/
void Prestamos::ingresar_prestamoPrendario() {
    int seleccion;
    std::string tipoCambio;
    float tasaActual;
    // Seleccion del tipo de moneda
    do {
        std::cout << "Seleccione el tipo de cambio:" << std::endl;
        std::cout << "1. Colón" << std::endl;
        std::cout << "2. Dólar" << std::endl;
        std::cout << "Ingrese su opción: ";
        std::cin >> seleccion; // guardando la opcion sleccionada

        if (seleccion < 1 || seleccion > 2) {
            std::cout << "Opción inválida. Inténtelo de nuevo." << std::endl;
        }
    } while (seleccion < 1 || seleccion > 2);

    switch (seleccion) {
        case 1:
            tipoCambio = "Colones"; // el tipo de moneda en colones
            tasaActual = 16.34;     // la tasa actual para colones
            break;
        case 2:
            tipoCambio = "Dólares"; // el tipo de monera en dolares
            tasaActual = 11.08;     // la tasa actual en dolares
            break;
        default:
            
            return;
    }
    // Solicitando el monto
    std::cout << "****Solicitud de Préstamo Prendario****" << std::endl;
    std::cout << "Ingrese el monto del préstamo: ";
    std::cin >> capital;
    std::string tipoInteres = "fijo"; // Asignación de tipoInteres
    std::string plazo = "6"; 

    // Calcular el pago mensual basado en la fórmula de cuota fija
    float tasaInteresMensual = tasaActual / 12 / 100; // Tasa de interés mensual
    float factor = pow(1 + tasaInteresMensual, std::stoi(plazo));
    float cuota = capital * (tasaInteresMensual * factor) / (factor - 1);

    std::cout << "****Detalles del préstamo****" << std::endl;
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

    // Construir la consult para insertar los datos 
    std::string sqlInsert = "INSERT INTO PRESTAMO (ID_CLIENTE, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL) VALUES (" +
                            std::to_string(cliente.id) + ", '" + tipoCambio + "', '" + tipoInteres + "', " + std::to_string(cuota) + ", " + plazo + ", " + std::to_string(tasaActual) + ", " + std::to_string(capital) + ", " + std::to_string(capital) + ");";

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
