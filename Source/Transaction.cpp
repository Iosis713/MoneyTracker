#include "Headers/Transaction.hpp"

Transaction::Transaction(float value, std::string description, Date date, int categoryID)
    : transactionID_(IDGenerator::id++)
    , value_(value)
    , description_(description)
    , date_(date)
    , categoryID_(categoryID)
{};

void Transaction::UpdateCategoryID(const int categoryID) {categoryID_ = categoryID;}
void Transaction::UpdateDescription(const std::string& description) {description_ = description;}
void Transaction::UpdateValue(const float value) {value_ = value;}
void Transaction::UpdateDate(const Date& date) {date_ = date;}

int Transaction::GetTransactionID() const {return this->transactionID_;}
float Transaction::GetValue() const {return this->value_;}
std::string Transaction::GetDescription() const {return this->description_;};
Date Transaction::GetDate() const {return this->date_;}
int Transaction::GetCategoryID() const {return this->categoryID_;}

bool Transaction::operator==(const Transaction& rhs) const
{
    bool result = true;
    result &= value_ == rhs.GetValue();
    result &= description_ == rhs.GetDescription();
    result &= date_ == rhs.GetDate();
    result &= categoryID_ == rhs.GetCategoryID();

    return result;
}