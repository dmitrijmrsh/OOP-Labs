#include <gtest/gtest.h>
#include "../header/Hex.hpp"

TEST(functions, test_01) {
    ASSERT_TRUE(HexCharToInt('f') == 15);
}

TEST(functions, test_02) {
    ASSERT_ANY_THROW(HexCharToInt('U'));
}

TEST(functions, test_03) {
    ASSERT_TRUE(IntToHexChar(11) == 'B');
}

TEST(functions, test_04) {
    ASSERT_ANY_THROW(IntToHexChar(154));
}

TEST(functions, test_05) {
    ASSERT_TRUE(IsHex('4'));
}

TEST(functions, test_06) {
    ASSERT_FALSE(IsHex('#'));
}

TEST(Hex_constructors, default_constructor) {
    Hex test;
    ASSERT_EQ(true, test.getsize() == 0);
}

TEST(Hex_constructors, uns_char_constructor_1) {
    Hex test(4, '1');
    ASSERT_EQ(test.getvalue(), "1111");
}

TEST(Hex_constructors, uns_char_constructor_2) {
    ASSERT_ANY_THROW(Hex(3, 'u'));
}

TEST(Hex_constructors, uns_char_constructor_3) {
    Hex test(0, '1');
    ASSERT_EQ(test.getvalue(), "");
}

TEST(Hex_constructors, uns_char_constructor_4) {
    Hex test(18, '0');
    ASSERT_EQ(test.getvalue(), "0");
}

TEST(Hex_constructors, init_list_constructor_1) {
    Hex test{'3', '2', '1'};
    ASSERT_EQ(test.getvalue(), "321");
}

TEST(Hex_constructors, init_list_constructor_2) {
    ASSERT_ANY_THROW(Hex({'3', '2', 'i'}));
}

TEST(Hex_constructors, init_list_constructor_3) {
    Hex test{};
    ASSERT_EQ(test.getvalue(), ""); 
}

TEST(Hex_constructors, init_list_constructor_4) {
    Hex test{'0', '0', '0', '1'};
    ASSERT_EQ(test.getvalue(), "1");
}

TEST(Hex_constructors, init_list_constructor_5) {
    Hex test{'0', '0', '0', '0'};
    ASSERT_EQ(test.getvalue(), "0");
}

TEST(Hex_constructors, string_constructor_1) {
    Hex test("34516782dfda");
    ASSERT_EQ(test.getvalue(), "34516782dfda");
}

TEST(Hex_constructors, string_constructor_2) {
    ASSERT_ANY_THROW(Hex("UUUUUiiiiooo"));
}

TEST(Hex_constructors, string_constructor_3) {
    Hex test("");
    ASSERT_EQ(test.getvalue(), "");
}

TEST(Hex_constructors, string_constructor_4) {
    Hex test("0000025f");
    ASSERT_EQ(test.getvalue(), "25f");
}

TEST(Hex_constructors, string_constructor_5) {
    Hex test("000000");
    ASSERT_EQ(test.getvalue(), "0");
}

TEST(Hex_constructors, lvalue_constructor_1) {
    Hex a("ffd21");
    Hex b(a);
    ASSERT_EQ(b.getvalue(), "ffd21");
}

TEST(Hex_constructors, rvalue_constructor_2) {
    Hex a("ffd21");
    Hex b(std::move(a));
    ASSERT_EQ(b.getvalue(), "ffd21");
}

TEST(Not_task_methods, getsize_1) {
    Hex a("aaa");
    ASSERT_EQ(a.getsize(), 3);
}

TEST(Not_task_methods, HexToDecimal_1) {
    Hex test("af123");
    ASSERT_EQ(test.HexToDecimal(), 717091);
}

TEST(Not_task_methods, HexToDecimal_2) {
    Hex test("fffffffa");
    ASSERT_EQ(test.HexToDecimal(), 4294967290);
}

TEST(Not_task_methods, getvalue_1) {
    Hex test{'0', '1', '2', '4', 'f', 'f'};
    ASSERT_EQ(test.getvalue(), "124ff");
}

TEST(Operators, lvalue_copy_1) {
    Hex a("123");
    Hex b;
    b = a;
    ASSERT_EQ(b.getvalue(), "123");
}

TEST(Operators, lvalue_copy_2) {
    Hex a("123");
    Hex b{};
    b = a;
    ASSERT_EQ(b.getvalue(), "123");
}

TEST(Operators, lvalue_copy_3) {
    Hex a("123");
    Hex b(0, '1');
    b = a;
    ASSERT_EQ(b.getvalue(), "123");
}

TEST(Operators, lvalue_copy_4) {
    Hex a("000123");
    Hex b("FFFFFaaaFFF");
    b = a;
    ASSERT_EQ(b.getvalue(), "123");
}

TEST(Operators, lvalue_copy_5) {
    Hex a;
    Hex b("fffaaadd");
    b = a;
    ASSERT_EQ(b.getvalue(), "");
}

TEST(Operators, rvalue_copy_1) {
    Hex a("000123");
    Hex b;
    b = std::move(a);
    ASSERT_TRUE((a.getvalue() == "") && (b.getvalue() == "123"));
}

TEST(Operators, rvalue_copy_2) {
    Hex a("123");
    Hex b{};
    b = std::move(a);
    ASSERT_TRUE((a.getvalue() == "") && (b.getvalue() == "123"));
}

TEST(Operators, rvalue_copy_3) {
    Hex a("123");
    Hex b(0, '1');
    b = std::move(a);
    ASSERT_TRUE((a.getvalue() == "") && (b.getvalue() == "123"));
}

TEST(Operators, rvalue_copy_4) {
    Hex a("123");
    Hex b("ffff45623");
    b = std::move(a);
    ASSERT_TRUE((a.getvalue() == "") && (b.getvalue() == "123"));
}

TEST(Operators, rvalue_copy_5) {
    Hex a;
    Hex b("f6f6f6f");
    b = std::move(a);
    ASSERT_TRUE((a.getvalue() == "") && (b.getvalue() == ""));
}

TEST(Operators, plus_eq_1) {
    Hex a;
    Hex b;
    a += b;
    ASSERT_EQ(a.getvalue(), "");
}

TEST(Operators, plus_eq_2) {
    Hex a{};
    Hex b("ff234");
    a += b;
    ASSERT_EQ(a.getvalue(), "FF234");
}

TEST(Operators, plus_eq_3) {
    Hex a;
    Hex b("ff234");
    b += a;
    ASSERT_EQ(b.getvalue(), "FF234");
}

TEST(Operators, plus_eq_4) {
    Hex a("fffddd4532");
    Hex b("000dddfa5678");
    a += b;
    ASSERT_EQ(a.getvalue(), "10DDBD79BAA");
}

TEST(Operators, plus_1) {
    Hex a("111");
    Hex b("0001");
    a = a + b;
    ASSERT_EQ(a.getvalue(), "112");
}

TEST(Operators, plus_2) {
    Hex a;
    Hex b;
    a = a + b;
    ASSERT_EQ(a.getvalue(), "");
}

TEST(Operators, plus_3) {
    Hex a{'1', '2', '3'};
    Hex b;
    a = a + b;
    ASSERT_EQ(a.getvalue(), "123");
}

TEST(Operators, plus_4) {
    Hex a("fffddd4532");
    Hex b("dddfa5678");
    a = a + b;
    ASSERT_EQ(a.getvalue(), "10DDBD79BAA");
}

TEST(Operators, minus_equal_1) {
    Hex a{};
    Hex b("12345");
    ASSERT_ANY_THROW(a -= b);
}

TEST(Operators, minus_equal_2) {
    Hex a("fffff1");
    Hex b{'2', '3', '4', '5'};
    a -= b;
    ASSERT_EQ(a.getvalue(), "FFDCAC");
}

TEST(Operators, minus_equal_3) {
    Hex a = {'1' ,'2', '3'};
    Hex b;
    a -= b;
    ASSERT_EQ(a.getvalue(), "123");
}

TEST(Operators, minus_equal_4) {
    Hex a{'0', '0', '0', '2', '3', '4', '5'};
    Hex b("000000fffff1");
    b -= a;
    ASSERT_EQ(b.getvalue(), "FFDCAC");
}

TEST(Operators, minus_equal_5) {
    Hex a;
    Hex b{};
    a -= b;
    ASSERT_EQ(a.getvalue(), "");
}

TEST(Operators, minus_equal_6) {
    Hex a("1000000");
    Hex b("999000");
    a -= b;
    ASSERT_EQ(a.getvalue(), "667000");
}

TEST(Operators, minus_1) {
    Hex a{};
    Hex b("12345");
    ASSERT_ANY_THROW(a - b);
}

TEST(Operators, minus_2) {
    Hex a("fffff1");
    Hex b{'2', '3', '4', '5'};
    a = a - b;
    ASSERT_EQ(a.getvalue(), "FFDCAC");
}

TEST(Operators, minus_3) {
    Hex a = {'1' ,'2', '3'};
    Hex b("000000000");
    a = a - b;
    ASSERT_EQ(a.getvalue(), "123");
}

TEST(Operators, minus_4) {
    Hex a{'0', '0', '0', '2', '3', '4', '5'};
    Hex b("000000fffff1");
    b = b - a;
    ASSERT_EQ(b.getvalue(), "FFDCAC");
}

TEST(Operators, minus_5) {
    Hex a("");
    Hex b(0, '1');
    a = a - b;
    ASSERT_EQ(a.getvalue(), "");
}

TEST(Operators, minus_6) {
    Hex a("0001000000");
    Hex b{'0', '0', '0', '9', '9', '9', '0', '0', '0'};
    a = a - b;
    ASSERT_EQ(a.getvalue(), "667000");
}

TEST(Operators, equality_1) {
    Hex a("12345667");
    Hex b{'1', '2', '3', '4', '5', '6', '6', '7'};
    ASSERT_TRUE(a == b);
}

TEST(Operators, equality_2) {
    Hex a("");
    Hex b;
    ASSERT_TRUE(b == a);
}

TEST(Operators, equality_3) {
    Hex a("0000000002431");
    Hex b{'0', '2', '4', '3', '1'};
    ASSERT_TRUE(a == b);
}

TEST(Operators, equality_4) {
    Hex a(1, '1');
    Hex b("123");
    ASSERT_FALSE(a == b);
}

TEST(Operators, inequality_1) {
    Hex a("12345667");
    Hex b{'1', '2', '3', '4', '5', '6', '6', '7'};
    ASSERT_FALSE(a != b);
}

TEST(Operators, inequality_2) {
    Hex a("");
    Hex b;
    ASSERT_FALSE(b != a);
}

TEST(Operators, inequality_3) {
    Hex a("0000000002431");
    Hex b{'0', '2', '4', '3', '1'};
    ASSERT_FALSE(a != b);
}

TEST(Operators, inequality_4) {
    Hex a("fffd");
    Hex b("123");
    ASSERT_TRUE(a != b);
}

TEST(Operators, less_1) {
    Hex a("fff");
    Hex b("111");
    ASSERT_TRUE(b < a);
}

TEST(Operators, less_2) {
    Hex a("");
    Hex b{'1', '2', '3'};
    ASSERT_TRUE(a < b);
}

TEST(Operators, less_3) {
    Hex a;
    Hex b("FFFFF");
    ASSERT_FALSE(b < a);
}

TEST(Operators, less_4) {
    Hex a("FFFFFFFF");
    Hex b("12345678");
    ASSERT_TRUE(b < a);
}

TEST(Operators, more_1) {
    Hex a("fff");
    Hex b("111");
    ASSERT_TRUE(a > b);
}

TEST(Operators, more_2) {
    Hex a("");
    Hex b{'1', '2', '3'};
    ASSERT_TRUE(b > a);
}

TEST(Operators, more_3) {
    Hex a;
    Hex b("FFFFF");
    ASSERT_FALSE(a > b);
}

TEST(Operators, more_4) {
    Hex a("FFFFFFFF");
    Hex b("12345678");
    ASSERT_TRUE(a > b);
}

TEST(Operators, more_or_equal_1) {
    Hex a("FFFFFFF");
    Hex b("000fffffff");
    ASSERT_TRUE((a >= b) && (b >= a));
}

TEST(Operators, more_or_equal_2) {
    Hex a("111111");
    Hex b("ffffff");
    ASSERT_TRUE(b >= a);
}

TEST(Operators, more_or_equal_3) {
    Hex a;
    Hex b{};
    ASSERT_TRUE((a >= b) && (b >= a));
}

TEST(Operators, more_or_equal_4) {
    Hex a;
    Hex b("111");
    ASSERT_TRUE(b >= a);
}

TEST(Operators, less_or_equal_1) {
    Hex a{};
    Hex b{'1', '1', '1'};
    ASSERT_TRUE(a <= b);
}

TEST(Operators, less_or_equal_2) {
    Hex a("fff");
    Hex b{'f', 'f', 'f'};
    ASSERT_TRUE((a <= b) && (b <= a));
}

TEST(Operators, less_or_equal_3) {
    Hex a("00fdfdfdfdfd");
    Hex b("1231231233");
    ASSERT_TRUE(a >= b);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}