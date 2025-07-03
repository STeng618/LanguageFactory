#include <iostream> 
#include <token.hpp>
#include <formula/formula.hpp>
#include <formulaDispatcher.hpp>
#include <valueDispatcher.hpp>
#include <parser.hpp>

using namespace Langfact;

int main() {
    while(1) {
        std::string x; 
        std::getline(std::cin, x);
        auto token {Parser::parse(x)};
        token->print();
        printf("\n");
    }

}