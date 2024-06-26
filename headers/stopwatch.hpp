#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class Stopwatch {

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
            return 0.0;
        }
        elapsed_seconds += elapsed_since_start();
        state = State::stopped;
        return elapsed();
    }

    double reset() {
        auto ret = stop();
        elapsed_seconds = 0.0;
        state = State::init;
        return ret;
    }

    double elapsed() const {
        if (state == State::started) {
            return elapsed_since_start() + elapsed_seconds;
        }
        if (state == State::stopped) {
            return elapsed_seconds;
        }
        return 0.0;
    }

};

#endif