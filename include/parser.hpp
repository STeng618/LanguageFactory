#ifndef PARSER_H 
#define PARSER_H 

#include <stack>
#include <set>
#include <token.hpp>

namespace Langfact {

    class Parser {
        private: 
        static const std::set<std::string_view> BREAKING_CHARS; 

        public: 
        static std::unique_ptr<Token> parse(std::string_view expr);
    };
}

#endif