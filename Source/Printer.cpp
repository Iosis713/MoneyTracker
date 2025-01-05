#include "Headers/Printer.hpp"

bool Printer::Print(transactionPtr transPtr, Category& categories) const
{
    if (!categories.ValidateCategoryID(std::forward<int>(transPtr->GetCategoryID()))) 
        return false;

    std::cout << "TransactionID: " << transPtr->GetTransactionID() << "   ";
    std::cout << "Value: " << transPtr->GetValue() << "   ";
    std::cout << "Date: " << transPtr->GetDate() << "   ";
    std::cout << "Description: " << transPtr->GetDescription() << "   ";
    const auto categoryName = categories.SearchForCategory(std::forward<int>(transPtr->GetCategoryID()))->second;
    std::cout << "Category: " << categoryName << "   \n";
    return true;
}
