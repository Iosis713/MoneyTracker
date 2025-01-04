#include "Headers/TransactionsManager.hpp"

void TransactionsManager::AddTransaction(const float value, const std::string& description, const Date date, int categoryID)
{
    if (categories.ValidateCategoryID(categoryID))
        transactions_.push_back(std::make_shared<Transaction>(value, description, date, categoryID));
    else
        throw std::runtime_error("Invalid category. Please check availbe categories or add new one!");
}

void TransactionsManager::SortTransactionsByCategoryName()
{
    std::sort(transactions_.begin(), transactions_.end(),//categories 
        [&](const auto& first, const auto& second)
            {
                const auto firstCategoryName = categories.SearchForCategory(first->GetCategoryID());
                const auto secondCategoryName = categories.SearchForCategory(second->GetCategoryID());

                return firstCategoryName->second  < secondCategoryName->second;
            });
}

void TransactionsManager::SortTransactionsByCategoryID()
{
    std::ranges::sort(transactions_,
            [&](const auto& first, const auto& second)
            {
                const auto firstCategoryID = categories.SearchForCategory(first->GetCategoryID());
                const auto secondCategoryID = categories.SearchForCategory(second->GetCategoryID());

                return firstCategoryID->first  < secondCategoryID->first;
            });
}
Transactions TransactionsManager::FindTransactionsByDate(const Date date) const
{
    Transactions transactions{};
    std::ranges::for_each(transactions_, [&](const auto& transaction)
        {
            if (date == transaction->GetDate())
                transactions.push_back(transaction);
        });

    return transactions;
}