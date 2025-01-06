#pragma once
#ifndef MENU
#define MENU

#include <iostream>

#include "Category.hpp"
#include "Transaction.hpp"
#include "TransactionsManager.hpp"
#include "Printer.hpp"

using ManagerPtr = std::shared_ptr<TransactionsManager>;

struct Menu
{
    ManagerPtr managerPtr_;

    Menu() = default;
    virtual ~Menu() = default;

    Menu(ManagerPtr sourceManagerPtr);

    void DisplayAllTransactions(std::shared_ptr<Printer> printer) const;

};

#endif
