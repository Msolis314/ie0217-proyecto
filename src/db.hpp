#ifndef DB_HPP //DB_HPP
#define DB_HPP

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
T returnValue(void *data, int argc, char **argv, char **azColName) {
    T value;

    *(T*)data =  (T)argv[0];
    
};

#endif // DB_HPP