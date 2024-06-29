#include <iostream>
#include <string>
#include <sqlite3.h>
#include <tuple>
#include <limits>
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
Prestamos::Prestamos(std::string nombre, std::string apellido, int id) : cliente(nombre, apellido, id) {}

// Declaración de la función calcularCuotaVariable
float Prestamos::calcularCuotaVariable(float tasaInteres, float indiceReferencia, float capital, int plazo) {
    float tasaMensual = (tasaInteres + indiceReferencia) / 12 / 100;
    float factor = pow(1 + tasaMensual, plazo);
    float cuota = capital * (tasaMensual * factor) / (factor - 1);
    return cuota;
}

// Metodo para solicitar un prestamo
void Prestamos::solicitarPrestamo() {
    int opcion;
    // Presenta al usuario las opciones de tipos de prestamos disponibles
    std::cout << "****Seleccione el tipo de prestamo****" << endl;
    std::cout << "1. Prestamo personal" << endl;
    std::cout << "2. Prestamo hipotecario" << endl;
    std::cout << "3. Prestamo prendario" << endl;
    std::cout << "Opcion: ";
    // Lee la opcion seleccionada por el usuario
    std::cin >> opcion;

    // Dependiendo de la opcion seleccionada, llama a la funcion correspondiente
    switch (opcion) {
        case PERSONAL:
            // Llamando a la funcion para ingresar un prestamo personal
            ingresar_prestamoPersonal();
            break;
        case HIPOTECARIO :
            // Llamando a la función para ingresar un prestamo hipotecario
            ingresar_prestamoHipotecario();
            break;
        case PRENDARIO:
            // Llamando a la función para ingresar un prestamo prendario
            ingresar_prestamoPrendario();
            break;
        default:
            // msj de error
            std::cout << "Opción no valida. Seleccione una opcion valida." << endl;
            break;
    }
}


// Método para obtener Tasa de de interés de la base de datos
float obtenerTasaInteresFija(const std::string& tipoPrestamo, const std::string& tipoMoneda) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    float tasaInteres = 0.0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return tasaInteres;
    }

    std::string columna;

    if (tipoPrestamo == "Personal") {
        columna = (tipoMoneda == "Colones") ? "PERSONAL_COLONES" : "PERSONAL_DOLARES";
    } else if (tipoPrestamo == "Hipotecario") {
        columna = (tipoMoneda == "Colones") ? "HIPOTECARIO_COLONES" : "HIPOTECARIO_DOLARES";
    } else if (tipoPrestamo == "Prendario") {
        columna = (tipoMoneda == "Colones") ? "PRENDARIO_COLONES" : "PRENDARIO_DOLARES";
    } else {
        std::cerr << "Tipo de préstamo no soportado." << std::endl;
        sqlite3_close(db);
        return tasaInteres;
    }

    std::string sql = "SELECT " + columna + " FROM BANKINFO ORDER BY FECHA DESC LIMIT 1";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return tasaInteres;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        tasaInteres = sqlite3_column_double(stmt, 0);
    } else {
        std::cerr << "No se encontró la tasa de interés para la combinación especificada." << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return tasaInteres;
}

std::pair<float, float> obtenerTasaInteresVariable(const std::string& tipoPrestamo, const std::string& tipoMoneda) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    float tasaInteres = 0.0;
    float indiceReferencia = 0.0;
    int rc;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return std::make_pair(tasaInteres, indiceReferencia);
    }

    std::string columna;

    if (tipoPrestamo == "Personal") {
        columna = (tipoMoneda == "Colones") ? "PERSONAL_COLONES" : "PERSONAL_DOLARES";
    } else if (tipoPrestamo == "Hipotecario") {
        columna = (tipoMoneda == "Colones") ? "HIPOTECARIO_COLONES" : "HIPOTECARIO_DOLARES";
    } else if (tipoPrestamo == "Prendario") {
        columna = (tipoMoneda == "Colones") ? "PRENDARIO_COLONES" : "PRENDARIO_DOLARES";
    } else {
        std::cerr << "Tipo de préstamo no soportado." << std::endl;
        sqlite3_close(db);
        return std::make_pair(tasaInteres, indiceReferencia);
    }

    std::string sql = "SELECT " + columna + ", INDICE_REFERENCIA FROM BANKINFO ORDER BY FECHA DESC LIMIT 1";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return std::make_pair(tasaInteres, indiceReferencia);
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        tasaInteres = sqlite3_column_double(stmt, 0);
        indiceReferencia = sqlite3_column_double(stmt, 1);
    } else {
        std::cerr << "No se encontró la tasa de interés para la combinación especificada." << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return std::make_pair(tasaInteres, indiceReferencia);
}


/*****************************************************
 * *****Metodo para ingresar prestamo Personal********
******************************************************/
void Prestamos::ingresar_prestamoPersonal() {
    int seleccion;
    std::string tipoCambio;
    int rightChoice;
    std::string tipoInteres;
    int id_P;
    std::string TipoPrestamo;
    float tasaActual = 0.0;
    float indiceReferencia = 0.0;
    std::string capitalStr;
    int tryCount = 0;
    
    // Ingrear la moneda y la con la opcion correcta.
    do {
        std::cout << "Seleccione el tipo de cambio:\n";
        std::cout << "1. Colon\n";
        std::cout << "2. Dolar\n";
        std::cout << "Ingrese su opción: ";
        cin >> seleccion;

        // Verificando que sea valido
        if (seleccion < COLON || seleccion > DOLAR) {
            cerr << "Opción inválida. Inténtelo de nuevo.\n";
        }
    } while (seleccion < COLON || seleccion > DOLAR || !cin.good());

    // Asigna el tipo de cambio segun la selecciin
    tipoCambio = (seleccion == COLON) ? "Colones" : "Dólares";

    // Solicita al usuario los detalles del prestamo personal
    cout << "****Solicitud de Prestamo Personal****" << endl;
    do {
        cout << "Ingrese el monto del préstamo: ";
        cin >> capitalStr;
        if (tryCount > 0) {
            cliente.returnMain("Por favor ingrese un monto válido");
        }
    }while (!cliente.validarDatos(capitalStr, &capital));

    
    
    do {
        cout << "Ingrese el plazo en meses: ";
        cin >> plazo;
        if (plazo < 1) {
            cout << "El plazo debe ser mayor a 0. Inténtelo de nuevo.\n";
        }
    } while (plazo < 1 || !cin.good());

    id_P = generar_id_prestamo(); // llamada a la funcion para generar el id del prestamo.
    tipoInteres = ingresarTipoInteres(); // llamada a la funcion para validar el tipo de interes.
    TipoPrestamo = "Personal";

    if (tipoInteres == "variable") {
        std::tie(tasaActual, indiceReferencia) = obtenerTasaInteresVariable(TipoPrestamo, tipoCambio);
        if (tasaActual == 0.0 || indiceReferencia == 0.0) {
            std::cerr << "Error al obtener la tasa de interés variable." << std::endl;
            return;
        }
    } else {
        tasaActual = obtenerTasaInteresFija(TipoPrestamo, tipoCambio); // Obteniendo la tasa de interés fija de la base de datos
        if (tasaActual == 0.0) {
            std::cerr << "Error al obtener la tasa de interés fija." << std::endl;
            return;
        }
    }

    
    // Calcular la cuota mensual
    float cuota;
    if (tipoInteres == "fijo") {
        float tasaInteresMensual = tasaActual / 12 / 100;
        float factor = pow(1 + tasaInteresMensual, plazo);
        cuota = capital * (tasaInteresMensual * factor) / (factor - 1);
    } else {
        cuota = calcularCuotaVariable(tasaActual, indiceReferencia, capital, plazo);
    }

    // Muestra los detalles generales del prestamo calculado
    std::cout << "****Detalles del prestamo****" << std::endl;
    std::cout << "Tipo de prestamo: " << TipoPrestamo << std::endl;
    std::cout << "Tipo de interes: " << tipoInteres << std::endl;
    std::cout << "Tasa de interes anual (%): " << tasaActual << std::endl;
    std::cout << "Indice de referencia: " << indiceReferencia << std::endl;
    std::cout << "Plazo en meses: " << plazo << std::endl;
    std::cout << "Monto del prestamo: " << capital << " " << tipoCambio << std::endl;
    std::cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << std::endl;

    // Abriedno la base de datos y guardando el préstamo
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    // Verificando si la base de datos se abrió correctamente
    if (rc) {
        cerr << "No se pudo abrir la base de datos" << endl;
        return;
    } else {
        cout << "Base de datos abierta" << endl;
    }

    // Consulta SQL para insertar los datos del préstamo en la tabla PRESTAMO
    std::string sqlInsert = "INSERT INTO PRESTAMO (ID_PRESTAMO,ID_CLIENTE, TIPO_PRESTAMO, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL, INTERESES_ABONADOS) VALUES (" +
                            std::to_string(id_P) + "," + std::to_string(this->cliente.id) +  ",'" + TipoPrestamo + "', '" + tipoCambio + "', '" + tipoInteres + "', " + std::to_string(cuota) + ", " + std::to_string(plazo) + ", " + std::to_string(tasaActual) + ", " + std::to_string(capital) + ", " + std::to_string(capital) + ", 0);";

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
    int rightChoice;
    std::string tipoInteres;
    int id_P;
    std::string TipoPrestamo;
    float tasaActual = 0.0;
    float indiceReferencia = 0.0;
    std::string capitalStr;
    int tryCount = 0;

    // Seleccion del tipo de moneda
    do {
        std::cout << "Seleccione el tipo de cambio:" << std::endl;
        std::cout << "1. Colón" << std::endl;
        std::cout << "2. Dólar" << std::endl;
        std::cout << "Ingrese su opción: ";
        std::cin >> seleccion;

        // Verificando si la selección es valida
        if (seleccion < COLON || seleccion > DOLAR) {
            std::cerr << "Opción inválida. Inténtelo de nuevo." << std::endl;
        }
    } while (seleccion < COLON || seleccion > DOLAR || !std::cin.good());

    // Asignando el tipo de cambio y la tasa de interes segun la selección
     tipoCambio = (seleccion == COLON) ? "Colones" : "Dólares";

    // Solicitando al usuario los detalles del prestamo
    std::cout << "****Solicitud de Prestamo Hipotecario****" << std::endl;
    do {
        std::cout << "Ingrese el monto del préstamo: ";
        std::cin >> capitalStr;
        if (tryCount > 0) {
            cliente.returnMain("Por favor ingrese un monto válido");
        }
    } while (!cliente.validarDatos(capitalStr, &capital));

    do {
        std::cout << "Ingrese el plazo en meses: ";
        std::cin >> plazo;
        if (plazo < 1) {
            std::cout << "El plazo debe ser mayor a 0. Inténtelo de nuevo.\n";
        }
    } while (plazo < 1 || !std::cin.good());

    id_P = generar_id_prestamo();
    tipoInteres = ingresarTipoInteres();
    TipoPrestamo = "Hipotecario";

    if (tipoInteres == "variable") {
        std::tie(tasaActual, indiceReferencia) = obtenerTasaInteresVariable(TipoPrestamo, tipoCambio);
        if (tasaActual == 0.0 || indiceReferencia == 0.0) {
            std::cerr << "Error al obtener la tasa de interés variable." << std::endl;
            return;
        }
    } else {
        tasaActual = obtenerTasaInteresFija(TipoPrestamo, tipoCambio); // Obteniendo la tasa de interés fija de la base de datos
        if (tasaActual == 0.0) {
            std::cerr << "Error al obtener la tasa de interés fija." << std::endl;
            return;
        }
    }

    // Calcular la cuota mensual
    float cuota;
    if (tipoInteres == "fijo") {
        float tasaInteresMensual = tasaActual / 12 / 100;
        float factor = pow(1 + tasaInteresMensual, plazo);
        cuota = capital * (tasaInteresMensual * factor) / (factor - 1);
    } else {
        cuota = calcularCuotaVariable(tasaActual, indiceReferencia, capital, plazo);
    }

    // Mostrar los detalles del préstamo calculado
    std::cout << "****Detalles del préstamo****" << std::endl;
    std::cout << "Tipo de préstamo: " << TipoPrestamo << std::endl;
    std::cout << "Tipo de interés: " << tipoInteres << std::endl;
    std::cout << "Tasa de interés anual (%): " << tasaActual << std::endl;
    std::cout << "Índice de referencia: " << indiceReferencia << std::endl;
    std::cout << "Plazo en meses: " << plazo << std::endl;
    std::cout << "Monto del préstamo: " << capital << " " << tipoCambio << std::endl;
    std::cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << std::endl;


    // Abriendo la base de datos y guardar el préstamo
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    // Verifica si la base de datos se abrio correctamente
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos" << std::endl;
        return;
    } else {
        std::cout << "Base de datos abierta" << std::endl;
    }

    // Consulta SQL para insertar los datos del préstamo en la tabla PRESTAMO
    std::string sqlInsert = "INSERT INTO PRESTAMO (ID_PRESTAMO,ID_CLIENTE, TIPO_PRESTAMO, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL, INTERESES_ABONADOS) VALUES (" +
                            std::to_string(id_P) + "," + std::to_string(this->cliente.id) +  ",'" + TipoPrestamo + "', '" + tipoCambio + "', '" + tipoInteres + "', " + std::to_string(cuota) + ", " + std::to_string(plazo) + ", " + std::to_string(tasaActual) + ", " + std::to_string(capital) + ", " + std::to_string(capital) + ", 0);";

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
    int rightChoice;
    std::string tipoInteres;
    int id_P;
    std::string TipoPrestamo;
    float tasaActual = 0.0;
    float indiceReferencia = 0.0;
    std::string capitalStr;
    int tryCount = 0;

    // Seleccion del tipo de moneda
    do {
        std::cout << "Seleccione el tipo de cambio:" << std::endl;
        std::cout << "1. Colón" << std::endl;
        std::cout << "2. Dólar" << std::endl;
        std::cout << "Ingrese su opción: ";
        std::cin >> seleccion; // guardando la opcion seleccionada

        if (seleccion < COLON || seleccion > DOLAR) {
            std::cerr << "Opción inválida. Inténtelo de nuevo." << std::endl;
        }
    } while (seleccion < COLON || seleccion > DOLAR || !std::cin.good());

    tipoCambio = (seleccion == COLON) ? "Colones" : "Dólares";

    std::cout << "****Solicitud de Préstamo Prendario****" << std::endl;
    do {
        std::cout << "Ingrese el monto del préstamo: ";
        std::cin >> capitalStr;
        if (tryCount > 0) {
            cliente.returnMain("Por favor ingrese un monto válido");
        }
    } while (!cliente.validarDatos(capitalStr, &capital));

    do {
        std::cout << "Ingrese el plazo en meses: ";
        std::cin >> plazo;
        if (plazo < 1) {
            std::cout << "El plazo debe ser mayor a 0. Inténtelo de nuevo.\n";
        }
    } while (plazo < 1 || !std::cin.good());

    id_P = generar_id_prestamo();
    tipoInteres = ingresarTipoInteres();
    TipoPrestamo = "Prendario";

     if (tipoInteres == "variable") {
        std::tie(tasaActual, indiceReferencia) = obtenerTasaInteresVariable(TipoPrestamo, tipoCambio);
        if (tasaActual == 0.0 || indiceReferencia == 0.0) {
            std::cerr << "Error al obtener la tasa de interés variable." << std::endl;
            return;
        }
    } else {
        tasaActual = obtenerTasaInteresFija(TipoPrestamo, tipoCambio); // Obteniendo la tasa de interés fija de la base de datos
        if (tasaActual == 0.0) {
            std::cerr << "Error al obtener la tasa de interés fija." << std::endl;
            return;
        }
    }

    // Calcular la cuota mensual
    float cuota;
    if (tipoInteres == "fijo") {
        float tasaInteresMensual = tasaActual / 12 / 100;
        float factor = pow(1 + tasaInteresMensual, plazo);
        cuota = capital * (tasaInteresMensual * factor) / (factor - 1);
    } else {
        cuota = calcularCuotaVariable(tasaActual, indiceReferencia, capital, plazo);
    }

    // Mostrar los detalles del préstamo calculado
    std::cout << "****Detalles del préstamo****" << std::endl;
    std::cout << "Tipo de préstamo: " << TipoPrestamo << std::endl;
    std::cout << "Tipo de interés: " << tipoInteres << std::endl;
    std::cout << "Tasa de interés anual (%): " << tasaActual << std::endl;
    std::cout << "Índice de referencia: " << indiceReferencia << std::endl;
    std::cout << "Plazo en meses: " << plazo << std::endl;
    std::cout << "Monto del préstamo: " << capital << " " << tipoCambio << std::endl;
    std::cout << "Cuota mensual estimada: " << cuota << " " << tipoCambio << std::endl;

    // Abrir la base de datos y guardar el préstamo
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("SistemaBancario.db", &db);

    if (rc) {
        std::cerr << "No se pudo abrir la base de datos" << std::endl;
        return;
    } else {
        std::cout << "Base de datos abierta" << std::endl;
    }

    // Consulta SQL para insertar los datos del préstamo en la tabla PRESTAMO
    std::string sqlInsert = "INSERT INTO PRESTAMO (ID_PRESTAMO,ID_CLIENTE, TIPO_PRESTAMO, TIPO_CAMBIO, TIPO_INTERES, CUOTA, PLAZO, TASA_INTERES, CAPITAL_OG, CAPITAL_ACTUAL, INTERESES_ABONADOS) VALUES (" +
                            std::to_string(id_P) + "," + std::to_string(this->cliente.id) +  ",'" + TipoPrestamo + "', '" + tipoCambio + "', '" + tipoInteres + "', " + std::to_string(cuota) + ", " + std::to_string(plazo) + ", " + std::to_string(tasaActual) + ", " + std::to_string(capital) + ", " + std::to_string(capital) + ", 0);";
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










/*Llamando a la funcion se ActualIDPrestamos para obtener los ids guardados en la base de datos sql, 
de sistema bancario, de la tabla cliente,*/
void Prestamos::setActualIDPrestamos(){
    sqlite3 *db;                                                           // Declaracion del puntero a sqlite3
    char *zErrMsg = 0;                                                     // Mensaje de error que puede generarlas funciones sql, comienza en cero, porque no hay errores.
    int rc;                                                                // Codigos de retorno, indicando si se ejecuto bien
    rc = sqlite3_open("SistemaBancario.db", &db);                          // abre la base de datos sistema bancario, con el puntero db
    if (rc){                                                               // ejecuta el if, para comprobar si se pudo abrir la base de datos
        std::cout << "No se pudo abrir la base de datos" << std::endl;  
    }else{
        std::cout << "....." << std::endl;
    }

    const char* sql = "SELECT ID_PRESTAMO FROM PRESTAMO";               // Selecciona de la tabla customers los ids_prestamos
    rc = sqlite3_exec(db, sql, callbackPrestamos, this, &zErrMsg);
    if (rc != SQLITE_OK){                                                  // si la funcion sqlite es ok  significa que no hubo errores, entoces se obtiene los ids prestamos.
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;                // mensaje de error
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "IDs de prestamos obtenidos con exito" << std::endl;
    }

};



/*****************************************************
 * ***********Procesar la consulta de datos***********
******************************************************/
int Prestamos::callbackPrestamos(void *data, int argc, char **argv, char **azColName){ // data apunta a prestamos, argc num de columnas, argv arreglo de punteros val columnas
    int i;
    try {
        if (argc < 0){
            throw std::invalid_argument("...");

        }

    } 
    catch (const std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    Prestamos* prestamos = static_cast<Prestamos*>(data);                                    
    for(i = 0;i <argc; i++){                                                       //ciclo for que va iterando desde 0 hasta argc -1
        if (argv[i]){
            prestamos->actualIDPrestamos.push_back(std::stoi(argv[i]));                // agregando los valores de las columnas al vector actualIDPrestamos.
        }                   // agregando los valores de las columnas al vector actualIDPrestamos.

    }
    return 0;
}



/*****************************************************
 * ************Generando un ID prestamo***************
******************************************************/
int Prestamos::generar_id_prestamo() {
    int ID_prestamo = 1; // Empezamos con el ID número 1
    while (checkID_PRESTAMO(ID_prestamo)) {
        ID_prestamo++; // Incrementando el ID hasta encontrar uno disponible
    }
    agregarID_lista(ID_prestamo); // agregando el ID generado a la lista
    return ID_prestamo; // Devolviendo el ID generado
}





/*****************************************************
 * *******Verificando que no exista en la base********
******************************************************/
bool Prestamos::checkID_PRESTAMO(int ID_prestamo){
    std:: vector<int>:: iterator it;
    // desde el inicio de la lista hasta el final, se compara el valor de iterador it con el valor del id proporcionado.
    for (it = actualIDPrestamos.begin(); it != actualIDPrestamos.end(); it++){ // verificando si ya existen en la lista de IDs clientes
        if (*it == ID_prestamo){
            return true; // Si retorna true, ya existe un id igual.
        }
    }
    return false;
}





/*****************************************************
 * *******Agregando el id generado a la lista*********
******************************************************/
void Prestamos::agregarID_lista(int ID_prestamo){
    if (!checkID_PRESTAMO(ID_prestamo)){
        std::cout << "ID agregado con exito" << std::endl;
        actualIDPrestamos.push_back(ID_prestamo);
    }
    std::cout << "El ID ya existe" << std::endl;
    return;
}



/*****************************************************
 * **********Validando ingreso de datos***************
******************************************************/

std::string Prestamos::ingresarTipoInteres(){
    string tipoInteres;
    cout << "Ingrese el tipo de interés (fijo/variable): ";
    cin >> tipoInteres;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Convertir a minúsculas para hacer la comparación sin importar mayúsculas/minúsculas
    for (char &minuscula : tipoInteres) {
        minuscula = tolower(minuscula);
    }

    // Validar la entrada
    while (tipoInteres != "fijo" && tipoInteres != "variable") {
        cout << "Tipo de interés no válido. Ingrese 'fijo' o 'variable': ";
        cin >> tipoInteres;


        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }

    return tipoInteres;
}








/*****************************************************
 * *****  Consultar los prestamos del cliente    *****
******************************************************/

void Prestamos::consultarPrestamos() {
    sqlite3 *db;            // Puntero a la base de datos SQLite
    sqlite3_stmt *stmt;     // Puntero a la declaración SQL preparada
    int rc;                 // Variable para el estado de las operaciones SQLite

    // Abrir la conexión a la base de datos SQLite
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        // En caso de error 
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Construir la consulta SQL
    std::string sql = "SELECT ID_PRESTAMO, TIPO_PRESTAMO, PLAZO, CUOTA FROM PRESTAMO WHERE ID_CLIENTE = " + std::to_string(this->cliente.id);

    // Preparar la consulta SQL
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        // En caso de error
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Mostrar encabezado de los resultados
    std::cout << "** Listado de préstamos del cliente **" << std::endl;
    std::cout << "ID\tTipo\tPlazo\tCuota" << std::endl;

    bool hayPrestamos = false;  // Variable para controlar si se encontraron 

    // Iterar de los resultados de la consulta
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Obtener los valores de cada columna para el actual
        int idPrestamo = sqlite3_column_int(stmt, 0);                                               // tomando la columna de idprestamo por su indice
        std::string tipoPrestamo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));     // la columna dos es el tipo de prestamode la tabla prestamos
        int plazo = sqlite3_column_int(stmt, 6);                                                    // la seis de plazo
        float cuota = sqlite3_column_double(stmt, 5);                                               // la cinco de cuopta

        // Mostrar cada préstamo encontrado
        std::cout << idPrestamo << "\t" << tipoPrestamo << "\t" << plazo << "\t" << cuota << std::endl;

        hayPrestamos = true;  // Indicar que se encontró al menos un préstamo
    }

    // Si no se encontraron préstamos, mostrar mensaje correspondiente
    if (!hayPrestamos) {
        std::cout << "El cliente no tiene préstamos registrados." << std::endl;
    }

    // Finalizar la consulta 
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
