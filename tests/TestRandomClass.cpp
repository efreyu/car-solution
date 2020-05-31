/* Created by efreyu on 31.05.2020. */
#include <gtest/gtest.h>
#include "../src/Classes/Random.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace TestCarExample {
    class TestObject {
    public:
        int id;
        explicit TestObject(int id) : id(id) {};
    };
}

using TestCarExample::TestObject;

TEST(TestRandomClass, TestRandomBetween) {
    std::vector<int> row = {1, 2, 3};
    int number1 = Random::GenerateBetween(0, row.size() - 1);
    ASSERT_TRUE(number1 >= 0 && number1 <= row.size() - 1);
}

TEST(TestRandomClass, TestRandomObject) {
    std::vector<TestObject> testObject;
    testObject.reserve(20);
    for (int i = 0; i < 20; ++i) {
        testObject.emplace_back(TestObject(i));
    }
    std::vector<TestObject> compareObject;
    compareObject.reserve(20);
    for (int i = 0; i < 20; ++i) {
        auto n = Random::GetRandomVector<TestObject>(testObject);
        compareObject.emplace_back(Random::GetRandomVector<TestObject>(testObject));
        ASSERT_TRUE(n.id >= 0 && n.id <= 20 );
    }
}