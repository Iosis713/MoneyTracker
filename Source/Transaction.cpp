#include "Headers/Transaction.hpp"

Transaction::Transaction(Date date, float value, std::string description)
    : date_(date)
    , value_(value)
    , description_(description)
{}

Date Transaction::getDate() const
{
    return this->date_;
}

std::string Transaction::getDescription() const
{
    return this->description_;
}

float Transaction::getValue() const
{
    return this->value_;
}

void Transaction::setDate(const unsigned int day, const unsigned int month, const unsigned int year)
{
    //day validation
    if((month == 1 or month == 3 or month == 5 or month == 7 or
        month == 8 or month == 10 or month == 12) and day <= 31)
    {
        date_[0] = day;
    }
    else if((month == 4 or month == 6 or month == 9 or month == 11) and day <= 30)
    {
        date_[0] = day;
    }
    else if(month == 2 and (year % 4 != 0 ) and day <= 28)
    {
        date_[0] = day;
    }
    else if(month == 2 and (year % 4 == 0) and day <= 29)
    {
        date_[0] = day;
    }
    else
    {
        throw std::runtime_error("INVALID DATE: DAY!");
    }
    
    //month validation
    if(month > 0 and month <= 12)
    {
        date_[1] = month;
    }
    else
    {
        throw std::runtime_error("INVALID DATE: MONTH!");
    }
    
    date_[2] = year;
}

void Transaction::setDescription(const std::string& description)
{
    description_ = description;
}

void Transaction::setValue(const float value)
{
    value_ = value;
}

