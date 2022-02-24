////////////////////////////////////////////////////////////////////////////
/**
 *  @file   SymbolGtest.cpp
 *  @date   Wed February 23 2022
 *  @brief  Unit test suite for the Sample class
 */
////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <sstream>

#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "../inc/Symbol.h"

using namespace testing;

class SymbolFixture: public ::testing::Test
{
    protected:
        static constexpr int FIRST_INT_VALUE = 42;
        static constexpr int SECOND_INT_VALUE = 43;
        static constexpr int THIRD_INT_VALUE = 41;
        static constexpr int FOURTH_INT_VALUE = 44;
        static constexpr double FIRST_DOUBLE_VALUE = 42.42e10;
        static constexpr double SECOND_DOUBLE_VALUE = 43.43e10;
        static constexpr double THIRD_DOUBLE_VALUE = 41.41e10;
        static constexpr double FOURTH_DOUBLE_VALUE = 44.44e10;
        static constexpr const char *BAD_USER_INPUT = "asdf";

        calculator::Symbol<int> intSymbolA;
        calculator::Symbol<int> intSymbolBBound;
        calculator::Symbol<int> intSymbolDBound;
        calculator::Symbol<double> doubleSymbolA;
        calculator::Symbol<double> doubleSymbolDBound;
        calculator::Symbol<double> doubleSymbolBBound;

        // Using SetUp() is normally preferred to having a ctor.
        // In this case, we can't get away from initializing in the ctor since 
        // the instance variables require symbols to be set on construction
        SymbolFixture(): 
                intSymbolA{'a'},
                intSymbolBBound{'B'},
                intSymbolDBound{'d'},
                doubleSymbolA{'A'},
                doubleSymbolBBound{'B'},
                doubleSymbolDBound{'d'}
        {
        }

        void SetUp() override
        {
            intSymbolBBound.setValue(FIRST_INT_VALUE);
            intSymbolDBound.setValue(FIRST_INT_VALUE);
            doubleSymbolBBound.setValue(FIRST_DOUBLE_VALUE);
            doubleSymbolDBound.setValue(FIRST_DOUBLE_VALUE);
        }
};
constexpr int SymbolFixture::FIRST_INT_VALUE;
constexpr int SymbolFixture::SECOND_INT_VALUE;
constexpr int SymbolFixture::THIRD_INT_VALUE;
constexpr int SymbolFixture::FOURTH_INT_VALUE;
constexpr double SymbolFixture::FIRST_DOUBLE_VALUE;
constexpr double SymbolFixture::SECOND_DOUBLE_VALUE;
constexpr double SymbolFixture::THIRD_DOUBLE_VALUE;
constexpr double SymbolFixture::FOURTH_DOUBLE_VALUE;
constexpr const char *SymbolFixture::BAD_USER_INPUT;

TEST_F(SymbolFixture, hasValueWithoutValue)
{
    EXPECT_FALSE(intSymbolA.hasValue());
    EXPECT_FALSE(doubleSymbolA.hasValue());
}

TEST_F(SymbolFixture, hasValueWithValue)
{
    EXPECT_TRUE(intSymbolBBound.hasValue());
    EXPECT_TRUE(doubleSymbolBBound.hasValue());
}

TEST_F(SymbolFixture, setValueFirstTime)
{
    calculator::Symbol<int> intSymbolC{'C'};
    calculator::Symbol<double> doubleSymbolC{'C'};
    intSymbolC.setValue(FIRST_INT_VALUE);
    doubleSymbolC.setValue(FIRST_DOUBLE_VALUE);
}

TEST_F(SymbolFixture, setValueRepeatedly)
{
    intSymbolDBound.setValue(FIRST_INT_VALUE);
    doubleSymbolDBound.setValue(FIRST_DOUBLE_VALUE);
    intSymbolDBound.setValue(SECOND_INT_VALUE);
    doubleSymbolDBound.setValue(SECOND_DOUBLE_VALUE);
}

TEST_F(SymbolFixture, getValueWhenItIsSet)
{
    EXPECT_EQ(intSymbolBBound.getValue(), FIRST_INT_VALUE);
    // Add some epsilon for floating point comparisons
    EXPECT_NEAR(doubleSymbolBBound.getValue(), FIRST_DOUBLE_VALUE,
            nextafter(FIRST_DOUBLE_VALUE, INFINITY) - 
            nextafter(FIRST_DOUBLE_VALUE, -INFINITY));
}

TEST_F(SymbolFixture, getValueWhenItIsNotSet)
{
    EXPECT_EQ(intSymbolA.getValue(), calculator::Symbol<int>::defaultValue());
    EXPECT_NEAR(doubleSymbolA.getValue(),
            calculator::Symbol<double>::defaultValue(),
            nextafter(calculator::Symbol<double>::defaultValue(), INFINITY) -
            nextafter(calculator::Symbol<double>::defaultValue(), -INFINITY));
}

TEST_F(SymbolFixture, bindFromStreamsWithGoodInput)
{
    std::stringstream inStream;
    std::stringstream outStream;
    inStream << THIRD_INT_VALUE << std::endl;
    intSymbolDBound.bindFromStreams(inStream, outStream);
    EXPECT_EQ(intSymbolDBound.getValue(), THIRD_INT_VALUE);
    EXPECT_EQ(outStream.str(),
            std::string{intSymbolDBound.getSymbol()} + " = ");
    
    inStream.str(std::string{});
    outStream.str(std::string{});
    inStream << THIRD_DOUBLE_VALUE << std::endl;
    doubleSymbolDBound.bindFromStreams(inStream, outStream);
    EXPECT_NEAR(doubleSymbolDBound.getValue(), THIRD_DOUBLE_VALUE,
            nextafter(THIRD_DOUBLE_VALUE, INFINITY) - 
            nextafter(THIRD_DOUBLE_VALUE, -INFINITY));
    EXPECT_EQ(outStream.str(),
            std::string{intSymbolDBound.getSymbol()} + " = ");
}

TEST_F(SymbolFixture, bindFromStreamsWithBadInput)
{
    std::stringstream inStream;
    std::stringstream outStream;
    inStream << BAD_USER_INPUT << std::endl << FOURTH_INT_VALUE << std::endl;
    intSymbolDBound.bindFromStreams(inStream, outStream);
    EXPECT_EQ(intSymbolDBound.getValue(), FOURTH_INT_VALUE);
    EXPECT_EQ(outStream.str(),
            std::string{intSymbolDBound.getSymbol()} +
            " = Please enter a valid number.\n" + intSymbolDBound.getSymbol() +
            " = ");
    
    inStream.str(std::string{});
    outStream.str(std::string{});
    inStream << BAD_USER_INPUT << std::endl << FOURTH_DOUBLE_VALUE << std::endl;
    doubleSymbolDBound.bindFromStreams(inStream, outStream);
    EXPECT_NEAR(doubleSymbolDBound.getValue(), FOURTH_DOUBLE_VALUE,
            nextafter(FOURTH_DOUBLE_VALUE, INFINITY) - 
            nextafter(FOURTH_DOUBLE_VALUE, -INFINITY));
    EXPECT_EQ(outStream.str(),
            std::string{intSymbolDBound.getSymbol()} +
            " = Please enter a valid number.\n" + intSymbolDBound.getSymbol() +
            " = ");
}
