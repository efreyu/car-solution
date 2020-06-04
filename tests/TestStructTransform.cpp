/* Created by efreyu on 22.05.2020. */
#include <gtest/gtest.h>
#include "../src/Classes/sTransform.h"
#include "../src/Classes/Collision.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace TestCarExample {
    class TestCollision : public Collision {
    public:
        static Point TestGetCenter(const sTransform &transform) {
            return GetCenter(transform);
        }
    };
}
using TestCarExample::TestCollision;

TEST(TestStructMain, TestTransformCollision) {
    /*
     * Testing constructors
     */
    sTransform transform1;
    ASSERT_TRUE( transform1.x == 0
                && transform1.y == 0
                && transform1.width == 0
                && transform1.height == 0
                && transform1.scale == 1
                );
    auto *transform2 = new sTransform(0, 0, 100, 100);
    ASSERT_TRUE( transform2->x == 0
                 && transform2->y == 0
                 && transform2->width == 100
                 && transform2->height == 100
                 && transform2->scale == 1
    );

    /*
     * Testing collision
     */
    sTransform *transform3 = new sTransform(50, 50, 100, 100);
    auto *transform4 = new sTransform(120, 120, 100, 100);
    ASSERT_TRUE(TestCollision::AABB(*transform2, *transform3));
    ASSERT_FALSE(TestCollision::AABB(*transform2, *transform4));
    ASSERT_TRUE(TestCollision::AABB(*transform3, *transform3));

    /*
     * Testing directions
     */
    EXPECT_EQ(transform3->direction, eDirection::DOWN);
}

TEST(TestStructMain, TestCollisionFindCenter) {
    /*
     * Test find center of rectangle
     */
    auto *transform1 = new sTransform(50, 50, 100, 100, eDirection::DOWN, 1, 45.0);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform1).x, transform1->x + transform1->width * transform1->scale / 2);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform1).y, transform1->y + transform1->height * transform1->scale / 2);
    auto *transform2 = new sTransform(150, 50, 100, 100, eDirection::DOWN, 1, 0.0);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform2).x, transform2->x + transform2->width * transform2->scale / 2);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform2).y, transform2->y + transform2->height * transform2->scale / 2);
}

//TEST(TestStructMain, TestCollisionFindPoints) {
//    /*
//     * Test find center of rectangle
//     */
//    auto *transform1 = new sTransform(50, 50, 100, 100, eDirection::DOWN, 1, 90);
//    EXPECT_EQ(TestCollision::TestGetCenter(*transform1).x, transform1->x + transform1->width * transform1->scale / 2);
//    EXPECT_EQ(TestCollision::TestGetCenter(*transform1).y, transform1->y + transform1->height * transform1->scale / 2);
//    auto *transform2 = new sTransform(150, 50, 100, 100, eDirection::DOWN, 1, 270);
//    EXPECT_EQ(TestCollision::TestGetCenter(*transform2).x, transform2->x + transform2->width * transform2->scale / 2);
//    EXPECT_EQ(TestCollision::TestGetCenter(*transform2).y, transform2->y + transform2->height * transform2->scale / 2);
//}

TEST(TestStructMain, TestStructTransformCollisionRotate) {
    /*
     * Test when one rotated rectangle overlapping
     */
    auto *transform1 = new sTransform(50, 50, 100, 100, eDirection::DOWN, 1, 45.0);
    auto *transform2 = new sTransform(150, 50, 100, 100, eDirection::DOWN, 1, 0.0);
    ASSERT_TRUE(TestCollision::AABB(*transform1, *transform2));
    /*
     * And not overlapping
     */
    auto *transform3 = new sTransform(200, 50, 100, 100, eDirection::DOWN, 1, 0.0);
    ASSERT_FALSE(TestCollision::AABB(*transform1, *transform3));
}
