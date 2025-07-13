#include <iostream> 
#include <token.hpp>
#include <formula/formula.hpp>
#include <formulaDispatcher.hpp>
#include <valueDispatcher.hpp>
#include <parser.hpp>
#include <arena.hpp>

using namespace Langfact;

int main() {
    std::string x; 
    while(1) {
        std::getline(std::cin, x);
        auto token {Parser::parse(x)};
        token->print_tree();
        printf("\n");
        clear_all_arenas();
    }
}