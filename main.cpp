#include "Source/Headers/Category.hpp"
#include "Source/Headers/Transaction.hpp"
#include "Source/Headers/TransactionsManager.hpp"
#include "Source/Headers/Printer.hpp"
#include "Source/Headers/FileManager.hpp"
#include "Source/Headers/Menu.hpp"

import <chrono>;
import <thread>;

int main()
{
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

