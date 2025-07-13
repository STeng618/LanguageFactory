# LanguageFactory

## Background

LanguageFactory is a structured-language parses which parses expressions that support arithmetic operators, function applications, and nested evaluation. It respects operator associativity and precedence rules, and handles prefix/postfix notations. The parser tokenizes valid expressions and constructs a token tree. This tree can be further processed for purposes such as evaluation, transformation, or code generation.

The project is designed with latency efficiency in mind, and several techniques were implemented to reduce memory and CPU overhead.

## Latency-Oriented Design

### Arena Allocation

LanguageFactory uses an arena allocator to efficiently manage memory for tokens and nodes during parsing. Instead of allocating each token on the heap, memory is drawn from a pre-allocated contiguous buffer. This eliminates per-object `malloc` overhead and reduces fragmentation.

Arena allocation benefits include:

- Quick runtime allocation via pointer bumping
- Fast reset via a single offset rollback (`arena.clear()`)

This approach is well-suited for short-lived parse trees that do not require individual deallocation of objects.

### Hash-Based Symbol Resolution

Operators and function symbols are resolved using a hash-based lookup system. The parser identifies relevant symbols using hashing techniques and dispatch tokens with the appropriate operator precedence, arity, and associativity.

This results in:
- Clean extensibility for adding new operators or functions
- Separation of symbol logic from parse logic

### Contiguous Token Tree Layout

Tokens and token nodes are allocated contiguously in memory through the arena. This improves cache locality during parsing and later traversal of the token tree. Small object sizes and reduced pointer indirection also contribute to faster execution.

## Current Status

The parser can handle a wide class of arithmetic expressions including:

- Binary operators (e.g. `+`, `-`, `*`, `/`, `^`)
- Function calls (e.g. `SUM(1, 2, 3)`)
- Parentheses and nesting
- Prefix and postfix unary operators (e.g. `-A1`, `B1%`)

## Getting Started
To get started with LanguageFactory, clone the repository and build the project. Create a build directory and run CMake:

```bash
mkdir build && cd build
cmake ..
make
```

Run the langfact binary and supply valid expressions:
```bash
./langfact 
=SUM(1, 2, 3)
```

I have also provided GPT-generated expressions in expressions.txt for testing. You can run the parser against these expressions to see how it handles various cases.
