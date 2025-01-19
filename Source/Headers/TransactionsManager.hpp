#pragma once
#ifndef TRANSACTION_MANAGER
#define TRANSACTION_MANAGER

#include "Transaction.hpp"
#include "Category.hpp"

#include <algorithm>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <utility>
#include <vector>

using Transactions = std::vector<std::shared_ptr<Transaction>>;

class TransactionsManager
{
private:
    Transactions transactions_;

public:
    Category categories;

    TransactionsManager() = default;
    ~TransactionsManager() = default;

    void AddTransaction(const float value, const std::string& description, const Date& date, int categoryID);
    Transactions FindTransactionsByDate(const Date& date) const;
    Transactions FindTransactionsByValueInRange(const float bottom, const float upper) const;
    float GetBalance() const;  
    Transactions& GetTransactions() {return this-> transactions_;} 
    void RemoveTransactinons(const Transactions& transactionsToRemove);
    void RemoveTransactinons(const std::vector<int> transactionsIDToRemove);

    void SortTransactionsByCategoryName();
    void SortTransactionsByCategoryID();


    template <typename CategoryIDorName>
    Transactions FindTransactionsByCategory(CategoryIDorName&& categoryIDorName) const
    {
        Transactions transactions{};
        const auto foundCategoryIterator = categories.SearchForCategory(std::forward<std::remove_cvref_t<CategoryIDorName>>(categoryIDorName));
        std::ranges::for_each(transactions_, [&](const auto& transaction)
            {
                if (categories.categories_.end() != foundCategoryIterator and
                    foundCategoryIterator->first == transaction->GetCategoryID())
                {
                    transactions.push_back(transaction);
                }    
            });

        return transactions;
    }
      
};
#endif
