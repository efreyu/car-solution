/* Created by efreyu on 22.05.2020. */
#include <gtest/gtest.h>
#include "../src/game.hpp"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int refull = 5;
int speed = 5;

TEST(TestStructCar, TestStructGasEngine) {
    /*
     * Gas Engine Car
     */
    sGasEngine car1;
    ASSERT_TRUE(car1.getFuel() == 0);
    car1.refill(refull);
    ASSERT_TRUE(car1.getFuel() == refull);
    car1.move();
    ASSERT_TRUE(car1.getFuel() == refull - 1);
    car1.setSpeed(speed);
    ASSERT_TRUE(car1.getSpeed() == speed);
}

TEST(TestStructCar, TestStructElectroCar) {
    /*
     * Electro Car
     */
    sElectroCar car2;
    ASSERT_TRUE(car2.getFuel() == 0);
    car2.refill(refull);
    ASSERT_TRUE(car2.getFuel() == refull);
    car2.move();
    ASSERT_TRUE(car2.getFuel() == refull - 1);
    car2.setSpeed(speed - 2);
    ASSERT_TRUE(car2.getSpeed() == speed - 2);
}

TEST(TestStructCar, TestStructHybridCar) {
    /*
     * Hybrid Car
     */
    sHybridCar car3;
    ASSERT_TRUE(car3.getFuel() == 0);
    car3.refill(refull);
    ASSERT_TRUE(car3.getFuel() == refull / 2 + refull / 2);
    car3.move();
    ASSERT_TRUE(car3.getFuel() == refull / 2 + refull / 2 - 1);
    car3.setSpeed(speed - 2);
    ASSERT_TRUE(car3.getSpeed() == speed - 2);
}

TEST(TestStructCar, TestStructCarConstruct) {
    /*
     * Constructor test
     */
    //TODO
}