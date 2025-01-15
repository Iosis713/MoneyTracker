#include "Source/Headers/Category.hpp"
#include "Source/Headers/Transaction.hpp"
#include "Source/Headers/TransactionsManager.hpp"
#include "Source/Headers/Printer.hpp"
#include "Source/Headers/FileManager.hpp"
#include "Source/Headers/Menu.hpp"

#include <chrono>
#include <thread>

int main()
{
    /*Category categories;
    categories.AddCategory({2, "Fuel"});
    auto transactionToPrint = std::make_shared<Transaction>(200.f,
                                       "FuelFull",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(3)},
                                       2);
                                       
    Printer().Print(transactionToPrint, categories);

    TransactionsManager transactionsManager;
    transactionsManager.categories.AddCategory({2, "Fuel"});
    transactionsManager.AddTransaction(200.f,
                                       "FuelFull",
                                       std::chrono::year_month_day{std::chrono::year(2020), std::chrono::May, std::chrono::day(3)},
                                       2);
    

    std::cout << "Saving to file completed: ";
    std::cout << std::boolalpha << FileManager("", "TestFile").SaveToFile(transactionsManager);
    
    TransactionsManager anotherTransactionsManager;
    std::cout << '\n' << "AnotherTransaction size before loading: " << anotherTransactionsManager.GetTransactions().size() << '\n';

    std::cout << "Loading from file!\n";
    FileManager("", "TestFile").LoadFromFile(anotherTransactionsManager);

    std::cout << "AnotherTransactions size after loading: " << anotherTransactionsManager.GetTransactions().size() << '\n';
    */

    auto menu = std::make_unique<Menu>();
    bool status = true;
    while (status)
    {
        try
        {
            menu->Clear();
            menu->DisplayOptions();
            status = menu->SelectOption();
        }
        catch(std::invalid_argument& ex)
        {
            std::cerr << ex.what() << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
    }

    return 0;
}

