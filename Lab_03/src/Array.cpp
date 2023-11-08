#include "../headers/Array.hpp"

void Array::reallocate(size_t newcapacity) {
    if (arr == nullptr) {
        return;
    }
    Figure** temp = new Figure*[size];
    memcpy(temp, arr, size*sizeof(Figure*));

    delete[] arr;
    arr = new Figure*[newcapacity];
    memcpy(arr, temp, size*sizeof(Figure*));
    capacity = newcapacity;
}

Array::Array() {
    size = 0;
    capacity = 2;
    arr = new Figure*[capacity];
}

Array::Array(size_t _size) {
    size = _size;
    if (size > 0) {
        capacity = size * 2;
    } else {
        capacity = 2;
    }
    arr = new Figure*[capacity];
}

void Array::push_back(Figure* elem) {
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

void Array::pop_back() {
    if (size == 0) {
        return;
    }
    size--;
}

void Array::erase(size_t index) {
    if (index >= size) {
        return;
    }
    for (size_t i = index + 1; i < size; ++i) {
        arr[i - 1] = arr[i];
    }
    size--;
}

Figure* Array::operator [] (size_t index) {
    if (index >= size) {
        throw std::logic_error("Bad index");
    }
    return arr[index];
}

Point Array::FigureCenter(size_t index) {
    if (index >= size) {
        throw std::logic_error("Bad index");
    }
    return arr[index]->Center();
}

double Array::FigureArea(size_t index) {
    if (index >= size) {
        throw std::logic_error("Bad index");
    }
    return arr[index]->Area();
}

double Array::CommonArea() {
    double sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += arr[i]->Area();
    }
    return sum;
}

std::ostream& operator << (std::ostream& out, Array& arr) {
    Point center;
    double area;
    for (size_t i = 0; i < arr.getsize(); ++i) {
        out << arr[i]->getname() << " ";
        center = arr.FigureCenter(i);
        std::cout << "center: " << center << " ";
        area = arr.FigureArea(i);
        std::cout << "area: " << area << '\n';
    }
    return out;
}

size_t Array::getsize() {
    return size;
}

size_t Array::getcapacity() {
    return capacity;
}

Array::~Array() {
    size = 0;
    capacity = 0;
    delete[] arr;
    arr = nullptr;
}