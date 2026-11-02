#include <iostream>
#include <assert.h>

template<class T>
class Vector {

    // private:

    T* m_data;

    size_t m_size;

public:
    // create class (constructor, destructor, at)

    Vector(size_t s)

        : m_data{ new T[s] }, m_size{ s } {}

    ~Vector() {
        delete[] m_data;
    }

    Vector(const Vector& other)

        : m_data{ new T[other.size()] }, m_size{ other.size() } {

        for (size_t i = 0; i < this->size(); i++) {

            this->at(i) = other.at(i);
        }
    }

    Vector& operator=(const Vector& other)

    {

        if (this == &other) return *this;

        delete[] m_data;

        m_data = new T[other.size()];

        m_size = other.size();

        for (size_t i = 0; i < this->size(); i++) {

            this->at(i) = other.at(i);
        }

        return *this;
    }

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

template<class T>
void print(const T& v) {

    // v.at(0) = 1000;

    for (size_t i = 0; i < v.size(); i++) {

        std::cout << "at(" << i << ") = " << v.at(i) << std::endl;
    }
}

//int main() {
//
//    Vector<float> v(3);
//
//    v.at(0) = 9.3;
//
//    v.at(1) = 11.1;
//
//    v.at(2) = 12.2;
//
//    print(v);
//
//    Vector<float> v2 = v;
//
//    v2 = v;
//
//    v2 = v2;
//
//    v.at(0) = 1000;
//
//    print(v2);
//}




int main() {
    assert(!IsOptionalV<int>);
    assert(IsOptionalV<std::optional<int>>);
}