////////////////////////////////////////////////////////////////////////////
/**
 *  @file   CompoundExpressionCalculator.cpp
 *  @date   Tue, June 15 2021
 *  @brief  Definitions for calculator that allows more than 2 terms
 */
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <mutex>
#include <regex>
#include <thread>

#include "CalculatorStrings.h"
#include "CompoundExpressionCalculator.h"

namespace calculator
{
    CompoundExpressionCalculator::CompoundExpressionCalculator(std::string compoundExpression)
            :compoundExpression_(std::move(compoundExpression))
    {
    }

    CompoundExpressionCalculator::CompoundExpressionCalculator(std::unordered_map<char, int> variables,
                                                               std::string variableCompoundExpression)
            :variableMap_(std::move(variables))
    {
        std::string resultExpression = std::move(variableCompoundExpression);
        for(auto varPair : variableMap_)
        {
            //create the regex for filtering
            std::string regexPattern(1, varPair.first);
            std::regex charRegex(regexPattern, std::regex_constants::ECMAScript);
            formatResultExpression(
                    resultExpression, charRegex,
                    &CompoundExpressionCalculator::replaceVariableWithNumberInResultExpression);
        }
        compoundExpression_ = resultExpression;
    }

    std::string CompoundExpressionCalculator::getExpression() const
    {
        return compoundExpression_;
    }

    int CompoundExpressionCalculator::getResult() const
    {
        std::string resultExpression = compoundExpression_;
        return computeResult(resultExpression);
    }

    std::string CompoundExpressionCalculator::toString() const
    {
        return getExpression() + CalculatorStrings::EQUAL + std::to_string(getResult());
    }

    std::unordered_map<char, int> CompoundExpressionCalculator::toVariableMap(const std::string& variables)
    {
        typedef std::pair<char,int> varPair;
        std::unordered_map<char, int> map;
        std::regex regex(CalculatorStrings::REGEX_PATTERN_VARIABLE_VALUE_PAIR, std::regex_constants::ECMAScript);

        auto match_begin = std::sregex_iterator (variables.begin(), variables.end(), regex);
        auto match_end = std::sregex_iterator();
        for(std::sregex_iterator i = match_begin; i != match_end; i++)
        {
            std::string match = (*i).str();
            char key = match[0];
            int value;
            // variable expression look like 'a=1000' or 'b = 1000', find '=' then add 1 to get just the number
            // we then sstream >> it to get rid of whitespace
            auto numberStart = match.rfind('=') + 1;
            std::stringstream stream(match.substr(numberStart));
            stream >> value;
            if (map.find(key) == map.end())
            {
                map.insert(varPair(key, value));
            }
            else
            {
                map.at(key) = value;
            }
        }
        return map;
    }

    int CompoundExpressionCalculator::computeResult(std::string &resultExpression) const
    {
        int result = 0;
        std::regex addSubtractRegex(CalculatorStrings::REGEX_PATTERN_ADD_SUBTRACT_EXPRESSION, std::regex_constants::ECMAScript);
        std::regex multiplyDivideRegex(CalculatorStrings::REGEX_PATTERN_MULTIPLY_DIVIDE_EXPRESSION, std::regex_constants::ECMAScript);

        formatResultExpression(
                resultExpression, multiplyDivideRegex,
                &CompoundExpressionCalculator::replaceSubexpressionWithResultInResultExpression);
        formatResultExpression(
                resultExpression, addSubtractRegex,
                &CompoundExpressionCalculator::replaceSubexpressionWithResultInResultExpression);
        try
        {
            result = std::stoi(resultExpression);
        }
        catch (std::invalid_argument &e)
        {
            std::cerr << CalculatorStrings::INVALID_INPUT << std::endl << e.what() << std::endl;
        }
        if (std::to_string(result) != resultExpression)
        {
            std::cerr << CalculatorStrings::INVALID_INPUT << std::endl;
        }
        return result;
    }

    void CompoundExpressionCalculator::formatResultExpression(std::string &resultExpression, const std::regex &regex,
                                                              void (CompoundExpressionCalculator::*classReplaceFunction)(std::string &,
                                                                                           const std::string &string) const) const
    {
        std::vector<std::thread> threads;

        auto match_begin = std::sregex_iterator(resultExpression.begin(), resultExpression.end(), regex);
        auto match_end = std::sregex_iterator();
        while(distance(match_begin, match_end))
        {
            for (std::sregex_iterator i = match_begin; i != match_end; i++)
            {
                threads.emplace_back(classReplaceFunction, this, std::ref(resultExpression), (*i).str());
            }
            for (auto &thread : threads)
            {
                thread.join();
            }

            //cleanup for next loop
            threads.clear();
            match_begin = std::sregex_iterator(resultExpression.begin(), resultExpression.end(), regex);
            match_end = std::sregex_iterator();
        }
    }

    void CompoundExpressionCalculator::replaceSubexpressionWithResultInResultExpression(std::string &resultExpression,
                                                                                        const std::string &expression) const
    {
        //get the result from the expression
        auto calculator = calculatorFactory_.createCalculator(expression);
        std::string result = std::to_string(calculator->getResult());

        //create the regex for filtering
        std::string escapedExpression = expressionWrapOperator(expression);
        std::regex expressionRegex(escapedExpression, std::regex_constants::ECMAScript | std::regex_constants::icase);

        threadedReplaceResultExpression(resultExpression, result, expressionRegex);
    }

    void CompoundExpressionCalculator::replaceVariableWithNumberInResultExpression(std::string &resultExpression,
                                                                                   const std::string &variable) const
    {
        std::string result = std::to_string(variableMap_.at(variable[0]));
        std::regex charRegex(variable, std::regex_constants::ECMAScript);
        threadedReplaceResultExpression(resultExpression, result, charRegex);
    }

    void CompoundExpressionCalculator::threadedReplaceResultExpression(std::string &resultExpression,
                                                                       const std::string &replacement,
                                                                       const std::regex &match) const
    {
        //static mutex
        static std::mutex expressionMutex;
        //lock while reading and updating the resultExpression
        expressionMutex.lock();
        std::string new_expression = regex_replace(resultExpression, match, replacement,
                                                   std::regex_constants::format_first_only);
        resultExpression = new_expression;
        expressionMutex.unlock();
    }

    std::string CompoundExpressionCalculator::expressionWrapOperator(const std::string &expression)
    {
        std::regex operatorRegex(CalculatorStrings::REGEX_PATTERN_OPERATOR_FROM_SIMPLE_EXPRESSION,
                                 std::regex_constants::ECMAScript);
        std::string escExpression = std::regex_replace(expression, operatorRegex,
                                                       CalculatorStrings::REGEX_PATTERN_REPLACE_SURROUND_WITH_BRACKET,
                                                       std::regex_constants::format_first_only);
        return escExpression;
    }
}