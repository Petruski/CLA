//
// Created by Petrus Söderström on 2022-04-30.
//

#ifndef CLA_DATASTREAMITERATOR_HPP
#define CLA_DATASTREAMITERATOR_HPP

#include <vector>

template<typename T>
class DataStreamIterator {
public:
    explicit DataStreamIterator(std::vector<T> &container) : m_container(container) {
        m_iterator = m_container.begin();
    }
    bool hasNext() {
        return m_iterator != m_container.end();
    };
    T next() {
        T temp = *m_iterator;
        m_iterator++;
        return temp;
    };

    void remove() {
        m_iterator = m_container.erase(--m_iterator);
    }
private:
    std::vector<T> &m_container;
    typename std::vector<T>::iterator m_iterator;
};

#endif //CLA_DATASTREAMITERATOR_HPP
