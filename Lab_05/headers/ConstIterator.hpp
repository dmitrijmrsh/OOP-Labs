#pragma once

template<class ItemType, class ArrayType>
class ConstIterator {
    private:
        const ArrayType* array;
        size_t size;
        size_t index;
    public:
        ConstIterator() = default;
        ConstIterator(const ArrayType*, size_t, size_t);

        const ItemType& operator * ();

        bool operator == (const ConstIterator<ItemType, ArrayType>&) const;
        bool operator != (const ConstIterator<ItemType, ArrayType>&) const;

        ConstIterator<ItemType, ArrayType>& operator ++ ();
        ConstIterator<ItemType, ArrayType>& operator + (size_t);

        ~ConstIterator() = default;
};

template<class ItemType, class ArrayType>
ConstIterator<ItemType, ArrayType>::ConstIterator(const ArrayType* array, size_t index, size_t size) {
    this->array = array;
    this->index = index;
    this->size = size;
}

template<class ItemType, class ArrayType>
const ItemType& ConstIterator<ItemType, ArrayType>::operator * () {
    if (index >= size) {
        std::invalid_argument("Iterator is out of bounds");
    }
    return (*array)[index];
}

template<class ItemType, class ArrayType>
bool ConstIterator<ItemType, ArrayType>::operator == (const ConstIterator<ItemType, ArrayType>& other) const {
    return (index == other.index);
}

template<class ItemType, class ArrayType>
bool ConstIterator<ItemType, ArrayType>::operator != (const ConstIterator<ItemType, ArrayType>& other) const {
    return (index != other.index);
}

template<class ItemType, class ArrayType>
ConstIterator<ItemType, ArrayType>& ConstIterator<ItemType, ArrayType>::operator ++ () {
    ++index;
    if (index > size) {
        throw std::invalid_argument("You left the borders of vector");
    }
    return *this;
}

template<class ItemType, class ArrayType>
ConstIterator<ItemType, ArrayType>& ConstIterator<ItemType, ArrayType>::operator + (size_t n) {
    index += n;
    if (index > size) {
        throw std::invalid_argument("You left the borders of vetor");
    }
    return *this;
}