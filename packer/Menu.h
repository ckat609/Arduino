#ifndef Menu_h
#define Menu_h

class Menu
{
public:
    Menu();
    void rootMenu();
    void positionsMenu();
    void cacaMenu();
    void updateMenu();
    void accept();
    void nextPage();
    void previousPage();

private:
    void showSelected(int option, int selected);
    void printDivider();
    enum rootPages
    {
        ROOT_MENU,
        SUB_MENU1,
        SUB_MENU2
    };
    enum subMenu1Pages
    {
        BAG,
        FUNNEL,
        DROP
    };
    bool _update = true;
    static const int ROOT_MENU_COUNT = 3;
    static const int SUB_MENU1_COUNT = 3;
    static const int SUB_MENU2_COUNT = 4;
    String ROOT_MENU_TITLES[ROOT_MENU_COUNT] = {"Dulces/bolsa", "Posiciones", "Caca"};
    String SUB_MENU1_TITLES[SUB_MENU1_COUNT] = {"Bolsa", "Embudo", "Banda"};
    String SUB_MENU2_TITLES[SUB_MENU2_COUNT] = {"Caca 1", "Caca 2", "Caca 3", "Caca 4"};

    int CURRENT_OPTION = 0;
    int CURRENT_PAGE = ROOT_MENU;
    int CURRENT_COUNT = ROOT_MENU_COUNT;
    String *CURRENT_TITLES = ROOT_MENU_TITLES;
};

#endif