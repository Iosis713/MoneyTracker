#include <iostream>
#include <string>
#include "Source/Category.cpp"
#include "Source/Transaction.cpp"
#include "Source/TransactionsManager.cpp"
#include "gtest/gtest.h"

struct CategoryFixture : public testing::Test
{
    Category category;

    void SetUp() override
    {
        category.AddCategory({1, "Food"});
        category.AddCategory({2, "Fuel"});
        category.AddCategory({3, "Rent"});
    }
};

/*_____________________________CATEGORY TESTS___________________________________*/

TEST_F(CategoryFixture, CategoryAdding)
{
    //GIVEN
    //WHEN
    category.AddCategory({123, "SomeNewCategory"});

    //THEN
    const auto& lastIter = category.categories_.end() - 1;
    ASSERT_EQ("SomeNewCategory", lastIter->second);
}

TEST_F(CategoryFixture, SearchForCategoryByID)
{
    //WHEN
    const auto& result = category.SearchForCategory(3);

    //THEN
    ASSERT_EQ(3, result->first);
    ASSERT_EQ("Rent", result->second);    
}

TEST_F(CategoryFixture, SearchForCategoryByString)
{
    //WHEN
    const auto& result = category.SearchForCategory(std::forward<std::string>("Rent"));

    //THEN
    ASSERT_EQ(3, result->first);
    ASSERT_EQ("Rent", result->second);    
}


TEST_F(CategoryFixture, RemovedCategoryByIDRvalue)
{
    //WHEN
    category.RemoveCategoryFoundByValue(3);
    
    //THEN
    const auto& result = category.categories_.end() - 1;
    ASSERT_EQ("Fuel", result->second);
}

TEST_F(CategoryFixture, RemovedCategoryByIDLvalue)
{
    //WHEN
    const int integer = 3;
    category.RemoveCategoryFoundByValue(integer);
    
    //THEN
    const auto& result = category.categories_.end() - 1;
    ASSERT_EQ("Fuel", result->second);
}

TEST_F(CategoryFixture, RemoveCategoryByNameRvalue)
{
    //WHEN
    category.RemoveCategoryFoundByValue(std::forward<std::string>("Food"));

    //THEN
    ASSERT_EQ("Fuel", category.categories_.begin()->second);
    ASSERT_EQ(2, category.categories_.begin()->first);
}

TEST_F(CategoryFixture, RemoveCategoryByNameLvalue)
{
    //WHEN
    const std::string str = "Food";
    category.RemoveCategoryFoundByValue(str);

    //THEN
    ASSERT_EQ("Fuel", category.categories_.begin()->second);
    ASSERT_EQ(2, category.categories_.begin()->first);
}

TEST_F(CategoryFixture, CategoryIDValidation)
{
    //WHEN
    bool resultTrue = category.ValidateCategoryID(3);
    bool resultFalse = category.ValidateCategoryID(1000000);
        
    //THEN
    ASSERT_TRUE(resultTrue);
    ASSERT_FALSE(resultFalse);
}

/*__________________________TRANSACTION TESTS_________________________*/

class TransactionFixture : public testing::Test
{
public:
    Transaction transaction{100.f,
                            "SomeDescription",
                            std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(1)},
                            4};
};

TEST_F(TransactionFixture, UpdateDateTest)
{
    //GIVEN
    using namespace std::chrono;
    const auto expectedDate = year_month_day{2024y, January, 1d};

    //WHEN
    transaction.UpdateDate({2024y, January, 1d});

    //THEN
    ASSERT_EQ(expectedDate, transaction.GetDate());
}

TEST_F(TransactionFixture, TransactionIDTest)
{
    //GIVEN
    Transaction otherTransaction{200.f,
                            "SomeOtherDescription",
                            std::chrono::year_month_day{std::chrono::year(1900), std::chrono::June, std::chrono::day(13)},
                            5};

    //THEN
    ASSERT_NE(transaction.GetTransactionID(), otherTransaction.GetTransactionID());
}

/*____________________________TRANSACTION MANAGER_______________________________*/

class TransactionsManagerFixture : public testing::Test
{
public:
    TransactionsManager transactionsManager;

    void SetUp() override;
};

TEST_F(TransactionsManagerFixture, TransactionsManagerSortingByCategoryName)
{
    //WHEN
    transactionsManager.SortTransactionsByCategoryName();
    const auto firstCategoryName = transactionsManager.categories.SearchForCategory(transactionsManager.GetTransactions().at(0)->GetCategoryID())->second;

    //THEN
    ASSERT_EQ("Entertainment", firstCategoryName);
}

TEST_F(TransactionsManagerFixture, TransactionsManagerSortingByCategoryID)
{
    //WHEN
    transactionsManager.SortTransactionsByCategoryID();
    const auto firstCategoryID = transactionsManager.categories.SearchForCategory(transactionsManager.GetTransactions().at(0)->GetCategoryID())->first;

    //THEN
    ASSERT_EQ(1, firstCategoryID);
}

TEST_F(TransactionsManagerFixture, TransactionsManagerFindByDate)
{
    //GIVEN
    std::chrono::year_month_day dateToFind{std::chrono::year(2020), std::chrono::May, std::chrono::day(2)};
    const auto result = transactionsManager.FindTransactionsByDate(dateToFind);

    ASSERT_EQ(transactionsManager.GetTransactions().at(2)->GetTransactionID(), result.at(0)->GetTransactionID());
}

TEST_F(TransactionsManagerFixture, RemovingByTransactions)
{
    //GIVEN
    Transactions toRemove{};
    toRemove.push_back(std::make_shared<Transaction>(200.f,
                                       "FuelFull",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(3)},
                                       2));
    
    //WHEN
    transactionsManager.RemoveTransactinons(toRemove);

    //THEN
    ASSERT_EQ(3, transactionsManager.GetTransactions().size());
}

TEST_F(TransactionsManagerFixture, EmptyTransactionsToRemove)
{
    //GIVEN
    Transactions toRemove{};
    
    //WHEN
    transactionsManager.RemoveTransactinons(toRemove);

    //THEN
    ASSERT_EQ(4, transactionsManager.GetTransactions().size());
}

TEST_F(TransactionsManagerFixture, RemovingTransactionsToRemoveByID)
{
    //GIVEN
    std::vector<int> toRemove;
    toRemove.push_back(transactionsManager.GetTransactions().at(0)->GetTransactionID());
    toRemove.push_back(transactionsManager.GetTransactions().at(1)->GetTransactionID());
    
    //WHEN
    transactionsManager.RemoveTransactinons(toRemove);

    //THEN
    ASSERT_EQ(2, transactionsManager.GetTransactions().size());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void TransactionsManagerFixture::SetUp()
{
    transactionsManager.categories.AddCategory({1, "Food"});
    transactionsManager.categories.AddCategory({2, "Fuel"});
    transactionsManager.categories.AddCategory({3, "Rent"});
    transactionsManager.categories.AddCategory({4, "Entertainment"});

    transactionsManager.AddTransaction(200.f,
                                       "FuelFull",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(3)},
                                       2);

    transactionsManager.AddTransaction(100.f,
                                       "SomeEntertainment",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(1)},
                                       4);

    transactionsManager.AddTransaction(35.f,
                                       "Cheese burger",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(2)},
                                       1);

    transactionsManager.AddTransaction(1500.f,
                                       "Flat",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(4)},
                                       3);
};
