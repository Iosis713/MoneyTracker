#pragma once
#ifndef MENU
#define MENU

#include <algorithm>
#include <iostream>
#include <type_traits>

#include "Category.hpp"
#include "Transaction.hpp"
#include "TransactionsManager.hpp"
#include "Printer.hpp"
#include "FileManager.hpp"

using ManagerPtr = std::shared_ptr<TransactionsManager>;

enum class Options : int
{
    EXIT = 0,
    ADD_TRANSACITON = 1,
    FIND_TRANSACTION_BY_DATE = 2,
    REMOVE_TRANSACTION = 3,
    SAVE_TRANSACTION_TO_FILE = 4,
    LOAD_TRANSACTION_FROM_FILE = 5,
    DISPLAY_ALL_TRANSACTIONS = 6
};

struct Menu
{
    ManagerPtr managerPtr_;

    Menu();
    virtual ~Menu() = default;

    Menu(ManagerPtr sourceManagerPtr);

    void Clear() const;
    void DisplayAllTransactions(std::shared_ptr<Printer> printer) const;
    void DisplayOptions() const;  
    bool SelectOption() const;
    
private:
    void AddTransactionUI() const;
    Date FindTransactionsByDateUI() const;
    FileManager FileManagerUI() const;
    void PrintTransaction(const std::shared_ptr<Transaction>&) const;
};

#endif
