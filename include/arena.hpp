#ifndef ARENA_H
#define ARENA_H

#include <cstddef>
#include <vector>

class ArenaBase {
public:
    virtual void clear() = 0;
    virtual ~ArenaBase() = default;
};

void register_arena(ArenaBase* arena);
void clear_all_arenas();

template <typename T, size_t N = 500>
class Arena : public ArenaBase {
public:
    void clear() override {
        m_offset = 0;
    }

    T* reserve() {
        if (m_offset >= N) {
            throw std::runtime_error("Arena has reached capacity");
        }
        return reinterpret_cast<T*>(&m_buffer[m_offset++]);
    }

    template <typename... Args>
    T* create(Args&&... args) {
        T* ptr = reserve();
        return new (ptr) T(std::forward<Args>(args)...); 
    }

    static Arena& get_instance() {
        static Arena arena_instance;
        static bool is_registered = (register_arena(&arena_instance), true);
        (void)(is_registered);
        return arena_instance;
    }

private:
    std::byte m_buffer[N][sizeof(T)];
    size_t m_offset;

    Arena() : m_offset(0) {}

    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
    Arena(Arena&&) = delete;
    Arena& operator=(Arena&&) = delete;
};

#endif
