#include <atomic>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
#include <memory>
// a queue of ints
class SpscQueue {
    std::vector<int> buf_;
    const std::size_t cap_;
    std::atomic<std::size_t> head_{ 0 }; // consumer index
    std::atomic<std::size_t> tail_{ 0 }; // producer index

public:
    SpscQueue(std::size_t capacity)
        : buf_(capacity + 1), // one slot wasted to distinguish full/empty
          cap_(capacity + 1) {}

    bool try_push(const int& v) {
        const auto t = tail_.load(std::memory_order_relaxed);
        if ((t + 1) % cap_ == head_.load(std::memory_order_acquire)) return false; // full
        buf_[t] = v;
        tail_.store((t + 1) % cap_, std::memory_order_release);
        return true;
    }

    bool try_pop(int& out) {
        const auto h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire)) return false; // empty
        out = std::move(buf_[h]);
        head_.store((h + 1) % cap_, std::memory_order_release);
        return true;
    }

    // polling helpers
    void push_wait(const int& v) {
        while (!try_push(v)) /* spin */
            ;
    }
    int pop_wait() {
        int v;
        while (!try_pop(v)) /* spin */
            ;
        return v;
    }
};

class Sender {
    std::shared_ptr<SpscQueue> queue_;
 public:
     // No copying
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    // Move
    Sender(Sender&& other) = default;

    Sender& operator=(Sender&& other) = default;

    Sender() = default;
    Sender(std::shared_ptr<SpscQueue> queue) :queue_(queue) {}

    void send(const int& v);
};

class Receiver {
    std::shared_ptr<SpscQueue> queue_;
public:
    // No copying
    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;
    // Move
    Receiver(Receiver&& other) = default;

    Receiver& operator=(Receiver&& other) = default;

    Receiver() = default;
    Receiver(std::shared_ptr<SpscQueue> queue) : queue_(queue) {}


    int recv();
};

struct Channel { // the return value of channel()
    Sender tx;
    Receiver rx;
};

Channel channel(std::size_t capacity) {
    // TODO: create a shared SpscQueue and move it into
    // a Sender and a Receiver (constructor params)
    std::shared_ptr<SpscQueue> queue = std::make_shared<SpscQueue>(capacity);
    return Channel{ .tx = Sender(queue), .rx = Receiver(queue) };
};


int main() {
    SpscQueue queue{ 2 };
    assert(queue.try_push(10));
    assert(queue.try_push(11));
    assert(!queue.try_push(12));

    int out;
    assert(queue.try_pop(out));
    std::cout << "out: " << out << "\n";
    assert(queue.try_pop(out));
    std::cout << "out: " << out << "\n";
    assert(!queue.try_pop(out));
}
