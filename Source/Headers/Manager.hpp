#pragma once
#ifndef MANAGER
#define MANAGER

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "Transaction.hpp"

using TransactionManager = std::vector<std::shared_ptr<Transaction>>;

class Manager
{
protected:
    TransactionManager manager_;

public:
    Manager();
    ~Manager() = default;
    
    void addTransaction(const std::array<uint16_t, 3>& date, const float value, const std::string& description);
    void addTransaction(const Transaction& transaction);

    void readFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    std::shared_ptr<Transaction>& selectByTransactionDescription(std::string& description);
    std::shared_ptr<Transaction>& selectByTransactionNumber(const uint16_t number);
};
#endif

