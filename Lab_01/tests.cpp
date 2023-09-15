#include <gtest/gtest.h>
#include "gcd.h"

TEST(test_01, basic_test_set) 
{
    ASSERT_TRUE(gcd(0,0)==0);
}

TEST(test_02, basic_test_set) 
{
    ASSERT_TRUE(gcd(30,18)==6);
}

TEST(test_03, basic_test_set) 
{
    ASSERT_TRUE(gcd(12, 8)==4);
}

TEST(test_04, basic_test_set) 
{
    ASSERT_TRUE(gcd(9,15)==3);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(gcd(8,8)==8);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}