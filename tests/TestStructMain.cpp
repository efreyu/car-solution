/* Created by efreyu on 22.05.2020. */
#include <gtest/gtest.h>
#include "../src/game.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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

