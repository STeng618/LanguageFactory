#include <iostream> 
#include <valueDispatcher.hpp>
#include <value/value.hpp>
#include <value/cellReference.hpp>
#include <value/fast_float.h>
#include <arena.hpp>

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

Token* ValueDispatcher::dispatch(std::string_view expr) {

    if (
        (expr[0] == '\'' && expr.back() == '\'') 
        || (expr[0] == '\"' && expr.back() == '\"') 
    ) {
        return Arena<Value<std::string_view>>::get_instance().create(expr.substr(1, expr.size() - 2));
    }

    auto isInt_intVal {parse_int(expr)};
    if (isInt_intVal.first) {
        return Arena<Value<int>>::get_instance().create(isInt_intVal.second);
    }

    double value;
    auto result = fast_float::from_chars(expr.data(), expr.data() + expr.size(), value);
    if (result.ec == std::errc() && result.ptr == expr.data() + expr.size()) {
        return Arena<Value<int>>::get_instance().create(value); 
    }

    if (expr == "TRUE") return Arena<Value<bool>>::get_instance().create(true);
    if (expr == "FALSE") return Arena<Value<bool>>::get_instance().create(false);

    auto cell_ref {CellReference::create(expr)};
    if (cell_ref != nullptr) return cell_ref;

    return Arena<Value<std::string_view>>::get_instance().create(expr);
}