/* Created by efreyu on 29.05.2020. */
#include <gtest/gtest.h>
#include "../src/Classes/Game.h"
#include "../src/Classes/GameObject.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace TestCarExample {

    class TestGameObjectClass : public GameObject {};

}

using TestCarExample::TestGameObjectClass;

TEST(TestGameObjectClass, TestGameObjectClassInit) {
    //Simple get game object class instance
    GameObject *car1 = new TestGameObjectClass();

    ASSERT_FALSE(car1->isActive);
    ASSERT_FALSE(car1->isDestroyed);
    car1->LoadTexture("resources/sprites/Hybrid/black.png");
    SDL_DestroyTexture(car1->texture);
    ASSERT_FALSE(car1->texture);
}
