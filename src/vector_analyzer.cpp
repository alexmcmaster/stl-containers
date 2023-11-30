#include <iostream>
#include <functional>
#include <random>

#include "vector_analyzer.h"

#define NOOP [](std::vector<BASETYPE>& _v){}

using namespace std::placeholders;

extern std::mt19937 g_rng;

static void fill_vector(std::vector<BASETYPE>& v, int count) {
    v.clear();
    v.shrink_to_fit();
    for (int i = 0; i < count; i++)
        v.push_back(i);
}

void VectorAnalyzer::print_header() {
    std::cout << "init size,init cap,final size,final cap,duration_ns\n";
}

void VectorAnalyzer::print_ckpt(std::vector<BASETYPE>& v) {
    std::cout << v.size() << "," << v.capacity() << ",";
}

void VectorAnalyzer::test(vector_func setup, vector_func preop,
                          vector_func op, int count) {
    print_header();
    std::vector<BASETYPE> v;
    setup(v);
    for (int i = 0; i < count; i++) {
        print_ckpt(v);
        preop(v);
        auto t1 = high_resolution_clock::now();
        op(v);
        auto t2 = high_resolution_clock::now();
        print_ckpt(v);
        print_duration(t1, t2);
    }
}

void VectorAnalyzer::test_operator_brackets_random(int count) {
    std::uniform_int_distribution<BASETYPE> randindex(0, count - 1);
    test(
        std::bind(fill_vector, _1, count),
        NOOP,
        [&](std::vector<BASETYPE>& _v){_v[randindex(g_rng)];},
        count
    );
}

void VectorAnalyzer::test_at_random(int count) {
    std::uniform_int_distribution<BASETYPE> randindex(0, count - 1);
    test(
        std::bind(fill_vector, _1, count),
        NOOP,
        [&](std::vector<BASETYPE>& _v){_v.at(randindex(g_rng));},
        count
    );
}

void VectorAnalyzer::test_push_back(int count) {
    test(
        NOOP,
        NOOP,
        [](std::vector<BASETYPE>& _v){_v.push_back(FIXEDNUM);},
        count
    );
}

void VectorAnalyzer::test_pop_back(int count) {
    test(
        std::bind(fill_vector, _1, count),
        NOOP,
        [](std::vector<BASETYPE>& _v){_v.pop_back();},
        count
    );
}

void VectorAnalyzer::test_insert_start(int count) {
    test(
        NOOP,
        NOOP,
        [](std::vector<BASETYPE>& _v){_v.insert(_v.begin(), FIXEDNUM);},
        count
    );
}

void VectorAnalyzer::test_insert_end(int count) {
    test(
        NOOP,
        NOOP,
        [](std::vector<BASETYPE>& _v){_v.insert(_v.end(), FIXEDNUM);},
        count
    );
}

void VectorAnalyzer::test_erase_start(int count) {
    test(
        std::bind(fill_vector, _1, count),
        NOOP,
        [](std::vector<BASETYPE>& _v){_v.erase(_v.begin());},
        count
    );
}

void VectorAnalyzer::test_erase_end(int count) {
    test(
        std::bind(fill_vector, _1, count),
        NOOP,
        [](std::vector<BASETYPE>& _v){_v.erase(_v.end() - 1);},
        count
    );
}

void VectorAnalyzer::test_clear(int count) {
    test(
        NOOP,
        std::bind(fill_vector, _1, count),
        [](std::vector<BASETYPE>& _v){_v.clear();},
        count
    );
}

void VectorAnalyzer::test_clear_and_shrink_to_fit(int count) {
    test(
        NOOP,
        std::bind(fill_vector, _1, count),
        [](std::vector<BASETYPE>& _v){_v.clear(); _v.shrink_to_fit();},
        count
    );
}
