#pragma once
#ifndef MENU
#define MENU

#include <algorithm>
#include <chrono>
#include <iostream>
#include <type_traits>
#include <thread>

#include "Category.hpp"
#include "Transaction.hpp"
#include "TransactionsManager.hpp"
#include "Printer.hpp"
#include "FileManager.hpp"

using ManagerPtr = std::shared_ptr<TransactionsManager>;

/*
TO DO:
Find by value lessThan/greaterThan - 
Options for found transaction - 
    - GetBalance
    - Update
    - Remove
RemoveUI - 

*/

enum class Options : int
{
    EXIT = 0,
    ADD_TRANSACITON = 1,
    FIND_TRANSACTION = 2,
    REMOVE_TRANSACTION = 3,
    SAVE_TRANSACTION_TO_FILE = 4,
    LOAD_TRANSACTION_FROM_FILE = 5,
    DISPLAY_ALL_TRANSACTIONS = 6
};

enum class OptionsForTransactionsFinding : int
{
    VALUE = 1,
    DATE = 2,
    TRANSACTION_CATEGORY = 3,

    CATEGORY_ID = 11,
    CATEGORY_NAME = 12
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
    int OptionSelectionUI() const;
};

#endif
