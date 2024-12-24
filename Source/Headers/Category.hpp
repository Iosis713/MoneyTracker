#pragma once
#ifndef CATEGORY
#define CATEGORY

#include <vector>
#include <string>
#include <utility>

using CategoryPair = std::pair<unsigned, std::string>;
using VectorOfCategories = std::vector<CategoryPair>;

struct Category
{
    VectorOfCategories categories_;
    
    void AddCategory(CategoryPair&& categoryPair);
    ~Category() = default;
};


#endif

