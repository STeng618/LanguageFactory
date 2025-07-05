#ifndef PARSER_H 
#define PARSER_H 

#include <stack>
#include <set>
#include <token.hpp>

namespace Langfact {

    class Parser {
        private: 
        static const std::set<char> BREAKING_CHARS; 
        
        public: 
        static std::unique_ptr<Token> parse(std::string expr);
    };
}

#endif