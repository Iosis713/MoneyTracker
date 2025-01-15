#include "Headers/FileManager.hpp"

FileManager::FileManager(const std::string& filepath, const std::string& filename) 
    : filepath_(filepath)
    , filename_(filename)
{}

FileManager::FileManager(const std::string& filename)
    : filepath_("")
    , filename_(filename)
{}

bool FileManager::LoadFromFile(TransactionsManager& transactionsManager)
{
    std::string fullPathAndName = GetFullPathAndName();

    std::fstream file(fullPathAndName);

    if (file.is_open())
    {
        float value = 0;
        std::string description = "";
        int year = 1900;
        unsigned int month = 0;
        unsigned int day = 0;
        int categoryID = 0;
        std::string categoryName = "";
        std::string buffer;
        
        
        while(getline(file, buffer, ';'))
        {
            value = std::stof(buffer);
            getline(file, buffer, ';');
            description = buffer;
            getline(file, buffer, '-');
            year = std::stoi(buffer);
            getline(file, buffer, '-');
            month = std::atoi(buffer.c_str());
            getline(file, buffer, ';');
            day = std::stoi(buffer);
            Date date = std::chrono::year_month_day(std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day});
            getline(file, buffer, ';');
            categoryID = std::stoi(buffer);
            getline(file, buffer, '\n');
            categoryName = buffer;
            //if category not found -- add
            const auto& availableCategories = transactionsManager.categories.categories_;
            if (std::none_of(availableCategories.begin(), availableCategories.end(), 
                    [&](const auto& element)
                    {
                        return element.first == categoryID;
                    })
                )
            {
                transactionsManager.categories.AddCategory({categoryID, categoryName});
            }

            try
            {
                transactionsManager.AddTransaction(value, description, date, categoryID);
            }
            catch(std::runtime_error& error)
            {
                throw;
            }
            
        };
        return true;
    }
    return false;
}

bool FileManager::SaveToFile(TransactionsManager& transactionsManager) const
{
    std::string fullPathAndName = GetFullPathAndName();

    std::fstream file(fullPathAndName, file.out);
    if (file.is_open())
    {
        /*Format of file extraction is like Transaction fields order*/
        for (const auto& transaction : transactionsManager.GetTransactions())
        {
            file << transaction->GetValue() << ';';
            file << transaction->GetDescription() << ';';
            file << transaction->GetDate() << ';';
            file << transaction->GetCategoryID() << ';';
            file << transactionsManager.categories.SearchForCategory(transaction->GetCategoryID())->second << '\n';
        }
        file.flush();
        return true;
    }
    else
        return false;
}

std::string FileManager::GetFullPathAndName() const
{
    std::string fullPathAndName = "";
    if ("" != filepath_)
        fullPathAndName += filepath_;
    fullPathAndName += filename_ + ".txt";
    return fullPathAndName;
}

