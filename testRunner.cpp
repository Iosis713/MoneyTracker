#include <array>
#include <cstring>
#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>

#include "Source/Headers/Transaction.hpp"
#include "Source/Headers/Manager.hpp"

using Date = std::array<uint16_t, 3>;

class TransactionFixture_dateValidation : public testing::TestWithParam<Date>
{
public:
    Transaction transaction{{10, 10, 2020}, 100.f, "Unknown"};
protected:
};

class ManagerFixture_descriptionSel : public testing::TestWithParam<std::string>
{
protected:

public:
    Manager manager;
    
    void setUp()
    {
        manager.addTransaction({1, 1, 2024}, -50.f, "Pizza");
        manager.addTransaction({10, 2, 2024}, -75.5f, "Fuel");
        manager.addTransaction({30, 3, 2024}, 3540.f, "salary");
    }
};

class ManagerFixture_ValueSelection : public testing::TestWithParam<float>
{
protected:

public:
    Manager manager;
    
    void setUp()
    {
        manager.addTransaction({1, 1, 2024}, -50.f, "Pizza");
        manager.addTransaction({10, 2, 2024}, -75.5f, "Fuel");
        manager.addTransaction({30, 3, 2024}, 3540.f, "salary");
    }
};

TEST_P(ManagerFixture_descriptionSel, positiveSel)
{     
    setUp();
    std::string param = GetParam();
    std::string result = manager.selectByDescription(param)->getDescription();
    ASSERT_STRCASEEQ(result.c_str(), param.c_str());
}

TEST_P(TransactionFixture_dateValidation, PositiveCatch)
{
    Date date = GetParam();

    ASSERT_THROW(transaction.setDate(date[0], date[1], date[2]), std::runtime_error);
}

TEST_P(ManagerFixture_ValueSelection, positiveSel)
{
    setUp();
    float param = GetParam();
    
    ASSERT_EQ(param, manager.selectByValue(param)->getValue());
}

TEST(ManagerOuterOfRange, positiveExceptionCatch)
{
    Manager manager;

    ASSERT_THROW(manager.selectByNumber(2), std::runtime_error);
}

TEST_F(ManagerFixture_descriptionSel, NoDescriptionFound)
{
    setUp();
    
    std::string input = "Cheesburger";

    ASSERT_THROW(manager.selectByDescription(input), std::runtime_error);
}

INSTANTIATE_TEST_CASE_P(DateValue, TransactionFixture_dateValidation, testing::Values(
    Date{32, 10, 2024},
    Date{31, 11, 2024},
    Date{31, 4, 2023},
    Date{29, 2, 2023},
    Date{10, 13, 2022}));

INSTANTIATE_TEST_CASE_P(Descriptions, ManagerFixture_descriptionSel, testing::Values(
    std::string{"Pizza"},
    std::string{"Salary"},
    std::string{"fuel"}));

INSTANTIATE_TEST_CASE_P(Values, ManagerFixture_ValueSelection, testing::Values(
    -50.0,
    -75.500,
    3540.000));


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

