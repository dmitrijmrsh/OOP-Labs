#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <exception>
#include <math.h>

int HexCharToInt(unsigned char value);
char IntToHexChar(int value);
bool IsHex(unsigned char value);

class Hex {
    private:
        size_t size;
        size_t capacity;
        unsigned char* digits;

        //Приватный метод реаллокации массива
        void reallocate(const size_t& newcapacity);
    public:
        //Конструкторы
        Hex();
        Hex(const size_t& n, unsigned char t);
        Hex(const std::initializer_list<unsigned char>& t);
        Hex(const std::string& t);
        Hex(const Hex& other);
        Hex(Hex&& other) noexcept;

        //Дополнительные методы
        size_t getsize();
        size_t HexToDecimal();
        std::string getvalue();

        //Деструктор
        virtual ~Hex() noexcept;

        //Оператор сдвига
        friend std::ostream& operator << (std::ostream& out, Hex& obj);

        //Арифметические операции
        Hex& operator = (const Hex&);
        Hex& operator = (Hex&&);
        Hex& operator += (const Hex&);
        Hex& operator -= (Hex&);
        Hex operator + (const Hex&);
        Hex operator - (Hex&);

        //Логические операторы
        bool operator == (Hex&);
        bool operator != (Hex&);
        bool operator < (Hex&);
        bool operator <= (Hex&);
        bool operator > (Hex&);
        bool operator >= (Hex&);
};