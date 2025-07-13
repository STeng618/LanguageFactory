#include <iostream>
#include <cassert> 
#include <stack> 
#include <set>
#include <algorithm>
#include <token.hpp>
#include <emptyToken.hpp>
#include <wrapper/wrapper.hpp>
#include <wrapper/formulaWrapper.hpp>
#include <parser.hpp>
#include <formulaDispatcher.hpp>
#include <operatorDispatcher.hpp>
#include <valueDispatcher.hpp>
#include <formula/operator.hpp>
#include <arena.hpp>

using namespace Langfact;

const std::bitset<256> Parser::BREAKING_CHARS = [] {
    std::bitset<256> bs;
    for (char c : {'+', '-', '*', '/', '&', '>', '<', '=', '!', '^', '(', ')', ',', ' ', '%'}) {
        bs.set(static_cast<unsigned char>(c));
    }
    return bs;
}();


template <typename T>
void print_stack(const T& container) {
    for (auto& x: container) {
        if(!x) {
            std::cout << "nullptr, ";
        } else {
            x->identify();
            std::cout << ", "; 
        }
    }
    std::cout << std::endl;
}

Token* Parser::parse(std::string_view expr) {

    int idx = 0; 
    int n = (int)expr.size();

    while (idx < n && (expr[idx] == '\n' || expr[idx] == ' ')) idx++;

    if (idx == n) {
        return Arena<EmptyToken>::get_instance().create();
        // return std::make_unique<EmptyToken> ();
    }

    if (expr[idx] != '=') {
        return ValueDispatcher::dispatch(expr); 
    }

    // Wrap expression in ()
    // expr[idx] = '(';
    // expr.push_back(')'); 
    // n++;

    int formula_start = -1; 
    std::vector<Token*> token_stack{}; 
    std::vector<Operator*> operator_stack{};  
    token_stack.reserve(1024);
    operator_stack.reserve(512);
    bool has_a_prior_token = false;

    // This is entirely based on whether the #tokens meets the #expected arguments
    auto can_trigger_latest_op = [&]() -> bool {
        if (operator_stack.empty()) return false;
        if (!operator_stack.back()) return false; 
        int expected_args = operator_stack.back()->m_expected_num_args;
        return token_stack.size() >= (size_t)expected_args; 
    }; 

    auto trigger_one_op = [&]() -> void {
        auto from = token_stack.end() - operator_stack.back()->m_expected_num_args;
        
        std::vector<Token*> args; 
        args.reserve(operator_stack.back()->m_expected_num_args);
        for (auto it = from; it != token_stack.end(); it++) {
            args.push_back(*it);
        }
        
        token_stack.erase(from, token_stack.end());
        operator_stack.back()->set_children(std::move(args));
        token_stack.push_back(std::move(operator_stack.back()));
        operator_stack.pop_back();
    };

    auto insert_op_into_op_stack = [&](Operator* op) -> void {
        while (
            can_trigger_latest_op() && (
                op->has_lower_precedence_than(operator_stack.back()) 
                || (op->has_equal_precedence_as(operator_stack.back()) && op->m_associativity == Associativity::LEFT)
            )
        ) {
            trigger_one_op();
        }
        operator_stack.push_back(op);
    };

    auto clear_op_stack = [&]() -> void {
        while (can_trigger_latest_op()) trigger_one_op(); 
    };

    auto process_opening = [&]() -> void {
        if (formula_start == -1) {
            token_stack.push_back(Arena<Wrapper>::get_instance().create());
        } else {
            token_stack.push_back(Arena<FormulaWrapper>::get_instance().create(
                FormulaDispatcher::dispatch(expr.substr(formula_start, idx - formula_start)) 
            ));
            formula_start = -1; 
        }
        operator_stack.push_back(nullptr);
        has_a_prior_token = false;
        idx++;
    };

    auto process_closing = [&]() ->void {
        clear_op_stack();

        if (!has_a_prior_token) {
            token_stack.push_back(Arena<EmptyToken>::get_instance().create());
        }

        int num_token_in_wrapper = 0; 
        int num_token_total = static_cast<int>(token_stack.size());

        while (
            num_token_in_wrapper < num_token_total
            && token_stack[num_token_total - 1 - num_token_in_wrapper]->m_token_type != TokenType::WRAPPER
        ) {
            num_token_in_wrapper++;
        }
        if (num_token_in_wrapper == num_token_total) {
            throw std::runtime_error("No opening wrapper token!");
        }

        Wrapper* owner = static_cast<Wrapper*>(token_stack[num_token_total - 1 - num_token_in_wrapper]); 
        Token::ChildrenList children {};
        children.reserve(num_token_in_wrapper);
        for (int i = 0; i < num_token_in_wrapper; i++) {
            children.push_back(token_stack[num_token_total - num_token_in_wrapper + i]);
        }
        owner->set_children(std::move(children));

        for (int i = 0; i < num_token_in_wrapper; i++) {
            token_stack.pop_back();
            assert(!operator_stack.back()); 
            operator_stack.pop_back();
        }
        auto closed_token {owner->close()};
        bool is_able_to_close = closed_token != nullptr;
        if (is_able_to_close) {
            token_stack.pop_back();
            token_stack.push_back(std::move(closed_token));
        }
        has_a_prior_token = true;
        idx++;
    };


    process_opening();
    while (idx < n) {
        
        if (expr[idx] == ' ' or expr[idx] == '\n') {
            idx++;
            continue;
        }

        if (expr[idx] == ',') {
            clear_op_stack();
            if (!has_a_prior_token) {
                token_stack.push_back(Arena<EmptyToken>::get_instance().create());
            }
            operator_stack.push_back(nullptr); // A nullptr is used as a "barrier"
            has_a_prior_token = false;
            idx++; 
            continue;
        }

        if (expr[idx] == '\'' || expr[idx] == '\"') {
            int str_start = idx;
            char terminate_target = expr[idx];
            idx++;
            while (idx < n && expr[idx] != terminate_target) idx++;
            if (idx == n) {
                throw std::runtime_error("Unterminated string literal");
            }
            token_stack.push_back(ValueDispatcher::dispatch(expr.substr(str_start, idx - str_start + 1)));
            has_a_prior_token = true;
            idx++;  
            continue;
        } 

        if (expr[idx] == '(') {
            process_opening();
            continue; 
        }

        if (expr[idx] == ')') {
            process_closing();
            continue; 
        }

        if (!Parser::BREAKING_CHARS[static_cast<unsigned int>(expr[idx])]) {
            int start_idx = idx++; 
            while (idx < n && !Parser::BREAKING_CHARS[static_cast<unsigned int>(expr[idx])]) {
                idx++;
            }
            if (idx < n && expr[idx] == '(') {
                formula_start = start_idx;
                continue; 
            }
            token_stack.push_back(ValueDispatcher::dispatch(expr.substr(start_idx, idx - start_idx)));
            has_a_prior_token = true;
            continue; 
        }

        std::string_view potential_op {expr.substr(idx, std::min(OperatorDispatcher::MAX_OP_LEN, n - idx))};
        auto op_len {OperatorDispatcher::dispatch(potential_op, has_a_prior_token)};
        if (op_len.second) {
            has_a_prior_token = op_len.first->m_expected_num_args == 1 && op_len.first->m_unary_position == UnaryPosition::POSTFIX;
            insert_op_into_op_stack(std::move(op_len.first));
            idx += op_len.second;
            continue; 
        }

        throw std::runtime_error("Unrecognised case"); 
    }
    process_closing();

    if (token_stack.size() != 1) {
        throw std::runtime_error("Unable to parse");
    }

    return std::move(token_stack.front());
}