#include "Headers/Category.hpp"

void Category::AddCategory(CategoryPair&& categoryPair)
{
    categories_.push_back(categoryPair);
}
