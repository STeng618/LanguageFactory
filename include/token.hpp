#ifndef TOKEN_H 
#define TOKEN_H 

#include <iostream>
#include <string>
#include <vector> 

namespace Langfact {

    class Token {
        public: 
        using ChildrenList = std::vector<std::unique_ptr<Token>>; 
        
        protected:
        ChildrenList m_children {};

        public: 
        Token(ChildrenList children = {}) 
            : m_children{std::move(children)}
        {}

        void set_tokens(ChildrenList tokens) {
            m_children = std::move(tokens);
        }

        virtual void identify() const {
            std::cout << "Generic token " << this << std::endl;
        }

        virtual std::pair<int,int> evaluate_output_dim() {
            return {-1, -1};
        }

        virtual ~Token() = default;
    };
}

#endif