////////////////////////////////////////////////////////////////////////////
/**
 *  @file   CalculatorApplication.cpp
 *  @date   Fri April 16 2021
 *  @brief  These are the functions that are used by main.cpp
 */
////////////////////////////////////////////////////////////////////////////

#include <future>
#include <sstream>
#include <thread>

#include "CalculatorApplication.h"
#include "CalculatorApplicationFactory.h"
#include "History.h"

namespace calculator {

// *****************************************************************************/
// ***************** CalculatorApplication public methods **********************/
// *****************************************************************************/

float CalculatorApplication::calculate(float firstNumber, float secondNumber, char operation, std::string const &originalEquation)
{
    float result = 0;

    if(limitCheck(firstNumber) && limitCheck(secondNumber))
    {
        calculator::CalculatorApplicationFactory calculatorAppFactory;  
        auto calculator = calculatorAppFactory.createCalculator(firstNumber, secondNumber, operation);
        if(calculator)
        {
            CalculatorApplication calculatorApplication;
            result = calculator->getResult();
            std::cout << calculator->toString() << std::endl;
        }
        else
        {
            std::cout << CalculatorStrings::ERROR_MESSAGE_INVALID_INPUT << std::endl;
            result = -1;
        }
    }
    else
    {
        result = -1;
    }

    return result;
}

std::pair <std::string, bool> CalculatorApplication::runCalculator(std::string webInput) //set to return bool and final answer and string and pass into request.body from pistatio 
{
    bool isValid = false;
    std::string finalResult;
    Parser parser;
    float answer;
    Expression parsedExpression;

    auto tempExpressionUnits = std::async(&Parser::createVector, parser, parser.getUserInput(webInput)); // pass into getUserinput request.body
    while(tempExpressionUnits.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
    {
        std::cout << CalculatorStrings::BUILDING_VECTORS;
    }
    std::cout << std::endl;
    auto setExpressionUnits = tempExpressionUnits.get();

    while(setExpressionUnits.second)
    {
        auto tempParsedExpression = std::async(&Parser::breakDownEquation, parser, setExpressionUnits.first);
        while(tempParsedExpression.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
        {
            std::cout << CalculatorStrings::DISSECTING_AND_CALCULATING;
        }
        std::cout << std::endl;

        parsedExpression = tempParsedExpression.get();

        if(parsedExpression.validExpression)
        {
            answer = CalculatorApplication::calculate(parsedExpression.firstNumber, parsedExpression.secondNumber, parsedExpression.operation, parser.getOriginalEquation());
            ExpressionUnit prevAnswer;
            prevAnswer.number = answer;
            prevAnswer.valid = true;

            if(setExpressionUnits.first->size() > 0)
            {
                setExpressionUnits.first->insert(setExpressionUnits.first->begin() + parsedExpression.placementIndex, prevAnswer);
            }
            else
            {
                break;
            }
            
        }
        else
        {
            std::cout << CalculatorStrings::ERROR_MESSAGE_INVALID_INPUT << std::endl;
            break;
        }

    }
    
    if(parsedExpression.validExpression == false)
    {
        isValid = false;
        finalResult =  parsedExpression.fullExpression;
    }
    else
    {
        isValid = true;
        finalResult = parser.getOriginalEquation() + CalculatorStrings::EQUAL_SIGN + std::to_string(answer);
        
    }
        std::pair <std::string, bool> calculatedResult(finalResult, isValid);

        //TODO: add history to website, storing history into a database 
            // History::getInstance()->ReadFromFile();
            // History::getInstance()->appendCalculator(answer, parser.getOriginalEquation());
            // History::getInstance()->storeHistory();
            // History::getInstance()->printHistory();

    return calculatedResult;     
}

bool CalculatorApplication::limitCheck(float firstNumber)
{
    bool result = true;
    if(firstNumber > std::numeric_limits<float>::max())
    {
        std::cerr << CalculatorStrings::ERROR_MESSAGE_INPUT_TOO_LARGE << std::endl;
        result = false;
    }
    else if(firstNumber < std::numeric_limits<float>::min())
    {
        std::cerr << CalculatorStrings::ERROR_MESSAGE_INPUT_TOO_SMALL << std::endl;
        result = false;
    }
    else if(firstNumber == std::numeric_limits<float>::infinity())
    {
        std::cerr << CalculatorStrings::ERROR_MESSAGE_INPUT_TOO_LARGE << std::endl;
        result = false;
    }
    
    return result;
}

} //namespace calculator