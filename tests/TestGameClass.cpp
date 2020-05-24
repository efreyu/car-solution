/* Created by efreyu on 23.05.2020. */
#include <gtest/gtest.h>
#include "../src/task.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int width = 1024;
int height = 768;

TEST(TestGameClass, TestGameClassInit) {
    Game *game = new Game();
    ASSERT_TRUE(game->isRunning());
}