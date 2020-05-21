/* Created by efreyu on 22.05.2020. */
#include <gtest/gtest.h>
#include "../src/game.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestStructMain, TestStructPos) {
    sPos position1;
    EXPECT_EQ(position1.x, 0);
    EXPECT_EQ(position1.y, 0);
    sPos *position2;
    position2 = new sPos(5, 5);
    EXPECT_EQ(position2->x, 5);
    EXPECT_EQ(position2->y, 5);
}

TEST(TestStructMain, TestStructSize) {
    sSize size1;
    EXPECT_EQ(size1.width, 0);
    EXPECT_EQ(size1.height, 0);
    sSize *size2;
    size2 = new sSize(100, 150);
    EXPECT_EQ(size2->width, 100);
    EXPECT_EQ(size2->height, 150);
}


