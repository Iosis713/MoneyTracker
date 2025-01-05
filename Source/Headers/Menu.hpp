#pragma once
#ifndef MENU
#define MENU

#include <iostream>

#include "Category.hpp"
#include "Transaction.hpp"
#include "TransactionsManager.hpp"

using ManagerPtr = std::shared_ptr<TransactionsManager>;

struct Menu
{
    ManagerPtr managerPtr_;

    Menu() = default;
    ~Menu() = default;

    Menu(ManagerPtr sourceManagerPtr);

    void displayAllTransactions() const;

};

#endif
