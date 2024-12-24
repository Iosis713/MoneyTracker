#include <iostream>
#include "Source/Category.cpp"
#include "Source/Transaction.cpp"
#include "gtest/gtest.h"

struct CategoryFixture : public testing::Test
{
    Category category;
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


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
