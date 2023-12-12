#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>
#include <limits>

class Stopwatch {

    double nan = std::numeric_limits<double>::quiet_NaN();
    std::chrono::high_resolution_clock clock;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    double elapsed_seconds = 0;

    enum class State {
        init,
        started,
        stopped
    };

    Stopwatch::State state = State::init;

    double elapsed_since_start() const {
        return std::chrono::duration<double>(clock.now() - start_time).count();
    }

public:

    Stopwatch() {
        reset();
    }

    void start() {
        if (state == State::started) {
            return;
        }
        state = State::started;
        start_time = clock.now();
    }

    double stop() {
        if (state != State::started) {
            return nan;
        }
        elapsed_seconds += elapsed_since_start();
        state = State::stopped;
        return elapsed();
    }

    void reset() {
        elapsed_seconds = 0;
        state = State::init;
    }

    double elapsed() const {
        if (state == State::started) {
            return elapsed_since_start() + elapsed_seconds;
        }
        if (state == State::stopped) {
            return elapsed_seconds;
        }
        return nan;
    }

};

#endif