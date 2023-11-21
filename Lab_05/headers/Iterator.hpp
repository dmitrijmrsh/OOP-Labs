#pragma once

template<class ItemType, class ArrayType>
class Iterator {
    private:
        ArrayType* array;
        size_t size;
        size_t index;
    public:
        Iterator() = default;
        Iterator(ArrayType*, size_t, size_t);

        ItemType& operator * ();

        bool operator == (const Iterator<ItemType, ArrayType>&) const;
        bool operator != (const Iterator<ItemType, ArrayType>&) const;

        Iterator<ItemType, ArrayType>& operator ++ ();
        Iterator<ItemType, ArrayType>& operator + (size_t);

        ~Iterator() = default;
};


template<class ItemType, class ArrayType>
Iterator<ItemType, ArrayType>::Iterator(ArrayType* array, size_t index, size_t size) {
    this->array = array;
    this->index = index;
    this->size = size;
}

template<class ItemType, class ArrayType>
ItemType& Iterator<ItemType, ArrayType>::operator * () {
    if (index >= size) {
        throw std::invalid_argument("Iterator is out of bounds");\
    }
    return (*array)[index];
}

template<class ItemType, class ArrayType>
bool Iterator<ItemType, ArrayType>::operator == (const Iterator<ItemType, ArrayType>& other) const {
    return (index == other.index);
}

template<class ItemType, class ArrayType>
bool Iterator<ItemType, ArrayType>::operator != (const Iterator<ItemType, ArrayType>& other) const {
    return (index != other.index);
}

template<class ItemType, class ArrayType>
Iterator<ItemType, ArrayType>& Iterator<ItemType, ArrayType>::operator ++ () {
    ++index;
    if (index > size) {
        throw std::invalid_argument("You left the borders of vector");
    }
    return *this;
}

template<class ItemType, class ArrayType>
Iterator<ItemType, ArrayType>& Iterator<ItemType, ArrayType>::operator + (size_t n) {
    index += n;
    if (index > size) {
        throw std::invalid_argument("You left the borders of vector");
    }
    return *this;
}
