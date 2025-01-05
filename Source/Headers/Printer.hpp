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

    virtual bool Print(transactionPtr transPtr, Category& categories) const;
};

#endif