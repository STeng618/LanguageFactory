#include <benchmark/benchmark.h>
#include <fstream>
#include <string>
#include <vector>
#include "parser.hpp" 

static std::vector<std::string> expressions;

static void LoadExpressions() {
    std::ifstream file("benchmarks/expressions.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) expressions.push_back(line);
    }
}

static void Parse(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& expr : expressions) {
            auto token = Langfact::Parser::parse(expr); 
            benchmark::DoNotOptimize(token);
        }
    }
}
BENCHMARK(Parse);

int main(int argc, char** argv) {
    LoadExpressions();
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}
