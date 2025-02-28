#pragma once
#ifndef CATEGORY
#define CATEGORY

import <algorithm>;
import <iostream>;
import <ranges>;
import <string>;
import <stdexcept>;
import <type_traits>;
import <utility>;
import <vector>;

using CategoryPair = std::pair<int, std::string>;
using VectorOfCategories = std::vector<CategoryPair>;
using CategoriesIterator = std::vector<std::pair<int, std::string>>::const_iterator;
struct Category
{
    VectorOfCategories categories_;
    
    void AddCategory(CategoryPair&& categoryPair);
    bool ValidateCategoryID(const int categoryID) const;

    ~Category() = default;  
    
    /*_______________________________________TEMPLATES__________________________________________*/

    template<typename SearchByType>
    CategoriesIterator SearchForCategory(SearchByType&& searchValue) const
    {        
            auto result = std::ranges::find_if(categories_, [&searchValue](const auto& element)
                    {
                        if constexpr (std::is_same_v<int, std::remove_cvref_t<SearchByType>>)
                            return searchValue == element.first;
                        else if constexpr (std::is_same_v<std::string, SearchByType>)
                            return searchValue == element.second;
                    });
            return result;
    }

    template<typename FoundByType>
    void RemoveCategoryFoundByValue(FoundByType&& foundByValue)
    {   
        categories_.erase(std::remove_if(categories_.begin(), categories_.end(), [&foundByValue](const auto& element)
            {
                if constexpr (std::is_same_v<int, std::remove_cvref_t<FoundByType>>)
                    return foundByValue == element.first;
                else if constexpr(std::is_same_v<std::string, std::remove_cvref_t<FoundByType>>)
                    return foundByValue == element.second;
            }), categories_.end());
    }

    bool operator==(const Category& rhs) const;
};

#endif
