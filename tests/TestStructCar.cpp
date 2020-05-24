/* Created by efreyu on 22.05.2020. */
#include <gtest/gtest.h>
#include "../src/task.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int fuel = 5;
int speed = 5;
int minSpeed = 1;

TEST(TestStructCar, TestStructGasEngine) {
    /*
     * Gas Engine Car, fuel and speed test
     */
    sGasEngine car1;
    ASSERT_TRUE(car1.getFuel() == 0);
    car1.refill(fuel);
    ASSERT_TRUE(car1.getFuel() == fuel);
    car1.move();
    ASSERT_TRUE(car1.getFuel() == fuel - 1);
    car1.setSpeed(speed);
    ASSERT_TRUE(car1.getSpeed() == speed);
}

TEST(TestStructCar, TestStructElectroCar) {
    /*
     * Electro Car, fuel and speed test
     */
    sElectroCar car2;
    ASSERT_TRUE(car2.getFuel() == 0);
    car2.refill(fuel);
    ASSERT_TRUE(car2.getFuel() == fuel);
    car2.move();
    ASSERT_TRUE(car2.getFuel() == fuel - 1);
    car2.setSpeed(speed - 2);
    ASSERT_TRUE(car2.getSpeed() == speed - 2);
}

TEST(TestStructCar, TestStructHybridCar) {
    /*
     * Hybrid Car, fuel and speed test
     */
    sHybridCar car3;
    ASSERT_TRUE(car3.getFuel() == 0);
    car3.refill(fuel);
    ASSERT_TRUE(car3.getFuel() == fuel / 2 + fuel / 2);
    car3.move();
    ASSERT_TRUE(car3.getFuel() == fuel / 2 + fuel / 2 - 1);
    car3.setSpeed(speed - 2);
    ASSERT_TRUE(car3.getSpeed() == speed - 2);
}

TEST(TestStructCar, TestStructCarConstruct) {
    /*
     * Constructor test, set and get speed test
     */
    sGasEngine *gasCar = new sGasEngine();
    sElectroCar *electroCar = new sElectroCar();
    sHybridCar *hybridCar = new sHybridCar();

    ASSERT_TRUE(gasCar->getSpeed() == minSpeed);
    ASSERT_TRUE(electroCar->getSpeed() == minSpeed);
    ASSERT_TRUE(hybridCar->getSpeed() == minSpeed);

    gasCar->setSpeed(2);
    gasCar->refill(fuel);
    ASSERT_TRUE(gasCar->getSpeed() == 2);
    ASSERT_TRUE(electroCar->getSpeed() == minSpeed);
    ASSERT_TRUE(hybridCar->getSpeed() == minSpeed);

    electroCar->setSpeed(3);
    electroCar->refill(5);
    ASSERT_TRUE(gasCar->getSpeed() == 2);
    ASSERT_TRUE(electroCar->getSpeed() == 3);
    ASSERT_TRUE(hybridCar->getSpeed() == minSpeed);

    hybridCar->setSpeed(4);
    hybridCar->refill(fuel);
    ASSERT_TRUE(gasCar->getSpeed() == 2);
    ASSERT_TRUE(electroCar->getSpeed() == 3);
    ASSERT_TRUE(hybridCar->getSpeed() == 4);
}

TEST(TestStructCar, TestStructCarMove) {
    /*
     * Test move method and fuel burn with direction and transform
     */
    sTransform *transform = new sTransform(50, 50, 100, 100);
    sHybridCar *hybridCar = new sHybridCar();
    hybridCar->setSpeed(speed);
    hybridCar->transform = *transform;
    hybridCar->transform.direction = eDirection::DOWN;
    hybridCar->move();
    hybridCar->transform.direction = eDirection::RIGHT;
    hybridCar->move();
    ASSERT_TRUE(hybridCar->transform.y == transform->y - minSpeed);
    ASSERT_TRUE(hybridCar->transform.x == transform->x + minSpeed);

    sGasEngine *gasEngineCar = new sGasEngine();
    gasEngineCar->setSpeed(speed);
    gasEngineCar->transform = *transform;
    gasEngineCar->transform.direction = eDirection::UP;
    gasEngineCar->move();
    gasEngineCar->transform.direction = eDirection::LEFT;
    gasEngineCar->move();
    ASSERT_TRUE(gasEngineCar->transform.y == transform->y + minSpeed);
    ASSERT_TRUE(gasEngineCar->transform.x == transform->x - minSpeed);
    //TODO test getFuel and fuelBurn
//    EXPECT_EQ(hybridCar->getFuel(), -1);
}