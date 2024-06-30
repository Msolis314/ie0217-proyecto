/*! @file menu.hpp
 @brief Header file de la clase Menu
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