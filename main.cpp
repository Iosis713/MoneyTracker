#include "Source/Headers/Category.hpp"
#include "Source/Headers/Transaction.hpp"
#include <chrono>
#include <type_traits>
#include <string>


int main()
{
    //const std::chrono::time_point now{std::chrono::system_clock::now()};
 
    std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
 
    std::cout << "Current Year: " << static_cast<int>(ymd.year()) << ", "
                 "Month: " << static_cast<unsigned>(ymd.month()) << ", "
                 "Day: " << static_cast<unsigned>(ymd.day()) << "\n"
                 "ymd: " << ymd << '\n';
    
    
    
    
    {
    
    using namespace std::chrono;
    //ymd = std::chrono::year_month_day(1998/std::chrono::April/8);
    ymd = std::chrono::year_month_day(2000y, std::chrono::April, 10d);
    }
    std::cout << "After day changing by std::chrono::day(value): \n";
    std::cout << ymd << '\n';

    return 0;
}

