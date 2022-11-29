#ifndef CALCULATOR_INTERFACE_H_INCLUDED
#define CALCULATOR_INTERFACE_H_INCLUDED

#include"syntax_tree.h"

class Calculator_interface
{
    Calculator_interface() {}
public:
    static void initialize() {Calculator::Ld_to_str::convert.precision(10);}
    static std::string calculate(const std::string& request)
    {
        Calculator::Syntax_tree tree;
        tree.construct(request);
        return tree.evaluate();
    }
};

#endif // CALCULATOR_INTERFACE_H_INCLUDED
