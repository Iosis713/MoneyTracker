#include "Headers/Category.hpp"

void Category::AddCategory(CategoryPair&& categoryPair)
{
    categories_.push_back(categoryPair);
}

bool Category::ValidateCategoryID(const int categoryID)
{
    return std::ranges::any_of(categories_, [&categoryID](const auto& element)
            {
                return element.first == categoryID;
            });
}

