#ifndef LOG_HF
#define LOG_HF

#include <iostream>
#include <sstream>

// Global variable to control logging
extern bool ENABLE_LOGGING;  //extern due to no One Definition Rule warning initialized in log.cpp

namespace pp {

template <typename... Args>
void log(bool should_print, Args&&... args) {
    if (should_print && ENABLE_LOGGING) {
        std::ostringstream stream;
        (stream << ... << std::forward<Args>(args));  // Fold expression (C++17) https://en.cppreference.com/w/cpp/language/fold
        std::cout << stream.str() << std::endl;
    }
}
}


#endif // LOG_HF