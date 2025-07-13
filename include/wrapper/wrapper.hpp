#ifndef WRAPPER_H 
#define WRAPPER_H 

#include <token.hpp>
#include <emptyToken.hpp>
#include <arena.hpp>

namespace Langfact {

    class Wrapper: public Token {
        public:
        Wrapper(Token::ChildrenList children = {}, TokenType token_type = TokenType::WRAPPER)
        : Token(std::move(children), token_type) {}

        /*
            Closes a wrapper token. There are 3 cases: 
            1. The wrapper wraps more than one children -> returns null 
            2. The wrapper wraps only one token -> transfers ownership of the child to caller 
            3. The wrapper wraps nothing -> returns an empty token 
        */
        virtual Token* close() {
            if (m_children.size() > 1) {
                return nullptr;
            } 
            if (m_children.size() == 1) {
                return m_children[0];
            }
            return Arena<EmptyToken>::get_instance().create();
        }
        
        void identify() const override {
            std::cout << "<class:Wrapper>";
        }
    };
}

#endif 