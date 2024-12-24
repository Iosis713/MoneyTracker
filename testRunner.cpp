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

TEST_F(CategoryFixture, SearchByCategoryID)
{
    //WHEN
    const auto& result = category.SearchForCategory(3);

    //THEN
    ASSERT_EQ(3, result->first);
    ASSERT_EQ("Rent", result->second);    
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
