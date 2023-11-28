#include <iostream>
#include <functional>

#include "vector_analyzer.h"

int usage(int argc, char *argv[]) {
    if (argc < 1) return 1;
    std::cerr << argv[0] << " container test [args]\n";
    std::cerr << std::endl;
    std::cerr << "containers: array, vector, deque, list, priority_queue, set, \
unordered_set, map, unordered_map\n";
    std::cerr << std::endl;
    std::cerr << "tests:\n";
    std::cerr << " vector: " << VectorAnalyzer::tests << "\n";
    return 1;
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

int main(int argc, char *argv[]) {
    if (argc < 3)
        return usage(argc, argv);
    int count = 10;
    if (argc >= 4)
        count = std::stoi(argv[3]);
    const std::string container_name(argv[1]);
    const std::string test_name(argv[2]);
    if (container_name == "vector")
        test_vector(test_name, count);
    else
        std::cerr << container_name << " not supported\n";
    return 0;
}
