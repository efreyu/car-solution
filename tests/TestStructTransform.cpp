/* Created by efreyu on 22.05.2020. */
#include <gtest/gtest.h>
#include "../src/Classes/sTransform.h"
#include "../src/Classes/Collision.h"
#include "../src/Classes/GameObject.h"

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

TEST(TestStructMain, TestCollisionFindPoints) {
    /*
     * Test find center of rectangle
     */
    auto *transform1 = new sTransform(50, 50, 100, 100, eDirection::DOWN, 1, 90);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform1).x, transform1->x + transform1->width * transform1->scale / 2);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform1).y, transform1->y + transform1->height * transform1->scale / 2);
    auto *transform2 = new sTransform(150, 50, 100, 100, eDirection::DOWN, 1, 270);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform2).x, transform2->x + transform2->width * transform2->scale / 2);
    EXPECT_EQ(TestCollision::TestGetCenter(*transform2).y, transform2->y + transform2->height * transform2->scale / 2);
}

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

// Использовалось для проверки теории, проверки нименьшего расстояния для пересечения перекрестка
TEST(TestStructMain, TestStructTransformTwoPoints) {
    /*
     * Test distance between two point
     */
    auto *point1 = new Point(3,4);
    auto *point2 = new Point(7,7);
    auto *point3 = new Point(4,3);
    auto *point4 = new Point(112,7);
    EXPECT_EQ(TestCollision::PointDistance(*point1, *point2), 5);
    EXPECT_EQ(TestCollision::PointDistance(*point3, *point2), 5);
    EXPECT_EQ(TestCollision::PointDistance(*point2, *point4), 105);
    EXPECT_EQ(TestCollision::PointDistance(*point4, *point4), 0);

    /*
     * Test distance between two rect
     */
    auto *transform1 = new sTransform(50, 50, 100, 100);
    auto *transform2 = new sTransform(150, 50, 100, 100);
    auto *transform3 = new sTransform(155, 155, 50, 50);
    EXPECT_EQ(TestCollision::SquareDistance(*transform1, *transform2), 100);
    EXPECT_EQ((int)TestCollision::SquareDistance(*transform1, *transform3), 113);
    EXPECT_EQ((int)TestCollision::SquareDistance(*transform3, *transform2), 82);
    EXPECT_EQ(TestCollision::SquareDistance(*transform2, *transform2), 0);
}

// Использовалось для проверки теории, проверки нименьшего расстояния для пересечения перекрестка
TEST(TestStructMain, TestStructTransformSquareDistances) {
    /*
     * Test square distances
     */
    auto *gameObject1 = new GameObject(1, sTransform(50, 50, 100, 100));
    auto *gameObject2 = new GameObject(2, sTransform(150, 50, 100, 100));
    auto *gameObject3 = new GameObject(3, sTransform(155, 155, 50, 50));
    auto *gameObject4 = new GameObject(4, sTransform(275, 145, 50, 50));
    auto *square = new sTransform(0,0,50,50);

    std::vector<GameObject> array = {*gameObject1, *gameObject2, *gameObject3, *gameObject4};

    EXPECT_EQ(TestCollision::MinObjectDistance(array, *square), 1);

    array.erase(array.cbegin(), array.cbegin() + 1);
    array.emplace_back(GameObject(6, sTransform(550, 550, 100, 100)));

    EXPECT_EQ(TestCollision::MinObjectDistance(array, *square), 2);


}
