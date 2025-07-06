#include <valueDispatcher.hpp>
#include <value/value.hpp>
#include <value/cellReference.hpp>
#include <iostream> 

using namespace Langfact;

std::unique_ptr<Token> ValueDispatcher::dispatch(std::string expr) {

    if (
        (expr[0] == '\'' && expr.back() == '\'') 
        || (expr[0] == '\"' && expr.back() == '\"') 
    ) {
        return std::make_unique<Value<std::string>>(expr);
    }

    try {
        size_t idx;
        int int_val = std::stoi(expr, &idx);
        if (idx == expr.size()) {
           return std::make_unique<Value<int>>(int_val); 
        }
    } catch (...) {}

    try {
        size_t idx;
        double int_val = std::stod(expr, &idx);
        if (idx == expr.size()) {
           return std::make_unique<Value<double>>(int_val); 
        }
    } catch (...) {} 

    if (expr == "TRUE") return std::make_unique<Value<bool>>(true);
    if (expr == "FALSE") return std::make_unique<Value<bool>>(false);

    auto cell_ref {CellReference::create(expr)};
    if (cell_ref != nullptr) return cell_ref;

    return std::make_unique<Value<std::string>>(expr);
}