// Incluyendo las librerias
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sqlite3.h>
#include <regex>
#include <random>
#include <set>
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
    //Todavia no esta lista la funcion
    //setActualIDCuentas();
    
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

    const char* sql = "SELECT ID FROM CUSTOMERS;";                      // Tomando todos los ids de la tabla customers
    rc = sqlite3_exec(db, sql, callbackIDs, this, &zErrMsg);              // db puntero,consulta sql, callback toma filas.
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
int Banco::callbackIDs(void *data, int argc, char **argv, char **azColName){ // data apunta a banco, argc num de columnas, argv arreglo de punteros val columnas
    Banco* banco = static_cast<Banco*>(data);
    for (int i = 0; i < argc; i++) {
        if (argv[i]) {
            banco->actualIDs.push_back(std::stoi(argv[i]));
        }
    }
    return 0;
}

// Procesando los datos de la consulta sql
int Banco::callbackPrestamos(void *data, int argc, char **argv, char **azColName){ // data apunta a banco, argc num de columnas, argv arreglo de punteros val columnas
    int i;
    Banco* banco = static_cast<Banco*>(data);                                      //  accediendo al objeto banco. 
    for(i = 0;i <argc; i++){                                                       //ciclo for que va iterando desde 0 hasta argc -1
        if (argv[i]){
            banco->actualIDPrestamos.push_back(std::stoi(argv[i]));                // agregando los valores de las columnas al vector actualIDPrestamos.
        }                   // agregando los valores de las columnas al vector actualIDPrestamos.

    }
    return 0;
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
    std::random_device rd; // Objeto para obtener una semilla aleatoria
    std::mt19937 gen(rd()); // Generador de números aleatorios Mersenne Twister
    std::uniform_int_distribution<> dis(0, 999999999); // Distribución uniforme en el rango 0 a 999999999

    while (true) {
        int id = dis(gen); // Genera un ID aleatorio
        if (!checkIDExists(id)) { // Verifica que el ID no exi
            return id; // Si el ID no existe, se devuelve y se habilita para un cliente.
        }
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

    sql = "INSERT INTO PASSWORDS (ID_CLIENTE, SALT, PASSWORD) VALUES (" + std::to_string(id) + ", '" + salt + "', '" + hashPassword + "');";
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
        if (nombre == "") {
            std::cout << "El nombre no puede estar vacío." << std::endl;
        } else {
            std::cout << "El nombre solo puede contener letras." << std::endl;
        }
        return false;
    }
}

bool Banco::validarContrasena(std::string contrasena){
    /// Debe contener al menos una letra minúscula
    if (!std::regex_search(contrasena, std::regex(".*[a-z].*"))) {
        std::cout << "La contraseña debe contener al menos una letra minúscula." << std::endl;
        return false;
    }

    // Debe contener al menos una letra mayúscula
    if (!std::regex_search(contrasena, std::regex(".*[A-Z].*"))) {
        std::cout << "La contraseña debe contener al menos una letra mayúscula." << std::endl;
        return false;
    }

    // Debe contener al menos un dígito
    if (!std::regex_search(contrasena, std::regex(".*\\d.*"))) {
        std::cout << "La contraseña debe contener al menos un dígito." << std::endl;
        return false;
    }

    // Checar longitud
    if (contrasena.length() < 8) {
        std::cout << "La contraseña debe tener al menos 8 caracteres." << std::endl;
        return false;
    }

    return true;
}
bool Banco::checkifClienteExists(std::string nombre, std::string apellido) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    bool found = false;

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return false;
    } else {
        std::cout << "Base de datos abierta con exito" << std::endl;
    }

    std::string sql = "SELECT * FROM CUSTOMERS WHERE NOMBRE = '" + nombre + "' AND APELLIDO = '" + apellido + "';";

    /*
    Se utiliza la función sqlite3_exec para ejecutar una consulta SQL.
    usa un callback para procesar los resultados de la consulta.
    db: la base de datos
    sql: la consulta SQL
    [](void* foundPtr, int argc, char** argv, char** azColName) -> int: función de callback que se llama para cada fila del resultado
    */
    rc = sqlite3_exec(db, sql.c_str(), [](void* foundPtr, int argc, char** argv, char** azColName) -> int {
        bool* found = static_cast<bool*>(foundPtr);
        *found = true;
        return 0;
    }, &found, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cout << "Error en la consulta SQL: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return found;
}
void Banco::newSession(){
    //Esta funcion se encarga de iniciar una nueva sesion
    std::string choice;
    int* opcion = new int();
    
    //Preguntar si desea iniciar sesion o registrarse como nuevo cliente
    do {
        do {
        std::cout << "\nQue desea hacer?" << std::endl;
        std::cout << "1. Iniciar sesion" << std::endl;
        std::cout << "2. Registrarse como nuevo cliente" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cin >> choice;
        } while (!(std::stringstream(choice) >> *opcion) || (*opcion < 1 || *opcion > 3));
        std::cout << "Opcion: " << *opcion << std::endl;
        switch (*opcion) {
        case LOGIN:
            login();
            //Crear el objeto cliente
            //Aqui se debe desplegar el menu del cliente
            return;
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
    }while(*opcion != SALIR);
    

}


// Generando login.
void Banco::login(){
    //Opcion de login
    std::string nombre;
    std::string apellido;
    int choice;

    do {
        
        std::cout << "\nIngrese su nombre: ";
        std::cin >> nombre;
        if(!validarNombre(nombre)){
            choice = this->returnMain("Nombre invalido");
            switch (choice)
            {
            case RETRY:
                //Intentar de nuevo
                break;
            case RETURN:
                //Salir
                return;
                break;
            default:
                break;
            }
            
        }
        
    } while (!validarNombre(nombre));

    do{
        std::cout << "Ingrese su apellido: ";
        std::cin >> apellido;
        if(!validarNombre(apellido)){
            choice = this->returnMain("Apellido invalido");
            switch (choice)
            {
            case RETRY:
                //Intentar de nuevo
                break;
            case RETURN:
                //Salir
                return;
                break;
            default:
                break;
            }
            
        }
    } while (!validarNombre(apellido));

    try {
        
        //Verificar si el cliente existe
        if (!checkifClienteExists(nombre, apellido)){
            throw std::string("El cliente no existe");
        }
    
    }
    catch (std::string& e) {
        //En caso que no exista el cliente
        //Se le da la opcion de intentar de nuevo, registrarse como nuevo cliente o salir
        std::cout << e << std::endl;
        std::cout << "\nQue desea hacer?" << std::endl;
        std::string choice;
        int* opcion = new int();

        do {
            std::cout << "1. Intentar de nuevo" << std::endl;
            std::cout << "2. Registrarse como nuevo cliente" << std::endl;
            std::cout << "3. Salir" << std::endl;
            std::cin >> choice;
            
        } while (!(std::stringstream(choice) >> *opcion) || (*opcion < 1 || *opcion > 3));
        std::cout << "Opcion: " << *opcion << std::endl;

        switch (*opcion) {
        case LOGIN:
            login();
            break;
        case REGISTRO:
            signUp();
            return;
        case SALIR:
            return;
            break;
        default:
            break;
        }
        
    }

    //En caso de que el cliente exista
        //Solicitar contraseña
    std::string password;
    while (true){
        std::cout << "\nIngrese su contraseña: ";
        std::cin >> password;
        if (password == ""){
            throw std::invalid_argument("Contraseña invalida");
        } else {
            break;
        }
    }

    //Optener el ID del cliente
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return;
    }else{
        std::cout << "...." << std::endl;
    }
    //Hacer una consulta para obtener el ID del cliente
    std::string sql = "SELECT ID FROM CUSTOMERS WHERE NOMBRE = '" + nombre + "' AND APELLIDO = '" + apellido + "';";
    const char* data = sql.c_str();

    //Se usa un puntero para guardar el ID
    void *id = new int();
    rc = sqlite3_exec(db, data, intCallback, id, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "SQL ERROR: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }else{
        std::cout << "...." << std::endl;
    }
    //Comienza el proceso de desencriptar la contraseña
    std::string storedPassword = getPassword(*(int*)id);
    std::string storedSalt = getSalt(*(int*)id);

    //Hay un limite de intentos
    int i;
    for (i = 0; i < NUMTRIES; i++){
        if (checkPassword(password, storedSalt, storedPassword)){
            std::cout << "\nLogin exitoso" << std::endl;
            this->idCliente = *(int*)id;
            this->nombreCliente = nombre;
            this->apellidoCliente = apellido;
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
    system("sleep 1");

}

void Banco::signUp(){
    std::string nombre;
    std::string apellido;
    std::string password;
    std::string password2;
    do {
        std::cout << "\nIngrese su nombre: ";
        std::cin >> nombre;
    } while (!validarNombre(nombre));
    
    do {
        std::cout << "\nIngrese su apellido: ";
        std::cin >> apellido;
    } while (!validarNombre(apellido));
    
    do{
        std::cout << "\nIngrese su contraseña: ";
        std::cin >> password;
    } while (!validarContrasena(password));
    
    do {
        std::cout << "Confirme su contraseña: ";
        std::cin >> password2;
        if (password != password2){
            std::cout << "\nLas contraseñas no coinciden" << std::endl;
        }
    } while ( password != password2);
    
    //Se agrega el cliente a la base de datos
    agregarCliente(nombre, apellido, password);
    std::cout << "\nRegistro exitoso" << std::endl;
}