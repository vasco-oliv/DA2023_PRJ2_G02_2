#ifndef DA2023_PRJ2_G02_2_MUTABLEPRIORITYQUEUE_H
#define DA2023_PRJ2_G02_2_MUTABLEPRIORITYQUEUE_H

#include <vector>


template <class T, class Compare = std::less<T>>
class MutablePriorityQueue {
    std::vector<T *> H;
    Compare compare;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, T * x);
public:
    MutablePriorityQueue();
    explicit MutablePriorityQueue(Compare compare);
    void insert(T * x);
    T * extractMin();
    void decreaseKey(T * x);
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T, class Compare>
MutablePriorityQueue<T, Compare>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T, class Compare>
MutablePriorityQueue<T, Compare>::MutablePriorityQueue(Compare compare)
        : compare(compare) {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T, class Compare>
bool MutablePriorityQueue<T, Compare>::empty() {
    return H.size() == 1;
}

template <class T, class Compare>
T* MutablePriorityQueue<T, Compare>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T, class Compare>
void MutablePriorityQueue<T, Compare>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T, class Compare>
void MutablePriorityQueue<T, Compare>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T, class Compare>
void MutablePriorityQueue<T, Compare>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && compare(*x, *H[parent(i)])) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T, class Compare>
void MutablePriorityQueue<T, Compare>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && compare(*H[k+1], *H[k]))
            ++k; // right child of i
        if (!compare(*H[k], *x))
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T, class Compare>
void MutablePriorityQueue<T, Compare>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif //DA2023_PRJ2_G02_2_MUTABLEPRIORITYQUEUE_H
