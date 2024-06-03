#include <iostream>

#include "Source/Headers/Transaction.hpp"
#include "Source/Headers/Manager.hpp"

int main()
{
    Transaction transaction({10, 2, 2024}, 250.60f, "Description22");
    std::cout << "Value: " << transaction.getValue() << '\n';
    Manager manager;
    
    manager.addTransaction(transaction);
    manager.addTransaction(transaction);
    manager.saveToFile("testFile");
    manager.readFromFile("testFile");
    
    auto selected = manager.selectByValue(250.6);
    std::cout << "Selected: " << selected->getValue() << " " << selected->getDescription() <<'\n';

    std::cout <<"TEST RUN!\n";
    return 0;
}

