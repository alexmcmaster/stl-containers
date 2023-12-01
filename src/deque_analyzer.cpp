#include <iostream>
#include <functional>
#include <random>

#include "deque_analyzer.h"

#define FIXEDNUM 85
#define NOOP [](std::deque<BASETYPE>& _d){}

using namespace std::placeholders;

extern std::mt19937 g_rng;

static void fill_deque(std::deque<BASETYPE>& d, int count) {
    for (int i = 0; i < count; i++)
        d.push_back(i);
}

void DequeAnalyzer::print_header() {
    std::cout << "init size,init max size,final size,final max size,duration_ns\n";
}

void DequeAnalyzer::print_ckpt(std::deque<BASETYPE>& d) {
    std::cout << d.size() << "," << d.max_size() << ",";
}

void DequeAnalyzer::test(deque_func setup, deque_func preop,
                          deque_func op, int count) {
    print_header();
    std::deque<BASETYPE> d;
    setup(d);
    for (int i = 0; i < count; i++) {
        print_ckpt(d);
        preop(d);
        auto t1 = high_resolution_clock::now();
        op(d);
        auto t2 = high_resolution_clock::now();
        print_ckpt(d);
        print_duration(t1, t2);
    }
}

void DequeAnalyzer::test_operator_brackets_random(int count) {
    std::uniform_int_distribution<BASETYPE> randindex(0, count - 1);
    test(
        std::bind(fill_deque, _1, count),
        NOOP,
        [&](std::deque<BASETYPE>& _d){_d[randindex(g_rng)];},
        count
    );
}

void DequeAnalyzer::test_at_random(int count) {
    std::uniform_int_distribution<BASETYPE> randindex(0, count - 1);
    test(
        std::bind(fill_deque, _1, count),
        NOOP,
        [&](std::deque<BASETYPE>& _d){_d.at(randindex(g_rng));},
        count
    );
}

void DequeAnalyzer::test_push_back(int count) {
    test(
        NOOP,
        NOOP,
        [](std::deque<BASETYPE>& _d){_d.push_back(FIXEDNUM);},
        count
    );
}

void DequeAnalyzer::test_push_front(int count) {
    test(
        NOOP,
        NOOP,
        [](std::deque<BASETYPE>& _d){_d.push_front(FIXEDNUM);},
        count
    );
}

void DequeAnalyzer::test_pop_back(int count) {
    test(
        std::bind(fill_deque, _1, count),
        NOOP,
        [](std::deque<BASETYPE>& _d){_d.pop_back();},
        count
    );
}

void DequeAnalyzer::test_pop_front(int count) {
    test(
        std::bind(fill_deque, _1, count),
        NOOP,
        [](std::deque<BASETYPE>& _d){_d.pop_front();},
        count
    );
}

void DequeAnalyzer::test_insert_middle(int count) {
    test(
        NOOP,
        NOOP,
        [](std::deque<BASETYPE>& _d){_d.insert(_d.begin() + (_d.size() / 2),
                                              FIXEDNUM);},
        count
    );
}

void DequeAnalyzer::test_erase_middle(int count) {
    test(
        std::bind(fill_deque, _1, count),
        NOOP,
        [](std::deque<BASETYPE>& _d){_d.erase(_d.begin() + (_d.size() / 2));},
        count
    );
}

void DequeAnalyzer::test_clear(int count) {
    test(
        NOOP,
        std::bind(fill_deque, _1, count),
        [](std::deque<BASETYPE>& _d){_d.clear();},
        count
    );
}

void DequeAnalyzer::test_clear_and_shrink_to_fit(int count) {
    test(
        NOOP,
        std::bind(fill_deque, _1, count),
        [](std::deque<BASETYPE>& _d){_d.clear(); _d.shrink_to_fit();},
        count
    );
}
