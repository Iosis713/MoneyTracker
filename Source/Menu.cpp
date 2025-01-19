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
    std::cout << "2. Find transactions\n";
    std::cout << "3. Remove transactions\n";
    std::cout << "4. Save transactions to file\n";
    std::cout << "5. Load transactions from file\n";
    std::cout << "6. Display all transactions\n";
}

Date Menu::FindTransactionsByDateUI() const
{
    std::cout << "Provide a date in numeric YYYY/MM/DD format\n" << std::flush;
    std::cout << "Enter the year: \n" << std::flush;
    const int year = OptionSelectionUI<int>();
    std::cout << "\nEnter the month: \n" << std::flush;
    const unsigned int month = OptionSelectionUI<unsigned int>();
    std::cout << "\nEnter the day: \n" << std::flush;
    const unsigned int day = OptionSelectionUI<unsigned int>();
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
    std::cout << std::format("ID: {}   Date: {}   Value: {}   CategoryID: {}   CategoryName: {}   Description: {}\n",
                            transaction->GetTransactionID(),
                            transaction->GetDate(),
                            transaction->GetValue(),
                            transaction->GetCategoryID(),
                            managerPtr_->categories.SearchForCategory(transaction->GetCategoryID())->second,
                            transaction->GetDescription());
}

bool Menu::SelectOption() const
{
    std::cout << "Select your option: " << std::flush;
    int currentOption = OptionSelectionUI<int>();
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
    case FIND_TRANSACTION:
    {
        /*
        Currently only by date. UI for finding by Category and Value will be added
        Extraction to function required
        DATE validation
        */
        std::cout << "Finding transaction by:\n" << std::flush;
        std::cout << "1. Value      2. Date (YYYY/MM/DD)        3. Transaction Category\n" << std::flush;        
        std::cout << "Select your option: " << std::flush;
        int selectedOption = OptionSelectionUI<int>();

        Transactions foundTransactions{};
        using enum OptionsForTransactionsFinding;
        if(static_cast<int>(VALUE) == selectedOption)
        {
            std::cout << "Please provide bottom value of the range: " << std::flush;
            float bottomValue = OptionSelectionUI<float>();
            std::cout << "\nPlease provide upper value of the range: " << std::flush;
            float upperValue = OptionSelectionUI<float>();
            foundTransactions = managerPtr_->FindTransactionsByValueInRange(bottomValue, upperValue);
        }
        else if(static_cast<int>(DATE) == selectedOption)
        {
            foundTransactions = managerPtr_->FindTransactionsByDate(FindTransactionsByDateUI());
        }
        else if(static_cast<int>(TRANSACTION_CATEGORY) == selectedOption)
        {
            std::cout << "Available categories: \n";
            for (const auto& category : managerPtr_->categories.categories_)
                std::cout << std::format("CategoryID: {}   CategoryName: {}\n", category.first, category.second);

            std::cout << "11. Select by category ID     12.Select by category name\n" << std::flush;
            int findCategoryBy = OptionSelectionUI<int>();
            if(static_cast<int>(CATEGORY_ID) == findCategoryBy)
            {
                std::cout << "Select categoryID: " << std::flush;
                int categoryIDToFind = OptionSelectionUI<int>();
                foundTransactions = managerPtr_->FindTransactionsByCategory(categoryIDToFind);
            }
            else if(static_cast<int>(CATEGORY_NAME) == findCategoryBy)
            {
                std::cout << "Select Category name: " << std::flush;
                std::string categoryNameToFind {};
                std::cin >> categoryNameToFind;
                foundTransactions = managerPtr_->FindTransactionsByCategory(categoryNameToFind);
            }            
        }

        if (foundTransactions.empty())
            {
                std::cout << "No transactions found!\n" << std::flush;
                std::cout << "Press any key to continue\n" << std::flush;
                char key;
                std::cin >> key;
            }
        else
        {
            Clear();
            std::cout << "Transactions found:\n" << std::flush;
            for(const auto& transaction : foundTransactions)
                PrintTransaction(transaction);  

            /*TO BE UPDATE TO SELECT OPTIONS Update/remove*/
            std::cout << "Press 'n' to update first transaction\n" << std::flush;
            char key;
            std::cin >> key;
            if(std::cin.good() && (key == 'n' or key == 'N'))
            {
                foundTransactions.at(0)->UpdateValue(1234);
            }
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
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