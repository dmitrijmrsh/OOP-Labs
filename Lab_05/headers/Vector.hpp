#pragma once

#include <initializer_list>
#include <vector>

#include "Allocator.hpp"
#include "Iterator.hpp"
#include "ConstIterator.hpp"


template<class T, class Allocator = std::allocator<T>>
class Vector {
    private:
        T* data;
        size_t _size;
        size_t capacity;
        Allocator alloc;

        void reallocate(size_t);
    public:
        Vector();
        Vector(size_t);
        Vector(size_t, const T&);
        Vector(const std::initializer_list<T>&);
        Vector(const Vector&);
        Vector(Vector&&);

        void push_back(const T&);
        void pop_back();
        void clear();
        void resize(size_t);

        size_t size();
        bool empty();

        Iterator<T, Vector<T, Allocator>> begin();
        ConstIterator<T, Vector<T,Allocator>> cbegin();
        Iterator<T, Vector<T, Allocator>> end();
        ConstIterator<T, Vector<T, Allocator>> cend();
        Iterator<T, Vector<T, Allocator>> erase(Iterator<T, Vector<T, Allocator>>);
        ConstIterator<T, Vector<T, Allocator>> erase(ConstIterator<T, Vector<T, Allocator>>);
        Iterator<T, Vector<T, Allocator>> insert(ConstIterator<T, Vector<T, Allocator>> pos, const T& value);

        T& operator [] (size_t) const;

        ~Vector() = default;
};

template<class T, class Allocator>
void Vector<T, Allocator>::reallocate(size_t newcapacity) {
    if (data == nullptr) {
        return;
    }
    T temp[_size];
    for (size_t i = 0; i < _size; ++i) {
        temp[i] = data[i];
    }

    for (size_t i = 0; i < _size; ++i) {
        alloc.destroy(&data[i]);
    }
    alloc.deallocate(data, _size);
    
    capacity = newcapacity;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        if (i < _size) {
            alloc.construct(&data[i], temp[i]);
            continue;
        }
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector() {
    _size = 0;
    capacity = 0;
    data = nullptr;
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size) {
    _size = size;
    capacity = _size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size, const T& value) {
    _size = size;
    capacity = _size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        alloc.construct(&data[i], value);
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const std::initializer_list<T>& list) {
    _size = list.size();
    capacity = _size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        if (i < _size) {
            alloc.construct(&data[i], *(list.begin() + i));
            continue;
        }
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& other) {
    _size = other._size;
    capacity = _size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        if (i < _size){
            alloc.construct(&data[i], other[i]);
            continue;
        }
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& other) {
    _size = other._size;
    capacity = _size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        if (i < _size) {
            alloc.construct(&data[i], other[i]);
            continue;
        }
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(const T& value) {
    ++_size;
    if (_size < capacity || _size == 1) {
        if (capacity == 0) {
            capacity = _size * 2;
            data = alloc.allocate(capacity);
            alloc.construct(&data[_size - 1], value);
            return;
        }
        data[_size - 1] = value;
        return;
    }
    this->reallocate(capacity * 2);
    data[_size - 1] = value;
}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
    if (_size == 0) {
        throw std::logic_error("Vector is empty");
    }
    --_size;
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear() {
    _size = 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_t newsize) {
    _size = newsize;
    if (newsize < capacity) {
        return;
    }
    capacity = _size * 2;
    if (data != nullptr) {
        this->reallocate(capacity);
        return;
    }
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i) {
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::size() {
    return _size;
}

template<class T, class Allocator>
bool Vector<T, Allocator>::empty() {
    return (_size == 0);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::begin() {
    return Iterator<T, Vector<T, Allocator>>(this, 0, _size);
}

template<class T, class Allocator>
ConstIterator<T, Vector<T, Allocator>> Vector<T, Allocator>::cbegin() {
    return ConstIterator<T, Vector<T, Allocator>>(this, 0, _size);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::end() {
    return Iterator<T, Vector<T, Allocator>>(this, _size, _size);
}

template<class T, class Allocator>
ConstIterator<T, Vector<T, Allocator>> Vector<T, Allocator>::cend() {
    return ConstIterator<T, Vector<T, Allocator>>(this, _size, _size);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::erase(Iterator<T, Vector<T, Allocator>> it) {
    if (it == this->end()) {
        return (this->end());
    }
    size_t index = 0;
    for (auto iter = this->begin(); iter != this->end(); ++iter) {
        if (iter == it) {
            break;
        }
        ++index;
    }
    for (size_t i = index + 1; i < _size; ++i) {
        data[i - 1] = data[i];
    }
    --_size;
    return (this->begin() + index);
}

template<class T, class Allocator>
ConstIterator<T, Vector<T, Allocator>> Vector<T, Allocator>::erase(ConstIterator<T, Vector<T, Allocator>> it) {
    if (it == this->cend()) {
        return (this->cend());
    }
    size_t index = 0;
    for (auto iter = this->cbegin(); iter != this->cend(); ++iter) {
        if (iter == it) {
            break;
        }
        ++index;
    }
    for (size_t i = index + 1; i < _size; ++i) {
        data[i - 1] = data[i];
    }
    --_size;
    return (this->cbegin() + index);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::insert(ConstIterator<T, Vector<T, Allocator>> pos, const T& value) {
    if (_size == 0) {
        this->push_back(value);
        return (this->begin());
    }
    if (_size + 1 == capacity) {
        this->reallocate(capacity * 2);
    }
    size_t index = 0;
    for (auto iter = this->cbegin(); iter != this->cend(); ++iter) {
        if (iter == pos) {
            break;
        }
        ++index;
    }
    for (size_t i = index; i < _size; ++i) {
        data[i + 1] = data[i];
    }
    data[index] = value;
    ++_size;
    return (this->begin() + index);
}

template<class T, class Allocator>
T& Vector<T, Allocator>::operator [] (size_t index) const {
    if (index >= _size) {
        throw std::invalid_argument("Bad index");
    }
    return data[index];
}