#include <iostream>

template<typename T>
class Vector {

    // private:

    T* m_data;

    size_t m_size;

public:
    // create class (constructor, destructor, at)

    Vector(size_t s)

        : m_data{ new T[s] }, m_size{ s } {}

    // at(idx) --> werte

    const T& at(size_t idx) const { // T& = referenz = alias = platzhalter für das was zurückgegeben wurde

        return m_data[idx];
    }

    T& at(size_t idx) { // T& = referenz = alias = platzhalter für das was zurückgegeben wurde

        return m_data[idx];
    }

    size_t size() const {

        return m_size;
    }
};

void print(const Vector<float>& v) {

    // v.at(0) = 1000;

    for (size_t i = 0; i < v.size(); i++) {

        std::cout << "at(" << i << ") = " << v.at(i) << std::endl;
    }
}

int main() {

    Vector<float> v(3);

    v.at(0) = 9.3;

    v.at(1) = 11.1;

    v.at(2) = 12.2;

    print(v);
}
