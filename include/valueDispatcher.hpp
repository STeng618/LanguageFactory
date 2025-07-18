#ifndef VALUE_DISPATCHER_H 
#define VALUE_DISPATCHER_H

#include <iostream> 
#include <token.hpp>

namespace Langfact {

    class ValueDispatcher {
        public:
        static Token* dispatch(std::string_view content);
    };
}

#endif 