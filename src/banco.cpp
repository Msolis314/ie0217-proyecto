// Incluyendo las librerias
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sqlite3.h>
#include <regex>
#include <stdexcept>
#include <sstream>
#include <type_traits>
#include "entidadBancaria.hpp"
#include "banco.hpp"
#include "db.hpp"
#include "cliente.hpp"
#include "tools.hpp"

#define NUMTRIES 3

// Definiendo el constructor
Banco::Banco(){
    // Llamando las funciones dentro del constructor.
    setActualIDs();
    setActualIDPrestamos();
    setActualIDCuentas();
}



/*Llamando a la funcion se actualIDs para obtener los ids guardados en la base de datos sql, 
de sistema bancario, de la tabla cliente,*/
void Banco::setActualIDs(){
    sqlite3 *db;                                                       // Declaracion del puntero a sqlite3
    char *zErrMsg = 0;                                                 // Mensaje de error que puede generarlas funciones sql, comienza en cero, porque no hay errores.
    int rc;                                                            // Codigos de retorno, indicando si se ejecuto bien
    rc = sqlite3_open("SistemaBancario.db", &db);                      // Abriendo la base de datos    

    if (rc){                                                           // se ejecuta un if, si no genera errores, mostrar mensaje de exito, sino de error
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;   // Base de datos abierta
    }

    const char* sql = "SELECT ID FROM CUSTOMERS";                      // Tomando todos los ids de la tabla customers
    rc = sqlite3_exec(db, sql, callback, this, &zErrMsg);              // db puntero,consulta sql, callback toma filas.
    if (rc != SQLITE_OK){                                              // Si no es sqlite_ok ocurrio un error y se muestra,
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "IDs obtenidos con exito" << std::endl;           // si se obtuvieron bien los ids.
    }

    
};


/*Llamando a la funcion se ActualIDCuentas para obtener los ids guardados en la base de datos sql, 
de sistema bancario, de la tabla cliente,*/
void Banco::setActualIDCuentas(){
    sqlite3 *db;                                                        // Declaracion del puntero a sqlite3
    char *zErrMsg = 0;                                                  // Mensaje de error que puede generarlas funciones sql, comienza en cero, porque no hay errores.
    int rc;                                                             // Codigos de retorno, indicando si se ejecuto bien
    rc = sqlite3_open("SistemaBancario.db", &db);                       // Abriendo la base de datos  
    if (rc){                                                            // se ejecuta un if, si no genera errores, mostrar mensaje de exito, sino de error
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    const char* sql = "SELECT ID_CUENTA FROM CUSTOMERS";                // Tomando todos los ids_cuentas de la tabla customers
    rc = sqlite3_exec(db, sql, callbackCuentas, this, &zErrMsg);        // db puntero,consulta sql, callback toma filas.
    if (rc != SQLITE_OK){                                               // Si no es sqlite_ok ocurrio un error y se muestra,
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "IDs de cuentas obtenidos con exito" << std::endl; // si se obtuvieron bien los ids de las cuentas.
    }

    
};  

// Procesando los datos de la consulta sql
int Banco::callback(void *data, int argc, char **argv, char **azColName){ // data apunta a banco, argc num de columnas, argv arreglo de punteros val columnas
    int i;
    Banco* banco = static_cast<Banco*>(data);                             //  accediendo al objeto banco.                
    for(i = 0;i <argc; i++){                                              //ciclo for que va iterando desde 0 hasta argc -1
        banco->actualIDs.push_back(std::stoi(argv[i]));                   // agregando los valores de las columnas al vector actualIDs.
                                                                         

    }
}

// Procesando los datos de la consulta sql
int Banco::callbackPrestamos(void *data, int argc, char **argv, char **azColName){ // data apunta a banco, argc num de columnas, argv arreglo de punteros val columnas
    int i;
    Banco* banco = static_cast<Banco*>(data);                                      //  accediendo al objeto banco. 
    for(i = 0;i <argc; i++){                                                       //ciclo for que va iterando desde 0 hasta argc -1
        banco->actualIDPrestamos.push_back(std::stoi(argv[i]));                    // agregando los valores de las columnas al vector actualIDPrestamos.

    }
}
// Procesando los datos de la consulta sql
int Banco::callbackCuentas(void *data, int argc, char **argv, char **azColName){ // data apunta a banco, argc num de columnas, argv arreglo de punteros val columnas
    int i;
    Banco* banco = static_cast<Banco*>(data);                                    //  accediendo al objeto banco.
    for(i = 0;i <argc; i++){                                                     //ciclo for que va iterando desde 0 hasta argc -1
        banco->actualIDCuentas.push_back(std::stoi(argv[i]));                    // agregando los valores de las columnas al vector actualIDPrestamos.

    }
}

int Banco::callbackClientes(void *data, int argc, char **argv, char **azColName){ // data apunta a banco, argc num de columnas, argv arreglo de punteros val columnas
    int i;
    Banco* banco = static_cast<Banco*>(data);                                     //  accediendo al objeto banco.
    if (argc == 0){                                                               // si argc es cero significa que no se encontraron clientes con esos datos
        std::cout << "No se encontraron clientes con esos datos" << std::endl;
        return 1;
    } else {
        return 0;
    }
}



/*Llamando a la funcion se ActualIDPrestamos para obtener los ids guardados en la base de datos sql, 
de sistema bancario, de la tabla cliente,*/
void Banco::setActualIDPrestamos(){
    sqlite3 *db;                                                           // Declaracion del puntero a sqlite3
    char *zErrMsg = 0;                                                     // Mensaje de error que puede generarlas funciones sql, comienza en cero, porque no hay errores.
    int rc;                                                                // Codigos de retorno, indicando si se ejecuto bien
    rc = sqlite3_open("SistemaBancario.db", &db);                          // abre la base de datos sistema bancario, con el puntero db
    if (rc){                                                               // ejecuta el if, para comprobar si se pudo abrir la base de datos
        std::cout << "No se pudo abrir la base de datos" << std::endl;  
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    const char* sql = "SELECT ID_PRESTAMO_C FROM CUSTOMERS";               // Selecciona de la tabla customers los ids_prestamos
    rc = sqlite3_exec(db, sql, callbackPrestamos, this, &zErrMsg);
    if (rc != SQLITE_OK){                                                  // si la funcion sqlite es ok  significa que no hubo errores, entoces se obtiene los ids prestamos.
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;                // mensaje de error
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "IDs de prestamos obtenidos con exito" << std::endl;
    }

    
};


// Generando un ID unico para cada cliente.
int Banco::generarID(){
    int id = 0;                     // Iniciando el primer id
    while (true){
        if (!checkIDExists(id)){    // verifica que el id no exista ya
            return id;              // si el id no existe, se le da se habilita para un cliente.
        }
        id++;                       // si el id ya existe, se aumenta en 1 y se vuelve a hacer el proceso.
    }
}

// Generando el verificador de ids
bool Banco::checkIDExists(int id){
    std:: vector<int>:: iterator it;
    // desde el inicio de la lista hasta el final, se compara el valor de iterador it con el valor del id proporcionado.
    for (it = actualIDs.begin(); it != actualIDs.end(); it++){ // verificando si ya existen en la lista de IDs clientes
        if (*it == id){
            return true; // Si retorna true, ya existe un id igual.
        }
    }
    return false;
}

// Generando la logica de la funcion para agregar clientes.
void Banco::agregarCliente(std::string nombre, std::string apellido,std::string password){ 
    sqlite3 *db;                                                        // Puntero de que se va usar a la base de datos
    char *zErrMsg = 0;                                                  // mensaje de error
    int rc;                                                             // codigo de retorno, indicador de si se ejecuto bien
    rc = sqlite3_open("SistemaBancario.db", &db);                       // abriendo la base de datos sistema bancario
    if (rc){                                                            // if para verificar que se abrio correctamente
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }
    
    int id = generarID();                                               // generar un id unico para el cliente, se llama la funcion
    // Haciendo una consulta SQL para insertar un nuevo cliente
    std::string sql = "INSERT INTO CUSTOMERS (ID, NOMBRE, APELLIDO) VALUES (" + std::to_string(id) + ", '" + nombre + "', '" + apellido + "');";
    const char* data = sql.c_str();                                     // Usando Sqlite
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);     
    if (rc != SQLITE_OK){                                               // si todo se ejecuta bien en el if, el cliente se agrega con exito, sino msj error
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Cliente agregado con exito" << std::endl;         //cliente agregado.
    }

    // Encriptando la contraseña
    std::string salt = genSalt();                                       // generando un salt
    std::string hashPassword = hash(password, salt);                    // hasheando la contraseña
    // Haciendo una consulta SQL para insertar la contraseña hasheada

    sql = "INSERT INTO PASSWORDS (ID, SALT, PASSWORD) VALUES (" + std::to_string(id) + ", '" + salt + "', '" + hashPassword + "');";
    data = sql.c_str();
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK){                                               // si todo se ejecuta bien en el if, la contraseña se agrega con exito, sino msj error
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "Contraseña agregada con exito" << std::endl;      //contraseña agregada.
    }


    sqlite3_close(db);                                                  // salir de la base de datos o cerrando la base de datos.
    this->actualIDs.push_back(id);
}

//  metodo para Consultar locs clientes existentes
void Banco::consultarClientes(std::string nombre, std::string apellido){ // dos parametros nombre y apellidos
    sqlite3 *db;                                                         // puntero db
    char *zErrMsg = 0;                                                   // msj de error
    int rc;                                                              // codigo de retorno
    rc = sqlite3_open("SistemaBancario.db", &db);                        // abriendo base de datos
    if (rc){                                                             // verificando que se abre la db correctamente.
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }
    // usando un selec de la tabla clientes para nombre
    std::string sql = "SELECT * FROM CUSTOMERS WHERE NOMBRE = '" + nombre + "' AND APELLIDO = '" + apellido + "';";
    const char* data = sql.c_str();
    rc = sqlite3_exec(db, data, callbackClientes, this, &zErrMsg);       // ejecutando la consulta.
    if (rc != SQLITE_OK){                                                // Verificando que se encuentre algun cliente.
        std::cout << "No se encontraron clientes con esos datos " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else {
        std::cout << "Consulta realizada con exito" << std::endl;
    }
    

}

bool Banco::validarNombre(std::string nombre){
    //^: Inicio de la cadena
    //[a-zA-Z]: Cualquier letra de la a a la z, mayúscula o minúscula
    //+: Uno o más caracteres
    //$: Fin de la cadena
    std::regex regex("^[a-zA-Z]+$"); // Expresion regular para validar el nombre
    if (std::regex_match(nombre, regex)){ // Si el nombre cumple con la expresion regular
        return true;
    } else {
        return false;
    }
}

bool Banco::validarContrasena(std::string contrasena){
    //^: Inicio de la cadena
    //(?=.*[a-z]): Al menos una letra minúscula
    //(?=.*[A-Z]): Al menos una letra mayúscula
    //(?=.*\d): Al menos un dígito
    //[a-zA-Z\d]: Cualquier letra de la a a la z, mayúscula o minúscula o dígito
    //{8,}: Al menos 8 caracteres
    //$: Fin de la cadena
    std::regex regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$"); // Expresion regular para validar la contraseña
    if (std::regex_match(contrasena, regex)){ // Si la contraseña cumple con la expresion regular
        return true;
    } else {
        return false;
    }
}

bool Banco::checkifClienteExists(std::string nombre, std::string apellido){
    sqlite3 *db;                                                        // puntero db
    char *zErrMsg = 0;                                                  // msj de error
    int rc;                                                             // codigo de retorno
    rc = sqlite3_open("SistemaBancario.db", &db);                       // abriendo base de datos
    if (rc){                                                            // verificando que se abre la db correctamente.
        std::cout << "No se pudo abrir la base de datos" << std::endl;
    }else{
        std::cout << "Base de datos abierta con exito" << std::endl;
    }
    // usando un selec de la tabla clientes para nombre
    std::string sql = "SELECT * FROM CUSTOMERS WHERE NOMBRE = '" + nombre + "' AND APELLIDO = '" + apellido + "';";
    const char* data = sql.c_str();
    rc = sqlite3_exec(db, data, NULL, 0, &zErrMsg);       // ejecutando la consulta.
    if (rc != SQLITE_OK){                                                // Verificando que se encuentre algun cliente.
        std::cout << "No se encontraron clientes con esos datos " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    else {
        std::cout << "Consulta realizada con exito" << std::endl;
        return true;
    }

}
// Generando login.
void Banco::login(){
    std::string nombre;
    std::string apellido;

    try {
        std::cout << "Ingrese su nombre: ";
        std::cin >> nombre;
        std::cout << "Ingrese su apellido: ";
        std::cin >> apellido;
        if (!validarNombre(nombre) || !validarNombre(apellido)){
            throw std::invalid_argument("Nombre o apellido invalido");
        }
        if (!checkifClienteExists(nombre, apellido)){
            throw std::invalid_argument("El cliente no existe");
        }
    
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "Que desea hacer?" << std::endl;
        std::string choice;
        int* opcion;
        while(!(this->validarEntrada<int>(choice,opcion)) || *opcion < 1 || *opcion > 3){
            std::cout << "1. Intentar de nuevo" << std::endl;
            std::cout << "2. Registrarse como nuevo cliente" << std::endl;
            std::cout << "3. Salir" << std::endl;
            std::cin >> choice;   
        }

        switch (*opcion)
        {
        case LOGIN:
            login();
            break;
        case REGISTRO:
            signUp();
            break;
        case SALIR:
            return;
            break;
        
        default:
            break;
        }
        
    }

    std::string password;
        while (true){
            std::cout << "Ingrese su contraseña: ";
            std::cin >> password;
            if (password == ""){
                throw std::invalid_argument("Contraseña invalida");
            } else {
                break;
            }
        }
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        rc = sqlite3_open("SistemaBancario.db", &db);
        if (rc){
            std::cout << "No se pudo abrir la base de datos" << std::endl;
        }else{
            std::cout << "Base de datos abierta con exito" << std::endl;
        }
        std::string sql = "SELECT ID FROM CUSTOMERS WHERE NOMBRE = '" + nombre + "' AND APELLIDO = '" + apellido + "';";
        const char* data = sql.c_str();
        void* id;
        rc = sqlite3_exec(db, data, intCallback, id, &zErrMsg);
        if (rc != SQLITE_OK){
            std::cout << "SQL ERROR: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }else{
            std::cout << "Consulta realizada con exito" << std::endl;
        }

        std::string storedPassword = getPassword(*(int*)id);
        std::string storedSalt = getSalt(*(int*)id);
        int i;
        for (i = 0; i < NUMTRIES; i++){
            if (checkPassword(password, storedSalt, storedPassword)){
                std::cout << "Login exitoso" << std::endl;
                break;
            } else {
                std::cout << "Contraseña incorrecta, intento " << i + 1 << " de " << NUMTRIES << std::endl;
                std::cout << "Ingrese su contraseña: ";
                std::cin >> password;
            }
        }
        if (i == NUMTRIES){
            std::cout << "Demasiados intentos, bloqueando cuenta" << std::endl;
            return;
        }

}

void Banco::signUp(){
    std::string nombre;
    std::string apellido;
    std::string password;
    std::string password2;
    while(!validarNombre(nombre)){
        std::cout << "Ingrese su nombre: ";
        std::cin >> nombre;
    }
    while(!validarNombre(apellido)){
        std::cout << "Ingrese su apellido: ";
        std::cin >> apellido;
    }

    while(!validarContrasena(password)){
        std::cout << "Ingrese su contraseña: ";
        std::cin >> password;
    }
    while(!validarContrasena(password2) || password != password2){
        std::cout << "Ingrese su contraseña de nuevo: ";
        std::cin >> password2;
    }
    agregarCliente(nombre, apellido, password);
}