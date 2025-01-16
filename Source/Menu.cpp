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
    std::string description{};
    int year = 1900;
    unsigned int month = 0;
    unsigned int day = 0;
    int categoryID = 0;
    std::string categoryName = "";

    std::cout << "\nEnter value of transaction: " << std::flush;
    std::cin >> value;
    std::cout << "\nEnter description of transaction: " << std::flush;
    std::getline(std::cin >> std::ws, description, '\n');
    std::cout << "\nEnter year of transaction: " << std::flush;
    std::cin >> year;
    std::cout << "\nEnter month (numeric) of transaction: " << std::flush;
    std::cin >> month;
    std::cout << "\nEnter day (numeric) of transaction: " << std::flush;
    std::cin >> day;
    Date date = std::chrono::year_month_day(std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day});
    std::cout << "\nEnter category name of transaction: " << std::flush;
    std::cin >> categoryName;

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
    std::cout << "3. Remove transactions\n";
    std::cout << "4. Save transactions to file\n";
    std::cout << "5. Load transactions from file\n";
    std::cout << "6. Display all transactions\n";
}

Date Menu::FindTransactionsByDateUI() const
{
    int year = 0;
    unsigned int month = 0;
    unsigned int day = 0;
    std::cout << "Provide a date in numeric YYYY/MM/DD format\n" << std::flush;
    std::cout << "Enter the year: \n" << std::flush;
    std::cin >> year;
    std::cout << "\nEnter the month: \n" << std::flush;
    std::cin >> month;
    std::cout << "\nEnter the day: \n" << std::flush;
    std::cin >> day;

    return Date{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
}

FileManager Menu::FileManagerUI() const
{
    std::string filepath = "";
    std::string filename = "";
    std::string filepathBuffer = "";
    std::cout << "Provide filepath (enter 'q' or 'Q' if you want current filepath): \n" << std::flush;
    std::cin >> filepathBuffer;
    if ("q" != filepathBuffer and "Q" != filepathBuffer)
        filepath = filepathBuffer;
    std::cout << "Provide filename (without extension!): \n" << std::flush;
    std::cin >> filename;

    return FileManager(filepath, filename);
}

void Menu::PrintTransaction(const std::shared_ptr<Transaction>& transaction) const
{
    std::cout << "ID: " << transaction->GetTransactionID() << "   ";
    std::cout << "Value: " << transaction->GetValue() << "   ";
    std::cout << "Description: " << transaction->GetDescription() << "   ";
    std::cout << "Date: " << transaction->GetDate() << "   ";
    std::cout << "Category ID: " << transaction->GetCategoryID() << "   ";
    std::cout << "Category: " << managerPtr_->categories.SearchForCategory(transaction->GetCategoryID())->second << "   \n";
}

bool Menu::SelectOption() const
{
    int currentOption = -1;
    std::cout << "Select your option: " << std::flush;

    std::cin >> currentOption;
    if (std::cin.good())
    {
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
            auto foundTransactions = managerPtr_->FindTransactionsByDate(FindTransactionsByDateUI());
            if (foundTransactions.empty())
            {
                std::cout << "No transactions found!\n" << std::flush;
                std::cout << "Press any key to continue\n" << std::flush;
                char key;
                std::cin >> key;
            }
            else
            {
                std::cout << "Press 'n' to update first transaction\n" << std::flush;
                char key;
                std::cin >> key;
                if(std::cin.good() && (key == 'n' or key == 'N'))
                {
                    foundTransactions.at(0)->UpdateValue(1234);
                }

            }
            break;
        }
        case REMOVE_TRANSACTION:
        {
            break;
        }
        case SAVE_TRANSACTION_TO_FILE:
        {
            FileManagerUI().SaveToFile(*managerPtr_);
            break;
        }
        case LOAD_TRANSACTION_FROM_FILE:
        {
            FileManagerUI().LoadFromFile(*managerPtr_);
            break;
        }
        case DISPLAY_ALL_TRANSACTIONS:
        {
            for(const auto& transaction : managerPtr_->GetTransactions())
                PrintTransaction(transaction);    

            std::cout << "Press any key if you want to continue:\n";
            char anyKey;
            std::cin >> anyKey;
            break;
        }
        default:
            break;
        }
        return true;
    }
    else
    {
        std::cin.clear();
        std::cin.ignore();
        throw std::invalid_argument("Invalid argument. Please enter the number!");
    }

}
