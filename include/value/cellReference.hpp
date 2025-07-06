#ifndef CELL_REFERENCE_H 
#define CELL_REFERENCE_H 

#include <iostream>
#include <string> 
#include <token.hpp>


namespace Langfact {
    class CellReference : public Token {
        public:
        static std::unique_ptr<CellReference> create(std::string_view expr);
        std::pair<int,int> get_dimensions();
        void identify() const override {
            std::cout << "<CellReference: " << m_repr << " l:" << m_l << " t:" << m_t  << " r:" << m_r << " b:" << m_b << ">";
        }

        private:
        std::string m_repr;
        int m_l, m_t, m_r, m_b;

        CellReference(std::string_view repr, int l = -1, int t = -1, int r = -1, int b = -1)
        : m_repr(repr), m_l(l), m_t(t), m_r(r), m_b(b) {}
    };
}


#endif 