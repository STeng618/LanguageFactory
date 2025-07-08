#include <valueDispatcher.hpp>
#include <value/value.hpp>
#include <value/cellReference.hpp>
#include <iostream> 

using namespace Langfact;

static constexpr std::pair<bool,int> parse_int(std::string_view expr) {

    size_t n = expr.size();
    if (!n) return {false, 0};

    size_t idx = 0; 
    int multiplier = 1;
    if (expr[0] == '-') {
        idx++;
        multiplier = -1;
    }
    if (idx == n) return {false, 0};

    int ans = 0;
    while (idx < n) {
        int val = expr[idx] - '0';
        if (val > 9 || val < 0) return {false, 0};
        ans = ans * 10 + val;
        idx++;
    }
    ans *= multiplier;
    return {true, ans};
}

std::unique_ptr<Token> ValueDispatcher::dispatch(std::string expr) {

    if (
        (expr[0] == '\'' && expr.back() == '\'') 
        || (expr[0] == '\"' && expr.back() == '\"') 
    ) {
        return std::make_unique<Value<std::string>>(expr.substr(1, expr.size() - 2));
    }

    auto isInt_intVal {parse_int(expr)};
    if (isInt_intVal.first) return std::make_unique<Value<int>>(isInt_intVal.second);

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