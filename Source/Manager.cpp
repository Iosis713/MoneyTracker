#include "Headers/Manager.hpp"

Manager::Manager()
{
    manager_.reserve(60);
}

void Manager::addTransaction(const std::array<uint16_t, 3>& date, const float value, const std::string& description)
{
    manager_.push_back(std::make_shared<Transaction>(date, value, description));
}

void Manager::addTransaction(const Transaction& transaction)
{
    manager_.push_back(std::make_shared<Transaction>(transaction));
}

std::shared_ptr<Transaction>& Manager::selectByTransactionNumber(uint16_t number)
{
    if(number > manager_.size())
    {
        throw std::runtime_error("Transaction number is out of range!");
    }
    else
    {
        return manager_[number];
    }    
}

