#include <arena.hpp>

static std::vector<ArenaBase*>& get_arena_registry() {
    static std::vector<ArenaBase*> registry;
    return registry;
}

void register_arena(ArenaBase* arena) {
    get_arena_registry().push_back(arena);
}

void clear_all_arenas() {
    for (ArenaBase* arena : get_arena_registry()) {
        arena->clear();
    }
}
