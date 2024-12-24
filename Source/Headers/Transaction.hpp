#pragma once
#ifndef TRANSACTION
#define TRANSACTION

#include <iostream>
#include <string>

struct Transaction
{
    [[maybe_unused]]unsigned transactionID_ = 0; //need to be changed to generate unique IDs
    [[maybe_unused]]float value_ = 0.f;
    [[maybe_unused]]std::string description_ = "Unknown";
    [[maybe_unused]]long date_ = 0; //Need to be chagned to separate struct with enums and validators
    [[maybe_unused]]unsigned categoryID_ = 0; //Need to be changed to separate struct

    Transaction(unsigned transactionID, float value, std::string description, long date, unsigned categoryID);
    ~Transaction() = default;

};

#endif

