#ifndef PARSER_H
#define PARSER_H

////////////////////////////////////////////////////////////////////////////////
/**
* @file Parser.h
* @brief calculator function declarations.
*/
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace calculator
{
    struct Expression
    {
        float       a;
        float       b;
        std::string fullExpression;
        bool        hasParenthesis = false;
        char        operation;
        int         placementIndex = 0;
        bool        validExpression = false;
    };

    struct ExpressionUnit
    {
        float number;
        char  operation;
        bool  valid = false;
    };

    class Parser
    {
        public:
            /**
             * @brief the main parsing function that puts all the peices together and returns an expression
             * @return an Expression object, along with whether it is valid or not
            */
            Expression breakDownEquation(const std::shared_ptr<std::vector<ExpressionUnit>> &equationVector);

            /**
             * @brief takes in input
             * @returns string of input entered
            */
            std::string getUserInput();

            /**
             * @brief creates a vector out of a string
             * @returns vector split into each unit of expression
            */
            std::pair <std::shared_ptr<std::vector<ExpressionUnit>>,bool> createVector(const std::string &fullEquation);

            /**
             * @brief returns the original equation string
             * @returns the unedited string input by user
            */
            std::string getOriginalEquation();
        private:
            std::string editedEquation_ = "";
            char        operations_[6] = {'+', '-', '/', '%', '*', 'x'};
            std::string originalEquation_ = "";

            /**
             * @brief counts parenthesis and ensures there are equal opening and closing
             * @return isValid if there is correct number of parenthesis
            */
            bool validateParenthesis(std::shared_ptr<std::vector<ExpressionUnit>> &equationVector);

            /**
             * @brief uses regex to ensure value is a float
             * @return isValid if it is a float
            */
            bool validateFloat(const std::string &input);

            /**
             * @brief removes all spaces from user input
             * @returns string of input entered, without spaces
            */
            std::string removeSpaces(const std::string &input);

            /**
             * @brief checks if inputed char is inside of Operations array
             * @returns isValid if it is valid operator
            */
            bool validateOperator(const char &expressionUnit);
            
            /**
             * @brief creates an expression unit for an operator and edits the editedString
             * @returns expression unit with an operator value
             * */
            ExpressionUnit findOperator(std::string &editedEquation);

            /**
             * @brief iterates through given expression and gives back the found number
             * @returns isValid if it is valid operator
            */
            ExpressionUnit findNumber(std::string &editedEquation);
    };
}//namespace calculator
#endif  // PARSER_H
