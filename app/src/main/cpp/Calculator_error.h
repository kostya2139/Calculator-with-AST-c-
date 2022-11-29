#ifndef CALCULATOR_ERROR_H_INCLUDED
#define CALCULATOR_ERROR_H_INCLUDED

#include<exception>

namespace Calculator
{
    enum class Calculator_error_type
    {
        INVALID_INPUT,
        SYNTAX_ERROR,
        NULL_DIVISION,
        SOMETHING_WENT_WRONG,
    };

    class Calculator_error : public std::exception
    {
        Calculator_error_type error_type;
    public:
        Calculator_error(Calculator_error_type _error_type) : error_type(_error_type) {}
        const char* what() noexcept
        {
            switch(error_type)
            {
            case Calculator_error_type::NULL_DIVISION:
                return "Division on zero forbidden";
                break;
            case Calculator_error_type::INVALID_INPUT:
                return "Invalid input";
                break;
            case Calculator_error_type::SYNTAX_ERROR:
                return "Syntax error";
                break;
            case Calculator_error_type::SOMETHING_WENT_WRONG:
                return "something went wrong";
                break;
            }
        }
    };
}

#endif // CALCULATOR_ERROR_H_INCLUDED
