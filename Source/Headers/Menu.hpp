#pragma once
#ifndef MENU
#define MENU

import <algorithm>;
import <chrono>;
import <concepts>;
import <iostream>;
import <type_traits>;
import <thread>;

#include "Category.hpp"
#include "Transaction.hpp"
#include "TransactionsManager.hpp"
#include "Printer.hpp"
#include "FileManager.hpp"

using ManagerPtr = std::shared_ptr<TransactionsManager>;

template<class T>
concept IsTrivialType = std::is_trivial_v<T>;

enum class Options : int
{
    EXIT = 0,
    ADD_TRANSACTION = 1,
    FIND_TRANSACTION = 2,
    SAVE_TRANSACTIONS_TO_FILE = 3,
    LOAD_TRANSACTIONS_FROM_FILE = 4,
    DISPLAY_ALL_TRANSACTIONS = 5
};

enum class OptionsForTransactionsFinding : int
{
    VALUE = 1,
    DATE = 2,
    TRANSACTION_CATEGORY = 3,

    CATEGORY_ID = 11,
    CATEGORY_NAME = 12,
};

enum class OptionsForFoundTransactions : int
{
    EXIT = 0,
    UPDATE = 1,
    REMOVE = 2,
    GET_BALANCE = 3
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
    void DisplayOptionsForFoundTransactions() const;
    bool SelectOption() const;
    
private:
    void AddTransactionUI() const;
    Date FindTransactionsByDateUI() const;
    FileManager FileManagerUI() const;

    template<IsTrivialType Type>
    Type OptionSelectionUI() const
    {
        Type selectedOption;
        std::cin >> selectedOption;
        if (!std::cin.good())
        {
            std::cin.clear();
            std::cin.ignore();
            throw std::invalid_argument("Invalid argument. Please enter the number!");
        }
        return selectedOption;
    }

    void FindTransactionsByCategoryUI(Transactions& foundTransactions) const;
    bool ExecuteSelectedOptionForFoundTransactions(const int option, Transactions& foundTransactions) const;

};

#endif
