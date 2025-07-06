#ifndef VALUE_H 
#define VALUE_H 

#include <iostream>
#include <string> 
#include <token.hpp>
#include <typeinfo>

namespace Langfact{

    template <typename T>
    class Value: public Token {
        private: 
        T m_content; 

        public:
        Value<T>(T content): Token(), m_content(content) {}

        void identify() const override {
            std::cout << "<Value " << typeid(m_content).name() << ": " << m_content << ">";
        }
    };
}

#endif 