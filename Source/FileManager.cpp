#include "Headers/FileManager.hpp"

FileManager::FileManager(const std::string& filepath, const std::string& filename) 
    : filepath_(filepath)
    , filename_(filename)
{}

bool FileManager::SaveToFile(TransactionsManager& transactionsManager) const
{
    std::string fullPathAndName = "";
    if ("" != filepath_)
        fullPathAndName += filepath_;
    fullPathAndName += filename_ + ".txt";

    std::fstream file(fullPathAndName);
    if (!file.is_open())
        return false;
    else
    {
        /*Format of file extraction is like Transaction fields order*/
        for (const auto& transaction : transactionsManager.GetTransactions())
        {
            file << transaction->GetTransactionID() << ",";
            file << transaction->GetValue() << ",";
            file << transaction->GetDescription() << ",";
            file << transaction->GetDate() << ",";
            file << transaction->GetCategoryID() << "\n";
            file << "Something";
        }
        return true;
    }
}

