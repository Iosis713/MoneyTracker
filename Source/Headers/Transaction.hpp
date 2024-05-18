#pragma once
#ifndef TRANSACTION
#define TRANSACTION

#include <array>
#include <iostream>
#include <stdexcept>

using Date = std::array<unsigned int, 3>;

class Transaction
{
protected:
    Date date_{1, 1, 2024};
    float value_ = 0.f;
    std::string description_ = "Unknown";

public:
    Transaction(Date date, float value, std::string description);
    ~Transaction() = default;

    Date getDate() const;
    std::string getDescription() const;    
    float getValue() const;

    void setDate(const unsigned int day, const unsigned int month, const unsigned int year);
    void setDescription(const std::string& description);
    void setValue(const float value);    
};

#endif

