#include "Headers/Transaction.hpp"

Transaction::Transaction(unsigned transactionID, float value, std::string description, long date, int categoryID)
    : transactionID_(transactionID)
    , value_(value)
    , description_(description)
    , date_(date)
    , categoryID_(categoryID)
{};

