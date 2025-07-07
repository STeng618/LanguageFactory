#include <benchmark/benchmark.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#include <cstdlib> 
#include <parser.hpp>  

std::mt19937 rng;
std::uniform_int_distribution<size_t> size_dist(1, 1024);
std::uniform_int_distribution<int> coin_flip(0, 1);

std::vector<void*> junk;
std::vector<std::string> expressions;
constexpr size_t ALLOC_COUNT = 100;

class RandomHeapParser : public benchmark::Fixture {
    public:
    void SetUp(const benchmark::State& state) override {
        junk.reserve(ALLOC_COUNT);
        for (size_t i = 0; i < ALLOC_COUNT; i++) {
            junk.push_back(malloc(size_dist(rng)));
        }
        for (size_t i = 0; i < ALLOC_COUNT; i++) {
            if (coin_flip(rng)) {
                free(junk[i]);
                junk[i] = nullptr;
            }
        }
    }
    void TearDown(const benchmark::State& state) override {
        for (size_t i = 0; i < ALLOC_COUNT; i++) {
            free(junk[i]);
            junk[i] = nullptr;
        }
        junk.clear();
    }
};

BENCHMARK_DEFINE_F(RandomHeapParser, ParseRandom)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& expr : expressions) {
            auto result = Langfact::Parser::parse(expr);
            benchmark::DoNotOptimize(result);
        }
    }
}
BENCHMARK_REGISTER_F(RandomHeapParser, ParseRandom);

static void Parse(benchmark::State& state) {
    for (auto _ : state) {
        for (auto& expr : expressions) {
            auto result = Langfact::Parser::parse(expr);
            benchmark::DoNotOptimize(result);
        }
    }
}
BENCHMARK(Parse);

int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);

    std::random_device rd;
    rng.seed(rd());

    std::string file_path;
    std::cin >> file_path;
    std::ifstream file(file_path);
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) expressions.push_back(line);
    }

    benchmark::RunSpecifiedBenchmarks();
}
