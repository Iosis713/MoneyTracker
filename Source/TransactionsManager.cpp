#include "Headers/TransactionsManager.hpp"

void TransactionsManager::AddTransaction(const float value, const std::string& description, const Date& date, int categoryID)
{
    if (categories.ValidateCategoryID(categoryID))
        transactions_.push_back(std::make_shared<Transaction>(value, description, date, categoryID));
    else
        throw std::runtime_error("Invalid category. Please check availbe categories or add new one!");
}

Transactions TransactionsManager::FindTransactionsByDate(const Date& date) const
{
    Transactions transactions{};
    std::ranges::for_each(transactions_, [&](const auto& transaction)
        {
            if (date == transaction->GetDate())
                transactions.push_back(transaction);
        });

    return transactions;
}

Transactions TransactionsManager::FindTransactionsByValueInRange(const float bottom, const float upper) const
{
    Transactions transactions{};
    std::ranges::for_each(transactions_, [&](const auto& transaction)
        {
            if (transaction->GetValue() >= bottom && transaction->GetValue() <= upper)
                transactions.push_back(transaction);
        });

    return transactions;
}

float TransactionsManager::GetBalance() const
{
    float balance = 0;
    std::ranges::for_each(transactions_, [&](const auto& transaction)
        {
            balance += transaction->GetValue();
        });
    return balance;
}

float TransactionsManager::GetBalance(const Transactions& transactions) const
{
    float balance = 0;
    std::ranges::for_each(transactions, [&](const auto& transaction)
        {
            balance += transaction->GetValue();
        });
    return balance;
}

void TransactionsManager::RemoveTransactinons(const Transactions& transactionsToRemove)
{
    auto iterToRemove = std::remove_if(transactions_.begin(), transactions_.end(),
        [&](const auto& element)
        {
            bool result = std::ranges::any_of(transactionsToRemove, 
                [&element](const auto& transToRemove)
                {   
                    bool result = true;
                    result &= element->GetValue() == transToRemove->GetValue();
                    result &= element->GetDate() == transToRemove->GetDate();
                    result &= element->GetDescription() == transToRemove->GetDescription();
                    result &= element->GetCategoryID() == transToRemove->GetCategoryID();
                    return result;
                });
            return result;
        });

    transactions_.erase(iterToRemove, transactions_.end());
}

void TransactionsManager::RemoveTransactinons(const std::vector<int>& transactionsIDToRemove)
{
    auto iterToRemove = std::remove_if(transactions_.begin(), transactions_.end(),
        [&](const auto& element)
        {
            bool result = std::ranges::any_of(transactionsIDToRemove, 
                [&element](const auto& transToRemove)
                {   
                    return element->GetTransactionID() == transToRemove;
                });
            return result;
        });

    transactions_.erase(iterToRemove, transactions_.end());
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
