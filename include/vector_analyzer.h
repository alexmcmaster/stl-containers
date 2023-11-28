#pragma once

#include <vector>

#include "container_analyzer.h"

class VectorAnalyzer : public ContainerAnalyzer<std::vector<int>> {
    typedef std::function<void(std::vector<int>&)> vector_func;
    virtual void test(vector_func setup, vector_func preop, vector_func op,
                      int count);
    virtual void print_header();
    virtual void print_ckpt(std::vector<int>& v);
public:
    VectorAnalyzer() = default;
    void test_operator_brackets_random(int count);
    void test_at_random(int count);
    void test_push_back(int count);
    void test_pop_back(int count);
    void test_insert_start(int count);
    void test_insert_end(int count);
    void test_erase_start(int count);
    void test_erase_end(int count);
    void test_clear(int count);
    void test_clear_and_shrink_to_fit(int count);
    static constexpr auto tests = "operator_brackets_random, at_random, \
push_back, pop_back, insert_start, insert_end, erase_start, erase_end, clear, \
clear_and_shrink_to_fit";
};
