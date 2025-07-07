#ifndef FORMULA_DISPATCHER_H 
#define FORMULA_DISPATCHER_H

#include <map>
#include <formula/formula.hpp>
#include <formula/operator.hpp>
#include <unordered_map>
#include <functional>

namespace Langfact {

    class FormulaDispatcher {
        private:
        static const std::unordered_map<std::string_view, std::function<std::unique_ptr<Formula>(Token::ChildrenList&&)>> FUNC_MAP;

        public:
        static std::unique_ptr<Formula> dispatch(std::string_view name, Token::ChildrenList&& children = {});
    };
}

#endif 