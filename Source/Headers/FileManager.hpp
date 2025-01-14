#pragma once
#ifndef FILEMANAGER
#define FILEMANAGER

#include <fstream>

#include "Category.hpp"
#include "Transaction.hpp"
#include "TransactionsManager.hpp"

struct FileManager
{
    std::string filepath_{""};
    std::string filename_{""};
    
    FileManager() = default;
    FileManager(const std::string& filepath, const std::string& filename);
    FileManager(const std::string& filename);
    ~FileManager() = default;

    bool LoadFromFile(TransactionsManager& transactionsManager);
    bool SaveToFile(TransactionsManager& transactionsManager) const;

private:
    std::string GetFullPathAndName() const;
};

#endif
