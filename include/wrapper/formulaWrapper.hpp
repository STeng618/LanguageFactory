#ifndef FORMULA_WRAPPER_H 
#define FORMULA_WRAPPER_H 
#include <formula/formula.hpp>
#include <wrapper/wrapper.hpp>

namespace Langfact {
    class FormulaWrapper: public Wrapper {
        protected: 
        Formula* m_formula; 

        public: 
        FormulaWrapper(Formula* formula, Token::ChildrenList&& children = {})
        : Wrapper(std::move(children)), m_formula(std::move(formula)) {}

        Token* close() override {
            m_formula->set_children(std::move(m_children)); 
            return m_formula;
        } 

        void identify() const override {
            std::cout << "<class:FormulaWrapper>";
        }
    };
}

#endif 