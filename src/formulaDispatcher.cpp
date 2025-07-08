#include <map>
#include <formulaDispatcher.hpp>
#include <formula/formula.hpp>
#include <formula/operator.hpp>
#include <arena.hpp>

using namespace Langfact;

const std::unordered_map<std::string_view, std::function<Formula*(Token::ChildrenList&&)>> FormulaDispatcher::FUNC_MAP = {
    {"XLOOKUP", [](Token::ChildrenList&& children) {
        return Arena<Xlookup>::get_instance().create(std::move(children));
    }},
};

Formula* FormulaDispatcher::dispatch(std::string_view name, Langfact::Token::ChildrenList&& children) {
    auto it = FUNC_MAP.find(name); 
    if (it == FUNC_MAP.end()) {
        return Arena<Formula>::get_instance().create(std::move(children), name);
    }
    return it->second(std::move(children));
}

