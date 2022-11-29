#ifndef SYNTAX_TREE_H_INCLUDED
#define SYNTAX_TREE_H_INCLUDED

#include"Token.h"


namespace Calculator
{
    struct Tree_node
    {
        Token data;
        Tree_node * left, * right;
        Tree_node(const Token& _data, Tree_node* _left=nullptr, Tree_node* _right=nullptr) : data(_data), left(_left), right(_right) {}
    };

    template <class F>
    void traverse_sub_tree(Tree_node* top, F functor)
    {
        if(top)
        {
            if(top->left) traverse_sub_tree(top->left, functor);
            functor(top);
            if(top->right) traverse_sub_tree(top->right, functor);
        }
    }

    template <class F>
    void post_order(Tree_node* top, F functor)
    {
        if(top)
        {
            post_order(top->right, functor);
            post_order(top->left, functor);
            functor(top);
        }
    }

    long double str_to_ld(const std::string& a)
    {
        if(a==".") return 0;
        return std::stold(a);
    }

    Token evaluate_node(Tree_node* top)
    {
        if(!top) return Token("0", Token_type::LONG);
        switch(top->data.get_token_type())
        {
            case Token_type::DOUBLE:
                return top->data;
                break;
            case Token_type::LONG:
                return top->data;
                break;
            case Token_type::PLUS:
            {
                if(!top->left || !top->right) throw Calculator_error(Calculator_error_type::SYNTAX_ERROR);
                Token t1 = evaluate_node(top->left), t2 = evaluate_node(top->right);
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::LONG)
                {
                    if(t1.get_data().length()<=98 && t2.get_data().length()<=98) return Token(Tlong(t1.get_data()) + Tlong(t2.get_data()));
                    return Token(str_to_ld(t1.get_data()) + str_to_ld(t2.get_data()));
                }
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::LONG) return Token(str_to_ld(t1.get_data()) + Tlong(t2.get_data()));
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::DOUBLE) return Token(Tlong(t1.get_data()) + str_to_ld(t2.get_data()));
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::DOUBLE) return Token(str_to_ld(t1.get_data()) + str_to_ld(t2.get_data()));
                break;
            }
            case Token_type::MINUS:
            {
                if(!top->left || !top->right) throw Calculator_error(Calculator_error_type::SYNTAX_ERROR);
                Token t1 = evaluate_node(top->left), t2 = evaluate_node(top->right);
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::LONG)
                {
                    if(t1.get_data().length()<=Tlong::get_n_max()-2 && t2.get_data().length()<=Tlong::get_n_max()-2) return Token(Tlong(t1.get_data()) - Tlong(t2.get_data()));
                    return Token(str_to_ld(t1.get_data()) - str_to_ld(t2.get_data()));
                }
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::LONG) return Token(str_to_ld(t1.get_data()) - Tlong(t2.get_data()));
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::DOUBLE) return Token(Tlong(t1.get_data()) - str_to_ld(t2.get_data()));
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::DOUBLE) return Token(str_to_ld(t1.get_data()) - str_to_ld(t2.get_data()));
                break;
            }
            case Token_type::MULTIPLE:
            {
                if(!top->left || !top->right) throw Calculator_error(Calculator_error_type::SYNTAX_ERROR);
                Token t1 = evaluate_node(top->left), t2 = evaluate_node(top->right);
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::LONG)
                {
                    if(t1.get_data().length() + t2.get_data().length() <= Tlong::get_n_max()-2) return Token(Tlong(t1.get_data()) * Tlong(t2.get_data()));
                    return Token(str_to_ld(t1.get_data()) * str_to_ld(t2.get_data()));
                }
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::LONG) return Token(str_to_ld(t1.get_data()) * Tlong(t2.get_data()));
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::DOUBLE) return Token(Tlong(t1.get_data()) * str_to_ld(t2.get_data()));
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::DOUBLE) return Token(str_to_ld(t1.get_data()) * str_to_ld(t2.get_data()));
                break;
            }
            case Token_type::DIVISION:
            {
                if(!top->left || !top->right) throw Calculator_error(Calculator_error_type::SYNTAX_ERROR);
                Token t1 = evaluate_node(top->left), t2 = evaluate_node(top->right);
                if(str_to_ld(t2.get_data()) == 0) throw Calculator_error(Calculator_error_type::NULL_DIVISION);
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::LONG)
                {
                    if(Tlong(t1.get_data()) % Tlong(t2.get_data()) == 0) return Token(Tlong(t1.get_data()) / Tlong(t2.get_data()));
                    return Token(str_to_ld(t1.get_data()) / str_to_ld(t2.get_data()));
                }
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::LONG) return Token(str_to_ld(t1.get_data()) / Tlong(t2.get_data()));
                if(t1.get_token_type() == Token_type::LONG && t2.get_token_type() == Token_type::DOUBLE) return Token(Tlong(t1.get_data()) / str_to_ld(t2.get_data()));
                if(t1.get_token_type() == Token_type::DOUBLE && t2.get_token_type() == Token_type::DOUBLE) return Token(str_to_ld(t1.get_data()) / str_to_ld(t2.get_data()));
                break;
            }
            case Token_type::UNARY_MINUS:
            {
                if(!top->right) throw Calculator_error(Calculator_error_type::SYNTAX_ERROR);
                Token t1 = evaluate_node(top->right);
                if(t1.get_token_type() == Token_type::LONG) return Token(-Tlong(t1.get_data()));
                if(t1.get_token_type() == Token_type::DOUBLE) return Token(-str_to_ld(t1.get_data()));
                break;
            }
            default:
                throw Calculator_error(Calculator_error_type::SOMETHING_WENT_WRONG);
                break;
            }
    }

    class Syntax_tree
    {
        Tree_node* root = nullptr;
    public:
        ~Syntax_tree() {clear();}
        Tree_node* get_root() const {return root;}
        void clear()
        {
            post_order(root, [](Tree_node* ptr){delete ptr;});
            root=nullptr;
        }
        template <class F>
        void traverse(F functor)
        {
            traverse_sub_tree(root, functor);
        }
        template <class F>
        void reverse_traverse(F functor)
        {
            reverse_traverse_sub_tree(root, functor);
        }
        void construct(const std::string& s);
        std::string evaluate() {return evaluate_node(root).get_data();}
    };

    Tree_node* parse(std::string::const_iterator &ref, const std::string::const_iterator begin, const std::string::const_iterator end);
    Tree_node* parse_mul(std::string::const_iterator &ref, const std::string::const_iterator begin, const std::string::const_iterator end);
    Tree_node* parse_minus(std::string::const_iterator &ref, const std::string::const_iterator begin, const std::string::const_iterator end);

    void Syntax_tree::construct(const std::string& s)
    {
        clear();
        std::string::const_iterator ref = s.begin();
        root = parse(ref, s.begin(), s.end());
        if(ref != s.end()) throw Calculator_error(Calculator_error_type::SYNTAX_ERROR);
    }

    Tree_node* parse(std::string::const_iterator &ref, const std::string::const_iterator begin, const std::string::const_iterator end)
    {
        Tree_node* res = parse_mul(ref, begin, end);
        while(ref != end && (*ref == '+' || *ref == '-'))
        {
            res = new Tree_node(get_next_token(ref, begin, end), res, parse_mul(ref, begin, end));
        }
        if(*ref == ')') ++ref;
        return res;
    }

    Tree_node* parse_mul(std::string::const_iterator &ref, const std::string::const_iterator begin, const std::string::const_iterator end)
    {
        Tree_node* res = parse_minus(ref, begin, end);
        while(ref != end && (*ref == '*' || *ref == '/'))
            res = new Tree_node(get_next_token(ref, begin, end), res, parse_minus(ref, begin, end));
        return res;
    }

    Tree_node* parse_minus(std::string::const_iterator &ref, const std::string::const_iterator begin, const std::string::const_iterator end)
    {
        if(*ref == '-')
        {
            Tree_node* res = new Tree_node(get_next_token(ref, begin, end));
            if(*ref == '(')
                res->right = parse(++ref, begin, end);
            else res->right = new Tree_node(get_next_token(ref, begin, end));
            return res;
        }
        if(*ref == '(')
            return parse(++ref, begin, end);
        return new Tree_node(get_next_token(ref, begin, end));
    }
}

#endif // SYNTAX_TREE_H_INCLUDED
