#ifndef CAR_EXAMPLE_CREATOR_H
#define CAR_EXAMPLE_CREATOR_H

#include <vector>
#include "Transform.h"

class Creator {
protected:
    std::vector<std::string> mTextures = {};

    virtual sCar* FactoryMethod() const { return nullptr; };

public:
    ~Creator() {
        mTextures = {};
    }

    sCar* GetObject() const {
        sCar *car = FactoryMethod();
        if (mTextures.size()) {
            std::srand(std::time(nullptr));
            auto n = std::rand()/((RAND_MAX + 1u)/(mTextures.size() - 1));
            car->LoadTexture(mTextures[n]);
            //todo load random textures
            //todo set random position
        }
        return car;
    };


    void SetTextures(const std::vector<std::string> textures) {
        mTextures = textures;
    }

    void SetTransform() {
        //todo set random position
    }

    sTransform GetRandomPosition() {
        std::srand(std::time(nullptr));
        sTransform *transform;
        //TODO
    }

};

class GasEngineCreator : public Creator {
private:
    sCar* FactoryMethod() const {
        return new sGasEngine();
    }
};

class ElectroCarCreator : public Creator {
private:
    sCar* FactoryMethod() const {
        return new sElectroCar();
    }
};

class HybridCarCreator : public Creator {
private:
    sCar* FactoryMethod() const {
        return new sHybridCar();
    }
};

#endif //CAR_EXAMPLE_CREATOR_H
