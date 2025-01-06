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

void Menu::DisplayOptions() const
{
    std::cout << "0. EXIT\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. Find Transactions By Date";
    std::cout << "3. Get Transactions\n";
    std::cout << "4. RemoveTransactions\n";
}