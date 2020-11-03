#include "gtest/gtest.h"
#include <iostream>
#include "regular.h"

TEST(Test_regular, Test_1) {
    regular testing_1("ab+c.aba.*.bac.+.+*", "babc");
    EXPECT_EQ(testing_1.longest_common_suffix(), 2);
}

TEST(Test_regular, Test_2) {
regular testing_2("acb..bab.c.*.ab.ba.+.+*a.", "cbaa");
    EXPECT_EQ(testing_2.longest_common_suffix(), 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    std::getchar(); // keep console window open until Return keystroke
}