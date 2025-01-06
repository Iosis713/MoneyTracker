#include "Headers/Menu.hpp"

Menu::Menu(ManagerPtr sourceManager)
    : managerPtr_(sourceManager)
{};

void Menu::DisplayAllTransactions(std::shared_ptr<Printer> printer) const
{
    const auto& categories = managerPtr_->categories;
    for (const auto& transaction : managerPtr_->GetTransactions())
    {
        printer->Print(transaction, categories);
    }
}