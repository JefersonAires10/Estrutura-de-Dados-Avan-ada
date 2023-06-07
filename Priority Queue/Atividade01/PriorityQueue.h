#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <stdexcept>
#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> m_queue;
    size_t m_size;

    void move_up(size_t i);

    void move_down(size_t i) {
        while (2 * i <= m_size) {
            size_t l = 2 * i;
            size_t r = 2 * i + 1;
            size_t largest = i;
            if (m_queue[l] > m_queue[largest]) {
                largest = l;
            }
            if (r <= m_size && m_queue[r] > m_queue[largest]) {
                largest = r;
            }
            if (largest != i) {
                T aux = m_queue[i];
                m_queue[i] = m_queue[largest];
                m_queue[largest] = aux;
                i = largest;
            }
            else {
                break;
            }
        }
    }

    void build_max_heap() {
        for (size_t i = m_size / 2; i > 1; i--) {
            move_down(i);
        }
    }

public:
    PriorityQueue ( const PriorityQueue &) = delete ;
    PriorityQueue & operator =( const PriorityQueue &) = delete ;
    PriorityQueue () ;
    PriorityQueue ( const std :: vector <T >& v) ;
    bool empty () const { return m_size == 0; }
    size_t size () const { return m_size ; }
    void push ( const T& val );
    void pop () ;

    // construtor 
    PriorityQueue {
        m_size = 0;
    }

    PriorityQueue(const std::vector<T>& v) {
        m_size = v.size();
        m_queue.resize(m_size + 1);
        for (size_t i = 0; i < m_size; i++) {
            m_queue[i + 1] = v[i];
        }
        build_max_heap();

    }

    const T& top () const {
        if (m_size == 0) {
            throw std::runtime_error("PriorityQueue is empty");
        }
        return m_queue[1];
    }
    
}
#endif // PRIORITYQUEUE_H