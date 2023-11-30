#pragma once

#include <deque>

#include "container_analyzer.h"

class DequeAnalyzer : public ContainerAnalyzer<std::deque<BASETYPE>> {
    typedef std::function<void(std::deque<BASETYPE>&)> deque_func;
    virtual void test(deque_func setup, deque_func preop, deque_func op,
                      int count);
    virtual void print_header();
    virtual void print_ckpt(std::deque<BASETYPE>& d);
public:
    DequeAnalyzer() = default;
    void test_operator_brackets_random(int count);
    void test_at_random(int count);
    void test_push_back(int count);
    void test_push_front(int count);
    void test_pop_back(int count);
    void test_pop_front(int count);
//    void test_insert_middle(int count);
//    void test_erase_middle(int count);
//    void test_clear(int count);
//    void test_clear_and_shrink_to_fit(int count);
    static constexpr auto tests = "operator_brackets_random, at_random, \
push_back, push_front, pop_back, pop_front, insert_middle, erase_middle, \
clear, clear_and_shrink_to_fit";
};
