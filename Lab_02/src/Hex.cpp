#include "../header/Hex.hpp"

int HexCharToInt(unsigned char value) {
    if (value >= '0' && value <= '9') {
        return value - '0';
    } else if (value >= 'A' && value <= 'F') {
        return value - 'A' + 10;
    } else if (value >= 'a' && value <= 'f') {
        return value - 'a' + 10;
    }
    throw std::logic_error("Not a hex symbol");
}

char IntToHexChar(int value) {
    if (value >= 0 && value <= 9) {
        return '0' + value;
    } else if (value >= 10 && value <= 15) {
        return 'A' + value - 10;
    }
    throw std::logic_error("Bad int number");
}

bool IsHex(unsigned char value) {
    if (!((value >= '0' && value <= '9') || (value >= 'A' && value <= 'F') || (value >= 'a' && value <= 'f'))) {
        return false;
    }
    return true;
}

Hex::Hex() : size(0), capacity(0), digits{nullptr} {}

Hex::Hex(const size_t& n, unsigned char t) {
    size = n;
    capacity = size * 2;
    digits = new unsigned char[capacity];
    if (!IsHex(t)) {
        delete[] digits;
        digits = nullptr;
        size = 0;
        capacity = 0;
        throw std::logic_error("This digit doesn't belong to hex system");
    }
    for (size_t i = 0; i < size; ++i) {
        if (t == '0' && size > 0) {
            digits[0] = '0';
            size = 1;
            break; 
        }
        digits[i] = t;
    }
}

Hex::Hex(const std::initializer_list<unsigned char>& t) {
    size = t.size();
    capacity = size * 2;
    digits = new unsigned char[capacity];
    size_t i = size - 1;
    size_t insignificantzerocount = 0;
    bool goodzero = false;
    for (const auto& elem : t) {
        if (!IsHex(elem)) {
            delete[] digits;
            digits = nullptr;
            size = 0;
            capacity = 0;
            throw std::logic_error("This digit doesn't belong to hex system");
        }
        if (!goodzero && size != 1 && elem == '0' && i != 0) {
            ++insignificantzerocount;
            --i;
            continue;
        }
        goodzero = true;
        digits[i] = elem;
        --i;
    }
    size = t.size() - insignificantzerocount;
}

Hex::Hex(const std::string& t) {
    size = t.size();
    capacity = size * 2;
    digits = new unsigned char[capacity];
    size_t i = size - 1;
    size_t insignificantzerocount = 0;
    bool goodzero = false;
    for (const auto& elem : t) {
        if (!IsHex(elem)) {
            delete[] digits;
            digits = nullptr;
            size = 0;
            capacity = 0;
            throw std::logic_error("This digit doesn't belong to hex system");
        }
        if (!goodzero && size != 1 && elem == '0' && i != 0) {
            ++insignificantzerocount;
            --i;
            continue;
        }
        goodzero = true;
        digits[i] = elem;
        --i;
    }
    size = t.size() - insignificantzerocount;
}

Hex::Hex(const Hex& other) {
    size = other.size;
    capacity = other.capacity;
    digits = new unsigned char[capacity];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}

Hex::Hex(Hex&& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    digits = other.digits;
    other.size = 0;
    other.capacity = 0;
    other.digits = nullptr;
}

void Hex::reallocate(const size_t& newcapacity) {
    unsigned char* newArray  = new unsigned char[newcapacity];
    capacity = newcapacity;
    for (size_t i = 0; i < size; ++i) {
        newArray[i] = digits[i];
    }
    delete[] digits;
    digits = newArray;
}

size_t Hex::getsize() const {
    return size;
}

Hex::~Hex() noexcept {
    if (capacity != 0) {
        delete[] digits;
        digits = nullptr;
    }
    size = 0;
    capacity = 0;
}

size_t Hex::HexToDecimal() const {
    size_t temp = 0;
    size_t ans = 0;
    for (size_t i = 0; i < size; ++i) {
        ans = ans + HexCharToInt(digits[i]) * pow(16, temp);
        ++temp;
    }
    return ans;   
}

std::string Hex::getvalue() const {
    std::string ans(size, '\0');
    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != '\0')
            ans[size - i - 1] = static_cast<char>(digits[i]);
    }
    return ans;
}

std::ostream& operator << (std::ostream& out, Hex& obj) {
    for (int i = obj.size - 1; i >= 0; --i) {
        out << obj.digits[i];
    }
    return out;
}

Hex& Hex::operator = (const Hex& other) {
    if (this != &other) {
        if (capacity < other.capacity) {
            reallocate(other.capacity);
        }
        size = other.size;

        for (size_t i = 0; i < size; ++i) {
            digits[i] = other.digits[i];
        }
    }
    return *this;
}

Hex& Hex::operator = (Hex&& other) {
    if (this != &other) {
        size = other.size;
        capacity = other.capacity;
        delete[] digits;
        digits = other.digits;

        other.digits = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

Hex& Hex::operator += (const Hex& other) {
    if (capacity < other.capacity) {
        reallocate(other.capacity);
    }

    std::string result = "";
    int carry = 0;
    int i = 0;
    int j = 0;

    while (i < size || j < other.size || carry != 0) {
        int sum = carry;

        if (i < size) {
            sum += HexCharToInt(digits[i]);
            ++i;
        }

        if (j < other.size) {
            sum += HexCharToInt(other.digits[j]);
            ++j;
        }

        carry = sum / 16;
        sum %= 16;

        result = IntToHexChar(sum) + result;
    }

    size = result.size();
    
    for (size_t i = 0; i < result.size(); ++i) {
        digits[size - 1 - i] = result[i];
    }

    return *this;
}

Hex Hex::operator + (const Hex& other) const {
    Hex ans = *this;
    ans += other;
    return ans;
}

Hex& Hex::operator -= (const Hex& other) {
    if (size < other.size) {
        throw std::logic_error("The size of left value is less than size of right value");
    }
    
    if (other.size == 0) {
        return *this;
    }

    std::string result = "";
    int borrow = 0;

    int i = 0;
    int j = 0;

    while (i < size || j < other.size) {
        int digit1 = (i < size) ? HexCharToInt(digits[i]) : 0;
        int digit2 = (j < other.size) ? HexCharToInt(other.digits[j]) : 0;

        digit1 -= borrow;

        if (digit1 < digit2) {
            digit1 += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }

        int difference = digit1 - digit2;

        result = result + IntToHexChar(difference);

        ++i;
        ++j;
    }

    bool goodzero = false;
    for (int i = result.size() - 1; i >= 0 && result.size() != 1; --i) {
        if (result[i] == '0' && !goodzero && i != 0) {
            result.erase(result.begin() + i);
            continue;
        }
        goodzero = true;
    }

    size = result.size();

    for(size_t i = 0; i < result.size(); ++i) {
        digits[i] = result[i];
    }

    return *this;
}

Hex Hex::operator - (const Hex& other) const {
    Hex ans = *this;
    ans -= other;
    return ans;
}

bool Hex::operator == (const Hex& other) const {
    size_t left = HexToDecimal();
    size_t right = other.HexToDecimal();
    if (left == right) {
        return true;
    }
    return false;
}

bool Hex::operator != (const Hex& other) const {
    return !(*this == other);
}

bool Hex::operator < (const Hex& other) const {
    size_t left = HexToDecimal();
    size_t right = other.HexToDecimal();

    if (left < right) {
        return true;
    }

    return false;
}

bool Hex::operator >= (const Hex& other) const {
    return !(*this < other);
}

bool Hex::operator > (const Hex& other) const {
    return (*this >= other) && (*this != other);
}

bool Hex::operator <= (const Hex &other) const {
    return !(*this > other);
}