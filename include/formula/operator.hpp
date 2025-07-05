#ifndef OPERATOR_H 
#define OPERATOR_H 

#include <iostream>
#include <string> 
#include <set>
#include <formula/formula.hpp>

namespace Langfact{

    using Precedence = int; 
    constexpr Precedence UNDEFINED = -1; 
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
    constexpr Precedence Exponentiate = 4; 
    constexpr Precedence Percent = 5;
    constexpr Precedence UnaryPlus = 6; 
    constexpr Precedence Negate = 6;
    constexpr Precedence SheetRef = 7; 
    constexpr Precedence RangeSeparator = 8; 

    enum class Associativity {
        LEFT, 
        RIGHT
    };

    enum class UnaryPosition {
        UNDEFINED,
        PREFIX, 
        POSTFIX
    };

    class Operator: public Formula {
        protected: 
        Precedence m_precedence;

        public:
        int m_expected_num_args;

        Operator(
            Token::ChildrenList children = {}, 
            Precedence precedence = UNDEFINED, 
            int expected_num_args = 0
        ): Formula(std::move(children)), m_precedence(precedence), m_expected_num_args(expected_num_args) {}

        bool has_lower_equal_precedence_than(const std::unique_ptr<Operator>& op) {
            return m_precedence <= op->m_precedence;
        }
    };

    class UnaryOp: public Operator {
        protected:
        UnaryOp(
            Token::ChildrenList children = {}, 
            Precedence precedence = UNDEFINED
        ): Operator(std::move(children), precedence, 1) {}
    };

    class BinaryOp: public Operator {
        protected:
        BinaryOp(
            Token::ChildrenList children = {}, 
            Precedence precedence = UNDEFINED
        ): Operator(std::move(children), precedence, 2) {}
    };

    class OpGE: public BinaryOp {
        public:
        OpGE(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), GE) {}
        void identify() const override {
            std::cout << ">=";
        }
    };

    class OpGT: public BinaryOp {
        public:
        OpGT(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), GT) {}
        void identify() const override {
            std::cout << ">";
        }
    };

    class OpLT: public BinaryOp {
        public:
        OpLT(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), LT) {}
        void identify() const override {
            std::cout << "<";
        }
    };

    class OpLE: public BinaryOp {
        public:
        OpLE(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), LE) {}
        void identify() const override {
            std::cout << "<=";
        }
    };


    class OpEQ: public BinaryOp {
        public:
        OpEQ(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), EQ) {}
        void identify() const override {
            std::cout << "=";
        }
    };

    class OpNE: public BinaryOp {
        public:
        OpNE(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), NE) {}
        void identify() const override {
            std::cout << "<>";
        }
    };

    class OpConcat: public BinaryOp {
        public:
        OpConcat(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), Concat) {}
        void identify() const override {
            std::cout << "&";
        }
    };

    class OpSum: public BinaryOp {
        public:
        OpSum(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), Sum) {}
        void identify() const override {
            std::cout << "+";
        }
    };

    class OpSubtract: public BinaryOp {
        public:
        OpSubtract(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), Subtract) {}
        void identify() const override {
            std::cout << "-";
        }
    };

    class OpDivide: public BinaryOp {
        public:
        OpDivide(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), Divide) {}
        void identify() const override {
            std::cout << "/";
        }
    };

    class OpMultiply: public BinaryOp {
        public:
        OpMultiply(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), Multiply) {}
        void identify() const override {
            std::cout << "*";
        }
    };


    class OpExponentiate: public BinaryOp {
        public:
        OpExponentiate(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), Exponentiate, Associativity::RIGHT) {}
        void identify() const override {
            std::cout << "^";
        }
    };

    class OpUnaryPlus: public UnaryOp {
        public:
        OpUnaryPlus(
            Token::ChildrenList children = {}
        ): UnaryOp(std::move(children), UnaryPlus) {}
        void identify() const override {
            std::cout << "U+";
        }
    };

    class OpNegate: public UnaryOp {
        public:
        OpNegate(
            Token::ChildrenList children = {}
        ): UnaryOp(std::move(children), Negate) {}
        void identify() const override {
            std::cout << "U-";
        }
    };

    class OpSheetRef: public BinaryOp {
        public:
        OpSheetRef(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), SheetRef) {}
        void identify() const override {
            std::cout << "!";
        }
    };

    class OpRangeSeparator: public BinaryOp {
        public:
        OpRangeSeparator(
            Token::ChildrenList children = {}
        ): BinaryOp(std::move(children), RangeSeparator) {}
        void identify() const override {
            std::cout << ":";
        }
    };

    class OpPercent: public UnaryOp {
        public:
        OpPercent(
            Token::ChildrenList children = {}
        ): UnaryOp(std::move(children), Percent, Associativity::RIGHT, UnaryPosition::POSTFIX) {}
        void identify() const override {
            std::cout << "%";
        }
    };
    
}

#endif