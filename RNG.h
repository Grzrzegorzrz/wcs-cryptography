#ifndef HEADER_HPP
#define HEADER_HPP

#include <chrono>

//random number generation using the linear congruence method, of length n
unsigned char* randomNumGen(int n) {
    int a = 1664525;
    int b = 1013904223;

    unsigned char* num = new unsigned char[n];

    //creates a seed using the current time
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    int seed = static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(duration).count());

    num[0] = seed % 127;

    for(int i = 1; i < n; i++) {
        num[i] = ((num[i-1] * a) + b) % 127;
    }

    return num;
}
//we want any int from 32 to 126 inclusive for ascii

#endif