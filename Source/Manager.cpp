#include "Headers/Manager.hpp"

Manager::Manager()
{
    manager_.reserve(60);
}

void Manager::addTransaction(const std::array<uint16_t, 3>& date, const float value, const std::string& description)
{
    manager_.push_back(std::make_shared<Transaction>(date, value, description));
}

void Manager::addTransaction(const Transaction& transaction)
{
    manager_.push_back(std::make_shared<Transaction>(transaction));
}

void Manager::readFromFile(const std::string& filename)
{
    std::fstream file;
    file.open(filename, file.in);
    if(file.is_open())
    {
        std::string data;
        while(file.eof())
        {   
            getline(file, data, ';');
            uint16_t day = static_cast<uint16_t>(stoi(data));
            getline(file, data, ';');
            uint16_t month = static_cast<uint16_t>(stoi(data));
            getline(file, data, ';');
            uint16_t year = static_cast<uint16_t>(stoi(data));
            getline(file, data, ';');
            float value = stof(data);
            getline(file, data, '\n');
            std::string description = data;

            addTransaction({day, month, year}, value, description);
        }
    }
    else
    {
        throw std::runtime_error("Unable to open file");
    }
}

void Manager::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename, file.out | file.trunc);
    if(file.is_open())
    {
        for(auto& transaction : manager_)
        {
            file << transaction->getDate()[0] << ";"
                 << transaction->getDate()[1] << ";"
                 << transaction->getDate()[2] << ";"
                 << transaction->getValue() << ";"
                 << transaction->getDescription() << "\n";
        }
    }
}

std::shared_ptr<Transaction>& Manager::selectByDescription(std::string& description)
{   
    //letter case insensitivity
    std::transform(description.begin(), description.end(), description.begin(),
        [](unsigned char c){return std::tolower(c);});
    
    auto iter = std::find_if(manager_.begin(), manager_.end(), [description](auto tran)
            {   
                //letter case insensitivity
                auto desc = tran->getDescription();
                std::transform(desc.begin(), desc.end(), desc.begin(),
                        [](unsigned char c){return std::tolower(c);});
    
                return description == desc;
            });
    if(iter == manager_.end())
    {
        throw std::runtime_error("No description found!");
    }

    return *iter;    
}

std::shared_ptr<Transaction>& Manager::selectByNumber(uint16_t number)
{
    if(number > manager_.size())
    {
        throw std::runtime_error("Transaction number is out of range!");
    }
    else
    {
        return manager_[number];
    }    
}

std::shared_ptr<Transaction>& Manager::selectByValue(const float value)
{
    auto iter = std::find_if(manager_.begin(), manager_.end(), [value](auto tran)
            {
                auto val = tran->getValue();
                return val == value;
            });
    return *iter;
}

TransactionManager Manager::getManager() const
{
    return this->manager_;
}




