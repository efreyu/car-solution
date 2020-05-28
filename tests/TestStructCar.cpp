/* Created by efreyu on 22.05.2020. */
#include <gtest/gtest.h>
#include "../src/Classes/sCars.h"

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
    ASSERT_TRUE(car1.GetFuel() == 0);
    car1.Refill(fuel);
    ASSERT_TRUE(car1.GetFuel() == fuel);
    car1.Update();
    ASSERT_TRUE(car1.GetFuel() == fuel - 1);
    car1.SetSpeed(speed);
    ASSERT_TRUE(car1.GetSpeed() == speed);
}

TEST(TestStructCar, TestStructElectroCar) {
    /*
     * Electro Car, fuel and speed test
     */
    sElectroCar car2;
    ASSERT_TRUE(car2.GetFuel() == 0);
    car2.Refill(fuel);
    ASSERT_TRUE(car2.GetFuel() == fuel);
    car2.Update();
    ASSERT_TRUE(car2.GetFuel() == fuel - 1);
    car2.SetSpeed(speed - 2);
    ASSERT_TRUE(car2.GetSpeed() == speed - 2);
}

TEST(TestStructCar, TestStructHybridCar) {
    /*
     * Hybrid Car, fuel and speed test
     */
    sHybridCar car3;
    ASSERT_TRUE(car3.GetFuel() == 0);
    car3.Refill(fuel);
    ASSERT_TRUE(car3.GetFuel() == fuel / 2 + fuel / 2);
    car3.Update();
    ASSERT_TRUE(car3.GetFuel() == fuel / 2 + fuel / 2 - 1);
    car3.SetSpeed(speed - 2);
    ASSERT_TRUE(car3.GetSpeed() == speed - 2);
}

TEST(TestStructCar, TestStructCarConstruct) {
    /*
     * Constructor test, set and get speed test
     */
    sGasEngine *gasCar = new sGasEngine();
    sElectroCar *electroCar = new sElectroCar();
    sHybridCar *hybridCar = new sHybridCar();

    ASSERT_TRUE(gasCar->GetSpeed() == minSpeed);
    ASSERT_TRUE(electroCar->GetSpeed() == minSpeed);
    ASSERT_TRUE(hybridCar->GetSpeed() == minSpeed);

    gasCar->SetSpeed(2);
    gasCar->Refill(fuel);
    ASSERT_TRUE(gasCar->GetSpeed() == 2);
    ASSERT_TRUE(electroCar->GetSpeed() == minSpeed);
    ASSERT_TRUE(hybridCar->GetSpeed() == minSpeed);

    electroCar->SetSpeed(3);
    electroCar->Refill(5);
    ASSERT_TRUE(gasCar->GetSpeed() == 2);
    ASSERT_TRUE(electroCar->GetSpeed() == 3);
    ASSERT_TRUE(hybridCar->GetSpeed() == minSpeed);

    hybridCar->SetSpeed(4);
    hybridCar->Refill(fuel);
    ASSERT_TRUE(gasCar->GetSpeed() == 2);
    ASSERT_TRUE(electroCar->GetSpeed() == 3);
    ASSERT_TRUE(hybridCar->GetSpeed() == 4);
}

TEST(TestStructCar, TestStructCarMove) {
    /*
     * Test move method and fuel burn with direction and transform
     */
    sTransform *transform = new sTransform(50, 50, 100, 100);
    sHybridCar *hybridCar = new sHybridCar();
    hybridCar->SetSpeed(speed);
    hybridCar->transform = *transform;
    hybridCar->transform.direction = eDirection::DOWN;
    hybridCar->Update();
    hybridCar->transform.direction = eDirection::RIGHT;
    hybridCar->Update();
    ASSERT_TRUE(hybridCar->transform.y == transform->y - minSpeed);
    ASSERT_TRUE(hybridCar->transform.x == transform->x + minSpeed);

    sGasEngine *gasEngineCar = new sGasEngine();
    gasEngineCar->SetSpeed(speed);
    gasEngineCar->transform = *transform;
    gasEngineCar->transform.direction = eDirection::UP;
    gasEngineCar->Update();
    gasEngineCar->transform.direction = eDirection::LEFT;
    gasEngineCar->Update();
    ASSERT_TRUE(gasEngineCar->transform.y == transform->y + minSpeed);
    ASSERT_TRUE(gasEngineCar->transform.x == transform->x - minSpeed);
    //TODO test GetFuel and FuelBurn
//    EXPECT_EQ(hybridCar->GetFuel(), -1);
}