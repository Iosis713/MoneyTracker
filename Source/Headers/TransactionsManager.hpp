#pragma once
#ifndef TRANSACTION_MANAGER
#define TRANSACTION_MANAGER

#include "Transaction.hpp"
#include "Category.hpp"

#include <memory>
#include <vector>
#include <stdexcept>

using Transactions = std::vector<std::shared_ptr<Transaction>>;

class TransactionsManager
{
private:
    Transactions transactions_;

public:
    Category categories;

    TransactionsManager() = default;
    ~TransactionsManager() = default;

    Transactions& GetTransactions() {return this-> transactions_;}

    void AddTransaction(const float value, const std::string& description, const Date date, int categoryID);
};
#endif
