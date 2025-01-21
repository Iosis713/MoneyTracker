#include "Headers/Printer.hpp"


bool Printer::Print(const transactionPtr transaction, const Category& categories) const
{
    if (!categories.ValidateCategoryID(std::forward<int>(transaction->GetCategoryID()))) 
        return false;

    std::cout << std::format("ID: {}   Date: {}   Value: {}   CategoryID: {}   CategoryName: {}   Description: {}\n",
                            transaction->GetTransactionID(),
                            transaction->GetDate(),
                            transaction->GetValue(),
                            transaction->GetCategoryID(),
                            categories.SearchForCategory(transaction->GetCategoryID())->second,
                            transaction->GetDescription());
    
    return true;
}

bool Printer::PrintAllSelectedTransactions(const Transactions& transactions, const Category& categories) const
{
    bool areAllPrinted = true;
    for(const auto& transaction : transactions)
        areAllPrinted &= Print(transaction, categories);

    return areAllPrinted;
}