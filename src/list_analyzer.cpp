#include <iostream>
#include <functional>
#include <random>

#include "list_analyzer.h"

#define NOOP [](std::list<BASETYPE>& _l){}

using namespace std::placeholders;

extern std::mt19937 g_rng;

static void fill_list(std::list<BASETYPE>& l, int count) {
    for (int i = 0; i < count; i++)
        l.push_back(i);
}

void ListAnalyzer::print_header() {
    std::cout << "init size,init max size,final size,final max size,duration_ns\n";
}

void ListAnalyzer::print_ckpt(std::list<BASETYPE>& l) {
    std::cout << l.size() << "," << l.max_size() << ",";
}

void ListAnalyzer::test(list_func setup, list_func preop,
                          list_func op, int count) {
    print_header();
    std::list<BASETYPE> l;
    setup(l);
    for (int i = 0; i < count; i++) {
        preop(l);
        print_ckpt(l);
        auto t1 = high_resolution_clock::now();
        op(l);
        auto t2 = high_resolution_clock::now();
        print_ckpt(l);
        print_duration(t1, t2);
    }
}

void ListAnalyzer::test_front(int count) {
    test(
        NOOP,
        [](std::list<BASETYPE>& _l){_l.push_back(FIXEDNUM);},
        [](std::list<BASETYPE>& _l){_l.front();},
        count
    );
}

void ListAnalyzer::test_back(int count) {
    test(
        NOOP,
        [](std::list<BASETYPE>& _l){_l.push_back(FIXEDNUM);},
        [](std::list<BASETYPE>& _l){_l.back();},
        count
    );
}

void ListAnalyzer::test_push_back(int count) {
    test(
        NOOP,
        NOOP,
        [](std::list<BASETYPE>& _l){_l.push_back(FIXEDNUM);},
        count
    );
}

void ListAnalyzer::test_push_front(int count) {
    test(
        NOOP,
        NOOP,
        [](std::list<BASETYPE>& _l){_l.push_front(FIXEDNUM);},
        count
    );
}

void ListAnalyzer::test_pop_back(int count) {
    test(
        std::bind(fill_list, _1, count),
        NOOP,
        [](std::list<BASETYPE>& _l){_l.pop_back();},
        count
    );
}

void ListAnalyzer::test_pop_front(int count) {
    test(
        std::bind(fill_list, _1, count),
        NOOP,
        [](std::list<BASETYPE>& _l){_l.pop_front();},
        count
    );
}

void ListAnalyzer::test_insert_middle(int count) {
    test(
        NOOP,
        NOOP,
        [](std::list<BASETYPE>& _l){
                auto it = _l.begin();
                std::advance(it, _l.size() / 2);
                _l.insert(it, FIXEDNUM);},
        count
    );
}

void ListAnalyzer::test_erase_middle(int count) {
    test(
        std::bind(fill_list, _1, count),
        NOOP,
        [](std::list<BASETYPE>& _l){
                auto it = _l.begin();
                std::advance(it, _l.size() / 2);
                _l.erase(it);},
        count
    );
}

void ListAnalyzer::test_clear(int count) {
    test(
        NOOP,
        std::bind(fill_list, _1, count),
        [](std::list<BASETYPE>& _l){_l.clear();},
        count
    );
}
