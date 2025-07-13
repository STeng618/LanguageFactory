# LanguageFactory

## Background

LanguageFactory is a structured-language parser that parses expressions supporting arithmetic operators, function applications, and nested evaluation. It respects operator associativity and precedence rules, and handles prefix/postfix notations. The parser tokenizes valid expressions and constructs a token tree, which can be further processed for evaluation, transformation, or code generation.

This work was inspired by my project at Modular Asset Management, where we analyzed Excel expressions and predicted spill dimensions of spill formulae for analytical purposes. As such, the test expressions and parts of the parser are tailored to support Excel-like grammar. However, the architecture is easily extensible to other formula-oriented languages.

## Latency-Oriented Design

### Arena Allocation

LanguageFactory uses an arena allocator to efficiently manage memory for tokens and nodes during parsing. Instead of allocating each token individually on the heap, memory is drawn from a pre-allocated contiguous buffer. This eliminates per-object `malloc` overhead and reduces fragmentation.

Benefits include:
- Fast allocation via pointer bumping
- Instantaneous reset via a single offset rollback (`arena.clear()`)

This approach is especially suitable for short-lived parse trees that do not require fine-grained memory reclamation.

### Hash-Based Symbol Resolution

Operators and function symbols are resolved using a hash-based lookup system. The parser identifies symbols via hashing and dispatches tokens with the appropriate precedence, arity, and associativity.

Advantages include:

- Clean extensibility for adding new operators or functions
- Decoupling of symbol metadata from parsing logic

### Contiguous Token Tree Layout

Tokens and token nodes are allocated contiguously in memory through the arena. This improves cache locality during parsing and later traversal of the token tree. 

## Current Status

The parser can handle a wide class of arithmetic expressions including:

- Binary operators (e.g. `+`, `-`, `*`, `/`, `^`)
- Function calls (e.g. `SUM(1, 2, 3)`)
- Parentheses and nesting
- Prefix and postfix unary operators (e.g. `-A1`, `B1%`)

## Getting Started
To get started with LanguageFactory, clone the repository and build the project.

```bash
git clone --recurse-submodules https://github.com/STeng618/LanguageFactory.git
mkdir build
cd build
cmake ..
make
```

It should just work. But it is a CPP project afterall :D

Run the langfact binary and supply valid expressions:
```bash
./langfact 
=SUM(1, 2, 3)
```

I have also provided GPT-generated expressions in expressions.txt for testing. You can run the parser against these expressions to see how it handles various cases.
