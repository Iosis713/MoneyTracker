#pragma once
#ifndef TRANSACTION
#define TRANSACTION

#include <array>
#include <iostream>
#include <stdexcept>

using Date = std::array<uint16_t, 3>;

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

    void setDate(const uint16_t day, const uint16_t month, const uint16_t year);
    void setDescription(const std::string& description);
    void setValue(const float value);    
};
#endif

