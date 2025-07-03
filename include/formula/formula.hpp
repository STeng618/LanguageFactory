#ifndef FORMULA_H 
#define FORMULA_H 

#include <iostream>
#include <string> 
#include <token.hpp>

namespace Langfact{
    class Formula: public Token {
        private: 
        std::string m_name;

        public:
        Formula(
            Token::ChildrenList children = {},
            std::string_view name = "GENERIC"
        ): Token(std::move(children)), m_name(name) {}

        void identify() const override { std::cout << "<class:Formula>" << m_name;}
    };

    class Xlookup: public Formula {
        public: 
        Xlookup(
            Token::ChildrenList children = {},
            std::string_view name = "XLOOKUP" 
        ): Formula(std::move(children), name) {}
    };
}

#endif 