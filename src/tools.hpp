#ifndef TOOL_HPP
#define TOOL_HPP

#include <iostream>
#include <vector>
#include <string>

/// @brief Función para convertir un string a un vector de bytes
/// @param data string a convertir
/// @param len tamaño del string
/// @return bytes del string
std::string toHex(const unsigned char *data, size_t len);


/// @brief Funcion para generar un salt
/// @note Se utiliza para hashear contraseñas
/// @return salt
std::string genSalt();

/// @brief Funcion para hashear una contraseña
/// @param password contraseña a hashear
/// @param salt salt a utilizar
std::string hash(const std::string &password, const std::string &salt);

bool checkPassword(const std::string &password, const std::string &storedsalt, const std::string &storedhash);

/// @brief Funcion para obtener una contraseña
// Tal vez deveria ir en la clase Cliente
std::string getPassword(int ID);

std::string getSalt(int ID);


#endif // TOOL_HPP