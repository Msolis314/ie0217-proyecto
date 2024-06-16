#ifndef MENU_HPP
#define MENU_HPP

int menu();

/// @brief Enumeracion de las opciones del menu
enum MenuOptions{
    ATENCION = 1,
    CONSULTA = 2,
    SALIRMENU= 3
};

/// @brief Clase que representa el menu
class Menu{
    public:
    /// @brief Constructor de la clase
        Menu();
        /// @brief Metodo para entrar al menu principal
        int showMainMenu();
        /// @brief Metodo para obtener la opcion del menu
        int getOption();
        

};
#endif // MENU_HPP