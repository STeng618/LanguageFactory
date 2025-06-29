#ifndef FORMULA_H 
#define FORMULA_H 

#include <iostream>
#include <string> 
#include <token.hpp>

namespace Langfact{
    class Formula: public Token {
        public:
        Formula(Token::ChildrenList children = {}): Token(std::move(children)) {}

        std::pair<int,int> evaluate_output_dim() override {
            return {-1, -1};
        }
    };

    class Xlookup: public Formula {
        public: 
        Xlookup(Token::ChildrenList children = {}): Formula(std::move(children)) {}

        void identify() const override {
            std::cout << "Xlookup " << this << std::endl;
        }
    };
}

#endif 