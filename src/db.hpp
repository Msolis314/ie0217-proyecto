#ifndef DB_HPP //DB_HPP
#define DB_HPP

#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
/// @brief Funcion que crea la base de datos
/// @return Codigo de error
int crearDB();


/// @brief Funcion que se llama para cada fila del resultado
/// @param NotUsed Primer argumento de la funcion de callback
/// @param argc Numero de columnas en la fila
/// @param argv Resultado de la fila
/// @param azColName Nombre de las columnas
/// @return Codigo de error
static int callback(void *NotUsed, int argc, char **argv, char **azColName);


template <typename T> 
int returnValue(void *data, int argc, char **argv, char **azColName) {
    T value;

    *(T*)data = strtof(argv[0],NULL);
    return 0;
    
};

/// @brief Funcion para retornar un unico string
/// @param data puntero a string
/// @param argc numero de columnas
/// @param argv Resultado de la fila
/// @param azColName Nombre de las columnas
/// @return 
static int stringCallback(void *data, int argc, char **argv, char **azColName){
    std::string *value = (std::string*)data;
    if (argv[0]){
        *value = argv[0];
    }
    return 0;
}

/// @brief Funcion para retornar un unico entero
/// @param data puntero a entero
/// @param argc numero de columnas
/// @param argv Resultado de la fila
/// @param azColName Nombre de las columnas
/// @return
static int intCallback(void *data, int argc, char **argv, char **azColName){
    int *value = (int*)data;
    if (argv[0]){
        *value = atoi(argv[0]);
    }
    return 0;
}

static int floatCallback(void *data, int argc, char **argv, char **azColName){
    
    if (argc > 0){
        float* saldo = static_cast<float*>(data);
        *saldo = std::stof(argv[0]);
    }
    return 0;
}



/// @brief Funcion para retorn la fecha actual
/// @return string con la fecha actual
std::string getFecha();

/// @brief Funcion para actualizar la fecha y el tipo de cambio en la base de datos

/// @return Codigo de error
int updateFecha();

int cleanBankInfo();
#endif // DB_HPP