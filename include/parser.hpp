#ifndef PARSER_H 
#define PARSER_H 

#include <stack>
#include <set>
#include <token.hpp>

namespace Langfact {

    class Parser {
        private: 
        static const std::bitset<256> BREAKING_CHARS; 
        
        public: 
        static Token* parse(std::string expr);
    };
}

#endif