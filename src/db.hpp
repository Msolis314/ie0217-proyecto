#ifndef DB_HPP //DB_HPP
#define DB_HPP

#include <stdlib.h>
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
    
};

/// @brief Funcion para retornar un unico string
/// @param data puntero a string
/// @param argc numero de columnas
/// @param argv Resultado de la fila
/// @param azColName Nombre de las columnas
/// @return 
static int stringCallback(void *data, int argc, char **argv, char **azColName);

/// @brief Funcion para retornar un unico entero
/// @param data puntero a entero
/// @param argc numero de columnas
/// @param argv Resultado de la fila
/// @param azColName Nombre de las columnas
/// @return
static int intCallback(void *data, int argc, char **argv, char **azColName);
#endif // DB_HPP