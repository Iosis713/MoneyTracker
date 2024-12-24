#include "Headers/Transaction.hpp"

Transaction::Transaction(unsigned transactionID, float value, std::string description, long date, int category)
    : transactionID_(transactionID)
    , value_(value)
    , description_(description)
    , date_(date)
    , category_(category)
{};

