#ifndef VALUE_H 
#define VALUE_H 

#include <iostream>
#include <string> 
#include <token.hpp>

namespace Langfact{

    template <typename T>
    class Value: public Token {
        private: 
        T m_content; 

        public:
        Value<T>(T content, Token::ChildrenList children = {})
        : Token(std::move(children)) 
        , m_content(content)
        {}

        std::pair<int,int> evaluate_output_dim() override {
            return {-1, -1};
        }

        void identify() const override {
            std::cout << m_content << std::endl;
        }
    };
}

#endif 