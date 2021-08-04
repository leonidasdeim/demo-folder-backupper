#ifndef UTILS_H
#define UTILS_H

#include <chrono>

using namespace std::chrono;

namespace Utils {

template <typename T>
std::time_t formatTime(T t) {
    auto t_temp = time_point_cast<system_clock::duration>(t - T::clock::now() + system_clock::now());
    return system_clock::to_time_t(t_temp);
}

}

#endif // UTILS_H
