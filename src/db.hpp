/*! @file db.hpp
 @brief Header file de la base de datos
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

/// @brief Funcion para retorn indice aleatorio
/// @return double con indice
double generarIndiceAleatorio();

/// @brief Funcion para actualizar la fecha y el tipo de cambio en la base de datos

/// @return Codigo de error
int updateFecha();

int cleanBankInfo();
#endif // DB_HPP