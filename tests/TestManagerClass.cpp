/* Created by efreyu on 23.05.2020. */
#include <gtest/gtest.h>
#include "../src/task.hpp"
#include "../src/Classes/Game.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(TestGameClass, TestGameClassInit) {
    Game *game = new Game();
    ASSERT_FALSE(game->isRunning());
}

TEST(TestManagerClass, TestAddCarType) {
//    std::vector<const char*> array = {"1","2"};
//    for (auto &v : array) {
//        EXPECT_EQ(v, "2");
//    }
//    Manager manager;
//    manager.addCarType<GasEngineCreator>((std::vector<const char*>){
//        "resources/sprites/Gas/grey.png",
//        "resources/sprites/Gas/red.png",
//        "resources/sprites/Gas/white.png"
//    });

}