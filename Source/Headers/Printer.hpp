#pragma once
#ifndef PRINTER
#define PRINTER

#include <iostream>
#include <memory>
#include <vector>

#include "Transaction.hpp"
#include "Category.hpp"

using transactionPtr = std::shared_ptr<Transaction>;
using Transactions = std::vector<transactionPtr>;

struct Printer
{
    Printer() = default;
    virtual ~Printer() = default;

    virtual bool Print(const transactionPtr transPtr, const Category& categories) const;
    virtual bool PrintAllSelectedTransactions(const Transactions& transactions, const Category& categories) const;
};

#endif