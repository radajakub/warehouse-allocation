#ifndef TIMER_H
#define TIMER_H

#include<chrono>
#include<iostream>
#include<fstream>

class Timer {
    private:
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;

    public:
        inline void start() { this->begin = std::chrono::steady_clock::now(); }

        inline void stop() { this->end = std::chrono::steady_clock::now(); }

        inline void print() { std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->begin).count() << "ms"; }

        inline void print(std::ofstream& out) { out << std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->begin).count() << "ms"; }
};

#endif

