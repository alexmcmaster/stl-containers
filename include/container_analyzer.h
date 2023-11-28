#pragma once

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::time_point;

template <typename C>
class ContainerAnalyzer {
protected:
    typedef std::function<void(C&)> container_func;
    virtual void test(container_func setup, container_func preop,
                      container_func op, int count) = 0;
    virtual void print_header() = 0;
    virtual void print_ckpt(C& c) = 0;
    void print_duration(time_point<high_resolution_clock> t1,
                        time_point<high_resolution_clock> t2) {
        auto tdiff = duration_cast<std::chrono::nanoseconds>(t2 - t1);
        std::cout << tdiff.count() << std::endl;
    };
};
