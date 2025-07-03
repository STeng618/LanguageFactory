#ifndef EMPTY_TOKEN_H 
#define EMPTY_TOKEN_H 

#include <token.hpp>

namespace Langfact {
    class EmptyToken: public Token {
        public:
        EmptyToken() = default;
        void identify() const override {
            std::cout << "<class:Empty>";
        } 
    };
}

#endif 
