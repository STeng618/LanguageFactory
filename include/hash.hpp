#ifndef HASH_H 
#define HASH_H

#include <iostream>

template <size_t N>
constexpr uint32_t hash(const char (&str)[N]) {
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < N - 1; i++) { // Last char assumed to be '\0' 
        hash ^= static_cast<unsigned char>(str[i]);
        hash *= 16777619u;
    }
    return hash;
}

template <size_t N>
constexpr bool are_unique_hashes(const std::array<uint32_t, N>& hashes) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = i + 1; j < N; j++) {
            if (hashes[i] == hashes[j]) return false;
        }
    }
    return true;
}

#endif 