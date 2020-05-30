/* Created by efreyu on 23.05.2020. */
#include <gtest/gtest.h>
#include "../src/Classes/Game.h"
#include "../src/Classes/Manager.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace TestCarExample {

    class TestManagerClass : public Manager {
    public:
        int getCountRegisteredCar() {
            return this->carTypes.size();
        }
        int getCountSpawnedCar() {
            return this->gameObjects.size();
        }
    };

    class TestGasEngineCreator : public GasEngineCreator {
    public:
        int getCountRegisteredTextures() {
            return mTextures.size();
        }
    };

    class TestElectroCarCreator : public ElectroCarCreator {
    public:
        int getCountRegisteredTextures() {
            return mTextures.size();
        }
    };

    class TestHybridCarCreator : public HybridCarCreator {
    public:
        int getCountRegisteredTextures() {
            return mTextures.size();
        }
    };

    std::vector<std::string> gasEngineTextures = {
            "resources/sprites/Gas/grey.png",
            "resources/sprites/Gas/red.png",
            "resources/sprites/Gas/white.png"
    };

    std::vector<std::string> electroCarTextures = {
            "resources/sprites/Electro/black.png",
            "resources/sprites/Electro/blue.png",
            "resources/sprites/Electro/red.png",
            "resources/sprites/Electro/yellow.png"
    };

    std::vector<std::string> hybridCarTextures = {
            "resources/sprites/Hybrid/black.png",
            "resources/sprites/Hybrid/gray.png",
            "resources/sprites/Hybrid/while.png"
    };

    class TestGameClass : public Game {
    public:
        void SetupWindowResolution(int width, int height) {
            mWidth = width;
            mHeight = height;
        }
    };

}


TEST(TestGameClass, TestGameClassInit) {
    auto game = new TestCarExample::TestGameClass();
    ASSERT_FALSE(game->isRunning());
    game->SetupWindowResolution(100, 150);
    auto [ width, height, scale ] = TestCarExample::TestGameClass::GetWindowResolution();
    ASSERT_TRUE(width == 100 && height == 150);
}

TEST(TestManagerClass, TestAddCarType) {
    /**
     * Register car types
     */
    TestCarExample::TestManagerClass manager1;

    ASSERT_TRUE(manager1.getCountSpawnedCar() == 0);

    manager1.RegisterCarType<GasEngineCreator>(TestCarExample::gasEngineTextures);
    ASSERT_TRUE(manager1.getCountRegisteredCar() == 1);

    manager1.RegisterCarType<ElectroCarCreator>(TestCarExample::electroCarTextures);
    ASSERT_TRUE(manager1.getCountRegisteredCar() == 2);

    manager1.RegisterCarType<HybridCarCreator>(TestCarExample::hybridCarTextures);
    ASSERT_TRUE(manager1.getCountRegisteredCar() == 3);

    /**
     * Spawn cars
     */
     ASSERT_TRUE(manager1.getCountSpawnedCar() == 0);
     manager1.SpawnCar();
     ASSERT_TRUE(manager1.getCountSpawnedCar() == 1);

     manager1.SpawnCar(2);
     ASSERT_TRUE(manager1.getCountSpawnedCar() == 3);
}

TEST(TestManagerClass, TestFactoryClass) {
    auto *gasEngineCar = new TestCarExample::TestGasEngineCreator();
    gasEngineCar->SetTextures(TestCarExample::gasEngineTextures);
    EXPECT_EQ(gasEngineCar->getCountRegisteredTextures(),
              TestCarExample::gasEngineTextures.size());

    auto *electroCar = new TestCarExample::TestElectroCarCreator();
    electroCar->SetTextures(TestCarExample::electroCarTextures);
    EXPECT_EQ(electroCar->getCountRegisteredTextures(),
              TestCarExample::electroCarTextures.size());

    auto *hybridCar = new TestCarExample::TestHybridCarCreator();
    hybridCar->SetTextures(TestCarExample::hybridCarTextures);
    EXPECT_EQ(hybridCar->getCountRegisteredTextures(),
              TestCarExample::hybridCarTextures.size());

    // Get GameObject class instance
    GameObject *car1 = gasEngineCar->GetObject();

    ASSERT_FALSE(car1->isActive);
    ASSERT_FALSE(car1->isDestroyed);

}