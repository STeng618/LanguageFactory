#include <map>
#include <operatorDispatcher.hpp>
#include <formula/operator.hpp>

using namespace Langfact; 

const std::unordered_map<std::string_view, std::function<std::unique_ptr<Operator>(Token::ChildrenList&&)>> OperatorDispatcher::OP_MAP = {
    {"b+", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpSum>(std::move(children));
    }},
    {"b-", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpSubtract>(std::move(children));
    }},
    {"b*", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpMultiply>(std::move(children));
    }},
    {"b/", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpDivide>(std::move(children));
    }},
    {"b=", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpEQ>(std::move(children));
    }},
    {"b<>", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpNE>(std::move(children));
    }},
    {"b>", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpGT>(std::move(children));
    }},
    {"b>=", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpGE>(std::move(children));
    }},
    {"b<", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpLT>(std::move(children));
    }},
    {"b<=", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpLE>(std::move(children));
    }},
    {"b&", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpConcat>(std::move(children));
    }},
    {"b!", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpSheetRef>(std::move(children));
    }},
    {"b:", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpRangeSeparator>(std::move(children));
    }},
    {"b^", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpExponentiate>(std::move(children));
    }},
    {"n-", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpNegate>(std::move(children));
    }},
    {"u+", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpUnaryPlus>(std::move(children));
    }},
    {"y%", [](Langfact::Token::ChildrenList&& children) {
        return std::make_unique<Langfact::OpPercent>(std::move(children));
    }}
};

const int OperatorDispatcher::MAX_OP_LEN = 2;

std::pair<std::unique_ptr<Operator>,int> OperatorDispatcher::dispatch(
    std::string_view name, bool has_token_since_last_nullptr, Token::ChildrenList&& children
) {
    std::string formatted = (has_token_since_last_nullptr ? std::string("b") : std::string("u")) + std::string(name);
    for (int len = std::min(static_cast<int>(name.size()), OperatorDispatcher::MAX_OP_LEN); len > 0; len--) {
        auto it = OperatorDispatcher::OP_MAP.find(formatted.substr(0, len + 1)); 
        if (it != OperatorDispatcher::OP_MAP.end()) {
            return {it->second(std::move(children)), len};
        }
    }
    return {nullptr, 0};
}

