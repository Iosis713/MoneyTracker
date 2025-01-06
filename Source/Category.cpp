#include "Headers/Category.hpp"

void Category::AddCategory(CategoryPair&& categoryPair)
{
    categories_.push_back(categoryPair);
}

bool Category::ValidateCategoryID(const int categoryID) const
{
    return std::ranges::any_of(categories_, [&categoryID](const auto& element)
            {
                return element.first == categoryID;
            });
}

bool Category::operator==(const Category& rhs) const
{
    bool result = std::all_of(categories_.begin(), categories_.end(), [&](const auto& el)
        {
            return std::any_of(rhs.categories_.begin(), rhs.categories_.end(), [&](const auto& rhsEl)
                {
                    return rhsEl == el;
                });
        });

    return result;
}