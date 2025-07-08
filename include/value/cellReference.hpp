#ifndef CELL_REFERENCE_H 
#define CELL_REFERENCE_H 

#include <iostream>
#include <string> 
#include <token.hpp>


namespace Langfact {
    class CellReference : public Token {
        public:
        const std::string m_repr;
        const int m_l, m_t, m_r, m_b;

        static CellReference* create(std::string_view expr);
        void identify() const override {
            std::cout << "<CellReference: " << m_repr << " l:" << m_l << " t:" << m_t  << " r:" << m_r << " b:" << m_b << ">";
        }

        private:
        CellReference(std::string_view repr, int l, int t, int r, int b)
        : m_repr(repr), m_l(l), m_t(t), m_r(r), m_b(b) {}
    };
}


#endif 