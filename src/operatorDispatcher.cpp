#include <map>
#include <operatorDispatcher.hpp>
#include <formula/operator.hpp>
#include <arena.hpp>

using namespace Langfact; 

const std::unordered_map<std::string_view, std::function<Operator*(Token::ChildrenList&&)>> OperatorDispatcher::OP_MAP = {
    {"y+", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpSum>::get_instance().create(std::move(children));
    }},
    {"y-", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpSubtract>::get_instance().create(std::move(children));
    }},
    {"y*", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpMultiply>::get_instance().create(std::move(children));
    }},
    {"y/", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpDivide>::get_instance().create(std::move(children));
    }},
    {"y=", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpEQ>::get_instance().create(std::move(children));
    }},
    {"y<>", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpNE>::get_instance().create(std::move(children));
    }},
    {"y>", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpGT>::get_instance().create(std::move(children));
    }},
    {"y>=", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpGE>::get_instance().create(std::move(children));
    }},
    {"y<", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpLT>::get_instance().create(std::move(children));
    }},
    {"y<=", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpLE>::get_instance().create(std::move(children));
    }},
    {"y&", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpConcat>::get_instance().create(std::move(children));
    }},
    {"y!", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpSheetRef>::get_instance().create(std::move(children));
    }},
    // {"y:", [](Langfact::Token::ChildrenList&& children) {
    //     return Arena<Langfact::OpRangeSeparator>::get_instance().create(std::move(children));
    // }},
    {"y^", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpExponentiate>::get_instance().create(std::move(children));
    }},
    {"n-", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpNegate>::get_instance().create(std::move(children));
    }},
    {"n+", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpUnaryPlus>::get_instance().create(std::move(children));
    }},
    {"y%", [](Langfact::Token::ChildrenList&& children) {
        return Arena<Langfact::OpPercent>::get_instance().create(std::move(children));
    }}
};


const int OperatorDispatcher::MAX_OP_LEN = 2;

std::pair<Operator*,int> OperatorDispatcher::dispatch(
    std::string_view name, bool has_a_prior_token, Token::ChildrenList&& children
) {
    std::string formatted = (has_a_prior_token ? std::string("y") : std::string("n")) + std::string(name);
    for (int len = std::min(static_cast<int>(name.size()), OperatorDispatcher::MAX_OP_LEN); len > 0; len--) {
        auto it = OperatorDispatcher::OP_MAP.find(formatted.substr(0, len + 1)); 
        if (it != OperatorDispatcher::OP_MAP.end()) {
            return {it->second(std::move(children)), len};
        }
    }
    return {nullptr, 0};
}

