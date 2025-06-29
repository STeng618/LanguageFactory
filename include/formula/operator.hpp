#ifndef OPERATOR_H 
#define OPERATOR_H 

#include <iostream>
#include <string> 
#include <formula/formula.hpp>

namespace Langfact{

    using Precedence = int; 
    constexpr Precedence GE = 0; 
    constexpr Precedence GT = 0; 
    constexpr Precedence LE = 0; 
    constexpr Precedence LT = 0; 
    constexpr Precedence EQ = 0; 
    constexpr Precedence NE = 0; 
    constexpr Precedence Concat = 1; 
    constexpr Precedence Sum = 2; 
    constexpr Precedence Subtract = 2; 
    constexpr Precedence Multiply = 3; 
    constexpr Precedence Divide = 3;
    constexpr Precedence SheetRef = 4; 
    constexpr Precedence RangeDivider = 5; 

    class Operator: public Formula {
        protected: 
        Precedence m_precedence;

        public:
        Operator(
            Token::ChildrenList children = {}, 
            Precedence precedence = 0
        )
        : Formula(std::move(children)), m_precedence(precedence) {}

        std::pair<int,int> evaluate_output_dim() override {
            return {1, 1};
        }

        bool operator<(const Operator& other) const {
            return m_precedence < other.m_precedence;
        }

    };

    class OperatorGE: public Operator {
        public:
        OperatorGE(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), GE) {}
    };

    class OperatorGT: public Operator {
        public:
        OperatorGT(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), GT) {}
    };

    class OperatorLE: public Operator {
        public:
        OperatorLE(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), LE) {}
    };

    class OperatorLT: public Operator {
        public:
        OperatorLT(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), LT) {}
    };
    class OperatorEQ: public Operator {
        public:
        OperatorEQ(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), EQ) {}
    };

    class OperatorNE: public Operator {
        public:
        OperatorNE(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), NE) {}
    };

    class OperatorConcat: public Operator {
        public:
        OperatorConcat( 
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), Concat) {}
    };

    class OperatorSum: public Operator {
        public:
        OperatorSum(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), Sum) {}
    };

    class OperatorSubtract: public Operator {
        public:
        OperatorSubtract(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), Subtract) {}
    };

    class OperatorMultiply: public Operator {
        public:
        OperatorMultiply(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), Multiply) {}
    };

    class OperatorDivide: public Operator {
        public:
        OperatorDivide(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), Divide) {}
    };

    class OperatorSheetRef: public Operator {
        public:
        OperatorSheetRef(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), SheetRef){}
    };

    class OperatorRangeDivider: public Operator {
        public:
        OperatorRangeDivider(
            Token::ChildrenList children = {}
        )
        : Operator(std::move(children), RangeDivider){}
    };
}

#endif 