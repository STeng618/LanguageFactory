#include <valueDispatcher.hpp>
#include <value/value.hpp>
#include <iostream> 

using namespace Langfact;

std::unique_ptr<Token> ValueDispatcher::dispatch(std::string expr) {
    return std::make_unique<Value<std::string>>(expr);
}