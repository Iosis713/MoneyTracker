#include "Headers/TransactionsManager.hpp"

void TransactionsManager::AddTransaction(const float value, const std::string& description, const Date date, int categoryID)
{
    if (categories.ValidateCategoryID(categoryID))
        transactions_.push_back(std::make_shared<Transaction>(value, description, date, categoryID));
    else
        throw std::runtime_error("Invalid category. Please check availbe categories or add new one!");
}

void TransactionsManager::SortTransactionByCategoryName()
{
    std::sort(transactions_.begin(), transactions_.end(),//categories 
        [&](const auto& first, const auto& second)
            {
                const auto firstCategoryName = categories.SearchForCategory(first->GetCategoryID());
                const auto secondCategoryName = categories.SearchForCategory(second->GetCategoryID());

                return firstCategoryName->second  < secondCategoryName->second;
            });
}