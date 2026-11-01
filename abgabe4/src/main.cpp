#include <atomic>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

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
    std::shared_ptr<class SpscQueue> queue;

public:
    // No copying allowed
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    // Moving
    Sender(Sender&& other) = default;
    Sender& operator=(Sender&& other) = delete;

    Sender(std::shared_ptr<class SpscQueue> qPtr) : queue{ qPtr } {};

    void send(const int& v) {
        assert(queue && "send on a moved-from Sender");
        queue->push_wait(v);
    };
};

class Receiver {
    std::shared_ptr<class SpscQueue> queue;

public:
    // No copying allowed
    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    // Moving
    Receiver(Receiver&& other) = default;
    Receiver& operator=(Receiver&& other) = delete;

    Receiver(std::shared_ptr<class SpscQueue> qPtr) : queue{ qPtr } {};

    int recv() {
        assert(queue && "recv on a moved-from Receiver");
        return queue->pop_wait();
    };
};

struct Channel { // the return value of channel()
    Sender tx;
    Receiver rx;
};

Channel channel(std::size_t capacity) {
    // TODO: create a shared SpscQueue and move it into
    std::shared_ptr<class SpscQueue> queue = std::make_shared<SpscQueue>(capacity);
    // a Sender and a Receiver (constructor params)
    return Channel{ Sender(queue), Receiver(queue) };
}

/*int main() {
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
}*/

#include <thread>

void producer_fun(Sender tx, int N) { // by value: the move happens here
    for (int i = 1; i <= N; ++i) {
        tx.send(i);
    }
}

int main() {
    Channel c = channel(2); // capacity 2 -> forces real waiting

    constexpr int N = 8;

    std::thread producer([&] { producer_fun(std::move(c.tx), N); });

    for (int i = 0; i < N; ++i) {
        int x = c.rx.recv();
        std::cout << "received = " << x << '\n';
    }

    // c.tx.send(1); // compiles but reports a runtime error (assert): tx was moved!
    // Receiver rx2 = c.rx; // does not compile (no copies!)

    producer.join();
}
