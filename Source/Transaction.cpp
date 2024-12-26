#include "Headers/Transaction.hpp"

Transaction::Transaction(const int transactionID, float value, std::string description, Date date, int categoryID)
    : transactionID_(transactionID)
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

