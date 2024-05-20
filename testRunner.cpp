#include <array>
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

TEST_P(TransactionFixture_dateValidation, PositiveCatch)
{
    Date date = GetParam();

    ASSERT_THROW(transaction.setDate(date[0], date[1], date[2]), std::runtime_error);
}

TEST(ManagerOuterOfRange, positiveExceptionCatch)
{
    Manager manager;

    ASSERT_THROW(manager.selectByTransactionNumber(2), std::runtime_error);
}

INSTANTIATE_TEST_CASE_P(DateValue, TransactionFixture_dateValidation, testing::Values(
    Date{32, 10, 2024},
    Date{31, 11, 2024},
    Date{31, 4, 2023},
    Date{29, 2, 2023},
    Date{10, 13, 2022}));

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

