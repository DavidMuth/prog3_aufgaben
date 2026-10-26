#include <atomic>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>

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
    /*Sender(Sender&& other) : queue_(std::move(other.queue_)) {
        std::cout << "Sender: move ctor\n";
    }*/

    Sender& operator=(Sender&& other) = default;

    Sender() = default;
    Sender(std::shared_ptr<SpscQueue> queue) :queue_(queue) {}

    void send(const int& v) {
            assert(queue_);
            queue_->push_wait(v);
    }
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


    int recv() {
        assert(queue_);
        return queue_->pop_wait();
    };
};

struct Channel { // the return value of channel()
    Sender tx;
    Receiver rx;
};

Channel channel(std::size_t capacity) {
    std::shared_ptr<SpscQueue> queue = std::make_shared<SpscQueue>(capacity);
    return Channel{ .tx = Sender(queue), .rx = Receiver(queue) };
};

void producer_fun(Sender tx, int N) { // by value: the move happens here
    for (int i = 1; i <= N; ++i) {
        tx.send(i);
    }
}


// TASK B:
// Warum weder SpscQueue-Member noch unique_ptr?
//  - Die Queue wird von 2 Objekten gebraucht (Sender und Receiver), und
//    beide müssen sie am Leben halten.
//  - Ein SpscQueue-Member gehörte nur einer Hälfte, die andere hätte keinen Zugriff.
//  - unique_ptr erlaubt nur einen Besitzer. Die andere Hälfte wäre ein reiner
//    Beobachter
//
// Warum shared_ptr?
//  - Die Queue wird zerstört, wenn der letzte
//    verschwindet, egal ob Sender oder Receiver zuerst endet.
//
// Warum ist das trotz atomic-Membern sicher?
//  - Der Referenzzähler des shared_ptr ist unabhängig von der Queue -> schützt nur die Lebensdauer der Queue.
//  - Die Elemente sind durch head und tail abgesichert: Der Producer ändert nur tail,
//    der Consumer nur head. Der acquire/release sorgt dafür, dass der andere Thread
//    die geschriebenen Daten sicher sieht.
//
// Warum bleibt SpscQueue einfach?
//  - Nur der shared_ptr wird verschoben, die Queue selbst nie. Sie
//    muss daher weder kopierbar noch verschiebbar sein


int main() {
    Channel c = channel(2); // capacity 2 -> forces real waiting

    constexpr int n = 8;

    std::thread producer([&] { producer_fun(std::move(c.tx), n); });

    for (int i = 0; i < n; ++i) {
        int x = c.rx.recv();
        std::cout << "received = " << x << '\n';
    }

    //c.tx.send(1); // compiles but reports a runtime error (assert): tx was moved!
    //receiver rx2 = c.rx; // does not compile (no copies!)

    producer.join();
}


//void by_value(Sender tx) {}
//void by_rref(Sender&& tx) {}
//int main() {
//    Channel c = channel(2);
//    by_rref(std::move(c.tx));  // keine Ausgabe: kein neues Objekt wird erstellt
//    by_value(std::move(c.tx)); // Ausgabe: Paramter neues eigenes Objekt -  Move-Konstruktor läuft
//}