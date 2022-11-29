#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include<sstream>
#include"Calculator_error.h"
#include"Tlong.h"

namespace Calculator
{
    class Ld_to_str
    {
        Ld_to_str() {}
    public:
        static std::stringstream convert;
        static std::string ld_to_str(const long double& a){Ld_to_str::convert.str(""); Ld_to_str::convert<<a; return Ld_to_str::convert.str();}
    };
    std::stringstream Ld_to_str::convert = std::stringstream();

    enum class Token_type
    {
        LONG=1,
        DOUBLE=2,
        UNARY_MINUS=-2,
        MULTIPLE=-3,
        DIVISION=-4,
        PLUS=-5,
        MINUS=-6,
        OPEN_BRACKET=-7,
        CLOSE_BRACKET=-8,
    };

    class Token
    {
        std::string data;
        Token_type data_type;
    public:
        Token(const std::string& _data, Token_type _data_type) : data(_data), data_type(_data_type) {}
        Token(const Tlong& a) : data(a.to_string()), data_type(Token_type::LONG) {}
        Token(const long double& a) : data(Ld_to_str::ld_to_str(a)), data_type(Token_type::DOUBLE) {}
        Token_type get_token_type() const {return data_type;}
        std::string get_data() const {return data;}
    };

    Token get_next_token(std::string::const_iterator &ref, const std::string::const_iterator begin, const std::string::const_iterator end)
    {
        if('0'<=*ref && *ref<='9' || *ref=='.')
        {
            const std::string::const_iterator begin_token = ref;
            bool double_num=0;
            while(ref<end && '0'<=*ref && *ref<='9' || *ref=='.')
            {
                if(*ref=='.') double_num=1;
                ++ref;
            }
            if(*ref == 'e')
            {
                double_num=1;
                ++ref;
                if(*ref=='+' || *ref=='-') ++ref;
                while(ref<end && '0'<=*ref && *ref<='9' || *ref=='.')
                {
                    if(*ref=='.') double_num=1;
                    ++ref;
                }
            }
            return Token(std::string(begin_token, ref), double_num ? Token_type::DOUBLE : Token_type::LONG);
        }
        if(*ref == '+') {++ref; return Token(std::string(1, '+'), Token_type::PLUS);}
        if(*ref == '*') {++ref; return Token(std::string(1, '*'), Token_type::MULTIPLE);}
        if(*ref == '/') {++ref; return Token(std::string(1, '/'), Token_type::DIVISION);}
        if(*ref == '-')
        {
            if(ref>begin && (*(ref-1)<='9' && *(ref-1)>='0' || *(ref-1)==')' || *(ref-1)=='.')) {++ref; return Token(std::string(1, '-'), Token_type::MINUS);}
            ++ref;
            return Token(std::string(1, '-'), Token_type::UNARY_MINUS);
        }
        if(*ref == '(') {++ref; return Token(std::string(1, '('), Token_type::OPEN_BRACKET);}
        if(*ref == ')') {++ref; return Token(std::string(1, ')'), Token_type::CLOSE_BRACKET);}
        else throw Calculator_error(Calculator_error_type::INVALID_INPUT);
    }
}

#endif // TOKEN_H_INCLUDED
