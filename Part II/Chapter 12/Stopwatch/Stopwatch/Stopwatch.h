#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

class Stopwatch {
    std::chrono::nanoseconds& result;
    const std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    Stopwatch(std::chrono::nanoseconds& result);
    ~Stopwatch();
};

#endif