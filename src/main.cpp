#include <iostream>
#include <functional>
#include <random>

#include "array_analyzer.h"
#include "vector_analyzer.h"
#include "deque_analyzer.h"

#define DEFAULT_COUNT 1000

std::random_device g_rd;
std::mt19937 g_rng(g_rd());

int usage(int argc, char *argv[]) {
    if (argc < 1) return 1;
    std::cerr << argv[0] << " container test [args]\n";
    std::cerr << std::endl;
    std::cerr << "containers: array, vector, deque, list, priority_queue, set, \
unordered_set, map, unordered_map\n";
    std::cerr << std::endl;
    std::cerr << "tests:\n";
    std::cerr << " vector: " << VectorAnalyzer::tests << "\n";
    std::cerr << " array: " << ArrayAnalyzer::tests << "\n";
    std::cerr << " deque: " << DequeAnalyzer::tests << "\n";
    return 1;
}

void test_array(const std::string test_name, int count) {
    ArrayAnalyzer aa;
    if (test_name == "operator_brackets_random")
        aa.test_operator_brackets_random(count);
    else if (test_name == "at_random")
        aa.test_at_random(count);
    else
        std::cerr << "array " << test_name << " not supported\n";
}

void test_vector(const std::string test_name, int count) {
    VectorAnalyzer va;
    if (test_name == "operator_brackets_random")
        va.test_operator_brackets_random(count);
    else if (test_name == "at_random")
        va.test_at_random(count);
    else if (test_name == "push_back")
        va.test_push_back(count);
    else if (test_name == "pop_back")
        va.test_pop_back(count);
    else if (test_name == "insert_start")
        va.test_insert_start(count);
    else if (test_name == "insert_end")
        va.test_insert_end(count);
    else if (test_name == "erase_start")
        va.test_erase_start(count);
    else if (test_name == "erase_end")
        va.test_erase_end(count);
    else if (test_name == "clear")
        va.test_clear(count);
    else if (test_name == "clear_and_shrink_to_fit")
        va.test_clear_and_shrink_to_fit(count);
    else
        std::cerr << "vector " << test_name << " not supported\n";
}

void test_deque(const std::string test_name, int count) {
    DequeAnalyzer da;
    if (test_name == "operator_brackets_random")
        da.test_operator_brackets_random(count);
    else if (test_name == "at_random")
        da.test_at_random(count);
    else if (test_name == "push_back")
        da.test_push_back(count);
    else if (test_name == "push_front")
        da.test_push_back(count);
    else if (test_name == "pop_back")
        da.test_push_back(count);
    else if (test_name == "pop_front")
        da.test_push_back(count);
    else
        std::cerr << "deque " << test_name << " not supported\n";
}

int main(int argc, char *argv[]) {
    if (argc < 3)
        return usage(argc, argv);
    int count = DEFAULT_COUNT;
    if (argc >= 4)
        count = std::stoi(argv[3]);
    const std::string container_name(argv[1]);
    const std::string test_name(argv[2]);
    if (container_name == "array")
        test_array(test_name, count);
    else if (container_name == "vector")
        test_vector(test_name, count);
    else if (container_name == "deque")
        test_deque(test_name, count);
    else
        std::cerr << container_name << " not supported\n";
    return 0;
}
