#ifndef ARENA_H
#define ARENA_H

#include <cstddef>
#include <vector>

class ArenaBase {
    protected:
    size_t m_offset;

    public:
    ArenaBase(): m_offset(0) {};
    void clear() {  m_offset = 0; }
};

void register_arena(ArenaBase* arena);
void clear_all_arenas();

template <typename T>
class Arena : public ArenaBase {

    private:
        // std::byte m_buffer[N][sizeof(T)];
        T* m_buffer;
        size_t m_n;
        Arena(size_t n = 500) : ArenaBase() {
            m_buffer = static_cast<T*>(malloc(n * sizeof(T)));
            m_n = n;
        };
        ~Arena() { free(m_buffer); }

        Arena(const Arena&) = delete;
        Arena& operator=(const Arena&) = delete;
        Arena(Arena&&) = delete;
        Arena& operator=(Arena&&) = delete;

    public:
        T* reserve() {
            if (m_offset >= m_n) {
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
};

#endif
