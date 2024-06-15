#ifndef MENU_HPP
#define MENU_HPP

int menu();
enum MenuOptions{
    ATENCION = 1,
    CONSULTA = 2,
    SALIRMENU= 3
};

class Menu{
    public:
        Menu();
        int showMainMenu();

        int getOption();
        void showAtencionMenu();
        void showConsultaMenu();
        void returnToMainMenu();

};
#endif // MENU_HPP