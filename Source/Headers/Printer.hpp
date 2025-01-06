#pragma once
#ifndef PRINTER
#define PRINTER

#include <iostream>
#include <memory>

#include "Transaction.hpp"
#include "Category.hpp"

using transactionPtr = std::shared_ptr<Transaction>;

struct Printer
{
    Printer() = default;
    virtual ~Printer() = default;

    bool Print(transactionPtr transPtr, const Category& categories) const;
};

#endif