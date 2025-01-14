#include "Headers/Menu.hpp"

Menu::Menu()
    :managerPtr_(std::make_shared<TransactionsManager>())
{};

Menu::Menu(ManagerPtr sourceManager)
    : managerPtr_(sourceManager)
{};

void Menu::AddTransactionUI() const
{
    /*Perhaps it could be modified to use also in FileManager*/
    float value = 0;
    std::string description = "";
    int year = 1900;
    unsigned int month = 0;
    unsigned int day = 0;
    int categoryID = 0;
    std::string categoryName = "";

    std::cout << "\nEnter value of transaction: " << std::flush;
    std::cin >> value;
    std::cout << "\nEnter description of transaction: " << std::flush;
    std::cin >> description;
    std::cout << "\nEnter year of transaction: " << std::flush;
    std::cin >> year;
    std::cout << "\nEnter month (numeric) of transaction: " << std::flush;
    std::cin >> month;
    std::cout << "\nEnter day (numeric) of transaction: " << std::flush;
    std::cin >> day;
    Date date = std::chrono::year_month_day(std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day});
    std::cout << "\nEnter category name of transaction: " << std::flush;
    std::cin >> categoryName;

    //const auto& availableCategories = managerPtr_->categories.categories_;
    if (std::none_of(managerPtr_->categories.categories_.begin(),
                     managerPtr_->categories.categories_.end(), 
            [&](const auto& element)
            {
                return element.second == categoryName;
            })
        )
    {
        std::cout << "\nEnter category ID of transaction: " << std::flush;
        std::cin >> categoryID;
        managerPtr_->categories.AddCategory({categoryID, categoryName});
    }
    try
    {
        managerPtr_->AddTransaction(value, description, date, categoryID);
    }
    catch(std::runtime_error& error)
    {
        throw;
    }
}

void Menu::Clear() const
{
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

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
    std::cout << "1. Add transaction\n";
    std::cout << "2. Find transactions By Date\n";
    std::cout << "3. Get transactions\n";
    std::cout << "4. Remove transactions\n";
    std::cout << "5. Save transactions to file\n";
    std::cout << "6. Load transactions from file\n";
    std::cout << "7. Display all transactions\n";
}

Date Menu::FindTransactionsByDateUI() const
{
    int year = 0;
        unsigned int month = 0;
        unsigned int day = 0;
        std::cout << "Provide a date in numeric YYYY/MM/DD format\n";
        std::cout << "Enter the year: \n";
        std::cin >> year;
        std::cout << "\nEnter the month: \n";
        std::cin >> month;
        std::cout << "\nEnter the day: \n";
        std::cin >> day;
        return Date{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
}

bool Menu::SelectOption() const
{
    int currentOption;
    std::cout << "Select your option: ";
    std::cin >> currentOption;

    using enum Options;
    switch (static_cast<Options>(currentOption))
    {
    case EXIT:
    {
        return false;
        break;
    }
    case ADD_TRANSACITON:
    {
        AddTransactionUI();
        break;
    }
    case FIND_TRANSACTION_BY_DATE:
    {
        managerPtr_->FindTransactionsByDate(FindTransactionsByDateUI());
        break;
    }
    case REMOVE_TRANSACTION:
    {
        break;
    }
    case SAVE_TRANSACTION_TO_FILE:
    {
        break;
    }
    case LOAD_TRANSACTION_FROM_FILE:
    {
        break;
    }
    case DISPLAY_ALL_TRANSACTIONS:
    {
        break;
    }
    default:
        break;
    }
    return true;

}
