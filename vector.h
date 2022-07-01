#pragma once

template <typename T>
class vector
{
public:
    vector() {
        arr = new T[1];
        Capacity = 1;
        Size = 0;
    }
    T& operator[](int index) {
        return arr[index];
    }
    T const& operator[](int index)const {
        return arr[index];
    }
    void push_back(const T& data) {
        if (Size == Capacity) {
            T* temp = new T[Capacity * 2];
            for (int i = 0; i != Capacity; i++) {
                temp[i] = arr[i];
            }
            delete arr;
            Capacity *= 2;
            arr = temp;
        }
        arr[Size] = data;
        Size++;
    }
    T& pop_back() {
        Size--;
        return arr[Size];
    }

    int size() {
        return Size;
    }
    int capacity() {
        return Capacity;
    }
    void clear() {
        delete arr;
        arr = new T[1];
        Size = 0;
        Capacity = 1;
    }
    ~vector() {
        delete arr;
    }
private:
    T* arr;
    int Capacity;
    int Size;
};

