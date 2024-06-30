#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include "tools.hpp"
#include "db.hpp"

#define SALT_SIZE 16
#define HASH_SIZE 32
#define ITERATIONS 10000


/* Pasos para hashear una contraseña
 * 1. Generar un salt
 * 2. Hashear la contraseña con el salt
 * 3. Almacenar el hash y el salt
 * 4. Para verificar la contraseña, hashear la contraseña con el salt almacenado y comparar con el hash almacenado
 
*/

std::string toHex(const unsigned char *data, size_t len){
    //stringstream para almacenar los bytes
    std::stringstream ss;
    //Establecer el formato de salida a hexadecimal
    ss << std::hex;

    //Recorrer los bytes
    for (size_t i = 0; i < len; ++i){
        //Agregar el byte al stringstream
        ss << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    //Retornar el stringstream como un string
    return ss.str();
}

std::string genSalt(){
    //Vector de bytes para almacenar el salt
    unsigned char salt[SALT_SIZE];
    //Generar el salt
    RAND_bytes(salt, SALT_SIZE);
    //Retornar el salt como un string
    return toHex(salt, SALT_SIZE);
}

std::string hash(const std::string &password, const std::string &salt){
    //Vector de bytes para almacenar el hash
    unsigned char hash[HASH_SIZE];
    //Hashear la contraseña
    PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), (unsigned char*)salt.c_str(), salt.size(), ITERATIONS, EVP_sha256(), HASH_SIZE, hash);
    //Retornar el hash como un string
    return toHex(hash, HASH_SIZE);
}

bool checkPassword(const std::string &password, const std::string &storedsalt, const std::string &storedhash){
    //Hashear la contraseña con el salt almacenado
    std::string newhash = hash(password, storedsalt);
    //Comparar el hash generado con el hash almacenado
    return newhash == storedhash;
}

std::string getPassword(int ID){
    std::string password;
    std::string salt;
    std::string hash;
    sqlite3 *db;
    char *zErrMsg = 0;
    const char * data = "SQLite 3";
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return "";
    }
    std::string sql = "SELECT PASSWORD FROM PASSWORDS WHERE ID_CLIENTE = " + std::to_string(ID) + ";";
    rc = sqlite3_exec(db, sql.c_str(), stringCallback, &password, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "Error en la consulta: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return "";
    }
    return password;
}


std::string getSalt(int ID){
    std::string salt;
    sqlite3 *db;
    char *zErrMsg = 0;
    const char * data = "SQLite 3";
    int rc;
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc){
        std::cout << "No se pudo abrir la base de datos" << std::endl;
        return "";
    }
    std::string sql = "SELECT SALT FROM PASSWORDS WHERE ID_CLIENTE = " + std::to_string(ID) + ";";
    rc = sqlite3_exec(db, sql.c_str(), stringCallback, &salt, &zErrMsg);
    if (rc != SQLITE_OK){
        std::cout << "Error en la consulta: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return "";
    }
    return salt;
}