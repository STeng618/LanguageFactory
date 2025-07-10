#include <map>
#include <operatorDispatcher.hpp>
#include <formula/operator.hpp>
#include <arena.hpp>

using namespace Langfact;

template <size_t N>
constexpr uint32_t hash(const char (&str)[N]) {
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < N - 1; i++) { // Last char assumed to be '\0' 
        hash ^= static_cast<unsigned char>(str[i]);
        hash *= 16777619u;
    }
    return hash;
}

constexpr uint32_t h_plus  = hash("+");
constexpr uint32_t h_minus = hash("-");
constexpr uint32_t h_star  = hash("*");
constexpr uint32_t h_slash = hash("/");
constexpr uint32_t h_eq    = hash("=");
constexpr uint32_t h_neq   = hash("<>");
constexpr uint32_t h_gt    = hash(">");
constexpr uint32_t h_gte   = hash(">=");
constexpr uint32_t h_lt    = hash("<");
constexpr uint32_t h_lte   = hash("<=");
constexpr uint32_t h_amp   = hash("&");
constexpr uint32_t h_excl  = hash("!");
constexpr uint32_t h_caret = hash("^");
constexpr uint32_t h_percent = hash("%");


template <size_t N>
constexpr bool are_unique_hashes(const std::array<uint32_t, N>& hashes) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = i + 1; j < N; j++) {
            if (hashes[i] == hashes[j]) return false;
        }
    }
    return true;
}

constexpr std::array<uint32_t, 14> op_hashes = {
    h_plus, h_minus, h_star, h_slash, h_eq, h_neq,
    h_gt, h_gte, h_lt, h_lte, h_amp, h_excl, h_caret, h_percent
};

static_assert(
    are_unique_hashes(op_hashes), 
    "Hash collision detected among operators"
);

const int OperatorDispatcher::MAX_OP_LEN = 2;

std::pair<Operator*, int> OperatorDispatcher::dispatch(
    std::string_view name, bool has_a_prior_token, Token::ChildrenList&& children
) {
    if (name.empty()) return {nullptr, 0};

    uint32_t op_hash = 0;
    if (name.size() >= 2) {
        const char two_char[] = {name[0], name[1], '\0'};
        op_hash = hash(two_char);
        if (has_a_prior_token) {
            switch (op_hash) {
                case h_neq: return {Arena<OpNE>::get_instance().create(std::move(children)), 2};
                case h_gte: return {Arena<OpGE>::get_instance().create(std::move(children)), 2};
                case h_lte: return {Arena<OpLE>::get_instance().create(std::move(children)), 2};
            }
        }
    }

    const char one_char[] = {name[0], '\0'};
    op_hash = hash(one_char);
    if (has_a_prior_token) {
        switch (op_hash) {
            case h_plus:     return {Arena<OpSum>::get_instance().create(std::move(children)), 1};
            case h_minus:    return {Arena<OpSubtract>::get_instance().create(std::move(children)), 1};
            case h_star:     return {Arena<OpMultiply>::get_instance().create(std::move(children)), 1};
            case h_slash:    return {Arena<OpDivide>::get_instance().create(std::move(children)), 1};
            case h_eq:       return {Arena<OpEQ>::get_instance().create(std::move(children)), 1};
            case h_gt:       return {Arena<OpGT>::get_instance().create(std::move(children)), 1};
            case h_lt:       return {Arena<OpLT>::get_instance().create(std::move(children)), 1};
            case h_amp:      return {Arena<OpConcat>::get_instance().create(std::move(children)), 1};
            case h_excl:     return {Arena<OpSheetRef>::get_instance().create(std::move(children)), 1};
            case h_caret:    return {Arena<OpExponentiate>::get_instance().create(std::move(children)), 1};
            case h_percent:  return {Arena<OpPercent>::get_instance().create(std::move(children)), 1};
        }
    } else {
        switch (op_hash) {
            case h_minus: return {Arena<OpNegate>::get_instance().create(std::move(children)), 1};
            case h_plus:  return {Arena<OpUnaryPlus>::get_instance().create(std::move(children)), 1};
        }
    }

    return {nullptr, 0};
}
