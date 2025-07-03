#ifndef OPERATOR_DISPATCHER_H 
#define OPERATOR_DISPATCHER_H

#include <map>
#include <formulaDispatcher.hpp>
#include <formula/operator.hpp>

namespace Langfact {

    class OperatorDispatcher {
        private:

        static const std::unordered_map<std::string_view, std::function<std::unique_ptr<Operator>(Token::ChildrenList&&)>> OP_MAP;

        public:
        static const int MAX_OP_LEN;
        static std::pair<std::unique_ptr<Operator>,int> dispatch(
            std::string_view op_str, 
            bool has_token_since_last_nullptr,
            Token::ChildrenList&& children = {}
        );
    };
}

#endif 