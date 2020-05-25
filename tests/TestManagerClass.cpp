/* Created by efreyu on 23.05.2020. */
#include <gtest/gtest.h>
#include "../src/task.hpp"
#include "../src/Classes/Game.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestManagerClass : public Manager {
public:
    int getCountRegisteredCar() {
        return this->carTypes.size();
    }
};


TEST(TestGameClass, TestGameClassInit) {
    Game *game = new Game();
    ASSERT_FALSE(game->isRunning());
}

TEST(TestManagerClass, TestAddCarType) {
    TestManagerClass manager1;
    std::vector<std::string> textures = {
            "resources/sprites/Gas/grey.png",
            "resources/sprites/Gas/red.png",
            "resources/sprites/Gas/white.png"
    };
    manager1.RegisterCarType<GasEngineCreator>(textures);
    ASSERT_TRUE(manager1.getCountRegisteredCar() == 1);

    manager1.RegisterCarType<ElectroCarCreator>((std::vector<std::string>){
            "resources/sprites/Electro/black.png",
            "resources/sprites/Electro/blue.png",
            "resources/sprites/Electro/red.png",
            "resources/sprites/Electro/yellow.png"
    });
    ASSERT_TRUE(manager1.getCountRegisteredCar() == 2);

    manager1.RegisterCarType<HybridCarCreator>((std::vector<std::string>){
            "resources/sprites/Hybrid/black.png",
            "resources/sprites/Hybrid/gray.png",
            "resources/sprites/Hybrid/while.png"
    });
    ASSERT_TRUE(manager1.getCountRegisteredCar() == 3);


}