#ifndef LAB0_COROUTINEHELPERS_H
#define LAB0_COROUTINEHELPERS_H

#include <coroutine>
#include <chrono>
#include <thread>

struct TimerAwaiter {
    std::chrono::milliseconds duration;

    bool await_ready() const noexcept { return duration.count() <= 0; }
    void await_suspend(std::coroutine_handle<> handle) const {
        std::thread([handle, this]() {
            std::this_thread::sleep_for(duration);
            handle.resume();
        }).detach();
    }
    void await_resume() const noexcept {}
};

struct Generator {
    struct promise_type {
        Generator get_return_object() { return {}; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle = nullptr;

    Generator() = default;
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (handle) handle.destroy();
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }
    ~Generator() {
        if (handle) handle.destroy();
    }

    bool next() {
        if (!handle) {
            handle = std::coroutine_handle<promise_type>::from_promise(*reinterpret_cast<promise_type*>(this));
            handle.resume();
        }
        if (!handle.done()) {
            handle.resume();
            return !handle.done();
        }
        return false;
    }
};

#endif //LAB0_COROUTINEHELPERS_H
