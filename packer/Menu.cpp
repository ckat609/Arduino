#include "Arduino.h"
#include "Menu.h"

Menu::Menu()
{
}

void Menu::rootMenu()
{
    if (_update)
    {
        Serial.println("[MENU]");
        printDivider();

        for (int i = 0; i < CURRENT_COUNT; i++)
        {
            showSelected(i, CURRENT_OPTION);
            Serial.println(CURRENT_TITLES[i]);
        }

        _update = false;

        printDivider();
    }
}

void Menu::updateMenu()
{
    _update = true;
}

void Menu::accept()
{
    switch (CURRENT_PAGE)
    {
    case ROOT_MENU:
        CURRENT_COUNT = 0;
        CURRENT_COUNT = ROOT_MENU_COUNT;
        CURRENT_TITLES = ROOT_MENU_TITLES;
        updateMenu();
    case SUB_MENU1:
        CURRENT_COUNT = 0;
        CURRENT_COUNT = SUB_MENU1_COUNT;
        CURRENT_TITLES = SUB_MENU1_TITLES;
        updateMenu();
        break;
    case SUB_MENU2:
        CURRENT_COUNT = 0;
        CURRENT_COUNT = SUB_MENU2_COUNT;
        CURRENT_TITLES = SUB_MENU2_TITLES;
        updateMenu();
        break;
    }
}

void Menu::nextPage()
{
    if (CURRENT_OPTION < CURRENT_COUNT - 1)
    {
        CURRENT_OPTION++;
    }
    else
    {
        CURRENT_OPTION = 0;
    };
    updateMenu();
}

void Menu::previousPage()
{
    if (CURRENT_OPTION > 0)
    {
        CURRENT_OPTION--;
    }
    else
    {
        CURRENT_OPTION = CURRENT_COUNT - 1;
    };
    updateMenu();
}

void Menu::showSelected(int option, int selected)
{
    if (option == selected)
    {
        Serial.print(">");
    }
    else
    {
        Serial.print(" ");
    };
}

void Menu::printDivider()
{
    Serial.println("===============");
}