#include <iostream>
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

TEST_F(CategoryFixture, CategoryAdding)
{
    //GIVEN
    //WHEN
    category.AddCategory({123, "SomeNewCategory"});

    //THEN
    const auto& lastIter = category.categories_.end() - 1;
    ASSERT_EQ("SomeNewCategory", lastIter->second);
}

TEST_F(CategoryFixture, SearchForCategory)
{
    //WHEN
    const auto& result = category.SearchForCategory(3);

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


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
