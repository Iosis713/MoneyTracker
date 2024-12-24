#pragma once
#ifndef CATEGORY
#define CATEGORY

#include <stdexcept>
#include <vector>
#include <string>
#include <utility>
#include <type_traits>

using CategoryPair = std::pair<int, std::string>;
using VectorOfCategories = std::vector<CategoryPair>;
using CategoriesIterator = std::vector<std::pair<int, std::string>>::iterator;
struct Category
{
    VectorOfCategories categories_;
    
    void AddCategory(CategoryPair&& categoryPair);
    ~Category() = default;
    
    template<typename SearchByType>
    CategoriesIterator SearchForCategory(const SearchByType& searchValue)
    {        
        if constexpr(std::is_same_v<std::string, SearchByType>)
        {
            auto result = std::ranges::find_if(categories_, [searchValue](const auto& element)
                    {
                        return searchValue == element.second;
                    });
            return result;
        }
        else 
        {
            auto result = std::ranges::find_if(categories_, [searchValue](const auto& element)
                    {
                        return static_cast<int>(searchValue) == element.first;
                    });
            return result;
        }
    }
};


#endif

