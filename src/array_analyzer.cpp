#include <iostream>
#include <functional>
#include <random>

#include "array_analyzer.h"

#define FIXEDNUM 0x55555555
#define NOOP [](std::array<int, ARRAY_SIZE>& _a){}

using namespace std::placeholders;

extern std::mt19937 g_rng;

static void fill_array(std::array<int, ARRAY_SIZE>& a, int count) {
    count = ARRAY_SIZE;
    for (int i = 0; i < count; i++)
        a[i] = i;
}

void ArrayAnalyzer::print_header() {
    std::cout << "init size,init max size,final size,final max size,duration_ns\n";
}

void ArrayAnalyzer::print_ckpt(std::array<int, ARRAY_SIZE>& a) {
    std::cout << a.size() << "," << a.max_size() << ",";
}

void ArrayAnalyzer::test(array_func setup, array_func preop,
                          array_func op, int count) {
    count = ARRAY_SIZE;
    print_header();
    std::array<int, ARRAY_SIZE> a;
    setup(a);
    for (int i = 0; i < count; i++) {
        print_ckpt(a);
        preop(a);
        auto t1 = high_resolution_clock::now();
        op(a);
        auto t2 = high_resolution_clock::now();
        print_ckpt(a);
        print_duration(t1, t2);
    }
}

void ArrayAnalyzer::test_operator_brackets_random(int count) {
    count = ARRAY_SIZE;
    std::uniform_int_distribution<int> randindex(0, count - 1);
    test(
        std::bind(fill_array, _1, count),
        NOOP,
        [&](std::array<int, ARRAY_SIZE>& _a){_a[randindex(g_rng)];},
        count
    );
}

void ArrayAnalyzer::test_at_random(int count) {
    count = ARRAY_SIZE;
    std::uniform_int_distribution<int> randindex(0, count - 1);
    test(
        std::bind(fill_array, _1, count),
        NOOP,
        [&](std::array<int, ARRAY_SIZE>& _a){_a.at(randindex(g_rng));},
        count
    );
}
