#pragma once
#ifndef TRANSACTION
#define TRANSACTION

#include <chrono>
#include <iostream>
#include <string>

using Date = std::chrono::year_month_day;

class Transaction
{
private:
    [[maybe_unused]]const int transactionID_ = 0; //need to be changed to generate unique IDs
    float value_ = 0.f;
    std::string description_ = "Unknown";
    Date date_ = std::chrono::year_month_day(std::chrono::year{2000}, std::chrono::January, std::chrono::day{1});
    int categoryID_ = 0;

public:
    Transaction(int transactionID, float value, std::string description, Date date, int categoryID);
    ~Transaction() = default;
    
    void UpdateCategoryID(const int categoryID);
    void UpdateDate(const Date& date);
    void UpdateDescription(const std::string& description);
    void UpdateValue(const float value);

    int GetTransactionID() const;
    float GetValue() const;
    std::string GetDescription() const;
    Date GetDate() const;
    int GetCategoryID() const;


};

#endif

