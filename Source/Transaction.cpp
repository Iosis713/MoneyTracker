#include "Headers/Transaction.hpp"

Transaction::Transaction(unsigned transactionID, float value, std::string description, long date, unsigned categoryID)
    : transactionID_(transactionID)
    , value_(value)
    , description_(description)
    , date_(date)
    , categoryID_(categoryID)
{};

