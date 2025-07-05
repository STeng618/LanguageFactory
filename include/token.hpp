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
        Token(ChildrenList&& children = {}) 
            : m_children{std::move(children)}
        {}

        virtual void set_children(ChildrenList&& children) {
            m_children = std::move(children);
        }

        virtual void identify() const {
            std::cout << "<class:Generic>";
        }

        void print() const {
            identify();  
            if (!m_children.size()) return;

            printf("(");
            for (size_t i = 0; i < m_children.size(); i++) {
                m_children[i]->print();
                if (i + 1 < m_children.size()) printf(", ");
            }
            printf(")");
        }

        void print_tree(int indent = 0) const {
            for (int i = 0; i < indent; i++) {
                printf(" ");
            }
            identify();
            for (auto& child: m_children) {
                printf("\n");
                child->print_tree(indent + 3);
            }
        }

        virtual ~Token() = default;
    };
}

#endif