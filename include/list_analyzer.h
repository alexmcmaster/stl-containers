#pragma once

#include <list>

#include "container_analyzer.h"

#define ARRAYLEN 1000

class ListAnalyzer : public ContainerAnalyzer<std::list<BASETYPE>> {
    typedef std::function<void(std::list<BASETYPE>&)> list_func;
    virtual void test(list_func setup, list_func preop, list_func op,
                      int count);
    virtual void print_header();
    virtual void print_ckpt(std::list<BASETYPE>& l);
public:
    ListAnalyzer() = default;
    void test_front(int count);
    void test_back(int count);
    void test_push_back(int count);
    void test_push_front(int count);
    void test_pop_back(int count);
    void test_pop_front(int count);
    void test_insert_middle(int count);
    void test_erase_middle(int count);
    void test_clear(int count);
    static constexpr auto tests = "operator_brackets_random, at_random";
};
