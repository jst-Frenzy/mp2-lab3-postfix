#ifndef __TQUEUE_H__
#define __TQUEUE_H__

#include <iostream>

template<typename T>
class TQueue {
    T* a;
    int n;
    int s, f;
    int cntElems;
public:
    TQueue(int size) {
        if (size <= 0) throw - 1;
        n = size;
        a = new T[n];
        s = 0;
        f = n - 1;
        cntElems = 0;
    }

    ~TQueue() {
        delete[] a;
    }

    int next(int i) {
        return ((i + 1) % n);
    }

    TQueue(const TQueue& other) {
        n = other.n;
        a = new T[n];
        s = other.s;
        f = other.f;
        cntElems = other.cntElems;
        for (int i = s; i != next(f); i = next(i)) {
            a[i] = other.a[i];
        }
    }

    TQueue& operator=(const TQueue& other) {
        if (this == &other) return *this;
        delete[] a;
        n = other.n;
        a = new T[n];
        s = other.s;
        f = other.f;
        cntElems = other.cntElems;
        for (int i = 0; i < n; i++) {
            a[i] = other.a[i];
        }
        return *this;
    }

    int size() {
        return cntElems;
    }

    bool isEmpty() {
        return cntElems == 0;
    }

    bool isFull() {
        return cntElems == n;
    }

    void push(const T& v) {
        if (isFull()) throw - 1;
        f = next(f);
        a[f] = v;
        cntElems++;
    }

    T pop() {
        if (isEmpty()) throw - 1;
        T res = a[s];
        s = next(s);
        cntElems--;
        return res;
    }
};

#endif