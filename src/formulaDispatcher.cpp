#include <map>
#include <formulaDispatcher.hpp>
#include <formula/formula.hpp>
#include <formula/operator.hpp>

const std::unordered_map<std::string_view, Langfact::FormulaDispatcher::FormulaCreator> Langfact::FormulaDispatcher::FUNC_MAP = {
    {"XLOOKUP", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::Xlookup>(std::move(children));
    }},
    {"+", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorSum>(std::move(children));
    }},
    {"-", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorSubtract>(std::move(children));
    }},
    {"*", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorMultiply>(std::move(children));
    }},
    {"/", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorDivide>(std::move(children));
    }},
    {"=", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorEQ>(std::move(children));
    }},
    {"<>", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorNE>(std::move(children));
    }},
    {">", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorGT>(std::move(children));
    }},
    {">=", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorGE>(std::move(children));
    }},
    {"<", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorLT>(std::move(children));
    }},
    {"<=", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorLE>(std::move(children));
    }},
    {"&", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorConcat>(std::move(children));
    }},
    {"!", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorSheetRef>(std::move(children));
    }},
    {":", [](Langfact::Token::ChildrenList children) {
        return std::make_unique<Langfact::OperatorRangeDivider>(std::move(children));
    }}
};

std::unique_ptr<Langfact::Formula> Langfact::FormulaDispatcher::dispatch(std::string_view name, Langfact::Token::ChildrenList children) {
    auto it = FUNC_MAP.find(name); 
    if (it == FUNC_MAP.end()) {
        return std::make_unique<Langfact::Formula>(std::move(children));
    }
    return it->second(std::move(children));
}

