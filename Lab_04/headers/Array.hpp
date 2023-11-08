#include "Figure.hpp"
#include <memory>

template<typename T>
class Array {
    private:
        size_t size;
        size_t capacity;
        std::shared_ptr<T[]> arr;

        void reallocate(size_t);
    public:
        Array();
        Array(size_t);

        void push_back(const T&);
        void pop_back();
        void erase(size_t);
        T operator[] (size_t);
        size_t getsize();
        size_t getcapacity();

        ~Array() = default;
};

template<typename T>
void Array<T>::reallocate(size_t newcapacity) {
    if (arr == nullptr) {
        return;
    }
    std::shared_ptr<T[]> newArr;
    newArr = std::shared_ptr<T[]>(new T[newcapacity]);
    for (size_t i = 0; i < this->getsize(); ++i) {
        newArr[i] = arr[i];
    }
    capacity = newcapacity;
    arr = newArr;
}

template<typename T>
Array<T>::Array() {
    size = 0;
    capacity = 2;
    arr = std::shared_ptr<T[]>(new T[capacity]);
}

template<typename T>
Array<T>::Array(size_t _size) {
    size = _size;
    if (size > 0) {
        capacity = size * 2;
    } else {
        capacity = 2;
    }
    arr = std::shared_ptr<T[]>(new T[capacity]);
}

template<typename T>
void Array<T>::push_back(const T& elem) {
    if (size < capacity) {
        if (size == 0) {
            arr[size] = elem;
            size = 1;
            return;
        }
        arr[size++] = elem;
        return;
    }
    this->reallocate(capacity * 2);
    arr[size++] = elem;
}

template<typename T>
void Array<T>::pop_back() {
    if (size == 0) {
        return;
    }
    size--;
}

template<typename T>
void Array<T>::erase(size_t index) {
    if (index >= size) {
        return;
    }
    for (size_t i = index + 1; i < size; ++i) {
        arr[i - 1] = arr[i];
    }
    size--;
}

template<typename T>
T Array<T>::operator [] (size_t index) {
    if (index >= size) {
        throw std::logic_error("Bad index");
    }
    return arr[index];
}

template<typename T>
size_t Array<T>::getsize() {
    return size;
}

template<typename T>
size_t Array<T>::getcapacity() {
    return capacity;
}