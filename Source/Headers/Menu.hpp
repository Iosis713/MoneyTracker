#pragma once
#ifndef MENU
#define MENU

#include <iostream>

#include "Transaction.hpp"
#include "Manager.hpp"

class Menu
{
protected:

public:
    Menu(Manager manager);
    ~Menu() = default;

    void displayOptions();
};
#endif

