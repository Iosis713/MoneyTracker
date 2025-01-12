#include <iostream>
#include <string>
#include <tuple>

#include "Source/Headers/Category.hpp"
#include "Source/Headers/Transaction.hpp"
#include "Source/Headers/TransactionsManager.hpp"
#include "Source/Headers/Printer.hpp"
#include "Source/Headers/Menu.hpp"
#include "Source/Headers/FileManager.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

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

/*____________________________PRINTER MOCKS____________________________*/

struct PrinterMock : public Printer
{
    /*      returnedT funcName,                                 arguments                  ,    atributes*/
    //bool Print(std::shared_ptr<Transaction> transType, Category& categories) const override {Printer::Print(transType, categories);}
    MOCK_METHOD(bool, Print, (std::shared_ptr<Transaction> transType, const Category& categories), (const, override));
};

struct PrinterMockFixture : public testing::TestWithParam<std::tuple<int, std::string, bool>>
{
    PrinterMock printerMock;
};

TEST_P(PrinterMockFixture, PrintingSingleTransaction)
{
    //GIVEN
    const auto [catID, catDesc, expectedResult] = GetParam();
    Category categories;
    categories.AddCategory({catID, catDesc});
    const auto transactionToPrint = std::make_shared<Transaction>(200.f,
                                       "FuelFull",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(3)},
                                       2);
    EXPECT_CALL(printerMock, Print(transactionToPrint, categories)).WillOnce(::testing::Return(expectedResult));
   
    //WHEN
    bool result = printerMock.Print(transactionToPrint, categories);

    //THEN
    ASSERT_EQ(expectedResult, result);
}

TEST_F(PrinterMockFixture, MenuPrinting)
{
    //GIVEN
    auto transactionMan = std::make_shared<TransactionsManager>();
    transactionMan->categories.AddCategory({2, "Fuel"});
    transactionMan->categories.AddCategory({3, "Rent"});
    transactionMan->AddTransaction(200.f,
                                 "FuelFull",
                                 std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(3)},
                                 2);
    transactionMan->AddTransaction(1500.f,
                                 "Flat",
                                 std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(4)},
                                 3);

    Menu menu(transactionMan);
    std::shared_ptr<PrinterMock> printerMockPtr = std::make_shared<PrinterMock>();
    EXPECT_CALL(*printerMockPtr, Print(::testing::_, transactionMan->categories)).Times(2);
    
    //WHEN
    menu.DisplayAllTransactions(printerMockPtr);
}

INSTANTIATE_TEST_SUITE_P(SinglePrintingInstantion, PrinterMockFixture, testing::Values(
    std::make_tuple<int, std::string, bool>(2, "Fuel", true),
    std::make_tuple<int, std::string, bool>(3, "Rent", false)));

/*_________________________________FileManager________________________________*/

struct FileManagerFixutre : public testing::TestWithParam<std::tuple<std::string, bool>>
{
    TransactionsManager transactionsManagerToLoad;
    TransactionsManager transactionsManagerToSave;

    void SetUp() override;
};

TEST_P(FileManagerFixutre, LoadingAndSavingFile)
{
    //GIVEN
    const auto& [expectedFilename, expectedStatus] = GetParam();

    //WHEN
    bool resultLoading = false;
    try
    {
        resultLoading= FileManager("", expectedFilename).LoadFromFile(transactionsManagerToLoad);
    }
    catch(std::runtime_error& error)
    {
        std::cerr << "Error catched: " << error.what() << '\n';
    }
    resultLoading &= 1 == transactionsManagerToLoad.GetTransactions().size();

    //THEN
    ASSERT_EQ(expectedStatus, resultLoading);
    std::remove("TestFileUT.txt");
}

INSTANTIATE_TEST_SUITE_P(LoadingSavingInstation, FileManagerFixutre, testing::Values(
    std::make_tuple<std::string, bool>("TestFileUT", true),
    std::make_tuple<std::string, bool>("SomeInvalidName", false)));

/*_______________________________________MAIN_____________________________________*/

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
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




void FileManagerFixutre::SetUp()
{
    Category categories;
    categories.AddCategory({2, "Fuel"});
    transactionsManagerToSave.categories.AddCategory({2, "Fuel"});
    transactionsManagerToSave.AddTransaction(200.f,
                                       "FuelFull",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(3)},
                                       2);

    FileManager("", "TestFileUT").SaveToFile(transactionsManagerToSave);
}