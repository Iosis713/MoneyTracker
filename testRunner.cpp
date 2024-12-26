#include <iostream>
#include <string>
#include "Source/Category.cpp"
#include "Source/Transaction.cpp"
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
    Transaction transaction{1,
                            100.f,
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

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
