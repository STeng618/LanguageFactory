#ifndef OPERATOR_DISPATCHER_H 
#define OPERATOR_DISPATCHER_H

#include <map>
#include <formulaDispatcher.hpp>
#include <formula/operator.hpp>

namespace Langfact {

    class OperatorDispatcher {
        public:
        static const int MAX_OP_LEN;
        static std::pair<Operator*,int> dispatch(
            std::string_view op_str, 
            bool has_token_since_last_nullptr,
            Token::ChildrenList&& children = {}
        );
    };
}

#endif 