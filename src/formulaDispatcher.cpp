#include <map>
#include <formulaDispatcher.hpp>
#include <formula/formula.hpp>
#include <formula/operator.hpp>

using namespace Langfact;

const std::unordered_map<std::string_view, std::function<std::unique_ptr<Formula>(Token::ChildrenList&&)>> FormulaDispatcher::FUNC_MAP = {
    {"XLOOKUP", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::Xlookup>(std::move(children));
    }},
};

std::unique_ptr<Langfact::Formula> FormulaDispatcher::dispatch(std::string_view name, Langfact::Token::ChildrenList&& children) {
    auto it = FUNC_MAP.find(name); 
    if (it == FUNC_MAP.end()) {
        return std::make_unique<Langfact::Formula>(std::move(children), name);
    }
    return it->second(std::move(children));
}

