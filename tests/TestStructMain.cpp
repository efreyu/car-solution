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

TEST(TestStructMain, TestStructTransformCollision) {
    sTransform transform1;
    ASSERT_TRUE( transform1.x == 0
                && transform1.y == 0
                && transform1.width == 0
                && transform1.height == 0
                );
    auto *transform2 = new sTransform(0, 0, 100, 100);
    ASSERT_TRUE( transform2->x == 0
                 && transform2->y == 0
                 && transform2->width == 100
                 && transform2->height == 100
    );
    sTransform *transform3 = new sTransform(50, 50, 100, 100);
    auto *transform4 = new sTransform(120, 120, 100, 100);
    ASSERT_TRUE(Collision::AABB(*transform2, *transform3));
    ASSERT_FALSE(Collision::AABB(*transform2, *transform4));
    ASSERT_TRUE(Collision::AABB(*transform3, *transform3));
}

