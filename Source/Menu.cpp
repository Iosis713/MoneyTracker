#include "Headers/Menu.hpp"

Menu::Menu(ManagerPtr sourceManager)
    : managerPtr_(sourceManager)
{};

void Menu::displayAllTransactions() const
{
    Printer printer;
    const auto& categories = managerPtr_->categories;
    for (const auto& transaction : managerPtr_->GetTransactions())
    {
        printer.Print(transaction, categories);
    }
    
}