#pragma once
#include "DynamicArray.h"

template <typename T>
class Stack {
private:
    DynamicArray<T> array;

public:
    Stack() {}

    T get(int index) {
        return array.get(index);
    }

    void set(int index, T& val) {
        array.set(index, val);
    }

    void remove(int index) {
        array.remove(index);
    }

    void push(const T& val) {
        array.add(array.size(), val);
    }

    void pop() {
        if (isEmpty()) return;

        array.remove(array.size() - 1);
    }

    T top() const {
        if (isEmpty()) return T();

        return array.get(array.size() - 1);
    }

    bool isEmpty() const {
        return array.size() == 0;
    }

    int size() const {
        return array.size();
    }


};