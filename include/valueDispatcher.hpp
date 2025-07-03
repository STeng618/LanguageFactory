#ifndef VALUE_DISPATCHER_H 
#define VALUE_DISPATCHER_H

#include <iostream> 
#include <token.hpp>

namespace Langfact {

    class ValueDispatcher {
        public:
        static std::unique_ptr<Token> dispatch(std::string content);
    };
}

#endif 