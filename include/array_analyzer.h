#pragma once

#include <array>

#include "container_analyzer.h"

#define ARRAY_SIZE 1000

class ArrayAnalyzer : public ContainerAnalyzer<std::array<BASETYPE, ARRAY_SIZE>> {
    typedef std::function<void(std::array<BASETYPE, ARRAY_SIZE>&)> array_func;
    virtual void test(array_func setup, array_func preop, array_func op,
                      int count);
    virtual void print_header();
    virtual void print_ckpt(std::array<BASETYPE, ARRAY_SIZE>& a);
public:
    ArrayAnalyzer() = default;
    void test_operator_brackets_random(int count);
    void test_at_random(int count);
    static constexpr auto tests = "operator_brackets_random, at_random";
};
