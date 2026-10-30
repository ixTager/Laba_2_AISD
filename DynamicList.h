#pragma once
#include <iostream>

template <typename T>
class DynamicList {
private:
    T* arr;
    int capacity;
    int length;

    void updateSize() {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newArray = new T[newCapacity];

        for (int i = 0; i < length; i++) {
            newArray[i] = arr[i];
        }

        delete[] arr;
        arr = newArray;
        capacity = newCapacity;
    }

public:
    DynamicList() {
        this->capacity = 16;
        this->length = 0;
        this->arr = new T[this->capacity];
    }

    DynamicList(int size) {
        if (size <= 0) {
            this->capacity = 16;
        }
        else {
            this->capacity = size;
        }
        this->length = 0;
        this->arr = new T[this->capacity];
    }

    ~DynamicList() {
        delete[] arr;
    }

    T get(int index) const {
        if (index < 0 || index >= length) {
            return T();
        }
        return arr[index];
    }

    int size() const {
        return length;
    }

    int getIndexByVal(const T& val) const {
        for (int i = 0; i < length; i++) {
            if (arr[i] == val) return i;
        }
        return -1;
    }

    void add(int index, const T& val) {
        if (index < 0 || index > length) return;

        if (length >= capacity) {
            updateSize();
        }

        for (int i = length; i > index; i--) {
            arr[i] = arr[i - 1];
        }

        arr[index] = val;
        length++;
    }

    void remove(int index) {
        if (index < 0 || index >= length) return;

        for (int i = index; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }

        length--;
    }
};